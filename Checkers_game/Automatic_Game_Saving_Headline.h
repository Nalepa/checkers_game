#pragma once
#include "Game_Saving_Headline.h"
class Automatic_Game_Saving : public Game_Saving
{
	sf::Clock clock;
	sf::Time time;
	const float time_period1 = 30, time_period2 = 2;
	bool statement_time;
public:
	Automatic_Game_Saving();
	void set(std::string file_name1, List_Item* Head1);
	bool check_time();
	bool get_statement_time();
	~Automatic_Game_Saving();
};