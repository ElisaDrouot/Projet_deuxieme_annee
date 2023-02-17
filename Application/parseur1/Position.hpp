#ifndef POSITION
#define POSITION
#include "Construction.hpp"

using namespace std;

class Position{
    Construction c;

    public:
        Position();
        float getLatitude(int position);
        float getLongitude(int position);
        int positionSuivante(int positionActuelle,int positionPrecedente);
};
#endif