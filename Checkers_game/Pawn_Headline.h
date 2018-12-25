#pragma once
#include"Menu_Headline.h"
#include "Index.h"

enum type_of_pawn {pawn, queen};
enum colour_of_pawn {white, black};

class Pawn
{
	type_of_pawn type;
	colour_of_pawn colour;
	sf::CircleShape Circle;
	bool clashing;

public:

	Pawn() = delete;
	Pawn(colour_of_pawn colour, type_of_pawn type, float default_circle_position_x, float default_circle_position_y);
	colour_of_pawn get_colour();
	void set_colour(const colour_of_pawn &colour_pom);
	type_of_pawn get_type();
	void set_type(const type_of_pawn & type_pom);
	bool get_clashing();
	void set_clashing(const bool & clashing_possibility);
	void Circle_set_position(const float & x_pom, const float & y_pom);
	float Circle_get_position_x();
	float Circle_get_position_y();
	bool Circle_getGlobalBounds_contains(const int &mouse_position_x, const int& mouse_position_y);
	void draw(sf::RenderWindow &Game_Window);
	void pawn_to_queen_transformation();
	//~Pawn();

};


