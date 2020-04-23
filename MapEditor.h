#ifndef MAPEDITOR_HH
#define MAPEDITOR_HH

#include <algorithm>
#include "Map.h"
/*
Le MapEditor hérite de la classe Map et permet de créer son environnement de jeu

*/

class MapEditor: public Map{
	private:
	std::string nomFichier; //pour indiquer où faire la sauvegarde;

	public:
	MapEditor(int , int , Point, std::string, int P=0);
	~MapEditor();
	void ajoutObjet(Objet );
	void supprimeObjet(Objet );	
	void sauvegarderMap();
	
	
	//getter
	std::string getNomFichier();
	
	
	
	//setter
	void setNomFichier(std::string);


	};













#endif
