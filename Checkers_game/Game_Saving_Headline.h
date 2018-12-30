#pragma once
#include "Menu_Headline.h"
#include "Game_Headline.h"
#include "List_Item_Headline.h"
#include <fstream>
class Game_Saving
{
protected:
	std::ofstream file;
	std::string file_name;
	List_Item* Ptr;
public:
	Game_Saving();
	Game_Saving(std::string file_name, List_Item* Head);
	void Save();
	~Game_Saving();
};
std::ostream & operator <<(std::ostream & output, const List_Item *Ptr);