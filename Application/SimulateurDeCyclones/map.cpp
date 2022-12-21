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
    int taille;
    //painter.drawPixmap(100, 100, pixCyclone);

    /*QRect rect(10, 20, 80, 60);
    painter.drawRect(rect);*/

    for(int i=0;i<listeCyclone.size();i++){
        taille=listeCyclone.at(i)->getTaille();
        painter.drawPixmap(listeCyclone.at(i)->getPosX(),listeCyclone.at(i)->getPosY(),taille,taille,pixCyclone);
    }


    //contours
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 1, width() - 1, height() - 1));
}

Cyclone* Map::getCyclone(int indice){return listeCyclone.at(indice);}
void Map::ajoutCyclone(){listeCyclone.append(new Cyclone);}
void Map::supprimerCyclone(int indice){listeCyclone.removeAt(indice);}

