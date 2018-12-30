#include "stdafx.h"
#include "Game_Saving_Headline.h"
Game_Saving::Game_Saving() {};
Game_Saving::Game_Saving (std::string file_name, List_Item* Ptr): file_name(file_name), Ptr(Ptr){}
void Game_Saving::Save()
{
	std::cout << "Dokonano zapisu" << std::endl;
	file.open(file_name);
	if (file.good())
	{
		Ptr = Ptr->Previous;
		int size = Ptr->Actual_Board.size;
		file << Ptr;
	}
	else std::cout << "Blad pliku" << std::endl;
		
	file.close();
}
std::ostream & operator <<(std::ostream & output, const List_Item *Ptr)
{
	int size = Ptr->Actual_Board.size;
	/*
	w - ruch maja biale
	b - ruch maja czarne
	0 - puste pole
	1 - bialy pionek
	2 - biala dama
	3 - czarny pionek
	4 - czarna dama
	*/
	if (Ptr->next_move_colour == white) output << 'w';
	else output << 'b';
	for (int line = 0; line < size; line++)
	{
		for (int column = 0; column < size; column++)
		{
			if (Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr == nullptr) output << '0';
			else
			{
				if (Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->get_colour() == white) // bialy
				{
					if (Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->get_type() == pawn) output << '1';	 // pionek
					else output << '2';		// dama
				}
				else // czarny
				{
					if (Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->get_type() == pawn) output << '3';	 // pionek
					else output << '4';		// dama
				}
			}
		}
	}
	return output;
}
Game_Saving::~Game_Saving() {}