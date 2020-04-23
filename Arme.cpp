#include "Arme.h"


Arme::Arme(std::string n, int p):nom(n), puissance(p){}
Arme::Arme(int i): i(i){}

Arme::~Arme(){}

Arme Arme::getArme(){return *this;}

Arme Arme::select(int i){
	
	switch(i){
		
		case 1 : {
					Arme a = Arme("pistolet", 2);
					return a;
				 }
		
		case 2 : {
					Arme a = Arme("fusil", 4);
					return a;
				}
		
		case 3 : {
					Arme a = Arme("couteau", 1);
					return a;
				}
	}
	
	return Arme(i);
}

