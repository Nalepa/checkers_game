#include "stdafx.h"
#include <iostream>
#include "Field_Headline.h"
#include "Board_Headline.h"
#include "Game_Headline.h"

Board::Board(std::string plik): Tab(new Field[size * size])
{
	texture.loadFromFile(plik);
	checkers_board.setTexture(texture);
	checkers_board.setPosition(100, 0);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Tab[index(i, j, size)].set_field_position(74 * i + 150, 74 * i + 223.5, 72 * j + 70, 72 * j + 142);
		}
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Tab[index(i, j, size)].set_default_circle_position(75 * i + 157, 74 * j + 77);
		}
	}	
}
void Board::initial_positions()
{
	int number_of_pawns_pom = number_of_pawns / 2;
	for (int i = 0; i < size; i++)
	{
		if (number_of_pawns_pom == 0) break;
		for (int j = 0; j < size; j += 2)
		{
			if (i > 0 && j == 0)
			{
				if (Tab[index( 0, i - 1, size)].Pawn_ptr != nullptr )
				{
					j++;
				}
			}
			Tab[index(j, i, size)].add_pawn(pawn,black);
			number_of_pawns_pom--;
		}
	}
	number_of_pawns_pom = number_of_pawns / 2;
	for (int i = size -1 ; i >= 0 ; i--)
	{
		if (number_of_pawns_pom == 0) break;
		for (int j = size - 1; j >= 0; j-=2)
		{
			if (i < size - 1 && j == size - 1)
			{
				if (Tab[index(size - 1, i + 1, size)].Pawn_ptr != nullptr)
				{
					j--;
				}
			}
			Tab[index(j , i, size)].add_pawn(pawn, white);
			number_of_pawns_pom--;
		}
	}
}
field_index Board::check_mouse_position(const int &mouse_position_x, const int &mouse_position_y)
{
	field_index index_pom;
	for (int line = 0; line < size; line++)
	{
		for (int column = 0; column < size; column++)
		{
			if (mouse_position_x > Tab[index(column, line, size)].field_position_x1 &&  mouse_position_x < Tab[index(column, line, size)].field_position_x2 && mouse_position_y > Tab[index(column, line, size)].field_position_y1 && mouse_position_y < Tab[index(column, line, size)].field_position_y2)
			{
				index_pom.column = column;
				index_pom.line = line;
				return index_pom;
			}
		}
	}
	index_pom.column = size + 1;
	index_pom.line = size + 1;
	return index_pom;
}
bool Board::check_move(const field_index &first_index, const field_index &second_index, const colour_of_pawn &move_colour, bool &during_the_beating, field_index &beating_pawn)
{
	if (during_the_beating == true && first_index.column != beating_pawn.column || during_the_beating == true && first_index.line != beating_pawn.line) return false;
	if (second_index.column == size + 1 || second_index.line == size + 1 || Tab[index(first_index.column, first_index.line, size)].Pawn_ptr->get_colour() != move_colour) return false;
	
	if (move_colour == white) // ruch maja biale
	{
		for (int line = 0; line < size; line++) // sprawdzanie czy mozliwe bicie przez biale
		{
			for (int column = 0; column < size; column++)
			{
				if (Tab[index(column, line, size)].Pawn_ptr != nullptr)
					if (Tab[index(column, line, size)].Pawn_ptr->get_colour() == white)
						if (Tab[index(column, line, size)].Pawn_ptr->get_clashing() == true)
						{
							if (check_move_2(first_index, second_index, move_colour) == true)
							{
								if (check_clashing_posibility(second_index) == true)
								{
									during_the_beating = true;
									beating_pawn.column = second_index.column;
									beating_pawn.line = second_index.line;
								}
								else during_the_beating = false;

								return true;
							}
							else return false;
						}
			}
		}
		if (Tab[index(first_index, size)].Pawn_ptr->get_type() == pawn) // sprawdzanie ruchu pionka
		{
			// -7
			if (second_index.line == first_index.line - 1 && second_index.column == first_index.column + 1)
			{
				if (Tab[index(second_index, size)].Pawn_ptr == nullptr)
				{
					Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
					Tab[index(first_index, size)].Pawn_ptr = nullptr;
					return true;
				}
			}
			//-9
			if (second_index.line == first_index.line - 1 && second_index.column == first_index.column - 1)
			{
				if (Tab[index(second_index, size)].Pawn_ptr == nullptr)
				{
					Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
					Tab[index(first_index, size)].Pawn_ptr = nullptr;
					return true;
				}
			}

			return false;
		}
		else // sprawdzanie ruchu bialej damy
		{
			field_index temp_index = first_index;
			//-18
			while (true)
			{
				if (temp_index.column - 1 >= 0 && temp_index.line - 1 >= 0 && temp_index.column - 1 < size && temp_index.line - 1 < size)
				{
					if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr == nullptr && index(temp_index.column - 1, temp_index.line - 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						return true;
					}
					else if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column -= 1;
						temp_index.line -= 1;
					}
					else break;
				}
				else break;
			}
			temp_index = first_index;
			//-14
			while (true)
			{
				if (temp_index.column + 1 >= 0 && temp_index.line - 1 >= 0 && temp_index.column + 1 < size && temp_index.line - 1 < size)
				{
					if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr == nullptr && index(temp_index.column + 1, temp_index.line - 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						return true;
					}
					else if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column += 1;
						temp_index.line -= 1;
					}
					else break;
				}
				else break;
			}
			temp_index = first_index;
			//+18
			while (true)
			{
				if (temp_index.column + 1 >= 0 && temp_index.line + 1 >= 0 && temp_index.column + 1 < size && temp_index.line + 1 < size)
				{
					if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr == nullptr && index(temp_index.column + 1, temp_index.line + 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						return true;
					}
					else if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column += 1;
						temp_index.line += 1;
					}
					else break;
				}
				else break;
			}
			temp_index = first_index;
			//+14
			while (true)
			{
				if (temp_index.column - 1 >= 0 && temp_index.line + 1 >= 0 && temp_index.column - 1 < size && temp_index.line + 1 < size)
				{
					if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr == nullptr && index(temp_index.column - 1, temp_index.line + 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						return true;
					}
					else if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column -= 1;
						temp_index.line += 1;
					}
					else break;
				}
				else break;
			}
			return false;
		}
	}
	else // ruch maja czarne
	{
		for (int line = 0; line < size; line++) // sprawdzanie czy mozliwe bicie przez czarne
		{
			for (int column = 0; column < size; column++)
			{
				if (Tab[index(column, line, size)].Pawn_ptr != nullptr)
					if (Tab[index(column, line, size)].Pawn_ptr->get_colour() == black)
						if (Tab[index(column, line, size)].Pawn_ptr->get_clashing() == true)
						{
							if (check_move_2(first_index, second_index, move_colour) == true)
							{
								if (check_clashing_posibility(second_index) == true)
								{
									during_the_beating = true;
									beating_pawn.column = second_index.column;
									beating_pawn.line = second_index.line;
								}
								else during_the_beating = false;
								return true;
							}
							else return false;
						}
			}
		}
		if (Tab[index(first_index, size)].Pawn_ptr->get_type() == pawn) // sprawdzanie ruchu pionka
		{
			// + 7
			if (second_index.line == first_index.line + 1 && second_index.column == first_index.column - 1)
			{
				if (Tab[index(second_index, size)].Pawn_ptr == nullptr)
				{
					Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
					Tab[index(first_index, size)].Pawn_ptr = nullptr;
					return true;
				}
			}
			// + 9
			if (second_index.line == first_index.line + 1 && second_index.column == first_index.column + 1)
			{
				if (Tab[index(second_index, size)].Pawn_ptr == nullptr)
				{
					Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
					Tab[index(first_index, size)].Pawn_ptr = nullptr;
					return true;
				}
			}
			return false;
		}
		else // sprawdzanie ruchu czarnej damy
		{
			field_index temp_index = first_index;
			//-18
			while (true)
			{
				if (temp_index.column - 1 >= 0 && temp_index.line - 1 >= 0 && temp_index.column - 1 < size && temp_index.line - 1 < size)
				{
					if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr == nullptr && index(temp_index.column - 1, temp_index.line - 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						return true;
					}
					else if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column -= 1;
						temp_index.line -= 1;
					}
					else break;
				}
				else break;
			}
			temp_index = first_index;
			//-14
			while (true)
			{
				if (temp_index.column + 1 >= 0 && temp_index.line - 1 >= 0 && temp_index.column + 1 < size && temp_index.line - 1 < size)
				{
					if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr == nullptr && index(temp_index.column + 1, temp_index.line - 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						return true;
					}
					else if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column += 1;
						temp_index.line -= 1;
					}
					else break;
				}
				else break;
			}
			temp_index = first_index;
			//+18
			while (true)
			{
				if (temp_index.column + 1 >= 0 && temp_index.line + 1 >= 0 && temp_index.column + 1 < size && temp_index.line + 1 < size)
				{
					if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr == nullptr && index(temp_index.column + 1, temp_index.line + 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						return true;
					}
					else if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column += 1;
						temp_index.line += 1;
					}
					else break;
				}
				else break;
			}
			temp_index = first_index;
			//+14
			while (true)
			{
				if (temp_index.column - 1 >= 0 && temp_index.line + 1 >= 0 && temp_index.column - 1 < size && temp_index.line + 1 < size)
				{
					if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr == nullptr && index(temp_index.column - 1, temp_index.line + 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						return true;
					}
					else if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column -= 1;
						temp_index.line += 1;
					}
					else break;
				}
				else break;
			}
			return false;
		}
	}
}
bool Board::check_move_2(const field_index &first_index, const field_index &second_index, const colour_of_pawn &move_colour)
{
	if (Tab[index(first_index, size)].Pawn_ptr->get_type() == pawn)
	{
		// -18
		if (second_index.column == first_index.column - 2 && second_index.line == first_index.line - 2 && Tab[index(second_index, size)].Pawn_ptr == nullptr)
		{
			if (Tab[index(first_index.column - 1, first_index.line - 1, size)].Pawn_ptr != nullptr)
			{
				if (Tab[index(first_index.column - 1, first_index.line - 1, size)].Pawn_ptr->get_colour() != move_colour)
				{
					Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
					Tab[index(first_index, size)].Pawn_ptr = nullptr;
					Tab[index(first_index.column - 1, first_index.line - 1, size)].clash();
					return true;
				}
			}
		}
		// -14
		if (second_index.column == first_index.column + 2 && second_index.line == first_index.line - 2 && Tab[index(second_index, size)].Pawn_ptr == nullptr)
		{
			if (Tab[index(first_index.column + 1, first_index.line - 1, size)].Pawn_ptr != nullptr)
			{
				if (Tab[index(first_index.column + 1, first_index.line - 1, size)].Pawn_ptr->get_colour() != move_colour)
				{
					Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
					Tab[index(first_index, size)].Pawn_ptr = nullptr;
					Tab[index(first_index.column + 1, first_index.line - 1, size)].clash();
					check_clashing_posibility();
					return true;
				}
			}
		}
		// +18
		if (second_index.column == first_index.column + 2 && second_index.line == first_index.line + 2 && Tab[index(second_index, size)].Pawn_ptr == nullptr)
		{
			if (Tab[index(first_index.column + 1, first_index.line + 1, size)].Pawn_ptr != nullptr)
			{
				if (Tab[index(first_index.column + 1, first_index.line + 1, size)].Pawn_ptr->get_colour() != move_colour)
				{
					Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
					Tab[index(first_index, size)].Pawn_ptr = nullptr;
					Tab[index(first_index.column + 1, first_index.line + 1, size)].clash();
					return true;
				}
			}
		}
		// +14
		if (second_index.column == first_index.column - 2 && second_index.line == first_index.line + 2 && Tab[index(second_index, size)].Pawn_ptr == nullptr)
		{
			if (Tab[index(first_index.column - 1, first_index.line + 1, size)].Pawn_ptr != nullptr)
			{
				if (Tab[index(first_index.column - 1, first_index.line + 1, size)].Pawn_ptr->get_colour() != move_colour)
				{
					Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
					Tab[index(first_index, size)].Pawn_ptr = nullptr;
					Tab[index(first_index.column - 1, first_index.line + 1, size)].clash();
					return true;
				}
			}

		}
		return false;
	}
	else // sprawdzenie damy
	{
		bool state = false;
		field_index temp_index = first_index;
		field_index index_to_clash;
		//-18
		while (true)
		{
			if (temp_index.column - 1 >= 0 && temp_index.line - 1 >= 0 && temp_index.column - 1 < size && temp_index.line - 1 < size)
			{
				if (state == false)
				{
					if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column -= 1;
						temp_index.line -= 1;
					}
					else
					{
						if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr->get_colour() != move_colour)
						{
							state = true; 
							temp_index.column -= 1;
							temp_index.line -= 1;
							index_to_clash.column = temp_index.column;
							index_to_clash.line = temp_index.line;
						}
						else break;
					}
				}
				else
				{
					if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr == nullptr && index(temp_index.column - 1, temp_index.line - 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						Tab[index(index_to_clash.column, index_to_clash.line, size)].clash();
						return true;
					}
					else if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column -= 1;
						temp_index.line -= 1;
					}
					else break;
				}
			}
			else break;
		}	
		state = false;
		temp_index = first_index;
		//-14
		while (true)
		{
			if (temp_index.column + 1 >= 0 && temp_index.line - 1 >= 0 && temp_index.column + 1 < size && temp_index.line - 1 < size)
			{
				if (state == false)
				{
					if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column += 1;
						temp_index.line -= 1;
					}
					else
					{
						if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr->get_colour() != move_colour)
						{
							state = true;
							temp_index.column += 1;
							temp_index.line -= 1;
							index_to_clash.column = temp_index.column;
							index_to_clash.line = temp_index.line;
						}
						else break;
					}
				}
				else
				{
					if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr == nullptr && index(temp_index.column + 1, temp_index.line - 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						Tab[index(index_to_clash.column, index_to_clash.line, size)].clash();
						return true;
					}
					else if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column += 1;
						temp_index.line -= 1;
					}
					else break;
				}
			}
			else break;
		}
		state = false;
		temp_index = first_index;
		//+18
		while (true)
		{
			if (temp_index.column + 1 >= 0 && temp_index.line + 1 >= 0 && temp_index.column + 1 < size && temp_index.line + 1 < size)
			{
				if (state == false)
				{
					if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column += 1;
						temp_index.line += 1;
					}
					else
					{
						if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr->get_colour() != move_colour)
						{
							state = true;
							temp_index.column += 1;
							temp_index.line += 1;
							index_to_clash.column = temp_index.column;
							index_to_clash.line = temp_index.line;
						}
						else break;
					}
				}
				else
				{
					if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr == nullptr && index(temp_index.column + 1, temp_index.line + 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						Tab[index(index_to_clash.column, index_to_clash.line, size)].clash();
						return true;
					}
					else if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column += 1;
						temp_index.line += 1;
					}
					else break;
				}
			}
			else break;
		}
		state = false;
		temp_index = first_index;
		//+14
		while (true)
		{
			if (temp_index.column - 1 >= 0 && temp_index.line + 1 >= 0 && temp_index.column - 1 < size && temp_index.line + 1 < size)
			{
				if (state == false)
				{
					if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column -= 1;
						temp_index.line += 1;
					}
					else
					{
						if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr->get_colour() != move_colour)
						{
							state = true;
							temp_index.column -= 1;
							temp_index.line += 1;
							index_to_clash.column = temp_index.column;
							index_to_clash.line = temp_index.line;
						}
						else break;
					}
				}
				else
				{
					if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr == nullptr && index(temp_index.column - 1, temp_index.line + 1, size) == index(second_index, size))
					{
						Tab[index(second_index, size)].Pawn_ptr = Tab[index(first_index, size)].Pawn_ptr;
						Tab[index(first_index, size)].Pawn_ptr = nullptr;
						Tab[index(index_to_clash.column, index_to_clash.line, size)].clash();
						return true;
					}
					else if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column -= 1;
						temp_index.line += 1;
					}
					else break;
				}
			}
			else break;
		}
		return false;
		}
}
bool Board::check_move_posibility(const field_index &temp_index) // tylko do sprawdzania blokady
{
	if (Tab[index(temp_index, size)].Pawn_ptr->get_type() == pawn) // pionek
	{
		if (Tab[index(temp_index, size)].Pawn_ptr->get_colour() == white) // bialy pionek
		{
			if (temp_index.column + 1 < size && temp_index.line - 1 >= 0)
			{
				if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr == nullptr) return true; //-7 
			}
			if (temp_index.column - 1 >= 0 && temp_index.line - 1 >= 0)
			{
				if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr == nullptr) return true; //-9
			}
			return false;	
		}
		else // czarny pionek
		{
			if (temp_index.column - 1 >= 0 && temp_index.line + 1 < size)
			{
				if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr == nullptr) return true; //+7 
			}
			if (temp_index.column + 1 < size && temp_index.line + 1 < size)
			{
				if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr == nullptr) return true; //+9
			}
			return false;
		}
	}
	else // dama
	{
		if (temp_index.column + 1 < size && temp_index.line - 1 >= 0)
		{
			if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr == nullptr) return true; //-7 
		}
		if (temp_index.column - 1 >= 0 && temp_index.line - 1 >= 0)
		{
			if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr == nullptr) return true; //-9
		}
		if (temp_index.column - 1 >= 0 && temp_index.line + 1 < size)
		{
			if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr == nullptr) return true; //+7 
		}
		if (temp_index.column + 1 < size && temp_index.line + 1 < size)
		{
			if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr == nullptr) return true; //+9
		}
		return false;
		}
}
bool Board::check_clashing_posibility(const field_index &second_index) //dla pojedynczej figury
{
	if (Tab[index(second_index, size)].Pawn_ptr->get_type() == pawn) // sprawdzenie czy moze bic pionek
	{
		colour_of_pawn pawn_colour = Tab[index(second_index.column, second_index.line, size)].Pawn_ptr->get_colour();
			//-18
			if (second_index.column - 2 >= 0 && second_index.line - 2 >= 0 && second_index.column - 2 < size && second_index.line - 2 < size)
			{
				if (Tab[index(second_index.column - 2, second_index.line - 2, size)].Pawn_ptr == nullptr)
				{
					if (Tab[index(second_index.column - 1, second_index.line - 1, size)].Pawn_ptr != nullptr)
					{
						if (Tab[index(second_index.column - 1, second_index.line - 1, size)].Pawn_ptr->get_colour() != pawn_colour) return true;
					}
				}
			}
			//-14
			if (second_index.column + 2 >= 0 && second_index.line - 2 >= 0 && second_index.column + 2 < size && second_index.line - 2 < size)
			{
				if (Tab[index(second_index.column + 2, second_index.line - 2, size)].Pawn_ptr == nullptr)
				{
					if (Tab[index(second_index.column + 1, second_index.line - 1, size)].Pawn_ptr != nullptr)
					{
						if (Tab[index(second_index.column + 1, second_index.line - 1, size)].Pawn_ptr->get_colour() != pawn_colour) return true;
					}
				}
			}
			// +18
			if (second_index.column + 2 >= 0 && second_index.line + 2 >= 0 && second_index.column + 2 < size && second_index.line + 2 < size)
			{
				if (Tab[index(second_index.column + 2, second_index.line + 2, size)].Pawn_ptr == nullptr)
				{
					if (Tab[index(second_index.column + 1, second_index.line + 1, size)].Pawn_ptr != nullptr)
					{
						if (Tab[index(second_index.column + 1, second_index.line + 1, size)].Pawn_ptr->get_colour() != pawn_colour) return true;
					}
				}

			}
			// +14
			if (second_index.column - 2 >= 0 && second_index.line + 2 >= 0 && second_index.column - 2 < size && second_index.line + 2 < size)
			{
				if (Tab[index(second_index.column - 2, second_index.line + 2, size)].Pawn_ptr == nullptr)
				{
					if (Tab[index(second_index.column - 1, second_index.line + 1, size)].Pawn_ptr != nullptr)
					{
						if (Tab[index(second_index.column - 1, second_index.line + 1, size)].Pawn_ptr->get_colour() != pawn_colour) return true;
					}
				}
			}
			return false;
		}
	else // sprawdzenie czy moze bic dama
	{
		colour_of_pawn queen_colour = Tab[index(second_index, size)].Pawn_ptr->get_colour();
		field_index temp_index = second_index;
		bool state = false;
		//-18
		while (true)
		{
			if (temp_index.column - 1 >= 0 && temp_index.line - 1 >= 0 && temp_index.column - 1 < size && temp_index.line - 1 < size)
			{
				if (state == false)
				{
					if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column -= 1;
						temp_index.line -= 1;
					}
					else
					{
						if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr->get_colour() != queen_colour)
						{
							state = true;
							temp_index.column -= 1;
							temp_index.line -= 1;
						}
						else break;
					}
				}
				else
				{
					if (Tab[index(temp_index.column - 1, temp_index.line - 1, size)].Pawn_ptr == nullptr) return true;
					else break;
				}
			}
			else break;
		}
		state = false;
		temp_index = second_index;
		//-14
		while (true)
		{
			if (temp_index.column + 1 >= 0 && temp_index.line - 1 >= 0 && temp_index.column + 1 < size && temp_index.line - 1 < size)
			{
				if (state == false)
				{
					if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column += 1;
						temp_index.line -= 1;
					}
					else
					{
						if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr->get_colour() != queen_colour)
						{
							state = true;
							temp_index.column += 1;
							temp_index.line -= 1;
						}
						else break;
					}
				}
				else
				{
					if (Tab[index(temp_index.column + 1, temp_index.line - 1, size)].Pawn_ptr == nullptr) return true;
					else break;
				}
			}
			else break;
		}
		state = false;
		temp_index = second_index;
		//+18
		while (true)
		{
			if (temp_index.column + 1 >= 0 && temp_index.line + 1 >= 0 && temp_index.column + 1 < size && temp_index.line + 1 < size)
			{
				if (state == false)
				{
					if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column += 1;
						temp_index.line += 1;
					}
					else
					{
						if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr->get_colour() != queen_colour)
						{
							state = true;
							temp_index.column += 1;
							temp_index.line += 1;
						}
						else break;
					}
				}
				else
				{
					if (Tab[index(temp_index.column + 1, temp_index.line + 1, size)].Pawn_ptr == nullptr) return true;
					else break;
				}
			}
			else break;
		}
		state = false;
		temp_index = second_index;
		//+14
		while (true)
		{
			if (temp_index.column - 1 >= 0 && temp_index.line + 1 >= 0 && temp_index.column - 1 < size && temp_index.line + 1 < size)
			{
				if (state == false)
				{
					if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr == nullptr)
					{
						temp_index.column -= 1;
						temp_index.line += 1;
					}
					else
					{
						if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr->get_colour() != queen_colour)
						{
							state = true;
							temp_index.column -= 1;
							temp_index.line += 1;
						}
						else break;
					}
				}
				else
				{
					if (Tab[index(temp_index.column - 1, temp_index.line + 1, size)].Pawn_ptr == nullptr) return true;
					else break;
				}
			}
			else break;
		}
		return false;	
	}
}
void Board:: check_clashing_posibility() // dla wszystkich figur na planszy
{
	field_index temp_index;
	for (int line = 0; line < size; line++)
	{
		for (int column = 0; column < size; column++)
		{
			if (Tab[index(column, line, size)].Pawn_ptr != nullptr)
			{
				temp_index.column = column;
				temp_index.line = line;
				if (check_clashing_posibility(temp_index) == true) Tab[index(temp_index, size)].Pawn_ptr->set_clashing(true);
				else Tab[index(temp_index, size)].Pawn_ptr->set_clashing(false);
			}
		}
	}
}

void Board::Display()
{
	for (int i = 0; i < size; i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < size; j++)
		{
			if (Tab[index(j, i, size)].Pawn_ptr == nullptr)
			{
				std::cout << " n ";
				continue;
			}

			if (Tab[index(j, i, size)].Pawn_ptr->get_colour() == white) std::cout << " 0 ";
			else std::cout << " 1 ";
			
		}
	}
	for (int i = 0; i < size; i++)
	{
		std::cout << std::endl;
		for (int j = 0; j < size; j++)
		{
			if (Tab[index(i, j, size)].Pawn_ptr != nullptr)
			{
				std::cout << Tab[index(i, j, size)].Pawn_ptr->get_clashing() << ' ';
			}
		}
	}
}
Board & Board::operator =(const Board& board1)
{
	texture = board1.texture;
	checkers_board = board1.checkers_board;

	Tab = new Field[size*size];
	for (int i = 0; i < size*size; i++)
	{
		Tab[i] = board1.Tab[i];
	}
	return *this;
}
Board::~Board()
{
	std::cout << "destruktor klasy Board" << std::endl;
	delete[] Tab;
}

