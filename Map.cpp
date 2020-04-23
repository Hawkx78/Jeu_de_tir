#include "Map.h"
#include "Personnage.h"
#include <iostream>
#include <vector>





Map::Map(int LARGEUR, int HAUTEUR, Point CENTRE, int PARTIE): largeur(LARGEUR), hauteur(HAUTEUR), centre(CENTRE), partie(PARTIE){

	this->init_liste(partie);
	
}

Map::Map(int LARGEUR, int HAUTEUR, Point CENTRE, std::vector<Objet>o, int PARTIE): largeur(LARGEUR), hauteur(HAUTEUR), centre(CENTRE), list(o), partie(PARTIE) { //constructeur pour générer une map à partir d'une sauvegarde
	this->init_liste(partie);
	
	
	}


void Map::setLargeur(int La){
	this->largeur = La;
}
void Map::setHauteur(int H){
	this->hauteur = H;
}
void Map::setCentre(Point C){
	this->centre = C;
}
void Map::setPartie(int P){
	this->partie = P;
}
	
int Map::getLa(){return this->largeur;}
int Map::getH(){return this->hauteur;}
int Map::getPartie(){return this->partie;}
Point Map::getCentre(){return this->centre;}


void Map::init_liste(int partie){
	
	// players
	
	this->init_personnage(partie);
	
	//Objet
	//std::vector <Objet> list;
	//~ Objet O = Objet(Point(0,0),id::MUR,70);
	//~ this->list.push_back(O);
//	std::cout<<this->list.size()<<std::endl;
}

void Map::placeObjet(){
	if (list.empty())
		std::cout<<"Pas d'objet"<<std::endl;
	else{
		for (int unsigned i = 0; i < list.size(); i++){
			std::cout << ' '<< i;
		}
	}
		
}

void Map::update_liste(){
	this->list.clear();
	Objet O = Objet(Point(200,200),id::ROCHER,10);
	this->list.push_back(O);
	Objet A = Objet(Point(100,100),id::ARBRE,10);
	A.takeDamage(10);
	this->list.push_back(A);

}

void Map::updateMap(){

	if (list.empty())
		std::cout<<"Pas d'objet"<<std::endl;
	else{
		for( Objet O : this->getliste())
		//for (std::vector <Objet>::iterator it = list.begin(); it != list.end(); it++)
		{
			//Objet O  = *it;
			if(O.isEnVie() == false){ list.pop_back(); std::cout<< "mort" << std::endl;}
			else std::cout<< "En vie" <<std::endl;
		}
	}
}

std::vector <Objet> & Map::getliste(){ return this->list;}
std::vector <Joueur> & Map::getlistep(){ return this->listp;}
std::vector <Ordinateur> & Map::getlistecpu(){ return this->listcpu;}


Map::~Map(){
	//std::cout<< "appel destructeur"<<std::endl;
}




Map chargerMap(std::string fic, int partie){//charge les fichiers du répertoire save selon le nom passé en argument
	
	std::ifstream load("ressources/save/" + fic, std::ios::in);	
	if (load){
		int longueur ;int largeur ;int centrex ;int centrey ;
		int objetX ;int objetY ;id objetId ;int objetVie ;
		std::vector<Objet> lesObjets;

		std:: string ligne;
		std::getline(load, ligne);
		

		//Donnees de la map
			longueur =std::stoi(ligne.substr(0, ligne.find(";"))) ; ligne = ligne.substr(ligne.find(";") + 1, ligne.length());
			largeur= std::stoi(ligne.substr(0, ligne.find(";"))); ligne = ligne.substr(ligne.find(";") + 1, ligne.length());
			centrex= std::stoi(ligne.substr(0, ligne.find(";"))); ligne = ligne.substr(ligne.find(";") + 1, ligne.length());
			centrey= std::stoi(ligne.substr(0, ligne.find(";")));
			
		// Donnees des objets
		
		while(std::getline(load, ligne)){
			objetX =std::stoi(ligne.substr(0, ligne.find(";"))) ; ligne = ligne.substr(ligne.find(";") + 1, ligne.length());			
			objetY= std::stoi(ligne.substr(0, ligne.find(";"))); ligne = ligne.substr(ligne.find(";") + 1, ligne.length());
			objetId= stringToID (ligne.substr(0, ligne.find(";"))); ligne = ligne.substr(ligne.find(";") + 1, ligne.length());
			objetVie= std::stoi(ligne.substr(0, ligne.find(";")));
			if(objetX > longueur/2 || objetX < -longueur/2 || objetY > largeur/2 || objetY < -largeur/2 || objetId==id::RIEN ){std::cout<<"Un objet est invalide"<<std::endl; exit(3); }
			
			lesObjets.push_back(Objet(Point(objetX, objetY), objetId, objetVie));
			//std::cout << objetX <<" "<<objetY <<" "<< get(objetId) << " "<<objetVie<<std::endl;
		}
			
	     return Map(longueur, largeur, Point(centrex, centrey), lesObjets, partie);
		 
	}
	
	else {
		std::cout<<"Erreur chargement"<<std::endl;
		std::cerr<< "Impossible d'ouvrir le fichier"<< std::endl;
		exit(2);
	}



		
}


void Map::init_personnage(int partie){
	//positions aléatoires
	srand(time(NULL));
	int j1x = - getLa()/2 + rand()%getLa();
	int j1y =  - getH()/2 + rand()% getH();
	
	int j2x = - getLa()/2 + rand() % getLa();
	int j2y = - getH()/2 + rand() % getH();
	
	
	std::cout<<"j1x : "<< j1x<<std::endl;
	std::cout<<"j1y : "<< j1y<<std::endl;
	
	if (partie == 3){

	Joueur p1 =Joueur(50,0,25,Point(j1x,j1y),Arme("a", 5));
	this->listp.push_back(p1);
	
	
	
	Joueur p2 =Joueur(50,0,25,Point(j2x,j2y),Arme("a", 5));
	this->listp.push_back(p2);

	}
	
	else if(partie == 4){
	
	Joueur P =Joueur(50,0,25,Point(j1x,j1y),Arme("a", 5));
	this->listp.push_back(P);
	
	// computers
	
	Ordinateur Or =Ordinateur(50,0,25,Point(j2x,j2y),Arme("a", 5));
	this->listcpu.push_back(Or);
		
		
	}
	
	
	else{
		
	Ordinateur Or1 = Ordinateur(50,0,25,Point(j1x,j1y),Arme("a", 5));
	this->listcpu.push_back(Or1);
	
	// computers
	
	Ordinateur Or2 =Ordinateur(50,0,25,Point(j2x,j2y),Arme("a", 5));
	this->listcpu.push_back(Or2);
		
		
	}
	
	
	
}



