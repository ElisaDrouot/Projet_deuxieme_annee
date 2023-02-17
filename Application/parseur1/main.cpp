// Fichier main.cpp

#include <iostream> 
#include <string> 
#include <time.h>
#include <stdlib.h>
#include "Matrice.hpp"
#include "Position.hpp"
#include "Construction.hpp"

int main() {
  srand(time(NULL));
  Position pos;
  int posuivant = pos.positionSuivante(42,41);
  float latitude = pos.getLatitude(24);
  float longitude = pos.getLongitude(24);
  return 0;
}