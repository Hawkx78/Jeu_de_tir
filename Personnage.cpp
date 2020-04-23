#include "Personnage.h"



	Personnage::Personnage(int pv, int o, int pas, Point pos, Arme a):hp(pv), orientation(o), nb_pas(pas), position(pos), attaque(a),tir( Tir(Point(-5000,-5000),0,0,0)){
		this->pas_restant=this->nb_pas;
		
		}
	
	//virtual getPersonnage(); A voir si besoin
	
	bool Personnage::estTouche(Tir &t){
						//printf("pastouché");

		
		if( 	
			(t.getPositionActuelle().getOrd() < getpos().getOrd()+ 5)
		&&
		
			(t.getPositionActuelle().getOrd() > getpos().getOrd()- 5)
		&&
			
			(t.getPositionActuelle().getAbs() > getpos().getAbs()- 5)
		&&
			
			(t.getPositionActuelle().getAbs() < getpos().getAbs()+ 5)
		   )
			{
				this->enVie=false;
				//printf("touché");
				return true;


			}
			
			//printf("pastouché");
			return false;

		
		}
		
	void Personnage::makeTir(){

		tir = Tir(getpos(),getorientation(),10,50);
		tir.setOrientation(getorientation());
		
		std::cout <<"orientation tir  = "<<tir.getOrientation()<<std::endl;
		//~ std::cout<<tir.getPositionActuelle().getOrd()<<std::endl;
		
		

		
	}

	
	bool Personnage::tire(int orientation){

		return tir.deplacer();

	}

	Tir & Personnage::getTir(){
		


		return tir;
		
	}

	
	
	void Personnage::setPos(Point P){
		this->position=P;
	}
	void Personnage::setOri(int O){
		this->orientation = O;
	}
	void Personnage::setpasrestant(int p){
		this->pas_restant = p;
	}
	void Personnage::sethp(int pv){
		this->hp = pv;
	}

	

	int Personnage::gethp(){return this->hp;}
	int Personnage::getorientation(){return this->orientation;}
	Point & Personnage::getpos(){return this->position;}
	int Personnage::getnb_pas(){return this->nb_pas;}
	int & Personnage:: getpasrestant(){return this->pas_restant;}
	int Personnage::getVitesse(){return this->vitesse;}
	Arme Personnage::getAttaque(){return this->attaque;}	
	bool Personnage::estEnVie(){return this->enVie;}





