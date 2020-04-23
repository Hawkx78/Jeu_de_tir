#include "Ordinateur.h"


	void Ordinateur::deplacer(Personnage P,bool vision){
		
		
		// PARTIE DEPLACEMENT SI L'ORDINATEUR VOIT L'ENNEMI
		
		if (vision)
		{ 
			
			// tirer
			if(getpos().getOrd()+getTir().getPortee() > P.getpos().getOrd() && (getpos().getAbs()+2>P.getpos().getAbs() &&getpos().getAbs()-2<P.getpos().getAbs())){ // au dessus
				setOri(180);
				if(getTir().getPositionActuelle().getAbs()==-5000){
									makeTir();

					}	


			}
			else if(getpos().getOrd()-getTir().getPortee()  < P.getpos().getOrd()&& (getpos().getAbs()+2>P.getpos().getAbs() &&getpos().getAbs()-2<P.getpos().getAbs())){
			setOri(0);

				if(getTir().getPositionActuelle().getAbs()==-5000){
									makeTir();

					}	


			}
			else if(getpos().getAbs()+getTir().getPortee()  > P.getpos().getAbs() && (getpos().getAbs()+2>P.getpos().getOrd() &&getpos().getAbs()-2<P.getpos().getOrd())){
				setOri(270);

				if(getTir().getPositionActuelle().getAbs()==-5000){
									makeTir();

					}	

			}
			else if(getpos().getAbs()-getTir().getPortee()  < P.getpos().getAbs() && (getpos().getAbs()+2>P.getpos().getOrd() &&getpos().getAbs()-2<P.getpos().getOrd())){
					setOri(90);
		
				if(getTir().getPositionActuelle().getAbs()==-5000){
									makeTir();

					}	

			}
		
			// avancer
			if(getpos().getOrd() + this->vitesse< P.getpos().getOrd()){
				this->position.setOrd(this->position.getOrd() + this->vitesse);
				setOri(0);


			}
			else if(getpos().getOrd()- this->vitesse > P.getpos().getOrd()){
				this->position.setOrd(this->position.getOrd() - this->vitesse);
				setOri(180);


			}
			else if(getpos().getAbs() < P.getpos().getAbs()){
				this->position.setAbs(this->position.getAbs() + this->vitesse);
				setOri(90);

			}
			else if(getpos().getAbs() > P.getpos().getAbs()){
				this->position.setAbs(this->position.getAbs() - this->vitesse);
				setOri(270);

			}
			
			
			
			
		}
		
		
		
		// PARTIE DEPLACEMENT RANDOM
		else{
			
		int r = rand() % 360; 
		
		setOri(r);

		
		switch(r){
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
			
					if(r != 90){ //si l'angle est différent des orientations cardinales, on déplace x selon le sinus de l'angle et y selon la formule
											//y=(1/tan(orientation)) * (x-position d'avant départ) +  ordonnée courante 
						
							
						float a= 1/tan(r*3.141592/180);  
						float precX =this->position.getAbs();
						float x =this->position.getAbs()+sin(r*3.141592/180);
						std::cout<<"Abscisse : "<<x<<";"<< "Ordonnees : "<<(a*(x-precX)) +this->position.getOrd()<<std::endl;
						this->setPos(Point(x, (a*(x-precX)) + this->position.getOrd() ));
						
						
					}
					
			}
			
		}
		
		
	}
