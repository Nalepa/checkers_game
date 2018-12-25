#pragma once
#include "Pawn_Headline.h"

class Field
{
//public:
	int field_position_x1, field_position_x2, field_position_y1, field_position_y2;
	float default_circle_position_x, default_circle_position_y;
	Pawn* Pawn_ptr;
	
public:
	Field();
	Field & operator=(const Field &field1);
	void add_pawn(type_of_pawn type_pom, colour_of_pawn colour_pom);
	void set_field_position(int x1, int x2, int y1, int y2);
	void set_default_circle_position(float x1, float x2);
	void clash();
	//~Field();
	friend class Game;
	friend class List_Item;
	friend class Board;
	friend class Game_Saving;
	friend class Game_Loading;
};