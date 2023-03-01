#include "cyclone.h"

Cyclone::Cyclone()
{
    nom="Cyclone";
    taille=30;
    dead=false;
    Position p;
    positionActuelle=85;
    positionAncienne=0;
    posX=p.getLatitude(positionActuelle);
    posY=p.getLongitude(positionActuelle);
    listePosition.push_back(positionActuelle);
}

void Cyclone::nextPosition(){
    if(!dead){
        int aux=positionActuelle;
        positionActuelle=p.positionSuivante(positionActuelle,positionAncienne);
        positionAncienne=aux;

        posX=p.getLatitude(positionActuelle);
        posY=p.getLongitude(positionActuelle);
        if(positionActuelle==265){
            dead=true;
        }
        else{
            listePosition.push_back(positionActuelle);
        }
    }

}

int Cyclone::getPosX(){return posX;}
int Cyclone::getPosY(){return posY;}
int Cyclone::getTaille(){return taille;}
QString Cyclone::getNom(){return nom;}
int Cyclone::getPosition(){return positionActuelle;}
bool Cyclone::IsDead(){return dead;}

void Cyclone::setPosX(int x){
    this->posX=x;
}
void Cyclone::setPosY(int y){
    this->posY=y;
}
void Cyclone::setTaille(int taille){this->taille=taille;}
void Cyclone::setPosition(int position){
    this->positionActuelle=position;
    posX=p.getLatitude(positionActuelle);
    posY=p.getLongitude(positionActuelle);
    listePosition.clear();
    listePosition.push_back(positionActuelle);
}
void Cyclone::setNom(QString nom){this->nom=nom;}
