#ifndef CONSTUCTION
#define CONSTUCTION
#include "Matrice.hpp"
#include <QString>
#include <string>
using namespace std;

class Construction{

    public:
        Matrice p;

        static Construction* getInstance(){
           if(instance==nullptr){
               instance=new Construction{};
           }
           return instance;
        }

        int nb;

        int getTaille();
        int position(string latitudestr, string longitudestr);

    private:
        static Construction *instance;
        Construction();
};
#endif
