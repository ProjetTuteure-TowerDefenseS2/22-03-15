#include "Tour.h"

using namespace sf;
using namespace std;

	Tour::Tour()
	{
		float posX;
		float posY;

		m_afficher = false;


        m_texture.loadFromFile("./img/tour.png");
		tour1.setTexture(m_texture);
		tour1.setPosition(0,0);
	}

	void Tour::initialiserTour(string nomTexture, string nomTexture_2, string nomTexture_3, string nomTexture_4, string nomTexture_5)
	{
	    m_Tir.creerTir(nomTexture, nomTexture_2, nomTexture_3, nomTexture_4, nomTexture_5);
	}

	void Tour::setPosition(float x, float y)
	{
		posX=x;
		posY=y;

		tour1.setPosition(posX,posY);
	}

	void Tour::draw(RenderWindow & window)
	{
		window.draw(tour1);
	}

	void Tour::setFillColor()
	{
		//tour1.setFillColor(sf::Color(250, 250, 250));
	}

	void Tour::setFillColorBlack()
	{
		//tour1.setFillColor(sf::Color(0, 0, 0));
	}

	float Tour::getGlobalBoundsW()
	{
		return tour1.getGlobalBounds().width+posX;
	}

	float Tour::getGlobalBoundsH()
	{
		return tour1.getGlobalBounds().height+posY;
	}
