#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include "Position.hpp"

using namespace std;

Position::Position()
    :c(Construction::getInstance())
    {}

int Position::positionSuivante(int positionActuelle, int positionPrecedente){
    int v = rand() % 101; 
    float r = (float)v/100.0;

    bool trouve = false;
    int res;

    int debut = c->p.nombresomme[positionActuelle-1];
    int fin = c->p.nombresomme[positionActuelle];
    int k=debut;
    if(r <= c->p.transition[k][2]){
        trouve = true;
        res = c->p.transition[k][1];
    }

    int compteur=0;
    while(trouve == false && compteur<266){
        for(k=debut+1;k<fin-1;k++){
            if((r >= c->p.transition[k-1][2])&&(r <= c->p.transition[k][2])){
                res = c->p.transition[k][1];
                trouve = true;
            }
        }
        compteur++;
    }

    if(compteur>=266){
        res=265;
    }

    compteur=0;
    while(res == positionPrecedente && compteur<10){
        res = positionSuivante(positionActuelle,positionPrecedente);
        compteur++;
    }
    if(compteur>=10){
        res=265;
    }
    return res;

}

float Position::getLatitude(int position){
    return 630-((position-1)%22)*30;
}

float Position::getLongitude(int position){
    return 330-((position-1)/22)*30;
}
