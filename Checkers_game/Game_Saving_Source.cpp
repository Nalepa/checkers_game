#include "stdafx.h"
#include "Game_Saving_Headline.h"
Game_Saving::Game_Saving() {};
Game_Saving::Game_Saving (std::string file_name, List_Item* Head): file_name(file_name), Head(Head){}
void Game_Saving::Save()
{
	std::cout << "Dokonano zapisu" << std::endl;
	file.open(file_name);
	if (file.good())
	{
		Head = Head->Previous;
		int size = Head->Actual_Board.size;
		/*
		 w - ruch maja biale
		 b - ruch maja czarne
		 0 - puste pole
		 1 - bialy pionek
		 2 - biala dama
		 3 - czarny pionek
		 4 - czarna dama
		*/
		if (Head->next_move_colour == white) file << 'w';
		else file << 'b';
		for (int line = 0; line < size; line++)
		{
			for (int column = 0; column < size; column++)
			{
				if (Head->Actual_Board.Tab[index(column, line, size)].Pawn_ptr == nullptr) file << '0';
				else
				{
					if (Head->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->get_colour() == white) // bialy
					{
						if (Head->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->get_type() == pawn) file << '1';	 // pionek
						else file << '2';		// dama
					}
					else // czarny
					{
						if (Head->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->get_type() == pawn) file << '3';	 // pionek
						else file << '4';		// dama
					}
				}

			}
		}
	}
	else std::cout << "Blad pliku" << std::endl;
		
	file.close();

}
Game_Saving::~Game_Saving(){}