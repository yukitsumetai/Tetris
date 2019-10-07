#ifndef GLASS_H
#define GLASS_H

#include <QWidget>
#include "figure.h"

class glass : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(uint rows READ rows WRITE setRows)
    Q_PROPERTY(uint cols READ cols WRITE cols)

    static const uint W=25;
    uint timerInterval;
    int  timerId;
    uint m_rows, m_cols;
    bool gameOn;
    uint score;

    figure *cur;
    figure *next;

    #define emptyCell QColor(150,150,150)
    QVector<QVector<QColor>>glassArray;

public:
void paintEvent(QPaintEvent*event);
explicit glass(QWidget *parent = nullptr);
~glass();
void clearGlass();
void keyPressEvent(QKeyEvent*event);
void AcceptColors(int i, int j);
void CheckGlass();
void removeEmpty(bool flag);
void timerEvent(QTimerEvent*event);
void timer();

uint rows() const
{
    return m_rows;
}

uint cols() const
{
    return m_cols;
}

QColor color(uint i, uint j) const
{
    //qDebug()<<"glass";
    return glassArray[j][i];
}

signals:
void signalGlassInit();
void signalStopTimer();
void signalStartTimer();
void nextFigure(figure nt);
void setScore(int);

public slots:
void slotGlassInit();
void slotNewGame();

void setRows(uint rows)
{
    m_rows = rows;
}
void cols(uint cols)
{
    m_cols = cols;
}
void colors(int i, int j, QColor col)
{
    glassArray[i][j]=col;
}


};

#endif // GLASS_H
