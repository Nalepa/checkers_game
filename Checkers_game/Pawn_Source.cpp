#include "stdafx.h"
#include "Pawn_Headline.h"

Pawn::Pawn( colour_of_pawn colour, type_of_pawn type , float default_circle_position_x, float default_circle_position_y): colour(colour) , type(type), clashing(false)
{
	Circle.setPosition(default_circle_position_x, default_circle_position_y);
		if (colour == black) Circle.setFillColor(sf::Color::Black);
		else Circle.setFillColor(sf::Color::White);
		Circle.setRadius(30);
}
colour_of_pawn Pawn::get_colour()
{
	return colour;
}
type_of_pawn Pawn::get_type()
{
	return type;
}
bool Pawn::get_clashing()
{
	return clashing;
}
void Pawn::set_colour(const colour_of_pawn &colour_pom)
{
	colour = colour_pom;
}
void Pawn::set_type(const type_of_pawn & type_pom)
{
	type = type_pom;
}
void Pawn::set_clashing(const bool & clashing_possibility)
{
	clashing = clashing_possibility;
}
void Pawn::Circle_set_position(const float & x_pom, const float & y_pom)
{
	Circle.setPosition(x_pom, y_pom);
}
float Pawn::Circle_get_position_x()
{
	return Circle.getPosition().x;
}
float Pawn::Circle_get_position_y()
{
	return Circle.getPosition().y;
}
bool Pawn::Circle_getGlobalBounds_contains(const int &mouse_position_x, const int& mouse_position_y)
{
	return Circle.getGlobalBounds().contains(mouse_position_x, mouse_position_y);
}
void Pawn::draw(sf::RenderWindow &game_window)
{
	if (type == queen)
	{
		Circle.setOutlineThickness(7);
		Circle.setOutlineColor(sf::Color::Yellow);
	}
	game_window.draw(Circle);
}
void Pawn::pawn_to_queen_transformation()
{
	std::cout << "Zmieniam na dame" << std::endl;
	type = queen;
}
Pawn::~Pawn(){}