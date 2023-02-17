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

Position::Position(){
    Construction c;
}

int Position::positionSuivante(int positionActuelle, int positionPrecedente){
    int v = rand() % 101; 
    float r = (float)v/100.0;

    bool trouve = false;
    int res;

    int debut = c.p.nombresomme[positionActuelle-1];
    int fin = c.p.nombresomme[positionActuelle];
    int k=debut;
    if(r <= c.p.transition[k][2]){
        trouve = true;
        res = c.p.transition[k][1];
    }
    while(trouve == false){
        for(k=debut+1;k<fin-1;k++){
            if((r >= c.p.transition[k-1][2])&&(r <= c.p.transition[k][2])){
                res = c.p.transition[k][1];
                trouve = true;
            }
        }
    }
    while(res == positionPrecedente){
        res = positionSuivante(positionActuelle,positionPrecedente);
    }
    return res;

}

float Position::getLatitude(int position){
    int entiere = (int)floor((double)(position/23));
    float latitude = 5*entiere +2.5;
    return latitude;
}

float Position::getLongitude(int position){
    int entiere = (int)floor((double)(position/22));
    int temp = position - entiere*22;
    float Longitude = 5*temp - 2.5;
    int reste = position % 22;
    if(reste == 0){Longitude = 107.5;}
    return Longitude;
}