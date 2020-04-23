#ifndef ORDINATEUR_HH
#define ORDINATEUR_HH



#include "Personnage.h"
#include <math.h> 





class Ordinateur: public Personnage {
	
	
	protected:
	int timeBeforeMove;
	

	
	public:
	Ordinateur(int pv , int o , int pas , Point pos , Arme a) : Personnage(pv, o, pas, pos, a ){}
	
		
	
	
	void deplacer(Personnage P,bool vision);
	
	
	};







#endif
