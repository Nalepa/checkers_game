#pragma once
#include "Game_Headline.h"
#include <fstream>
class Game_Loading
{
	std::ifstream file;
	std::string file_name;
public:
	Game_Loading(std::string file_name);
	List_Item* Load();
	~Game_Loading();
};
std::istream & operator >>(std::istream & input, List_Item* Head);