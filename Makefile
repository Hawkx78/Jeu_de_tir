NOM=D
run: jeu
	./jeu
#Edition de liens

jeu: Main.o Joueur.o Personnage.o Ordinateur.o Map.o MapEditor.o Tir.o Arme.o Afficher.o Point.o Objet.o Gestion.o Menu.o
	g++ -g -Wall Main.o Joueur.o Personnage.o Ordinateur.o Map.o MapEditor.o Tir.o Arme.o Afficher.o Point.o Objet.o Gestion.o Menu.o -o jeu -L ./ressources/compile/lib -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -Wl,-rpath=./ressources/compile/lib

#Compilation:

Gestion.o: Gestion.cpp 
	g++ -c -Wall Gestion.cpp   -I./ressources/compile/include -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

Joueur.o: Joueur.cpp 
	g++ -c -Wall Joueur.cpp 

Personnage.o: Personnage.cpp
	g++ -c -g -Wall Personnage.cpp 
	
Main.o: Main.cpp 
	g++ -c -g -Wall Main.cpp -I./ressources/compile/include -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

Ordinateur.o: Ordinateur.cpp 
	g++ -c -g -Wall Ordinateur.cpp 

Map.o: Map.cpp
	g++ -c -g -Wall Map.cpp 

MapEditor.o: MapEditor.cpp
	g++ -c -g -Wall MapEditor.cpp 

Tir.o: Tir.cpp
	g++ -c -g -Wall Tir.cpp 

Arme.o: Arme.cpp
	g++ -c -g -Wall Arme.cpp 

Afficher.o: Afficher.cpp 
	g++ -c -g -Wall Afficher.cpp -I./ressources/compile/include -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

Point.o: Point.cpp
	g++ -c -g -Wall Point.cpp 

Objet.o: Objet.cpp
	g++ -c -g -Wall Objet.cpp 

Menu.o: Menu.cpp
	g++ -c -g -Wall Menu.cpp  -I./ressources/compile/include -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

	
clean:
	rm -f Objet.o
	rm -f Map.o
	rm -f Main.o
	rm -f Joueur.o
	rm -f MapEditor.o
	rm -f Point.o
	rm -f Arme.o
	rm -f Tir.o
	rm -f Ordinateur.o
	rm -f Personnage.o
	rm -f Afficher.o
	rm -f Gestion.o
	rm -f Menu.o

	rm -f jeu
	
	
	
