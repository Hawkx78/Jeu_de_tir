#include "Joueur.h"
#include <math.h> 



	void Joueur::deplacer(float orientation){
	//printf("depla \n");

		Point tmp = this->position;
		//cout<<"orientation : "<<orientation<<endl;

		
		switch((int)orientation){
			case 0 : 
				this->position.setOrd(this->position.getOrd() + this->vitesse);
				break;
			case 90 :
				this->position.setAbs(this->position.getAbs()  + this->vitesse);
				break;
			case 180 :
				this->position.setOrd(this->position.getOrd() - this->vitesse);
				break;
			case 270 : 
				this->position.setAbs(this->position.getAbs() - this->vitesse);
				break;
			default :
			
					if(orientation != 90){ //si l'angle est différent des orientations cardinales, on déplace x selon le sinus de l'angle et y selon la formule
											//y=(1/tan(orientation)) * (x-position d'avant départ) +  ordonnée courante 
						
							
						float a= 1/tan(orientation*3.141592/180);  
						float precX =this->position.getAbs();
						float x =this->position.getAbs()+sin(orientation*3.141592/180);
						std::cout<<"Abscisse : "<<x<<";"<<"Ordonnees : "<<(a*(x-precX)) +this->position.getOrd()<<std::endl;
						this->setPos(Point(x, (a*(x-precX)) + this->position.getOrd() ));
						
						
					}
					
					
					
					
						
						
						break;
			
			}
		
		
	}
