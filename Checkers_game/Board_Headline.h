#pragma once
#include "Field_Headline.h"
#include <string>

class Board
{
	
public:
	const int size = 8;
	const int number_of_pawns = 24;
	Field *Tab;
	sf::Texture texture;
	sf::Sprite checkers_board;

	Board(std::string file);
	void initial_positions();
	field_index check_mouse_position(const int &mouse_position_x, const int &mouse_position_y);
	bool check_move(const field_index &first_index, const field_index &second_index, const colour_of_pawn &colour_pom, bool &during_the_beating, field_index &beating_pawn);
	bool check_move_2(const field_index &first_index, const field_index &second_index, const colour_of_pawn &move_colour);
	void Display();
	void check_clashing_posibility();
	bool check_clashing_posibility(const field_index &second_index);
	bool check_move_posibility(const field_index &temp_index);
	Board & operator =(const Board& board1);
	~Board();
};
