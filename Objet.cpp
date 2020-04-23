#include "Objet.h"
#include <iostream>

/* Exemple de création d'objet :
 * Objet O = Objet(Point(1,2),id::ROCHER,50); 
 */


Objet::Objet(Point POS, id TYPE, int VIE):pos(POS),type(TYPE), vie(VIE)  {}
	
Objet::~Objet(){}

//Getters	
Point Objet::getPos(){return this->pos;}
id Objet::getType(){return this->type;}
int Objet::getVie(){return this->vie;}
int Objet::getHauteur(){return this->hauteur;}
int Objet::getDiametre(){return this->diametre;}

//Setters
void Objet::setPos(Point P){
	this->pos=P;
}
void Objet::setType(id T){
	this->type=T;
}
void Objet::setVie(int V){
	this->vie=V;
}
void Objet::setHauteur(int H){
	this->hauteur=H;
}
void Objet::setDiametre(int D){
	this->diametre=D;
}



bool Objet::isEnVie(){
	if(getVie()>0){
		return true;
	}
	return false;
}


void Objet::takeDamage(int d){
	if(getVie()-d>0){
		setVie(getVie()-d);

	}
	else{
		setVie(0);

	}
}


bool Objet::operator== (Objet const& a){
	
if(this->pos==a.pos  &&  this->type == a.type  &&  this->vie == a.vie  &&  this->diametre == a.diametre  && this->hauteur == a.hauteur)return true;
else return false;

} 

std::string get(id t){

	switch(t){
		
		case id::ROCHER : return "Rocher";
		case id::BUISSON : return "Buisson";
		case id::MUR : return "Mur";
		case id::ARBRE : return "Arbre";
		case id::ALGUE : return "Algue";
		default: return "error";		
	
	}
		
	
}



id stringToID(std::string mot){
	
	if (mot == "Rocher") return id::ROCHER;
	else if (mot == "Algue") return id::ALGUE;
	else if (mot == "Mur") return id::MUR;
	else if (mot == "Buisson") return id::BUISSON;
	else if (mot == "Arbre") return id::ARBRE;
	else  return id::RIEN;
	

}


