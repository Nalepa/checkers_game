// Checkers_game.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include "Menu_Headline.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	Menu Menu1{ settings };
	Menu1.main_menu();
	return 0;
}