#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include "Construction.hpp"

using namespace std;

Construction::Construction(){

    ifstream filename("atlantic.csv"); // open the file
    string line, field,idactuel,idprecedent,lata,longa,latsuiv,longsuiv;
    string ligne[3];
    int i, posa, posuiv;
    nb = 0;
    if (!filename) // error if the file doesn't exist
  {
    cerr << "Can't open file " << endl;
  }
    getline(filename,line);   // get next line in file
    getline(filename,line);
    stringstream ss(line); 
    i = 0;
    while (getline(ss,field,','))  // break line into comma delimitted fields
    {
        ligne[i] = field;
        i++;
    } 
    idactuel = ligne[0];
    lata = ligne[1];
    longa = ligne[2];
    posuiv = position(lata,longa);
    //p.incrementer(posa,posuiv);
    
    while ( getline(filename,line,'\n') )    // get next line in file
    {
        nb += 1;
        std::cout<<nb<<std::endl;
        idprecedent = idactuel;
        stringstream ss(line);
        i = 0;

        while (getline(ss,field,','))  // break line into comma delimitted fields
        {
            ligne[i] = field;
            i++;
        }

        idactuel = ligne[0];

        lata = ligne[1];
        longa = ligne[2];

        if((stoi(lata) < 60)&&(stoi(longa) < 110)){
            posa = posuiv;
            posuiv = position(lata,longa);

            if ( idactuel != idprecedent){
                //P[posa-1][264] +=1 
                if(posa != posuiv ){p.incrementer(posa,265);}

                posa = posuiv;

                idprecedent = idactuel;
                getline(filename,line);
                stringstream ss(line); 
                i = 0;
                while (getline(ss,field,','))  // break line into comma delimitted fields
                {
                    ligne[i] = field;
                    i++;
                }
                idactuel = ligne[0];
                lata = ligne[1];
                longa = ligne[2];
                posuiv = position(lata,longa);

            }
            if ( idactuel == idprecedent ){
                //cout<<posa<<" "<<posuiv<<endl;
                if(posa != posuiv) {p.incrementer(posa,posuiv);}
            }
        }
        else{p.incrementer(posa,265);}

    }

    p.afficherGrille();
    p.operation();
    p.afficherArray();

}

int Construction::position(string latitudestr, string longitudestr){
    int latitude = stoi(latitudestr);
    int longitude = stoi(longitudestr);

    int partieEntiereLatitude = (int)floor((double)(latitude/5));
    int partieEntiereLongitude = (int)floor((double)(longitude/5));
    int position = 110*partieEntiereLatitude/5 + partieEntiereLongitude +1;

    return position;
}

int Construction::getTaille(){return p.getTaille();}

