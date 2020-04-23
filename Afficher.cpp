#include "Afficher.h"
#include "MapEditor.h"
#include <iostream>


	void afficherMen(sf::RenderWindow & window, Menu m){ //affiche le menu

		sf::Font font;
		if (!font.loadFromFile("ressources/verdana.ttf")){
			exit(1);
		}
		sf::Text option[m.getOption().size()];
		for( unsigned int i =0; i<m.getOption().size(); i++){
			
			option[i].setFont(font);
			option[i].setString(m.getOption()[i].first);
			option[i].setFillColor(sf::Color::White);
			option[i].setPosition(sf::Vector2f(window.getSize().x/2, 100*(i+1)));			
				
		}
		
		option[m.getPosition()].setFillColor(sf::Color::Green);
 
		
		window.clear(sf::Color::Black);
		
		for( unsigned int j =0; j<m.getOption().size(); j++){
			window.draw(option[j]);
				
				
		}
		window.display();
		
	
	}
	
	
	void afficherChoixNiveau(sf::RenderWindow & window, std::string file){

		sf::Font font;
		if (!font.loadFromFile("ressources/verdana.ttf")){
			exit(1);
		}
		
		sf::Text titre;
		
			titre.setFont(font);
			titre.setString("Choisissez votre niveau\n(Utiliser haut/bas)");
			titre.setFillColor(sf::Color::Red);
			titre.setPosition(sf::Vector2f(window.getSize().x/4, 100));			
		
		sf::Text option;
		
			option.setFont(font);
			option.setString(file);
			option.setFillColor(sf::Color::White);
			option.setPosition(sf::Vector2f(window.getSize().x/2, 100*2));			

 		
		window.clear(sf::Color::Black);
	
		window.draw(option);
		window.draw(titre);
			
		window.display();
		
	
	}



	void afficherTextInput(sf::RenderWindow & window,std::string title, std::string text){//affichage des pages de saisie de données

		sf::Font font;
		if (!font.loadFromFile("ressources/verdana.ttf")){
			exit(1);
		}
		
		sf::Text option;
		sf::Text t;
		
			option.setFont(font);
			option.setString(title);
			option.setFillColor(sf::Color::White);
			option.setPosition(sf::Vector2f(window.getSize().x/5, 100*2));			
			t.setFont(font);
			t.setString(text);
			t.setFillColor(sf::Color::White);
			t.setPosition(sf::Vector2f(window.getSize().x/5, 100*3));			

		
		option.setFillColor(sf::Color::Green);
 
		
		window.clear(sf::Color::Black);
		
		window.draw(option);
		window.draw(t);

		window.display();
		
		
		
		
		
	}



	void afficherChoixTaille(sf::RenderWindow & window){ //affiche la fenêtre de choix de taille de l'écran
		
		window.clear(sf::Color::Black);
		sf::Font font;
		if (!font.loadFromFile("ressources/verdana.ttf")){
			exit(1);
		}

		sf::Text text;
		text.setFont(font); 
		text.setString("Entrez la taille");
		text.setFillColor(sf::Color::Green);
		text.setPosition(sf::Vector2f(800/2,200)); 
	


		window.draw(text);

		window.display();
		while (window.isOpen()){
		
			sf::Event event;
			while (window.pollEvent(event)){
				switch (event.type){

				case sf::Event::Closed: window.close();break;

				case sf::Event::TextEntered: ;
					
			
				break;

				
				case sf::Event::KeyPressed: 

					if (event.key.code == sf::Keyboard::Escape){ window.close();}
					
					else if(event.key.code == sf::Keyboard::Enter){
							
							 afficherEditeur(window, MapEditor(window.getSize().x, window.getSize().y, Point(window.getSize().x/2,window.getSize().y/2),"jsp" ), 10);
						
				   }break;	
					

				default: break;
			
				}
        
			}

			window.draw(text);

			window.display();

		}
		
		
		
	}
//Editeur
	void afficherEditeur(sf::RenderWindow & window, MapEditor Me, int tailleActuelle) { //Affiche l'interface d'édition
		
		window.clear(sf::Color::Black);
		sf::Font font;
		if (!font.loadFromFile("ressources/verdana.ttf")){
			exit(1);
		}
		window.getSize().x;
		sf::Vertex line[] ={
			sf::Vertex(sf::Vector2f(window.getSize().x-100, 0.f)),
			sf::Vertex(sf::Vector2f(window.getSize().x-100, window.getSize().y))
		};
			
	
		afficherGrilleObjet(window);
		window.draw(line, 2, sf::Lines);
		afficherTaille(window,tailleActuelle);
		for( Objet O : Me.getliste()){
		afficherObjetEditeur(window,O);
	}
		
		afficherCommandesEditeur(window);
		window.display();
			
		
	}
	
	
	
	
	void afficherGrilleObjet(sf::RenderWindow & window){
		afficherSolEditeur(window);
		afficherRocher(window, 50, Point(window.getSize().x-75,window.getSize().y*0.10));
		afficherArbre(window, 50, Point(window.getSize().x-25,window.getSize().y*0.10 ));
		afficherMur(window, 50, Point(window.getSize().x-75,window.getSize().y*0.20));
		afficherBuisson(window, 50, Point(window.getSize().x-25,window.getSize().y*0.20));
		afficherAlgue(window, 50, Point(window.getSize().x-75,window.getSize().y*0.30));
		
	}
	
// map



void afficherMap(Map map,sf::RenderWindow & window, int tour,bool visible){//affiche le terrain de jeu
	
	window.clear();
	afficherSol(window);
	
	int mode=0;
	int n=0;
	for( Joueur& P : map.getlistep()){ // mode pvp
			n++;
			if ((P.estEnVie()&& n==tour) || visible){
		afficherPerso(window, P);
		afficherTir(window,P.getTir().getPositionActuelle());
		}

	}
	mode=n; // si un joueur a joué on sait qu'on est pas en mode 0 soit cpu v cpu
	
	n=0;

	for( Ordinateur & P : map.getlistecpu()){ // mode cpuvcpu
			n++;
			if (((P.estEnVie()&& n==tour )|| visible )&& mode==0 ){

			afficherPerso(window, P);
			afficherTir(window,P.getTir().getPositionActuelle());
		}

	}
	
	// pour le mode pvcpu
	
	if((n==1 && tour==2) || visible){
		for( Ordinateur & P : map.getlistecpu()){ 
			if (P.estEnVie() ){

			afficherPerso(window, P);
			afficherTir(window,P.getTir().getPositionActuelle());
			}

		}
		
	}

	
	
	
	
	for( Objet O : map.getliste()){
		afficherObjet(window,O);
	}
	
	
	// autres
	
	afficherTour(window,tour);
	
	afficherCommandes(window);
	
	// afficher vie
	
	 mode=0;
	 n=0;
	for( Joueur& P : map.getlistep()){ // mode pvp
			n++;
			if ((P.estEnVie()&& n==tour)){
				afficherViePas(window, P);
		}

	}
	mode=n;
	
	n=0;

	for( Ordinateur & P : map.getlistecpu()){ // mode cpuvcpu
			n++;
			if (P.estEnVie()&& n==tour && mode==0){

			afficherViePas(window, P);
		}

	}
	
	// pour le mode pvcpu
	
	if(n==1 && tour==2){
		for( Ordinateur & P : map.getlistecpu()){ 
			if (P.estEnVie()){

			afficherViePas(window, P);
			}

		}
		
	}

	

	
		
    window.display();
    
}

void afficherSolEditeur(sf::RenderWindow & window){
	sf::Sprite grass;
	
	sf::Texture grassTexture;
	if(!grassTexture.loadFromFile("ressources/tilable-IMG_0044-grey1.png"))exit(1);
	grassTexture.setRepeated(true);
	grass.setTexture(grassTexture);
	grass.setTextureRect(sf::IntRect(0,0,window.getSize().x-100,window.getSize().y));
	window.draw(grass);
	
	}

void afficherSol(sf::RenderWindow & window){
	sf::Sprite grass;
	
	sf::Texture grassTexture;
	if(!grassTexture.loadFromFile("ressources/tilable-IMG_0044-grey1.png"))exit(1);
	grassTexture.setRepeated(true);
	grass.setTexture(grassTexture);
	grass.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
	window.draw(grass);
	
	}
	

//Personnage


void afficherPerso(sf::RenderWindow & window,Personnage P){
	
    afficherPersonnage(window, Point(P.getpos().getAbs() + window.getSize().x/2 ,  window.getSize().y/2 - P.getpos().getOrd()  ), P.getorientation());
	
}

void afficherPersonnage(sf::RenderWindow & window, Point position, int orientation){
	

	sf::Sprite object;
	sf::Texture Texture;
	Texture.setSmooth(true);
	Texture.setRepeated(false);
	if(!Texture.loadFromFile("ressources/Sans titre.png"))exit(1);
	object.setTexture(Texture);
	//object.setTextureRect(sf::IntRect(object.getOrigin().x, object.getOrigin().y, taille, taille));
	object.setOrigin(object.getTexture()->getSize().x/2,object.getTexture()->getSize().y/2);
	object.setPosition(position.getAbs(),position.getOrd());
	object.setRotation(orientation);
    window.draw(object);
    
    
}

// tir

void afficherTir(sf::RenderWindow & window, Point position){
	
	sf::CircleShape object;
	object.setFillColor(sf::Color::Red);
	object.setPosition(position.getAbs()+ window.getSize().x/2 ,window.getSize().y/2 - position.getOrd());
	object.setRadius(3);
	object.setOrigin(object.getRadius(), object.getRadius());
    window.draw(object);
  
}




// OBJets

void afficherObjet(sf::RenderWindow & window,Objet O){
	


    switch (O.getType()){
		case id::ROCHER: 
			afficherRocher(window, O.getVie(), Point(O.getPos().getAbs() + window.getSize().x/2 ,  window.getSize().y/2 - O.getPos().getOrd()  ));
			break;
		case id::ARBRE: 
			afficherArbre(window, O.getVie(), Point(O.getPos().getAbs() + window.getSize().x/2 ,window.getSize().y/2 - O.getPos().getOrd() ));
			break;
		case id::MUR: 
			afficherMur(window, O.getVie(), Point(O.getPos().getAbs() + window.getSize().x/2 , window.getSize().y/2 - O.getPos().getOrd() ));
			break;
		case id::BUISSON: 
			afficherBuisson(window, O.getVie(), Point(O.getPos().getAbs() + window.getSize().x/2 , window.getSize().y/2 - O.getPos().getOrd() ));
			break;
		case id::ALGUE: 
			afficherAlgue(window, O.getVie(), Point(O.getPos().getAbs() + window.getSize().x/2 , window.getSize().y/2 - O.getPos().getOrd() ));
			break;
		default:break;			

		
	}
}
void afficherObjetEditeur(sf::RenderWindow & window,Objet O){
	


    switch (O.getType()){
		case id::ROCHER: 
			afficherRocher(window, O.getVie(), Point(O.getPos().getAbs() + (window.getSize().x-100)/2 ,  window.getSize().y/2 - O.getPos().getOrd()  ));
			break;
		case id::ARBRE: 
			afficherArbre(window, O.getVie(), Point(O.getPos().getAbs() + (window.getSize().x-100)/2 ,window.getSize().y/2 - O.getPos().getOrd() ));
			break;
		case id::MUR: 
			afficherMur(window, O.getVie(), Point(O.getPos().getAbs() + (window.getSize().x-100)/2 , window.getSize().y/2 - O.getPos().getOrd() ));
			break;
		case id::BUISSON: 
			afficherBuisson(window, O.getVie(), Point(O.getPos().getAbs() + (window.getSize().x-100)/2, window.getSize().y/2 - O.getPos().getOrd() ));
			break;
		case id::ALGUE: 
			afficherAlgue(window, O.getVie(), Point(O.getPos().getAbs() + (window.getSize().x-100)/2 , window.getSize().y/2 - O.getPos().getOrd() ));
			break;
		default:break;			

		
	}
}
		
		
		
void afficherRocher(sf::RenderWindow & window, float taille, Point position){
	
	sf::Sprite object;
	sf::Texture Texture;
	Texture.setRepeated(false);
	if(!Texture.loadFromFile("ressources/Rocher.png"))exit(1);
	object.setTexture(Texture);
	//object.setTextureRect(sf::IntRect(object.getOrigin().x, object.getOrigin().y, taille, taille));
	object.setOrigin(object.getTexture()->getSize().x/2,object.getTexture()->getSize().y/2);

	object.setPosition(position.getAbs(),position.getOrd());
	object.setScale(taille/object.getTexture()->getSize().x, taille/object.getTexture()->getSize().y); // pour que l'image soit vraiment à la bonne taille

	
    window.draw(object);
    
    
}

void afficherArbre(sf::RenderWindow & window, float taille, Point position){
	//sf::RectangleShape object(sf::Vector2f(taille,taille));
	sf::Sprite object;
	sf::Texture Texture;
	Texture.setRepeated(false);
	if(!Texture.loadFromFile("ressources/Arbre.png"))exit(1);
	object.setTexture(Texture);
	//object.setTextureRect(sf::IntRect(object.getOrigin().x, object.getOrigin().y, taille, taille));
	object.setOrigin(object.getTexture()->getSize().x/2,object.getTexture()->getSize().y/2);

	object.setScale(taille/object.getTexture()->getSize().x, taille/object.getTexture()->getSize().y); // pour que l'image soit vraiment à la bonne taille

	object.setPosition(position.getAbs(),position.getOrd());
	
	
    window.draw(object);
  
}

void afficherMur(sf::RenderWindow & window, float taille, Point position){
sf::Sprite object;
	sf::Texture Texture;
	Texture.setRepeated(true);
	if(!Texture.loadFromFile("ressources/Mur.png"))exit(1);
	object.setTexture(Texture);
	
	object.setOrigin(object.getTexture()->getSize().x/2,object.getTexture()->getSize().y/2); // pour que ce soit centré
	object.setScale(taille/object.getTexture()->getSize().x, taille/object.getTexture()->getSize().y); // pour que l'image soit vraiment à la bonne taille

	//object.setTextureRect(sf::IntRect(object.getOrigin().x, object.getOrigin().y, taille, taille));
	object.setPosition(position.getAbs(),position.getOrd());
	
	
    window.draw(object);
     
}


void afficherBuisson(sf::RenderWindow & window, float taille, Point position){
	sf::Sprite object;
	sf::Texture Texture;
	Texture.setRepeated(true);
	
	if(!Texture.loadFromFile("ressources/Buisson.png"))exit(1);
	object.setTexture(Texture);
	//object.setTextureRect(sf::IntRect(object.getOrigin().x, object.getOrigin().y, taille, taille));
	
	object.setOrigin(object.getTexture()->getSize().x/2,object.getTexture()->getSize().y/2);
	object.setScale(taille/object.getTexture()->getSize().x, taille/object.getTexture()->getSize().y); // pour que l'image soit vraiment à la bonne taille

	object.setPosition(position.getAbs(),position.getOrd());
	
	
    window.draw(object);
     
}

void afficherAlgue(sf::RenderWindow & window, float taille, Point position){
	sf::Sprite object;
	sf::Texture Texture;
	Texture.setRepeated(true);
	if(!Texture.loadFromFile("ressources/Algue.png"))exit(1);
	object.setTexture(Texture);
	//object.setTextureRect(sf::IntRect(object.getOrigin().x, object.getOrigin().y, taille, taille));
	
	object.setOrigin(object.getTexture()->getSize().x/2,object.getTexture()->getSize().y/2);
	object.setScale(taille/object.getTexture()->getSize().x, taille/object.getTexture()->getSize().y); // pour que l'image soit vraiment à la bonne taille

	object.setPosition(position.getAbs(),position.getOrd());
	
	
    window.draw(object);
     
}

void afficherTaille(sf::RenderWindow & window, int tailleActuelle){//affiche la taille pour l'éditeur
	
	sf::Text taille;
	sf::RectangleShape object(sf::Vector2f(window.getSize().x *0.15, 20));
	object.setFillColor(sf::Color::Black);
	object.setOutlineThickness(2.f);
	object.setOutlineColor(sf::Color(0,0,100));
	object.setPosition(window.getSize().x*0.80, window.getSize().y *0.90);
	window.draw(object);
	sf::Font font;
	if (!font.loadFromFile("ressources/verdana.ttf")){
			exit(1);
		}
	taille.setFont(font); 
	taille.setString(std::to_string(tailleActuelle));
    taille.setFillColor(sf::Color::White);
	taille.setPosition(sf::Vector2f(window.getSize().x*0.80, window.getSize().y *0.90));
	window.draw(taille);
	
	
}


// autres

void afficherCommandes(sf::RenderWindow & window){//affiche les touches pour jouer
	
	
		sf::Font font;
		if (!font.loadFromFile("ressources/verdana.ttf")){
			exit(1);
		}
		
		sf::Text text;
		text.setFont(font); 
		text.setString(" Espace : Tirer     Entrer : Passer ");
		text.setFillColor(sf::Color::White);
		text.setPosition(sf::Vector2f(0,window.getSize().y-30)); 
		
		text.setCharacterSize(20);
	


		window.draw(text);

		//window.display();
	
}

void afficherTour(sf::RenderWindow & window,int t){// affiche le joueur qui doit jouer
	
		sf::Font font;
		if (!font.loadFromFile("ressources/verdana.ttf")){
			exit(1);
		}
		string s = "Joueur ";
		s+='0'+t;
		sf::Text text;
		text.setFont(font); 
		text.setString(s);
		text.setFillColor(sf::Color::White);
		text.setPosition(sf::Vector2f(0,0)); 
	


		window.draw(text);

		window.display();
	
	
	
}


void afficherViePas(sf::RenderWindow & window,Personnage P){//affiche la vie et les pas restants du joueur en cours
	sf::Font font;
		if (!font.loadFromFile("ressources/verdana.ttf")){
			exit(1);
		}
		string s = "Vies restantes :";
		s+=to_string(P.gethp());
		sf::Text text;
		text.setFont(font); 
		text.setString(s);
		text.setFillColor(sf::Color::Red);
		text.setPosition(sf::Vector2f(window.getSize().x/2,0)); 
		text.setCharacterSize(20);
		
		s = "Pas restants :";
		s+=to_string(P.getpasrestant());
		sf::Text pas;
		pas.setFont(font); 
		pas.setString(s);
		pas.setFillColor(sf::Color::Red);
		pas.setPosition(sf::Vector2f(window.getSize().x/2,30)); 
		pas.setCharacterSize(20);
	


		window.draw(text);
		window.draw(pas);
	
	
}


void afficherGagnant(sf::RenderWindow & window,int g){//affiche le gagnant 
	
	
	window.clear();
	sf::Font font;
		if (!font.loadFromFile("ressources/verdana.ttf")){
			exit(1);
		}
		string s = " gagnant : Joueur ";
		s+='0'+g;
		sf::Text text;
		text.setFont(font); 
		text.setString(s);
		text.setFillColor(sf::Color::White);
		text.setPosition(sf::Vector2f(window.getSize().x/4,window.getSize().y/3)); 
	


		window.draw(text);

		window.display();
		
		sf::Event event;
			while (window.pollEvent(event))
			{
				// gestion des evenements
				if (event.type == sf::Event::Closed)
					window.close();
			}
	
	
	
}

void afficherCommandesEditeur(sf::RenderWindow & window){//affiche les touches de l'éditeur
	
	
		sf::Font font;
		if (!font.loadFromFile("ressources/verdana.ttf")){
			exit(1);
		}
		
		sf::Text text;
		text.setFont(font); 
		text.setString(" Z : Effacer     Haut/Bas : Taille    S:Sauvegarder ");
		text.setFillColor(sf::Color::White);
		text.setPosition(sf::Vector2f(0,window.getSize().y-30)); 
		
		text.setCharacterSize(20);
	


		window.draw(text);

	
}

