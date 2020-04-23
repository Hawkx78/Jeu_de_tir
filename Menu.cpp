#include "Menu.h"
#include "Afficher.h"

	Menu::Menu(std::vector<std::pair<std::string, int>> o): option(o){
		
		this->position = 0;
		
		
		}
	
	Menu::~Menu(){}
	
	std::vector<std::pair<std::string, int>>& Menu::getOption(){
		
		return this->option;
		
		}
	
	int Menu::getPosition(){return this->position;}
	
	void  Menu::setOption(std::vector<std::pair<std::string, int>> o){
		
		this->option.clear();
		
		this->option = o; 
		
		
		
		} 

	int Menu::naviguer(){
		
		sf::RenderWindow window(sf::VideoMode(800, 600), "Menu", sf::Style::Titlebar | sf::Style::Close);	// la fenetre

		while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event)){
					
					if (event.type == sf::Event::Closed)
						window.close();
					
					else if(event.type == sf::Event::KeyPressed ){
					
						 if (event.key.code == sf::Keyboard::Up){ // en haut
							
							this->position = (this->position - 1) % this->option.size();

						}
						else if (event.key.code == sf::Keyboard::Down){ // en bas
							this->position = (this->position + 1) % this->option.size();
						}
						else if (event.key.code == sf::Keyboard::Enter){ // en bas
							
							const int choix = this->option[position].second;
							
							if(choix == 0){window.close();return 0; }
							
							else if(choix == 1){ //choisit l'editeur
								window.close();
								return 1;
								
							}
							
							else if(choix == 2){ //choisit de joueur
								this->position = 0 ;
								this->setOption(std::vector<std::pair<std::string, int>> {std::pair<std::string, int>("Jouer contre un ami", 3), std::pair<std::string, int>("Jouer contre Cpu",4), std::pair<std::string, int>("Cpu contre Cpu",5)} );
							}
							
							else if(choix == 3){ //choisit de jouer contre un humain
								window.close();
								return 3;
								
							}
							
							else if(choix == 4){ //choisit de jouer contre l'ordinateur
								window.close();
								return 4;
								
							}
							
							else if(choix == 5){ //choisit ordinateur contre l'ordinateur
								window.close();
								return 5;
								
							}
							
							
						
						
						
						
						}	

				
				
					}		
				}
					
							afficherMen(window, *this);	
				
			}
		
		
		return 0;		
		
		
	}
