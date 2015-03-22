#ifndef ENNEMIS_H_INCLUDED
#define ENNEMIS_H_INCLUDED

#include "string.h"
#include <SFML/Graphics.hpp>
#include <cmath>

#include <iostream>



const int MAX_ENNEMIS = 50;
const int TAILLE_MAX_MAP = 300;

const int LARGEUR_TILE = 32;
const int HAUTEUR_TILE = 32;

const int TAILLE_BLOC = 32;

const int MAX_LARGEUR_MAP = 20;
const int MAX_HAUTEUR_MAP = 10;

const int NB_TILE = 5;
///const float VitesseMonstre = 200;

bool trouveA_B(int posSouris_X, int posSouris_Y, int &a, int &b);

class Ennemi{
public :
    Ennemi(std::string nomEnnemi, sf::Sprite newSprite, float valVitesse = 150);
    Ennemi();
    ~Ennemi();


    bool verifColisionDeplacementEnnemi(bool tileBloquant[NB_TILE], int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP]);
    bool deplacement(sf::Clock & clock, bool tileBloquant[NB_TILE], int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP], int etape);
    void choixZone(sf::Texture texture, sf::RenderWindow & window, sf::Clock & clock, int posX = 0, int posY = 0);

    int supprimerPV(int degats); ///retourne les pv du monstre aprés le coup
    void afficheEnnemi(sf::RenderWindow & window) const;
    void setPos(int posX, int posY);

    void setVivant(bool Vivant){m_vivant = Vivant;}

    bool getMoving(){return m_moving;}
    std::string getNomEn(){ return _nomEnnemi; }
    float getVitesse(){ return _vitesseDeplaEnnemi; }
    const sf::Vector2f getPosition(){return _sprite.getPosition();}
    int getPVRestant(){return _ptsVieActuel;}
    bool getVivant(){return m_vivant;}
    const sf::Vector2f getVelocity(){return m_velocity;}
    const sf::Vector2f getTarget(){return m_target;}

private :
    std::string _nomEnnemi;
    int _ptsVieMax = 10;
    int _ptsVieActuel;
    int _armure = 0;
    sf::Sprite _sprite;
    float _vitesseDeplaEnnemi;

    bool m_moving;
    sf::Vector2f m_target;
    sf::Vector2f m_velocity;
    bool m_vivant = true;

};



#endif // ENNEMIS_H_INCLUDED




