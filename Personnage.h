#ifndef PERSONNAGE_HH
#define PERSONNAGE_HH

#include "Tir.h"
#include "Arme.h"
#include "Point.h"
#include <iostream>


class Personnage{
	
	protected:
	int hp;
	int orientation;
	int nb_pas;
	int pas_restant;
	Point position;

	Arme attaque;
	Tir tir;
	
	bool enVie=true;
	int vitesse=2;
	

	
	public:
	
	
	Personnage(int, int, int, Point, Arme );
	
	bool estTouche(Tir &t);
	void makeTir();
	bool tire(int orientation);
	Tir & getTir();
	void deplacer(int orientation);
	
	
	
	
	
	//setters
	void setPos(Point P);
	void setOri(int O);
	void setpasrestant(int p);
	void sethp(int hp);
	
	
	
	//Getters
	int gethp();
	int getorientation();
	Point & getpos();
	int & getpasrestant();
	int getnb_pas();
	int getVitesse();
	Arme getAttaque();	
	bool estEnVie();
	
	
	
	};













#endif
