#include "glass.h"
#include "QDebug"
#include "QPainter"
#include "QKeyEvent"
#include "QTimer"
#include <QMessageBox>

glass::glass(QWidget *parent) : QWidget(parent)
{
  gameOn=false;
  setFocusPolicy(Qt::StrongFocus);
  m_rows=0, m_cols=0;
  score=0;
  connect(this, SIGNAL(signalGlassInit()), this, SLOT(slotGlassInit()), Qt::QueuedConnection);


  signalGlassInit();

  cur=new figure();
  next=new figure();


}

glass::~glass()
{
    delete cur;
    delete next;
    clearGlass();
}
void glass::slotGlassInit(){

    glassArray.resize(m_rows);
    for(int i=0; i<m_rows; i++ ) glassArray[i].resize(m_cols);
    QSize s(m_cols*W, m_rows*W);
    this->setFixedSize(s);
    clearGlass();
};

void glass::clearGlass(){

  for(int i=0; i<m_rows; i++)
 glassArray[i].fill(emptyCell);
  score=0;
   emit setScore(score);
};

void glass::paintEvent(QPaintEvent*event)
{

QPainter p(this);

 for (int j=0; j<m_cols;j++){
   for (int i=0; i<m_rows;i++){
       QBrush brush(color(j,i));
       p.setBrush(brush);
       p.drawRect(j*W,i*W,W-2,W-2);
}
}

if(gameOn) //а фигурку будем рисовать только, если «идет игра»

{
cur->paintFigure(p);

}
//repaint();
}

void glass::slotNewGame(){
    gameOn=true;
    clearGlass();

    cur->setI((m_cols-0.1)/2);
    cur->setJ(0);
    cur->MakeRandomColors();
    next->MakeRandomColors();
    setFocus();
  timerId = startTimer(1000);
    emit nextFigure(*next);
}

void glass::keyPressEvent(QKeyEvent*event)
{

if(gameOn)
{


switch(event->key()){//коднажатойклавиши
case Qt::Key_Right:{
uint i=cur->getI();
uint j=cur->getJ();
if(i<m_cols-1 && (color(i+1,j+2)==emptyCell)) cur->setI(i+1); repaint();
    break;}
case Qt::Key_Left:{
    uint i=cur->getI();
    uint j=cur->getJ();
    if(i>0 &&  (color(i-1,j+2)==emptyCell)) cur->setI(i-1); repaint();
break;}
case Qt::Key_Down:
cur->rotateColors(false);//циклически ”переливаем” цвета в фигурке сверху вниз
break;
case Qt::Key_Up:
cur->rotateColors(true);//циклически ”переливаем” цвета в фигурке снизу вверх
break;
case Qt::Key_Space:
{
    uint i=cur->getI();
    uint j2=m_rows;

    for (uint j=m_rows-1; j>0; j--){
    if (color(i, j)!=emptyCell) j2=j;
    };
     cur->setJ(j2-3); repaint();

    AcceptColors(cur->getI(), cur->getJ());


     break;
}

default:
QWidget::keyPressEvent(event); //принажатиилюбыхдругихклавишвызываембазовуюобработкусобытия
}
}
else QWidget::keyPressEvent(event);
}

void glass::AcceptColors(int i, int j){
 // connect(this, SIGNAL(signalStopTimer()), timerInterval, SLOT(stop()));
//  emit signalStopTimer();
  colors(j,i,cur->getCol(0));
  colors(j+1,i,cur->getCol(1));
  colors(j+2,i,cur->getCol(2));
   //Добавляем фигурку в стакан
    //Анализируем и сбрасываем текущее содержимое стакана, вызываем например:

CheckGlass();
   cur->setColor(next->getColors());
   cur->setI((m_cols-0.1)/2);
   cur->setJ(0);
   next->MakeRandomColors();
   emit nextFigure(*next);
   repaint();
}

void glass::CheckGlass(){
    bool flag=false;
    for(int j=0; j<m_rows-2; j++){
        for(int i=0; i<m_cols; i++){
    if (color(i, j)!=emptyCell&&color(i, j)==color(i, j+1)&&color(i, j+1)==color(i, j+2)){
        flag=true;
     colors(j,i,emptyCell);
      colors(j+1,i,emptyCell);
       colors(j+2,i,emptyCell);
       score+=3;
        emit setScore(score);
    }
        }
    }

    for(int j=0; j<m_rows; j++){
        for(int i=0; i<m_cols-2; i++){
    if (color(i, j)!=emptyCell&&color(i, j)==color(i+1, j)&&color(i+1, j)==color(i+2, j)){
    flag=true;
        colors(j,i,emptyCell);
      colors(j,i+1,emptyCell);
       colors(j,i+2,emptyCell);
        score+=3;
        emit setScore(score);
    }
        }
    }
    bool flag2=false;
    removeEmpty(flag2);
    if(flag2) CheckGlass();
    if(flag) CheckGlass();

}

void glass::removeEmpty(bool flag){
    uint j2=m_rows, j3=0;
    for(int i=0; i<m_cols; i++){
        for(int j=m_rows-1; j>0; j--){
            if (color(i,j)!=emptyCell) j2=j;
     }

        for(int j=0; j<m_rows; j++){
            if (color(i,j)==emptyCell) j3=j;
     }

        if (j2<j3) { colors(j3,i,color(i,j2));
            colors(j2,i,emptyCell);
            flag=true;}
        else flag=false;
    }

}

void glass::timerEvent(QTimerEvent*event){

    uint i=cur->getI(), j=cur->getJ();
      if(color(i,j+3)==emptyCell & j+4!=m_rows) {cur->setJ(j+1);
     repaint();}
     else if (j>0) {  AcceptColors(i, cur->getJ());

               repaint();}
      else {killTimer(timerId);

          QMessageBox* msg = new QMessageBox();
          msg->setText("Game over!");

          msg->setStandardButtons(QMessageBox::Ok);

          msg->open();

          return;
         }

}



