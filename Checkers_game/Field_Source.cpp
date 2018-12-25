#include "stdafx.h"
#include "Field_Headline.h"

Field::Field() : Pawn_ptr(nullptr){}
void Field:: set_field_position(int x1, int x2, int y1, int y2)
{
	field_position_x1 = x1;
	field_position_x2 = x2;
	field_position_y1 = y1;
	field_position_y2 = y2;
}
void Field::set_default_circle_position(float x, float y)
{
	default_circle_position_x = x;
	default_circle_position_y = y;
}
void Field::add_pawn( type_of_pawn type_pom ,colour_of_pawn colour_pom)
{
	Pawn_ptr = new Pawn{ colour_pom,type_pom,default_circle_position_x,default_circle_position_y };
}
void Field::clash()
{
	delete Pawn_ptr;
	Pawn_ptr = nullptr;
}
Field & Field::operator=(const Field &field1)
{
	field_position_x1 = field1.field_position_x1;
	field_position_x2 = field1.field_position_x2;
	field_position_y1 = field1.field_position_y1;
	field_position_y2 = field1.field_position_y2;
	default_circle_position_x = field1.default_circle_position_x;
	default_circle_position_y = field1.default_circle_position_y;
	if (field1.Pawn_ptr == nullptr) Pawn_ptr = nullptr;
	else
	{
			Pawn_ptr = new Pawn{field1.Pawn_ptr->get_colour(), field1.Pawn_ptr->get_type(), default_circle_position_x,default_circle_position_y };
	}
	return *this;
}
//Field::~Field()
//{
//	delete Pawn_ptr;
//}


