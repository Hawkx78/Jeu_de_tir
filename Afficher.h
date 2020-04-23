#ifndef AFFICHER_HH
#define AFFICHER_HH

#include <SFML/Graphics.hpp>
#include "Objet.h"
#include "MapEditor.h"
#include "Menu.h"
#include "Personnage.h"
#include <string>



void afficherMenu();

void afficherMen(sf::RenderWindow &, Menu);

void afficherChoixJeu(sf::RenderWindow &);

void afficherChoixTaille(sf::RenderWindow &);

void afficherTextInput(sf::RenderWindow & ,std::string, std::string );//affichage des pages de saisie de données

void afficherChoixNiveau(sf::RenderWindow & window, std::string file);

//Editeur

void afficherEditeur(sf::RenderWindow &, MapEditor , int );

void afficherObjetEditeur(sf::RenderWindow &, Objet );

void afficherGrilleObjet(sf::RenderWindow& );

void afficherTaille(sf::RenderWindow &, int );
// map

void afficherMap();
void afficherMap(Map ,sf::RenderWindow &,int tour,bool visible);

void afficherSol(sf::RenderWindow &);

void afficherSolEditeur(sf::RenderWindow &);

// tir

void afficherTir(sf::RenderWindow & window, Point position);

//Personnage

void afficherPerso(sf::RenderWindow &,Personnage );

void afficherPersonnage(sf::RenderWindow &, Point, int);

// objets

void afficherObjet(sf::RenderWindow &, Objet );

void afficherRocher(sf::RenderWindow &, float, Point);

void afficherArbre(sf::RenderWindow &, float, Point);

void afficherMur(sf::RenderWindow &, float, Point);

void afficherBuisson(sf::RenderWindow &, float, Point);

void afficherAlgue(sf::RenderWindow &, float, Point);


// autre

void afficherCommandes(sf::RenderWindow &);

void afficherCommandesEditeur(sf::RenderWindow &);

void afficherTour(sf::RenderWindow &,int t);

void afficherViePas(sf::RenderWindow & window,Personnage);

void afficherGagnant(sf::RenderWindow & window,int g);




#endif
