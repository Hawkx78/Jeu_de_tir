#ifndef JOUEUR_HH
#define JOUEUR_HH

#include <iostream>
using namespace std;


#include "Personnage.h"





class Joueur: public Personnage {
	
	
	protected:

	

	
	public:
	Joueur(int pv , int o , int pas , Point pos , Arme a) : Personnage(pv, o, pas, pos, a ){}
	
		
	
	
	void deplacer(float orientation);
	
	
	};
















#endif
