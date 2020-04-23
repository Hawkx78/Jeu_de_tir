#include "Tir.h"
#include <math.h> 
/*
 * Un tir est caractérisé par :
- un angle de tir (0° à 90°), que le joueur peut ajuster avant de tirer
- une portée de frappe (un nombre de pixels, au maximum 5)
- une force de frappe entre 1 à 5.
*/


	Tir::Tir(Point dep,int ori,int forc,int port){
		this->depart=dep;
		this->actuelle=dep;
		this->orientation=orientation;
		this->force=forc;
		this->portee=port;
		this->portcount=port;
	}
	
	// get
	
	Point Tir::getPositionDepart(){
		return this->depart;
	}
	Point Tir::getPositionActuelle(){
		return this->actuelle;
	}
	int Tir::getOrientation(){
		return this->orientation;
	}
	
	int Tir::getForce(){
		return this->force;
	}
	int Tir::getPortee(){
		return this->portee;
	}
	
	//set
	void Tir::setPositionActuelle(Point A){
		this->actuelle=A;
		
	}
	
	void Tir::setOrientation(int o){
		this->orientation=o;
		
	}
	
	
	// fuctions
	
	//Fonction qui deplace le tir dansla direction souhaitée revoie vrai quand le tir a finit
	bool Tir::deplacer(){
		//if (getPositionActuelle() < getPositionDepart()+getPortee()){
			// trouver la formule
		//}

		if(getPositionActuelle().getAbs()!=-5000){
				int orientation = getOrientation();
								
				switch(orientation){
					
				case 0 : 
					if (getPositionActuelle().getOrd() < getPositionDepart().getOrd()+getPortee()){
						setPositionActuelle(Point(getPositionActuelle().getAbs(),getPositionActuelle().getOrd()+1));
					}
					else{
						setPositionActuelle(Point(-5000,-5000));
						return true;

					}
					break;
				
					
				case 90 : 
					if (getPositionActuelle().getAbs() < getPositionDepart().getAbs()+getPortee()){
						setPositionActuelle(Point(getPositionActuelle().getAbs()+1,getPositionActuelle().getOrd()));
					}
					else{
						setPositionActuelle(Point(-5000,-5000));
						return true;

					}
					break;
					
				case 180 : 
					if (getPositionActuelle().getOrd() > getPositionDepart().getOrd()-getPortee()){
						setPositionActuelle(Point(getPositionActuelle().getAbs(),getPositionActuelle().getOrd()-1));
					}
					else{
						setPositionActuelle(Point(-5000,-5000));
						return true;

					}
					break;
				
				
					
				case 270 : 
					if(getPositionActuelle().getAbs() > getPositionDepart().getAbs()-getPortee()){
						setPositionActuelle(Point(getPositionActuelle().getAbs()-1,getPositionActuelle().getOrd()));
					}
					else{
						setPositionActuelle(Point(-5000,-5000));
						return true;

					}
					break;
					
					
					
					
				//Direction en diagonale	
				default :
					
					if(orientation !=90){
							
							 float a= 1/tan(orientation*3.141592/180);  
							if(this->portcount>0){
								float x =getPositionActuelle().getAbs()+sin(orientation*3.141592/180);
								setPositionActuelle(Point(x, a*(x-getPositionDepart().getAbs()) + getPositionDepart().getOrd() ));
								this->portcount=this->portcount-1;
							}
							else{
								setPositionActuelle(Point(-5000,-5000));
								this->portcount=this->portee;
								return true;

							}		
					}
					
						break;

				
				
				

		
				
			}
		
		}
		
		return false;
		
	}
