#include "figure.h"
#include "QPainter"
#include "QDebug"



figure::figure()
{
   uint m_i=0, m_j=0;
}

void figure::rotateColors(bool up){
QColor tmp=element[0];
    if(up){

        element[0]=element[1];
        element[1]=element[2];
        element[2]=tmp;
}
else {
        element[0]=element[2];
        element[2]=element[1];
        element[1]=tmp;
    }
}

void figure::MakeRandomColors(){

    for(int i=0;i<3;i++){
       int r=qrand() % 4;
      switch (r){
           case 0: element[i]=Qt::blue; break;
           case 1: element[i]=Qt::red; break;
           case 2: element[i]=Qt::yellow; break;
           case 3: element[i]=Qt::green; break;
     }
    }
    qDebug()<<1;
 return;
};

void figure::paintFigure(QPainter& p){

       for (int i=0; i<3; i++){
           QBrush brush(getCol(i));
           p.setBrush(brush);
          uint j=getJ()*m_W+m_W*i;
           p.drawRect(getI()*m_W,j,m_W-2,m_W-2);

    }
};
