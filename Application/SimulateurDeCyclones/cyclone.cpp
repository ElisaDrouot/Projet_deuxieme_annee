#include "cyclone.h"

Cyclone::Cyclone()
{
    nom="Cyclone";
    taille=100;
    posX=100;
    posY=100;
}

int Cyclone::getPosX(){return posX;}
int Cyclone::getPosY(){return posY;}
int Cyclone::getTaille(){return taille;}
QString Cyclone::getNom(){return nom;}

void Cyclone::setPosX(int x){this->posX=x;}
void Cyclone::setPosY(int y){this->posY=y;}
void Cyclone::setTaille(int taille){this->taille=taille;}
void Cyclone::setNom(QString nom){this->nom=nom;}
