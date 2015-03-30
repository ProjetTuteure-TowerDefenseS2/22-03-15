
#include "constante.h"
//#include "Carte.h"

using namespace sf;
using namespace std;


int main()
{
	RenderWindow window(sf::VideoMode(1200, 704), "Tower Defense !");
	cout <<"bienvenue dans notre projet de Tower Defense !";

    const sf::Vector2f pos(279,258);

	Texture texture;
	texture.loadFromFile("./img/dragRoug2.png");
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(0,0);

	Ennemi ennemi("Dragon", sprite, 150);

	Texture textureMap;
	textureMap.loadFromFile("map.jpg", IntRect(0, 150, 1200, 704));
	Sprite spriteMap;
	spriteMap.setTexture(textureMap);

	Texture textureTour;
	textureTour.loadFromFile("./image/text.png");

	int x = 0;
	int etape =0;
	double deplacement = 0.01;



	Tour tour;
	tour.initialiserTour("./image/tirBase.png", "./image/tirBase2.png", "./image/tirBase3.png");

    Clock temps;
    temps.restart();

    bool moving = false;;
    Clock clock;
    Vector2f target, velocity;


    bool depClique = true;

    Texture textureTile;
	textureTile.loadFromFile("./maps/herbe.png");
	Sprite mySprite;
	mySprite.setTexture(textureTile);

	int map[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
	int mapRecup[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
    bool tileBloquant[NB_TILE];

	int tabOuAller[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2];
	int nbCase;

	chargerMap("./maps/map2.txt", map, tileBloquant);
	for(int i = 0 ; i < MAX_HAUTEUR_MAP ; i++)
    {
        for(int j = 0 ; j < MAX_LARGEUR_MAP ; j++)
        {
            mapRecup[j][i] = map[j][i];
        }
    }

	Sprite tile[NB_TILE];

    for(int i = 0 ; i < NB_TILE ; i++)
    {
        mySprite.setTextureRect(IntRect(LARGEUR_TILE * i, 0, LARGEUR_TILE, HAUTEUR_TILE));
        mySprite.setPosition(LARGEUR_TILE * i, 0);
        tile[i] = mySprite;
    }

    int imageActu = 0, a, b;

    int zoneArriverX = 18, zoneArriverY = 6;

    int endroitMonstreX = 0, endroitMonstreY = 0;

    bool dep = false, cliqueGauche = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
            if (event.type == sf::Event::KeyPressed)//MouseButtonReleased pour relacher
            {
                if (event.key.code == sf::Keyboard::Return)
                {
                    //if(depClique){depClique = false;x = 0;ennemi.setPos(279,258);}
                    //else{depClique = true;}
                    endroitMonstreX = 0;
                    endroitMonstreY = 0;
                    dep = true;
                }
                else if (event.key.code == sf::Keyboard::Tab  )
                {
                    chargerMap("./maps/map2.txt", map, tileBloquant);
                    for(int i = 0 ; i < MAX_HAUTEUR_MAP ; i++)
                    {
                        for(int j = 0 ; j < MAX_LARGEUR_MAP ; j++)
                        {
                            mapRecup[j][i] = map[j][i];
                        }
                    }
                }

                if (event.key.code == sf::Keyboard::Numpad1 )
                {
                    imageActu = 0;
                }
                else if (event.key.code == sf::Keyboard::Numpad2 )
                {
                    imageActu = 1;
                }
                else if (event.key.code == sf::Keyboard::Numpad3 )
                {
                    imageActu = 2;
                }

                if (event.key.code == sf::Keyboard::Escape )
                {
                    window.close();
                }
            }
            if (event.type == sf::Event::LostFocus)
            {

            }
		}


		if (ennemi.getPosition().x < tour.getGlobalBoundsW() + 70 && ennemi.getPosition().x + texture.getSize().x + 70 > tour.getGlobalBoundsW() &&
            ennemi.getPosition().y < tour.getGlobalBoundsH() + 70 && ennemi.getPosition().y + texture.getSize().y + 70 > tour.getGlobalBoundsH())
        {
            if(temps.getElapsedTime().asSeconds() > 1.5)
            {
                try{
                    tour.creationTir(textureTour, ennemi.getPosition(), 1, 3);
                    temps.restart();
                }
                catch(string msg)
                {
                    cout << msg << endl;
                }
            }
		}

        if(tour.getTirTirer())
        {
            if(tour.deplacementTir(texture, ennemi.getPosition()) && ennemi.getPVRestant() > 0)
            {
                cout << "TOUCHER !!" << endl;
                ennemi.supprimerPV(3);
                cout << "PV restant a l'ennemi : " << ennemi.getPVRestant() << endl;
            }
        }


		if (event.type == sf::Event::MouseButtonPressed)//MouseButtonReleased pour relacher
		{
			if (event.mouseButton.button == sf::Mouse::Left && !cliqueGauche)
			{
                if(trouveA_B(event.mouseButton.x, event.mouseButton.y, a, b))
                {
                    cliqueGauche = true;
                    //map[a][b] = imageActu;
                    if(map[a][b] == 4)
                    {
                        tour.setPosition(a * LARGEUR_TILE, b * HAUTEUR_TILE);
                    }
                    else
                    {
                        int nbCaseTempo;
                        int tabOuAllerTempo[MAX_LARGEUR_MAP * MAX_HAUTEUR_MAP][2];
                        int mapTempo[MAX_LARGEUR_MAP][MAX_HAUTEUR_MAP];
                        int valX = 0, valY;
                        bool different = false;


                        for(int i = 0; i < MAX_LARGEUR_MAP; i++)
                        {
                            for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
                            {
                                map[i][j] = mapRecup[i][j];
                            }
                        }
                        map[a][b] = 4;

                        for(int i = 0; i < MAX_LARGEUR_MAP; i++)
                        {
                            for(int j = 0 ; j < MAX_HAUTEUR_MAP; j++)
                            {
                                mapTempo[i][j] = map[i][j];
                            }
                        }

                        if(trouveA_B(ennemi.getPosition().x + (LARGEUR_TILE / 2), ennemi.getPosition().y + (HAUTEUR_TILE / 2), valX, valY))
                        {
                            endroitMonstreX = valX;
                            endroitMonstreY = valY;
                        }


                        if(dijkstra(endroitMonstreX, endroitMonstreY, zoneArriverX, zoneArriverY, map, tabOuAller, nbCase))
                        {
                            if(dijkstra(0, 0, zoneArriverX, zoneArriverY, mapTempo, tabOuAllerTempo, nbCaseTempo))
                            {
                                mapRecup[a][b] = 4;
                                etape = 1;
                            }
                        }


                        map[a][b] = mapRecup[a][b];

                    }
                }
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased )//MouseButtonReleased pour relacher
		{
		    if (event.mouseButton.button == sf::Mouse::Left)
			{
			    cliqueGauche = false;
			}
		}


        if(!ennemi.getMoving() && dep)
        {
            if(etape == 0)
            {
                for(int i = 0; i < MAX_LARGEUR_MAP; i++)
                {
                    for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
                    {
                        map[i][j] = mapRecup[i][j];
                    }
                }

                dijkstra(endroitMonstreX, endroitMonstreY, zoneArriverX, zoneArriverY, map, tabOuAller, nbCase);
                cout << endl << "posX : " << ennemi.getPosition().x << "posY: " << ennemi.getPosition().y << endl;
                etape++;
            }
            cout << endl << "nbCase: " << nbCase << endl;
            if(nbCase - etape >= 0)
            {
                ennemi.choixZone(texture, window, clock, tabOuAller[nbCase - etape][0] * LARGEUR_TILE, tabOuAller[nbCase - etape][1] * HAUTEUR_TILE);
                etape++;
            }
            else
            {
                cout << endl << "REMISE A ZERO !!!!!!!!!!!" << endl << endl;
                endroitMonstreX = 0;
                endroitMonstreY = 0;
                etape = 0;
                ennemi.setPos(LARGEUR_TILE * endroitMonstreX, HAUTEUR_TILE * endroitMonstreY);
            }
        }






		if(!ennemi.deplacement(clock, tileBloquant, map, etape))///Seulement si la fenetre a le focus
        {
            cout << endl << "PAS DEPLACEMENT" << endl;
            if(trouveA_B(ennemi.getPosition().x + (LARGEUR_TILE / 2), ennemi.getPosition().y + (HAUTEUR_TILE / 2), a, b) && etape > 1)
            {
                cout << "ERREUR !!! L'ennemie ne peut plus bouger." << endl;
                endroitMonstreX = a;
                endroitMonstreY = b;
                etape = 0;

            }
        }


        ///Affichage

		window.clear(sf::Color(127,127,127));

		for(int i = 0; i < MAX_LARGEUR_MAP; i++)
        {
            for(int j = 0; j < MAX_HAUTEUR_MAP; j++)
            {
                if(map[i][j] >= 0 || map[i][j] < NB_TILE)
                {
                    tile[map[i][j]].setPosition(i * LARGEUR_TILE, j * HAUTEUR_TILE);
                    window.draw(tile[map[i][j]]);
                }
            }
        }

		tour.draw(window);
		tour.afficheTir(window);
        ennemi.afficheEnnemi(window);



		window.display();
	}

	return 0;
}
