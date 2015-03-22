#ifndef CONSTANTE
#define CONSTANTE


#include "carte.h"

#include <sstream>




void chargerMap(std::string level, int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], bool tileBloquant[NB_TILE]);
bool trouveA_B(int posSouris_X, int posSouris_Y, int &case_X, int &case_Y);
bool dijkstra(int numDepartX, int numDepartY, int numATrouverX, int numATrouverY, int mapNum[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], int tabOuAller[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2], int &nbCase);
void trouveNewCase(int noeudPetitI, int noeudPetitJ, int noeudPetitIBase, int noeudPetitJBase, int &nbValeur2, int mapNum[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP][2], int tabPredes[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], int tabATeste[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2]);
bool testMap(int val);



#endif 

