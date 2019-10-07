#ifndef NEXTFIGURE_H
#define NEXTFIGURE_H

#include <QWidget>
#include "figure.h"

class nextFigure : public QWidget
{
    Q_OBJECT
    figure* next;

public:
    explicit nextFigure(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*event);

signals:

public slots:
    void showNext(figure nt);
};

#endif // NEXTFIGURE_H
