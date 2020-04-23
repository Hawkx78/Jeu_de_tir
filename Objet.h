#ifndef OBJET_HH
#define OBJET_HH

#include "Point.h"
#include <string>
enum class id{ARBRE, ROCHER, MUR, BUISSON, ALGUE ,RIEN};

std::string get(id);

id stringToID(std::string);

class Objet{
	
	
	protected: 
	
	Point pos =Point(0,0);
	id type; // peut servir pour différencier les objects à l'affichage;
	int vie;
	int diametre;
	int hauteur;
	
	
	public:
	
	Objet(Point POS, id TYPE, int VIE);
	~Objet();
	// getters
	Point getPos();
	id getType();
	int getVie();
	int getDiametre();
	int getHauteur();
	bool isEnVie();
	
	//setters
	void setPos(Point P);
	void setType(id T);
	void setVie(int V);
	void setHauteur(int H);
	void setDiametre(int D);
	
	// action
	
	void takeDamage(int d); // reçoit des dommages
	
	bool operator==(Objet const&a);
	
	
	
	
	
	
	
	
	
	
	};











#endif
