#ifndef MENU_HH
#define MENU_HH

#include <vector>
#include <utility>
#include <string>


class Menu {
	
	private:
	
	std::vector<std::pair<std::string, int>> option;
	
	int position=0;
	
	public:
	
	Menu(std::vector<std::pair<std::string, int>> o);
	
	~Menu();
	
	std::vector<std::pair<std::string, int>>& getOption(); 
	
	void setOption(std::vector<std::pair<std::string, int>> o); 
	
	int getPosition(); 

	int naviguer();
	
	
	
	
	
	
};













#endif 
