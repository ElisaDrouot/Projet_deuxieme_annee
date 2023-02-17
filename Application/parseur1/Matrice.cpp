#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Matrice.hpp" 

Matrice::Matrice(){
    int i;
    for(i=0; i<265;i++){
        nombresomme[i]=0;
    }
}

bool Matrice::existeElement(int i, int j){
    bool res = false;
    
    int debut = nombresomme[i-1];
    int fin = nombresomme[i];
    int k;

    for(k=debut;k<fin;k++){
        if(grille[k][1]==j){
            res = true;
        }
    }
    return res;
}

void Matrice::incrementer(int i,int j){
    bool existe = existeElement(i,j);

    if(existe == false){
        creer(i,j);
    }
    if(existe == true){
        int debut = nombresomme[i-1];
        int fin = nombresomme[i];
        int k;
        for(k=debut;k<fin;k++){
            if(grille[k][1]==j){
            grille[k][2] += 1;
            }
        }
    }
}

void Matrice::creer(int i,int j){
    int n = nombresomme[i];
    
    std::vector<std::vector<int> > grille1;
    std::vector<std::vector<int> > grille2;

    grille1.insert(grille1.begin(), grille.begin(), grille.begin() + n);

    grille2.insert(grille2.begin(), grille.begin() + n , grille.end());
    
    std::vector<std::vector<int> > grillea;
    grillea.push_back(std::vector<int>(3));   //On ajoute une ligne de 3 cases à notre grille
    grillea[0][0] = i;
    grillea[0][1] = j;
    grillea[0][2] = 1;

    std::vector<std::vector<int> > grillenew;
    grillenew.insert(grillenew.begin(), grille1.begin(), grille1.end());
    grillenew.insert(grillenew.end(), grillea.begin(), grillea.end());
    grillenew.insert(grillenew.end(), grille2.begin(), grille2.end());
    this->grille = grillenew;

    //nombre[i-1] += 1;

    int k;

    for(k=i;k<265;k++){
        nombresomme[k] += 1;
    }
}

void Matrice::afficherGrille(){
    int n = grille.size();
    int i;

    std::cout<<"Grille :"<<"\n";

    for(i=0;i<n;i++){
        std::cout<<grille[i][0]<<" "<<grille[i][1]<<" "<<grille[i][2]<<"\n";
    }
}

void Matrice::operation(){
    int n = grille.size();
    int i,k,debut,fin,somme,temp,h;
    std::vector<std::vector<float> > transitiona;
    transitiona.push_back(std::vector<float>(3));   //On ajoute une ligne de 2 cases à notre grille

    h = 0;
    while(h<n){
        i = grille[h][0];
        debut = nombresomme[i-1];
        fin = nombresomme[i];
        somme = 0;

        for(k=debut;k<fin;k++){
            temp = grille[k][2];
            grille[k][2] += somme;
            somme += temp;
        }
        for(k=debut;k<fin;k++){

            transitiona[0][0] = (float)grille[k][0];      
            transitiona[0][1] = (float)grille[k][1];
            transitiona[0][2] = (float)grille[k][2]/(float)somme;
            
            transition.insert(transition.end(), transitiona.begin(), transitiona.end());

        }
        h+= fin-debut;
    }
}

void Matrice::afficherArray(){
    int n = transition.size();
    int i;

    std::cout<<"Matrice de transition :"<<"\n";
    for(i=0;i<n;i++){
        std::cout<<transition[i][0]<<" "<<transition[i][1]<<" "<<transition[i][2]<<"\n";
    }
}

int Matrice::getTaille(){return grille.size();}