#include "map.h"
#include <QPainter>

Map::Map(QWidget *parent)
{
    pixCyclone.load(":/images/ressources/cyclone.png");

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}


QSize Map::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize Map::sizeHint() const
{
    return QSize(400, 200);
}

void Map::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    painter.drawPixmap(100, 100, pixCyclone);

    QRect rect(10, 20, 80, 60);
    painter.drawRect(rect);


    //contours
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

