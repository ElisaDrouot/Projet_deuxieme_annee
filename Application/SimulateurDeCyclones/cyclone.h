#ifndef CYCLONE_H
#define CYCLONE_H

#include "qobject.h"
#include <QString>
#include <QPoint>

class Cyclone
{
public:
    Cyclone();
    void setPosX(int x);
    void setPosY(int y);
    void setTaille(int taille);
    void setNom(QString nom);

    int getPosX();
    int getPosY();
    int getTaille();
    QString getNom();

private:
    int posX;
    int posY;
    int taille;
    QString nom;

};

#endif // CYCLONE_H
