#ifndef ARME_HH
#define ARME_HH

#include <string>

class Arme{
	
	private:
	std::string nom;
	int puissance;
	int i;
	
	public:
	Arme(std::string, int);
	Arme(int);
	~Arme();
	Arme getArme();
	Arme select(int);
	
};




#endif
