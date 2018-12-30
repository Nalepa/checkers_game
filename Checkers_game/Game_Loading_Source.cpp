#include "stdafx.h"
#include "Game_Loading_Headline.h"
#include <string>

Game_Loading::Game_Loading(std::string file_name): file_name(file_name){}
List_Item* Game_Loading::Load()
{
	List_Item* Head = new List_Item;
	file.open(file_name);
	if (file.good()) file >> Head;
	else std::cout << "Blad pliku" << std::endl;
	file.close();
	Head->Actual_Board.checkers_board.setPosition(sf::Vector2f(150, 70));
	return Head;
}
std::istream & operator >>(std::istream & input, List_Item*  Head)
{
	std::string line;
	getline(input, line);
	if (line[0] == 'b') Head->next_move_colour = black;
	else Head->next_move_colour = white;
	int size = pow(Head->Actual_Board.size, 2);
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
			Head->Actual_Board.Tab[i].Pawn_ptr = nullptr;
			break;
		}
		case 1:
		{
			Head->Actual_Board.Tab[i].Pawn_ptr = new Pawn{ white, pawn, Head->Actual_Board.Tab[i].default_circle_position_x, Head->Actual_Board.Tab[i].default_circle_position_y };
			break;
		}
		case 2:
		{
			Head->Actual_Board.Tab[i].Pawn_ptr = new Pawn{ white, queen, Head->Actual_Board.Tab[i].default_circle_position_x, Head->Actual_Board.Tab[i].default_circle_position_y };
			break;
		}
		case 3:
		{
			Head->Actual_Board.Tab[i].Pawn_ptr = new Pawn{ black, pawn, Head->Actual_Board.Tab[i].default_circle_position_x, Head->Actual_Board.Tab[i].default_circle_position_y };
			break;
		}
		case 4:
		{
			Head->Actual_Board.Tab[i].Pawn_ptr = new Pawn{ black, queen, Head->Actual_Board.Tab[i].default_circle_position_x, Head->Actual_Board.Tab[i].default_circle_position_y };
			break;
		}
		}
	}
	return input;
}
Game_Loading::~Game_Loading(){}