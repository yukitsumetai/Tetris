#ifndef FIGURE_H
#define FIGURE_H
#include <QColor>
#include <QPainter>
#include <qDebug>


class figure
{
    QColor element[3];
   uint m_i, m_j;
   static const uint m_W=25;

public:
    figure();
    uint getI() const
    {
        return m_i;
    }

    uint getJ() const
    {
        return m_j;
    }

    uint getJ3() const
    {
        return m_j+2;
    }

    QColor getCol(int i) const
    {
        return element[i];
    }

    QColor* getColors()
    {
        return element;
    }

    void setI(uint i)
    {
        m_i = i;
    }
    void setJ(uint j)
    {
      m_j = j;
    }

    void setColor(QColor c[3])
    {
        qDebug()<<c[0];
      element[0]=c[0];
      element[1]=c[1];
      element[2]=c[2];
    }
     void rotateColors(bool up);
void MakeRandomColors();
    void paintFigure(QPainter& painter);

};

#endif // FIGURE_H
