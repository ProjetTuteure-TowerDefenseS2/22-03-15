#include "constante.h"

using namespace sf;
using namespace std;

void chargerMap(string level, int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], bool tileBloquant[NB_TILE])
{
    ifstream fichier(level.c_str(), ios::in);

    if(fichier)  // si l'ouverture a fonctionné
    {
        for(int i = 0 ; i < NB_TILE ; i++)
        {
            fichier >> tileBloquant[i];
        }
        for(int i = 0 ; i < MAX_HAUTEUR_MAP ; i++)
        {
            for(int j = 0 ; j < MAX_LARGEUR_MAP ; j++)
            {
                fichier >> map[j][i];
            }
        }

        fichier.close();
    }
    else  // sinon
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}



bool trouveA_B(int posSouris_X, int posSouris_Y, int &case_X, int &case_Y)
{
    bool trouveCoordo = false;
    if(posSouris_Y < MAX_HAUTEUR_MAP * HAUTEUR_TILE)
    {
        case_X = 0;
        while(case_X <= MAX_LARGEUR_MAP && !trouveCoordo)
        {
            if((case_X * LARGEUR_TILE) > posSouris_X)
            {
                case_X--;
                case_Y = 0;
                while(case_Y <= MAX_HAUTEUR_MAP && !trouveCoordo)
                {
                    if((case_Y * HAUTEUR_TILE) > posSouris_Y)
                    {
                        case_Y--;
                        trouveCoordo = true;
                    }
                    case_Y++;
                }
            }

            case_X++;
        }
        if(case_X > 0){case_X--;}
        if(case_Y > 0){case_Y--;}
    }
    return trouveCoordo;
}


bool dijkstra(int numDepartX, int numDepartY, int numATrouverX, int numATrouverY, int mapNum[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], int tabOuAller[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2], int &nbCase)
{
    int numTemp = 0;

    int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP][2];

    for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
    {
        for(int i = 0; i < MAX_LARGEUR_MAP; i++)
        {
            map[i][j][0] = numTemp;
            numTemp++;
            map[i][j][1] = 0;
        }
    }


    int tabPredes[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
    int tabATeste[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2];

    int nbValeur = 1, nbValeur2 = 0;

    int noeudPetitI = numDepartX;
    int noeudPetitJ = numDepartY;

    int varLargeur = 0, varHauteur = 0, testNbValeurFaite = 0;

    tabATeste[map[noeudPetitI][noeudPetitJ][0]][0] = 0;
    tabPredes[noeudPetitI][noeudPetitJ] = -1;
    map[noeudPetitI][noeudPetitJ][1] = 1;


    bool nonTrouve = true, trouverTester = false;

    int valeurAntiBug = 0;

    while(nonTrouve && valeurAntiBug <= HAUTEUR_TILE * LARGEUR_TILE)
    {
        testNbValeurFaite = 0;
        while(testNbValeurFaite < nbValeur && nonTrouve)
        {
            varLargeur = 0;
            while(varLargeur < MAX_LARGEUR_MAP && !trouverTester)
            {
                varHauteur = 0;
                while(varHauteur < MAX_HAUTEUR_MAP && !trouverTester)
                {
                    if(map[varLargeur][varHauteur][0] == tabATeste[testNbValeurFaite][0])
                    {
                        noeudPetitI = varLargeur;
                        noeudPetitJ = varHauteur;
                        trouverTester = true;
                    }
                    varHauteur++;
                }
                varLargeur++;
            }
            trouverTester = false;

            if(map[numATrouverX][numATrouverY][0] == map[noeudPetitI][noeudPetitJ][0])
            {
                nonTrouve = false;
            }
            else
            {
                if(noeudPetitI + 1 < MAX_LARGEUR_MAP)
                {
                    trouveNewCase(noeudPetitI + 1, noeudPetitJ, noeudPetitI, noeudPetitJ, nbValeur2, mapNum, map, tabPredes, tabATeste);
                }
                if(noeudPetitI - 1 >= 0)
                {
                    trouveNewCase(noeudPetitI - 1, noeudPetitJ, noeudPetitI, noeudPetitJ, nbValeur2, mapNum, map, tabPredes, tabATeste);
                }
                if(noeudPetitJ + 1 < MAX_HAUTEUR_MAP)
                {
                    trouveNewCase(noeudPetitI, noeudPetitJ + 1, noeudPetitI, noeudPetitJ, nbValeur2, mapNum, map, tabPredes, tabATeste);
                }
                if(noeudPetitJ - 1 >= 0)
                {
                    trouveNewCase(noeudPetitI, noeudPetitJ - 1, noeudPetitI, noeudPetitJ, nbValeur2, mapNum, map, tabPredes, tabATeste);
                }

            }

            testNbValeurFaite++;
        }
        if(nbValeur2 > 0 && nonTrouve)
        {
            for(int i = 0 ; i < nbValeur2 ; i++)
            {
                tabATeste[i][0] = tabATeste[i][1];
            }
            nbValeur = nbValeur2;
            nbValeur2 = 0;
        }
        valeurAntiBug++;


    }


    if(valeurAntiBug >= HAUTEUR_TILE * LARGEUR_TILE)
    {
        cout << endl << "ERREUR DIJKSTRA !!!!" << endl << endl;
        return false;
    }
    else
    {
        cout << endl;
        nbCase = 0;
        valeurAntiBug--;
        while(tabPredes[numATrouverX][numATrouverY] != -1 && valeurAntiBug > -1)
        {
            cout << "Num Case : " << valeurAntiBug << " case actu : " << map[numATrouverX][numATrouverY][0] << " predescesseur : " << tabPredes[numATrouverX][numATrouverY] << endl;
            mapNum[numATrouverX][numATrouverY] = 3; ///On met l'image "OK" pour le chemin
            valeurAntiBug--;
            varLargeur = 0;
            while(varLargeur < MAX_LARGEUR_MAP && !trouverTester)
            {
                varHauteur = 0;
                while(varHauteur < MAX_HAUTEUR_MAP && !trouverTester)
                {
                    if(map[varLargeur][varHauteur][0] == tabPredes[numATrouverX][numATrouverY])
                    {
                        tabOuAller[nbCase][0] = numATrouverX;
                        tabOuAller[nbCase][1] = numATrouverY;
                        nbCase++;
                        numATrouverX = varLargeur;
                        numATrouverY = varHauteur;
                        trouverTester = true;
                    }
                    varHauteur++;
                }
                varLargeur++;
            }

            trouverTester = false;
        }

        nbCase--;

        if(numDepartX != numATrouverX || numDepartY != numATrouverY)
        {
            cout << endl << "ERREUR DIJKSTRA !!!! numX" << numDepartX << " numTrouX: " << numATrouverX << endl << endl;
            return false;
        }
        cout << "case actu : " << map[numATrouverX][numATrouverY][0] << endl;

        cout << endl << "OK DIJKSTRA !!!! numX" << numDepartX << " numTrouX: " << numATrouverX << endl << endl;
        return true;
    }

}




void trouveNewCase(int noeudPetitI, int noeudPetitJ, int noeudPetitIBase, int noeudPetitJBase, int &nbValeur2, int mapNum[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP][2], int tabPredes[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], int tabATeste[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2])
{
    if(map[noeudPetitI][noeudPetitJ][1] == 0 && testMap(mapNum[noeudPetitI][noeudPetitJ]))
    {
            map[noeudPetitI][noeudPetitJ][1] = 1;
            tabPredes[noeudPetitI][noeudPetitJ] = map[noeudPetitIBase][noeudPetitJBase][0];
            tabATeste[nbValeur2][1] = map[noeudPetitI][noeudPetitJ][0];
            nbValeur2++;
    }
}

bool testMap(int val)
{
    bool different = true;
    if(val == 2 || val == 4)
    {
        different = false;
    }
    return different;
}
