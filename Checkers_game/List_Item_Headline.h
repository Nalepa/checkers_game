#pragma once
#include "Board_Headline.h"

class List_Item
{
public:
	colour_of_pawn next_move_colour;
	Board Actual_Board;
	List_Item* Previous;
	List_Item* Next;

	List_Item();
	void add_board();
	void delete_last_board();
	List_Item & operator =(const List_Item &list_item1);
	~List_Item();
};