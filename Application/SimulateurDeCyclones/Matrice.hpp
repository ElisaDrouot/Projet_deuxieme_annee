#ifndef MATRICE
#define MATRICE 
#include <vector>

class Matrice {
  
 public:
   std::vector<std::vector<int> > grille;
   std::vector<std::vector<float> > transition;
   int nombresomme[265];
  Matrice();
  bool existeElement(int i, int j);
  void incrementer(int i,int j);
  void creer(int i,int j);
  void afficherGrille();
  void operation();
  void afficherArray();
  int getTaille();


};

#endif 