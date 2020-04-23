#include "Tir.h"
#include "Objet.h"
#include "MapEditor.h"
#include "Gestion.h"
#include "Menu.h"
#include <time.h>  

#include <iostream>


using namespace std;
int main(){
	
	// MENU
	Menu m = Menu(std::vector<std::pair<std::string, int>> {std::pair<std::string, int>("Editer",1),std::pair<std::string, int>("Jouer",2), std::pair<std::string, int>("Quitter",0)} );
	const int choix=m.naviguer();
	
	
	if (choix == 1){ //choix éditeur
		sf::RenderWindow window(sf::VideoMode(600, 400), "Jeu", sf::Style::Titlebar | sf::Style::Close);
		const int largeur= getNumberInput(window, "Entrez la largeur");
		const int hauteur= getNumberInput(window, "Entrez la hauteur");
		const std::string fic = getTextInput(window, "Entrez le nom du fichier");
		if(largeur == 0 || hauteur == 0 || fic==""){
			std::cout << "Vous avez quitté"<<std::endl; 
			return 0;	
			
		}
		window.close();
		Gestion_Editeur(largeur, hauteur, fic);
	
	
	}
	
	
	if(choix == 3 || choix == 4 || choix==5){
		sf::RenderWindow window(sf::VideoMode(600, 400), "Jeu", sf::Style::Titlebar | sf::Style::Close);
		clock_t t;
		t=clock();
		const std::string file= choixNiveau(window);
		window.close();
		if (choix == 3){
				Gestion_Jeu(choix, file); 
			
		}
		if (choix == 4){
				Gestion_Jeu_CPU(t, choix, file);
			
		}
		if (choix == 5){
				Gestion_Jeu_CPUCPU(t,choix,file); 
			
		}
		
		
	}
	
	

	
		return 0;
	}
