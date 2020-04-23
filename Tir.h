#ifndef TIR_HH
#define TIR_HH

#include "Point.h"
#include <iostream>




class Tir{
	
	private:
	int vitesse =2; // se deplace 2 pixel par 2 pixel
	Point depart=Point(-1,-1);
	Point actuelle=Point(-1,-1);;
	int orientation; // [0-90]
	int force; // entre 1 et 5
	int portee; // maximum 5 pixel 
	
	int portcount;

	public :

	Tir(Point dep,int orin, int forc,int port); // on initie avec sa position de depart soit la position du personnage qui tire

	Point getPositionDepart();
	Point getPositionActuelle();
	int getOrientation();
	int getForce();
	int getPortee();
	
	void setPositionActuelle(Point A);
	void setOrientation(int o);
	
	bool deplacer();
	


	
};


#endif
