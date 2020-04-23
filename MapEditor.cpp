#include "MapEditor.h"
/*
Le MapEditor hérite de la classe Map et permet de créer son environnement de jeu

*/
MapEditor::MapEditor(int L, int l, Point c, std::string fic, int P ):Map(L,l,c,P),nomFichier(fic){}

MapEditor::~MapEditor(){}

void MapEditor::ajoutObjet(Objet o){
			list.push_back(o);

}
	
	
void MapEditor::supprimeObjet(Objet o){ 
	std::vector <Objet>::iterator it=std::find(list.begin(), list.end(), o);
	if(it!=this->list.end()){
		this->list.erase(it);
			
	}

	
}
	
void MapEditor::sauvegarderMap(){
		std::cout<<this->nomFichier<<std::endl;
	std::ofstream save("ressources/save/" + this->nomFichier, std::ios::out | std::ios::trunc);	
	
	if (save){
		
		save << this->largeur << ";" << this->hauteur << ";" << this->centre.getAbs() << ";" << this->centre.getOrd()<<std::endl; 	
		
		for( Objet & O : this->list){
			
			save<< O.getPos().getAbs() << ";" << O.getPos().getOrd() << ";" << get( O.getType())<< ";" << O.getVie() << std::endl; 
		
		}
		
		
		
	}	
		
		
}




	
	
	//getter
std::string MapEditor::getNomFichier(){
	
		return this->nomFichier;
	
}
	
//setter
void MapEditor::setNomFichier(std::string remplacement){
		
	this->nomFichier=remplacement;	
		
		
}
