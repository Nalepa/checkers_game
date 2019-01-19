#include "stdafx.h"
#include "Game_Loading_Headline.h"
#include <string>

Game_Loading::Game_Loading(std::string file_name): file_name(file_name){}
List_Item* Game_Loading::Load()
{
	List_Item* Ptr = new List_Item;
	file.open(file_name);
	if (file.good()) file >> Ptr;
	else std::cout << "Blad pliku" << std::endl;
	file.close();
	Ptr->Actual_Board.checkers_board.setPosition(sf::Vector2f(150, 70));
	return Ptr;
}
std::istream & operator >>(std::istream & input, List_Item *Ptr)
{
	std::string line;
	getline(input, line);
	if (line[0] == 'b') Ptr->next_move_colour = black;
	else Ptr->next_move_colour = white;
	int size = pow(Ptr->Actual_Board.size, 2);
	for (int i = 0; i < size; i++)
	{
		char temp1 = line[i + 1];
		int temp2 = (temp1 - '0') % 48;
		/*
		w - ruch maja biale
		b - ruch maja czarne
		0 - puste pole
		1 - bialy pionek
		2 - biala dama
		3 - czarny pionek
		4 - czarna dama
		*/
		switch (temp2)
		{
		case 0:
		{
			Ptr->Actual_Board.Tab[i].Pawn_ptr = nullptr;
			break;
		}
		case 1:
		{
			Ptr->Actual_Board.Tab[i].Pawn_ptr = new Pawn{ white, pawn, Ptr->Actual_Board.Tab[i].default_circle_position_x, Ptr->Actual_Board.Tab[i].default_circle_position_y };
			break;
		}
		case 2:
		{
			Ptr->Actual_Board.Tab[i].Pawn_ptr = new Pawn{ white, queen, Ptr->Actual_Board.Tab[i].default_circle_position_x, Ptr->Actual_Board.Tab[i].default_circle_position_y };
			break;
		}
		case 3:
		{
			Ptr->Actual_Board.Tab[i].Pawn_ptr = new Pawn{ black, pawn, Ptr->Actual_Board.Tab[i].default_circle_position_x, Ptr->Actual_Board.Tab[i].default_circle_position_y };
			break;
		}
		case 4:
		{
			Ptr->Actual_Board.Tab[i].Pawn_ptr = new Pawn{ black, queen, Ptr->Actual_Board.Tab[i].default_circle_position_x, Ptr->Actual_Board.Tab[i].default_circle_position_y };
			break;
		}
		}
	}
	return input;
}
Game_Loading::~Game_Loading(){}