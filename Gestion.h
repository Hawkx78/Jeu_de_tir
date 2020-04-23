#include "Tir.h"
#include "Afficher.h"
#include "Objet.h"
#include "MapEditor.h"
#include "Map.h"
#include "Personnage.h"

#include <time.h>  
#include <math.h> 

#include <iostream>

void Gestion_Jeu(int, std::string);

void Gestion_Jeu_CPU(clock_t t, int, std::string);

void Gestion_Jeu_CPUCPU(clock_t t, int, std::string);

int Gestion_Map_pvcpu(Map & M,clock_t t,sf::RenderWindow & window, int tour);

int Gestion_Map_cpuvcpu(Map & M,clock_t t,sf::RenderWindow & window, int tour);

int Gestion_Map_pvp(Map & M,sf::RenderWindow & window, int tour);

void Gestion_CPU(Map &,sf::RenderWindow & ,clock_t );

void Gestion_CPUvCPU(Map &M,Ordinateur &O,sf::RenderWindow & window,clock_t t);

void Gestion_Editeur(const int, const int, const std::string );

bool esttouche( Objet &, Tir & , Map );

bool collision(Personnage &, Objet &, Map );

bool insideMap(Personnage,Map);

bool vision(Personnage P1, Personnage P2, Map M);

bool collision_vision(Map M,int x,int y);

int getNumberInput(sf::RenderWindow & , std::string);

int getPositionInput(sf::RenderWindow & , std::string);

std::string getTextInput(sf::RenderWindow & , std::string);

std::string choixNiveau(sf::RenderWindow & );
