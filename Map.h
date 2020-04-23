#ifndef MAP_HH
#define MAP_HH

#include <vector>
#include <iostream>
#include <fstream>
#include "Objet.h"
#include "Personnage.h"
#include "Joueur.h"
#include "Ordinateur.h"



class Map{
	
	protected:
	
	//valeur défini pour test
	int largeur = 10;
	int hauteur = 10;
	Point centre = Point(5,5);
	std::vector <Joueur> listp;
	std::vector <Ordinateur> listcpu;
	std::vector <Objet> list;
	int partie;// définie quelle genre de partie on veut faire(ordi vs ordi ou humain vs humain ou humain vs ordi)
	
	
	public:
	
	Map(int, int, Point, int);
	Map(int , int, Point, std::vector<Objet>, int);
	~Map();
	void updateMap();
	void placeObjet();
	void init_liste(int);
	void update_liste();
	
	//setters
	void setLargeur(int );
	void setHauteur(int );
	void setCentre(Point );
	void setPartie(int);
	
	//getters
	int getLa();
	int getH();
	int getPartie();
	Point getCentre();
	int getTailleListe();
	std::vector <Objet> & getliste();
	std::vector <Joueur> & getlistep();
	std::vector <Ordinateur> & getlistecpu();
	
	void init_personnage(int);
	Objet & operator [] (Objet);//retourne un élément de la liste
	friend std::ostream &operator <<( std::ostream &, Objet &);
	
	
	
	};

	Map chargerMap(std::string, int);










#endif
