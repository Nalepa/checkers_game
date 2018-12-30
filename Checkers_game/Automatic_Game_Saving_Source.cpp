#include "stdafx.h"
#include "Automatic_Game_Saving_Headline.h"

Automatic_Game_Saving::Automatic_Game_Saving() :statement_time(false) {};
void Automatic_Game_Saving::set(std::string file_name1, List_Item* Ptr1)
{
	file_name = file_name1;
	Ptr = Ptr1;
}
bool Automatic_Game_Saving::check_time()
{
	time = clock.getElapsedTime();
	if (time.asSeconds() >= time_period2 && statement_time == true) statement_time = false;
	if (time.asSeconds() >= time_period1)
	{
		time = clock.restart();
		statement_time = true;
		return true;
	}
	else return false;
}
bool Automatic_Game_Saving::get_statement_time()
{
	return statement_time;
}
Automatic_Game_Saving::~Automatic_Game_Saving() {};