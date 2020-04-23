#include <dirent.h>
#include "Gestion.h"
#include "Personnage.h"

using namespace std;


void Gestion_Jeu_CPU(clock_t t,int partie, std::string file){ //permet de jouer contre un ordinateur
	
	Map M = chargerMap(file, partie);


	sf::RenderWindow window(sf::VideoMode(M.getLa(),M.getH()), file, sf::Style::Titlebar | sf::Style::Close);	// la fenetre
	
	const int J1x= getPositionInput(window, "J1:Entrez votre abscisse"); //prend la position x du joueur
	const int J1y= getPositionInput(window, "J1:Entrez votre ordonne");// prend la position y du joueur
	M.getlistep()[0].setPos(Point(J1x, J1y));
	
	bool alive=true; // renvoie faux si un des perso est mort
	
	int tour=1; // on commence par joueur 1
	
	int g; // le gagnant
	while (window.isOpen()){
			// les joueurs sont encore en vie ? :
		
			if (alive){
				for( Joueur& J : M.getlistep()){
					
					alive=alive && J.estEnVie();
					if (!J.estEnVie()){
						g=2;
					}
				}
				
				for( Ordinateur& O : M.getlistecpu()){
					
					alive=alive &&  O.estEnVie();
					if (!O.estEnVie()){
						g=1;
					}
				}

			
			
			
			tour = Gestion_Map_pvcpu(M,t,window,tour);
			
			
			
		}
		
		else{
			
				afficherGagnant(window,g);

		}
			

	}
	
	
	
}


void Gestion_Jeu_CPUCPU(clock_t t,int partie, std::string file){ //deux ordinateurs s'affrontent
	
	Map M = chargerMap(file, partie);
	sf::RenderWindow window(sf::VideoMode(M.getLa(),M.getH()), file, sf::Style::Titlebar | sf::Style::Close);	// la fenetre
	
	bool alive=true; // renvoie faux si un des perso est mort
	
	int tour=1; // on commence par joueur 1
	int g;
	while (window.isOpen()){
			// les joueurs sont encore en vie ? :
			
			
			
			if (alive){
				
					int n=1;
					for( Ordinateur& O : M.getlistecpu()){
				
					alive=alive &&  O.estEnVie();
					if(!O.estEnVie()){
						g=3-n;
					}
					n++;
					}

		
		
		
				tour = Gestion_Map_cpuvcpu(M,t,window,tour);
				
			}
			
			else{
				
				afficherGagnant(window,g);
			}
			

	}
	
	
	
}

void Gestion_Jeu(int partie, std::string file){
	
	Map M = chargerMap(file, partie);
	sf::RenderWindow window(sf::VideoMode(M.getLa(),M.getH()), file, sf::Style::Titlebar | sf::Style::Close);	// la fenetre
	
	//prend les positions des joueurs
	const int J1x= getPositionInput(window, "J1:Entrez votre abscisse");
	const int J1y= getPositionInput(window, "J1:Entrez votre ordonne");
	const int J2x= getPositionInput(window, "J2:Entrez votre abscisse");
	const int J2y= getPositionInput(window, "J2:Entrez votre ordonne");
	
	M.getlistep()[0].setPos(Point(J1x, J1y));
	M.getlistep()[1].setPos(Point(J2x, J2y));
	
	
	
	bool alive=true; // renvoie faux si un des perso est mort
	
	int tour=1; // on commence par joueur 1
	int g;
	while (window.isOpen()){
		
					// les joueurs sont encore en vie ? :
		if (alive){
			
			int n=1;
				for( Joueur& J : M.getlistep()){
					
					alive=alive && J.estEnVie();
					if(!J.estEnVie()){
						g=3-n;
						}
					n++;
					}
					
					tour = Gestion_Map_pvp(M,window,tour);

				}
							
				else{
						afficherGagnant(window,g);
			
				}
						

	}
	
	
	
}

int Gestion_Map_cpuvcpu(Map  & M,clock_t t,sf::RenderWindow & window, int tour){
	
			
			sf::Event event;
			while (window.pollEvent(event))
			{
				// gestion des evenements
				if (event.type == sf::Event::Closed)
					window.close();
			}
			
		
				

			int n=0;

			for( Ordinateur & P : M.getlistecpu()){
					n++;
					if (P.estEnVie()&& n==tour){
						
							P.tire(0);
							for (Objet& O: M.getliste()){
								esttouche(O, P.getTir(), M);
							}
							for( Ordinateur & CPU : M.getlistecpu()){
								if (&P!=&CPU){ // on peut tirer sur l'autre joueur si il n'est pas nous même
									CPU.estTouche(P.getTir());

								}
							}
							
							Gestion_CPUvCPU(M,P,window,t);
							
							if (P.getpasrestant()==0){
							
							tour=tour%2+1;
							P.setpasrestant(P.getnb_pas());
							
							

							}
							//	cout<<P.getpasrestant()<<endl;

				}
			}
			
			//if (tour==1){ // si c'est au tour du joueur 2 de jouer
				

		//	}
			
		
			 n=0;
			Ordinateur P1=Ordinateur(0,0,0,Point(0,0),Arme("a", 0));
			Ordinateur P2=Ordinateur(0,0,0,Point(0,0),Arme("a", 0));
			for( Ordinateur& P : M.getlistecpu()){
				n++;
				if (n==1){
					
					P1=P;
				}
				else{
					P2=P;

				}
				
				
			}

			

			afficherMap(M,window,tour,vision(P1,P2,M));
			
				
			
		
	return tour;
	
	
}


int Gestion_Map_pvcpu(Map  & M,clock_t t,sf::RenderWindow & window, int tour){
	
			
			sf::Event event;
			if (window.pollEvent(event))
			{
				// gestion des evenements
				if (event.type == sf::Event::Closed)
					window.close();
				
				else if(event.type == sf::Event::KeyPressed){
					if (event.key.code == sf::Keyboard::Up && tour==1){ // en haut
						for( Joueur& P : M.getlistep()){
							if (P.estEnVie() && P.getpasrestant()>0){
								P.setpasrestant(P.getpasrestant()-1);

								if(window.getSize().y/2 - P.getpos().getOrd()-P.getVitesse() > 0){
									//~ cout<<P.getpos().getOrd()<<endl;
									//~ cout<<P.getpos().getAbs()<<endl;
									
									cout<<"le joueur avance"<<endl;
									Point tmp=P.getpos();
										P.deplacer(P.getorientation());
										bool test = true;
											for( Objet& O: M.getliste()){
												if(collision(P, O, M) == true){
													cout<<"collision avec ";
													cout<<"objet "<<get(O.getType())<<endl;
													
												//	P.getpos().setOrd(O.getPos().getOrd() - O.getVie()/2-5); 

													test = false;
												} else if (collision(P, O, M) == false){
													//~ cout<<"pas de collision"<<endl;
													test = test && true;
												}
											}
										if(!test){ // collision objet
											P.setPos(tmp);

											}
										if(!insideMap(P,M)){ // on reset la pos si il sort de la map
											P.setPos(tmp);
										}
								}
								
							}
							else{
									cout<<"Tirer ou passer votre tour"<<endl;
								}
						}
						
					}
				
			
					else if (event.key.code == sf::Keyboard::Left && tour==1){ // en orientation gauche
						for( Joueur& P : M.getlistep()){
							if (P.estEnVie()){
									cout<<"Orientation a gauche"<<endl;
									int tmp = P.getorientation();
									if(tmp -2 < 0 ) P.setOri(360 +(tmp- 2));
									else P.setOri((tmp - 2) % 360 );
									
								

							}
						}
					}
					else if (event.key.code == sf::Keyboard::Right && tour==1){ // en orientation droite
							for( Joueur& P : M.getlistep()){
							if (P.estEnVie()){
									cout<<"Orientation a droite"<<endl;
									P.setOri((P.getorientation() + 2 ) % 360);
								

							}
						}
					
					}
					
					else if (event.key.code == sf::Keyboard::Space && tour==1){ // tire
						for( Joueur& P : M.getlistep()){
								if (P.estEnVie() && P.gethp() > 0){
									if(P.getTir().getPositionActuelle().getAbs()==-5000){
										cout<<"Le joueur tire"<<endl;
											P.makeTir();
											P.sethp(P.gethp() - P.getTir().getForce());
											P.setpasrestant(0);
											
									}	
									
							}
						}
						

					}
					
					else if (event.key.code == sf::Keyboard::Enter && tour==1){ // passer tour
						for( Joueur& P : M.getlistep()){
								if (P.estEnVie()){
									cout<<"Le joueur passe son tour"<<endl;
									P.setpasrestant(P.getnb_pas());
									tour=tour%2+1; // on passe au joueur suivant
									cout<<"A l'ordinateur de jouer"<<endl;
									
							}
						}
						

					}
					
					
					
				
				}
			}
			
			for( Joueur& P : M.getlistep()){
				if (P.estEnVie()){
						
							if(P.tire(0)){
								P.setpasrestant(P.getnb_pas());
								tour=tour%2+1; // on passe au joueur 
								cout<<"A l'ordinateur de jouer"<<endl;

							}
							for (Objet& O: M.getliste()){
								if(esttouche(O, P.getTir(), M)){		
									P.setpasrestant(P.getnb_pas());
									tour=tour%2+1; // on passe au joueur suivant
									cout<<"A l'ordinateur de jouer"<<endl;
								}
							}
							for( Ordinateur& O : M.getlistecpu()){
							
								O.estTouche(P.getTir());
							}
				}
			}
			for( Ordinateur& P : M.getlistecpu()){
				
				if (P.estEnVie()){
						
							if(P.tire(0)){
								P.setpasrestant(P.getnb_pas());
								tour=tour%2+1; // on passe au joueur suivant
								cout<<"A l'ordinateur de jouer"<<endl;

							}
							for (Objet& O: M.getliste()){
								if(esttouche(O, P.getTir(), M)){		
									P.setpasrestant(P.getnb_pas());
									tour=tour%2+1; // on passe au joueur suivant
									cout<<"A l'ordinateur de jouer"<<endl;
								}
							}
							for( Joueur& J : M.getlistep()){

								J.estTouche(P.getTir());
							}
				}
			}
			
			if (tour==2){ // si c'est au tour du joueur 2 de jouer
				Gestion_CPU(M,window,t);

			}
			
			for( Ordinateur & O : M.getlistecpu()){ // plus de pas restants pour cpu on passe au joueur suivant
					if (O.getpasrestant()==0){
						tour=1;
						O.setpasrestant(O.getnb_pas());
							

					}
				}
			
			Joueur P1=Joueur(0,0,0,Point(0,0),Arme("a", 0));
			Ordinateur P2=Ordinateur(0,0,0,Point(0,0),Arme("a", 0));
			for( Joueur& P : M.getlistep()){
					
					P1=P;
		
			}
			for( Ordinateur& O : M.getlistecpu()){
					
					P2=O;
		
			}
			

			afficherMap(M,window,tour,vision(P1,P2,M));
			
				
			
		
	return tour;
	
	
}

int Gestion_Map_pvp(Map & M,sf::RenderWindow & window, int tour){
	sf::Event event;
			if (window.pollEvent(event))
			{
				// gestion des evenements
				if (event.type == sf::Event::Closed)
					window.close();
				
				else if(event.type == sf::Event::KeyPressed){
					 if (event.key.code == sf::Keyboard::Up){ // en haut
						int n=0;

						for( Joueur& P : M.getlistep()){
							n++;
							if (P.estEnVie()&& n==tour && P.getpasrestant()>0){
								
								P.setpasrestant(P.getpasrestant()-1);

								if(window.getSize().y/2 - P.getpos().getOrd()-P.getVitesse() > 0){
									cout<<P.getpos().getOrd()<<endl;
									cout<<P.getpos().getAbs()<<endl;
									
									
								
											
										Point tmp=P.getpos();
										P.deplacer(P.getorientation());
										bool test = true;
											for( Objet& O: M.getliste()){
												if(collision(P, O, M) == true){
													//~ cout<<"collision"<<endl;
													
												//	P.getpos().setOrd(O.getPos().getOrd() - O.getVie()/2-5); 

													test = false;
												} else if (collision(P, O, M) == false){
													//~ cout<<"pas de collision"<<endl;
													test = test && true;
												}
											}
										if(!test){ // collision objet
											P.setPos(tmp);

											}
										if(!insideMap(P,M)){ // on reset la pos si il sort de la map
											P.setPos(tmp);
										}
								}
								
							}
						}
						
					}
					
				
			
					else if (event.key.code == sf::Keyboard::Left){ // en orientation gauche
						int n=0; // sert a savoir quel joueur joue 1 ou 2

						for( Joueur& P : M.getlistep()){
							n++;
							if (P.estEnVie()&& n==tour){
								
									int tmp = P.getorientation();
									if(tmp -2 < 0 ) P.setOri(360 +(tmp- 2));
									else P.setOri((tmp - 2) % 360 );
									
								

							}
						}
					}
					else if (event.key.code == sf::Keyboard::Right){ // en orientation droite
						int n=0;

						for( Joueur& P : M.getlistep()){
							n++;
							if (P.estEnVie()&& n==tour){
								
									P.setOri((P.getorientation() + 2 ) % 360);
								

							}
						}
					
					}
					
					else if (event.key.code == sf::Keyboard::Space){ // tire
						int n=0;

						for( Joueur& P : M.getlistep()){
							n++;
							if (P.estEnVie()&& n==tour && P.gethp() > 0){
									if(P.getTir().getPositionActuelle().getAbs()==-5000){
											P.makeTir();
											P.setpasrestant(0); // on ne peut plus bouger après avoir tiré
											P.sethp(P.gethp() - P.getTir().getForce());

									}	
								

									
								

							}
						}

					}
					else if (event.key.code == sf::Keyboard::Enter){ // passer tour
						int n=0;
						
						for( Joueur& P : M.getlistep()){
							n++;
							if (P.estEnVie()&& n==tour){
								
									P.setpasrestant(P.getnb_pas());
									tour=tour%2+1; // on passe au joueur suivant
									n=10;
									
								

							}
						}

					}
								
					
				}
			}
			
			int n=0;

			for( Joueur& P : M.getlistep()){
				n++;
					if (P.estEnVie()&& n==tour){
						
							if(P.tire(0)){
								P.setpasrestant(P.getnb_pas());
								tour=tour%2+1; // on passe au joueur suivant

							}
							for (Objet& O: M.getliste()){
								if(esttouche(O, P.getTir(), M)){		
									P.setpasrestant(P.getnb_pas());
									tour=tour%2+1; // on passe au joueur suivant
								}
							}

							for( Joueur& J : M.getlistep()){
								if (&P!=&J){ // on peut tirer sur l'autre joueur si il n'est pas nous même
									J.estTouche(P.getTir());

								}
							}
				}
			}
			
			
			 n=0;
			Joueur P1=Joueur(0,0,0,Point(0,0),Arme("a", 0));
			Joueur P2=Joueur(0,0,0,Point(0,0),Arme("a", 0));
			for( Joueur& P : M.getlistep()){
				n++;
				if (n==1){
					
					P1=P;
				}
				else{
					P2=P;

				}
				
				
			}
			

			

			afficherMap(M,window,tour,vision(P1,P2,M));
			
				
			
	return tour;
	
	
}


void Gestion_CPU(Map &M,sf::RenderWindow & window,clock_t t){ //action de l'ordinateur
	
		

		int time = (clock() - t);
		//~ cout<<"hey"<<endl;

		if (time%9==1){
			for( Ordinateur& O : M.getlistecpu()){
					if(O.getpos().getAbs()+  window.getSize().x/2 + O.getVitesse()< M.getLa()-10- O.getVitesse()){
						Point tmp=O.getpos();
						bool test=true;
						for( Joueur& J : M.getlistep()){
									O.setpasrestant(O.getpasrestant()-1);
									O.deplacer(J,vision(O,J,M)); // on met le joueur en parametre pour que l'ordi puises le suivre si il est visible

								}
						for( Objet& Ob: M.getliste()){
												if(collision(O, Ob, M) == true){
													//~ cout<<"collision"<<endl;
													
												//	P.getpos().setOrd(O.getPos().getOrd() - O.getVie()/2-5); 

													test = false;
												} else if (collision(O, Ob, M) == false){
													//~ cout<<"pas de collision"<<endl;
													test = test && true;
												}
											}
										if(!test){ // collision objet
											O.setPos(tmp);
											O.setpasrestant(O.getpasrestant()+1);

											}
										if(!insideMap(O,M)){ // on reset la pos si il sort de la map
											O.setPos(tmp);
											O.setpasrestant(O.getpasrestant()+1);
										}
							

						}
					}
			
		}
		
	
	
		
	
}

void Gestion_CPUvCPU(Map & M,Ordinateur & O,sf::RenderWindow & window,clock_t t){
	
		

		int time = (clock() - t);
		//cout<<"hey"<<endl;

		if (time%9==1){
				if(O.getpos().getAbs()+  window.getSize().x/2 + O.getVitesse()< M.getLa()-10- O.getVitesse()){
					Point tmp=O.getpos();
						bool test=true;
						for( Ordinateur & P : M.getlistecpu()){
								if(&P!=&O){
									O.setpasrestant(O.getpasrestant()-1);
									O.deplacer(P,vision(O,P,M)); // on met l'autre ordi en parametre pour que l'ordi puises le suivre si il est visible
								}
							}
						for( Objet& Ob: M.getliste()){
												if(collision(O, Ob, M) == true){
													//~ cout<<"collision"<<endl;
													
												//	P.getpos().setOrd(O.getPos().getOrd() - O.getVie()/2-5); 

													test = false;
												} else if (collision(O, Ob, M) == false){
													//~ cout<<"pas de collision"<<endl;
													test = test && true;
												}
											}
										if(!test){ // collision objet
											O.setPos(tmp);
											O.setpasrestant(O.getpasrestant()+1);

											}
										if(!insideMap(O,M)){ // on reset la pos si il sort de la map
											O.setPos(tmp);
											O.setpasrestant(O.getpasrestant()+1);
										}
							

						}
					}
			
		}
		
	


bool collision(Personnage &P, Objet &O, Map M){
	if( 
		(P.getpos().getOrd() < O.getPos().getOrd()+ O.getVie()/2)
	&&
		
		(P.getpos().getOrd() > O.getPos().getOrd()- O.getVie()/2)
	&&
			
		(P.getpos().getAbs() > O.getPos().getAbs()- O.getVie()/2)
	&&
			
		(P.getpos().getAbs() < O.getPos().getAbs()+ O.getVie()/2)
		)
	{
		return true;
	}
	return false;
}

// Teste si le joueur ne sort pas de la map
bool insideMap(Personnage P ,Map M){
	return (
	
		(P.getpos().getOrd() < M.getH()/2)
	&&
		
		(P.getpos().getOrd() > - M.getH()/2)
	&&
			
		(P.getpos().getAbs() > -M.getLa()/2)
	&&
			
		(P.getpos().getAbs() < M.getLa()/2)
	
	);
	
	
}

bool vision(Personnage P1, Personnage P2, Map M){ //gère la vision
			// d'abord trouver l'equation la ligne entre les deux points
			
			bool visible=false;
			
			float m=(P2.getpos().getOrd()-P1.getpos().getOrd()) /(P2.getpos().getAbs()-P1.getpos().getAbs());
			float b=P1.getpos().getOrd() - m* P1.getpos().getAbs();
			
			
			float x=P1.getpos().getAbs();
			float y=m*x+b;
			
			if(P1.getpos().getAbs()<P2.getpos().getAbs()){
				if (y<P2.getpos().getOrd()){
					while(y<P2.getpos().getOrd()){
				
						x++;
						y=m*x+b;
						
						if(collision_vision(M,x,y)){
							return false; // pas de vision si on croise un objet
						}
						
						//~ cout<<y<<" ici et"<< P2.getpos().getOrd()<<endl;
				
					}
					
				}
				
				else if (y>P2.getpos().getOrd()){
					while(y>P2.getpos().getOrd()){
				
						x++;
						y=m*x+b;
						
						if(collision_vision(M,x,y)){
							return false; // pas de vision si on croise un objet
						}
											//	cout<<y<<"par la et "<< P2.getpos().getOrd()<<endl;

				
					}
					
				}
				
				return true;
			}
			
			else if (P1.getpos().getAbs()>P2.getpos().getAbs()){
				
				if (y<P2.getpos().getOrd()){
					while(y<P2.getpos().getOrd()){
				
						x--;
						y=m*x+b;
						
						if(collision_vision(M,x,y)){
							return false; // pas de vision si on croise un objet
						}
										//~ cout<<y<<"par ici et"<< P2.getpos().getOrd()<<" x :" <<x<<endl;

					}
					
				}
				
				else if (y>P2.getpos().getOrd()){
					while(y>P2.getpos().getOrd()){
				
						x--;
						y=m*x+b;
						
						if(collision_vision(M,x,y)){
							return false; // pas de vision si on croise un objet
						}
										//~ cout<<y<<"la et "<< P2.getpos().getOrd()<<endl;

					}
					
				}
				
				return true;
				
				
				
			}
		
			
			
			
		return visible;
	
	
	
}


bool collision_vision(Map M,int x,int y){ // Vérifie s'il y a un objet bloquant la vision
	
	for( Objet& O: M.getliste()){
		
		if( 
			(y < O.getPos().getOrd()+ O.getVie()/2)
		&&
			
			(y > O.getPos().getOrd()- O.getVie()/2)
		&&
				
			(x > O.getPos().getAbs()- O.getVie()/2)
		&&
				
			(x < O.getPos().getAbs()+ O.getVie()/2)
			)
		{
			return true;
		}
		
		
	}
	
	return false;
	
	
}

//Teste si un objet de la map est touché par un tir
bool esttouche( Objet &O, Tir &t , Map M){
	
	
		
		if( 	
			(t.getPositionActuelle().getOrd() < O.getPos().getOrd()+ O.getVie()/2)
		&&
		
			(t.getPositionActuelle().getOrd() > O.getPos().getOrd()- O.getVie()/2)
		&&
			
			(t.getPositionActuelle().getAbs() > O.getPos().getAbs()- O.getVie()/2)
		&&
			
			(t.getPositionActuelle().getAbs() < O.getPos().getAbs()+ O.getVie()/2)
		   )
		{
			O.takeDamage(t.getForce());
			t.setPositionActuelle(Point(-5000,-5000)); // on ne touche l'objet qu'une fois et le tir s'arrête
			

			return true;
		}
		
		return false;

}

//Editeur

void Gestion_Editeur(const int l, const int la, const std::string fic){ //fait fonctionner l'éditeur
	
	id type=id::RIEN ;	
	int tailleActuelle=10;
	int longueur= l; int largeur=la; int centrex=l/2; int centrey=la/2;
	MapEditor Me = MapEditor(longueur, largeur, Point(centrey,centrex), fic);
	sf::RenderWindow window(sf::VideoMode(Me.getLa()+ 100, Me.getH()), "Editeur", sf::Style::Titlebar | sf::Style::Close);	// la fenetre 
	afficherEditeur(window, Me, tailleActuelle);
	while (window.isOpen()){
			sf::Event event;
			while (window.pollEvent(event)){
				switch (event.type){

				case sf::Event::Closed: window.close();break;

				case sf::Event::KeyPressed: 
			
					if (event.key.code == sf::Keyboard::Escape){
						std::cout << "Escape" << std::endl;

						window.close();
					}
					
					else if (event.key.code == sf::Keyboard::S){
						Me.sauvegarderMap();
						window.close();
					}
					else if (event.key.code == sf::Keyboard::Z){
						
						std::cout<<"Effacer"<<endl;
						if(!Me.getliste().empty()){
							
							Me.supprimeObjet(Me.getliste().back());	

						}
						else std::cout<<" Vide"<<std::endl;
					
					
					}
					else if (event.key.code == sf::Keyboard::Up){
						if(tailleActuelle <100) tailleActuelle+=1;
					}
					else if (event.key.code == sf::Keyboard::Down){
						if (tailleActuelle > 0)tailleActuelle-=1;
					}
						
				
				 break;

				case sf::Event::MouseButtonPressed:
				
					if(event.mouseButton.button == sf::Mouse::Left){
						int x =event.mouseButton.x - longueur/2  ;
						int y = largeur/2 -event.mouseButton.y ;
					
						if ( ((unsigned) event.mouseButton.x <= window.getSize().x - 75 + 15 ) && ((unsigned)event.mouseButton.x >= window.getSize().x - 75 - 15) && ((unsigned)event.mouseButton.y <= window.getSize().y*0.10 +15) && ((unsigned)event.mouseButton.y >= window.getSize().y*0.10 - 15) ){
							type = id::ROCHER;
							cout<< "rocher"<<endl;
							
							
						}
						if ( ( (unsigned)event.mouseButton.x <= window.getSize().x-25 + 15) && ((unsigned)event.mouseButton.x >= window.getSize().x- 25 -15) && ((unsigned)event.mouseButton.y <= window.getSize().y*0.10 + 15) && ((unsigned)event.mouseButton.y >= window.getSize().y*0.10 - 15) ){
							type = id::ARBRE;
							cout<< "arbre"<<endl;
							
							
						}
						if ( ((unsigned)event.mouseButton.x <= window.getSize().x-75 + 15) && ((unsigned)event.mouseButton.x >= window.getSize().x- 75 -15) && ((unsigned)event.mouseButton.y <= window.getSize().y*0.20 + 15) && ((unsigned)event.mouseButton.y >= window.getSize().y*0.20 - 15) ){
							type = id::MUR;
							cout<< "mur"<<endl;
							
							
						}
						if ( ((unsigned)event.mouseButton.x <= window.getSize().x-25 + 15) && ((unsigned)event.mouseButton.x >= window.getSize().x - 25 -15) && ((unsigned)event.mouseButton.y <= window.getSize().y*0.20 + 15) && ((unsigned)event.mouseButton.y >= window.getSize().y*0.20 -15) ){
							type = id::BUISSON;
							cout<< "buisson"<<endl;
							
							
						}
						if ( ((unsigned)event.mouseButton.x <= window.getSize().x-75 + 15) && ((unsigned)event.mouseButton.x >= window.getSize().x- 75 -15) && ((unsigned)event.mouseButton.y <= window.getSize().y*0.30 + 15) && ((unsigned)event.mouseButton.y >= window.getSize().y*0.30 -15) ){
							type = id::ALGUE;
							cout<< "algue"<<endl;
							
							
						}
						 if (((unsigned)event.mouseButton.x <= window.getSize().x -100) && ((unsigned)event.mouseButton.x >= 0) && ((unsigned int) event.mouseButton.y <= window.getSize().y) && (event.mouseButton.y >= 0)){
							
							cout<<"Dans le carré"<<endl;
							if(type != id::RIEN){
								
								Me.ajoutObjet(Objet(Point( x, y ), type, tailleActuelle ));
								
								
							}	
								
								
								
						 }
						
						
						
						
						
					}	
				
				
				
				
				
				break;

				default: break;
				
				}
			
			}

			afficherEditeur(window, Me, tailleActuelle);
		
		}
	
	
	
	
	
	
	
	
	
}


std::string getTextInput(sf::RenderWindow & window, std::string titre ){ //Interface pour récupérer des chaines de caractères
	
	
	std::string text;
	afficherTextInput(window, titre,text);
	while (window.isOpen()){
			sf::Event event;
			while (window.pollEvent(event)){
				
				if (event.type == sf::Event::Closed){
					window.close();
					exit(0);
				}
				else if(event.type == sf::Event::TextEntered) {
					if( event.text.unicode > 96 && event.text.unicode < 123 && text.length() < 20) {
						text+= static_cast<char>(event.text.unicode);	
						afficherTextInput(window, titre,text);
						
					}
				}
				else if(event.type == sf::Event::KeyPressed){
				
					if(event.key.code == sf::Keyboard::Backspace) {
							text = text.substr(0, text.length() - 1);
							afficherTextInput(window, titre,text);
					}
					if(event.key.code == sf::Keyboard::Enter) {
						if(!text.empty() )
						return text;
						else
						afficherTextInput(window, titre +"\n" + "Rentrez un nom",text);
					}
				}
			}
	}
		return "" ;
	
}
int getNumberInput(sf::RenderWindow & window, std::string titre ){ //Interface por récupérer des nombres 
	
	
	std::string text;
	afficherTextInput(window, titre,text);
	while (window.isOpen()){
			sf::Event event;
			while (window.pollEvent(event)){
				
				if (event.type == sf::Event::Closed){
					window.close();
					exit(0);
				}
				else if(event.type == sf::Event::TextEntered) {
					if(event.text.unicode >47 && event.text.unicode < 58 && text.length() < 4){
						text+= static_cast<char>(event.text.unicode);	
						afficherTextInput(window, titre,text);
						
					}
				}
				else if(event.type == sf::Event::KeyPressed){
				
					if(event.key.code == sf::Keyboard::Backspace) {
							text = text.substr(0, text.length() - 1);
							afficherTextInput(window, titre,text);
					}
					if(event.key.code == sf::Keyboard::Enter) {
						try{
						int t = std::stoi(text);
						if(!text.empty() && t!= 0 ){
							if(t >= 300  )
								return t;
					}
					
						else
						afficherTextInput(window, titre +"\n" + "(0 impossible)\n <300",text);
						}
						
						catch(const std::invalid_argument& ia){
							
							std::cerr<<"invalid"<<std::endl;
							}
					
					
					}
				}
			}
	}
		return 0;
	
}

int getPositionInput(sf::RenderWindow & window, std::string titre ){ //Interface pour récupérer les positions des joueurs 
	
	
	std::string text;
	afficherTextInput(window, titre,text);
	while (window.isOpen()){
			sf::Event event;
			while (window.pollEvent(event)){
				
				if (event.type == sf::Event::Closed){
					window.close();
					exit(0);
				}
				else if(event.type == sf::Event::TextEntered) {
					if(((event.text.unicode >47 && event.text.unicode < 58) || event.text.unicode == 45) && text.length() < 5){ //prend les nombres et le signe moins
						text+= static_cast<char>(event.text.unicode);	
						afficherTextInput(window, titre,text);
						
					}
				}
				else if(event.type == sf::Event::KeyPressed){
				
					if(event.key.code == sf::Keyboard::Backspace) {
							text = text.substr(0, text.length() - 1);
							afficherTextInput(window, titre,text);
					}
					if(event.key.code == sf::Keyboard::Enter) {
						if(!text.empty() ){
							
							try {	
							int nbre=std::stoi(text);
							if(titre == "J1:Entrez votre abscisse" || titre == "J2:Entrez votre abscisse" ){
								if(nbre < (int)window.getSize().x/2 || nbre  > (int) (-window.getSize().x/2)  )
								return nbre;
							}
							else {
								if(nbre < (int) window.getSize().y/2 || nbre > (int)(-window.getSize().y/2 ) )
								return nbre;
								
							}
							}
							
							catch(const std::invalid_argument& ia){
							
							std::cerr<<"invalid"<<std::endl;
							}
						
						}
						else
						afficherTextInput(window, titre +"\n" + "hors champs",text);
					}
				}
			}
	}
		return 0;
	
}


std::string choixNiveau(sf::RenderWindow & window){
	
	
	std::vector<std::string> list;
	int position = 0;
	DIR * rep = opendir("ressources/save");
	
	if(rep != NULL){
		
			struct dirent * dos;
			
			while((dos = readdir(rep)) != NULL){
				
				if(dos->d_name[0] != '.')
				list.push_back(dos->d_name);	
				
				
				
			}
	closedir(rep);	
	
		while (window.isOpen()){
				sf::Event event;
				while (window.pollEvent(event)){
					
					if (event.type == sf::Event::Closed){
						window.close(); exit(0); 
					}
					else if(event.type == sf::Event::KeyPressed ){
					
						 if (event.key.code == sf::Keyboard::Up){ // en haut
							
							position = (position - 1) % list.size();

						}
						else if (event.key.code == sf::Keyboard::Down){ // en bas
							position = (position + 1) % list.size();
						}
						else if (event.key.code == sf::Keyboard::Enter) return list[position];
					}		
				}
					
							afficherChoixNiveau(window, list[position]);	
				
			}
	
		
		
		
	}
	
	
	
	
	return "";
	
	
	

}



