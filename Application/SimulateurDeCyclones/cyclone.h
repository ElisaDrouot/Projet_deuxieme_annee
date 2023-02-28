#ifndef CYCLONE_H
#define CYCLONE_H

#include "qobject.h"
#include <QString>
#include <QPoint>

#include "Position.hpp"

class Cyclone
{
public:
    Cyclone();
    void setPosX(int x);
    void setPosY(int y);
    void setTaille(int taille);
    void setNom(QString nom);

    void nextPosition();

    int getPosX();
    int getPosY();
    int getAnciennePosX();
    int getAnciennePosY();
    int getTaille();
    int getPosition();
    void setPosition(int position);

    bool IsDead();
    QString getNom();
    QList<int> listePosition;


private:
    int posX;//en pixel sur la map
    int posY;//en pixel sur la map
    int taille;
    bool dead;
    Position p;
    int positionActuelle;
    int positionAncienne;

    QString nom;

};

#endif // CYCLONE_H
