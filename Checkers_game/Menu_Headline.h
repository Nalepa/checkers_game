#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Menu
{
	sf::Font font;
	sf::RenderWindow game_window;
	sf::Text text[4];
	sf::RectangleShape rectangle[3];
	int choice;
public:
	Menu(sf::ContextSettings settings);
	void main_menu();
	void loading_menu();
	~Menu();
};

