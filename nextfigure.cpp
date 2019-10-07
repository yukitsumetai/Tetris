#include "nextfigure.h"
#include <QPoint>;

nextFigure::nextFigure(QWidget *parent) : QWidget(parent)
{
next=new figure;
}

void nextFigure::paintEvent(QPaintEvent*event)
{
QPainter p(this);
QPoint* n = new QPoint(30,0);
p.translate(*n);
next->paintFigure(p);

}

void nextFigure::showNext(figure nt){
   next=&nt;
   repaint();
}
