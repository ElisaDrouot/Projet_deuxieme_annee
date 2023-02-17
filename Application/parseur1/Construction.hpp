#ifndef CONSTUCTION
#define CONSTUCTION
#include "Matrice.hpp"

using namespace std;

class Construction{

    public:
        Matrice p;

        int nb;
        Construction();
        int getTaille();
        int position(string latitudestr, string longitudestr);
};
#endif