#include "stdafx.h"
#include "Menu_Headline.h"
#include "Game_Headline.h"
#include <Windows.h>

Menu::Menu(sf::ContextSettings settings) :  game_window(sf::VideoMode(900, 700, 33), "Warcaby gra", sf::Style::Default, settings)
{
	if (!font.loadFromFile("contm.ttf")) std::cout << "Nie udalo sie poprawnie wczytac czcionki" << std::endl;

	rectangle[0].setSize(sf::Vector2f{ 300,100 });
	rectangle[0].setPosition(300, 100);
	rectangle[0].setFillColor(sf::Color::Blue);

	rectangle[1].setSize( sf::Vector2f{ 300,100 } );
	rectangle[1].setPosition(300, 220);
	rectangle[1].setFillColor(sf::Color::Blue);

	rectangle[2].setSize( sf::Vector2f{ 300,100 } );
	rectangle[2].setPosition(300, 340);
	rectangle[2].setFillColor(sf::Color::Blue);

	text[0].setString("Menu");
	text[0].setFont(font);
	text[0].setCharacterSize(50);
	text[0].setPosition(400, 0);
	text[0].setFillColor(sf::Color::Black);

	text[1].setString("Nowa gra");
	text[1].setFont(font);
	text[1].setCharacterSize(50);
	text[1].setPosition(350, 120);
	text[1].setFillColor(sf::Color::Black);

	text[2].setString("Wczytaj gre");
	text[2].setFont(font);
	text[2].setCharacterSize(50);
	text[2].setPosition(320, 240);
	text[2].setFillColor(sf::Color::Black);

	text[3].setString("Zakoncz");
	text[3].setFont(font);
	text[3].setCharacterSize(50);
	text[3].setPosition(340, 355);
	text[3].setFillColor(sf::Color::Black);
}

void Menu::main_menu()
{
	while (game_window.isOpen())
	{
		sf::Event game_event;
		while (game_window.pollEvent(game_event))
		{
			if (game_event.type == sf::Event::Closed)
			{
				game_window.close();
			}
			if (game_event.type == sf::Event::KeyPressed && game_event.key.code == sf::Keyboard::Escape)
			{
				game_window.close();
			}
		}
		sf::Vector2i mouse_position = sf::Mouse::getPosition(game_window);
		
		//obsluga przycisku nowa gra
		if (rectangle[0].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			choice = 1;
			Game game{};
			game.play(game_window, choice);
			return;
		}
		else if (rectangle[0].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true) rectangle[0].setFillColor(sf::Color::Green);
		else rectangle[0].setFillColor(sf::Color::Blue);
		
		//obsluga przycisku wczytaj
		if (rectangle[1].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			loading_menu();
			return;
		}
		else if (rectangle[1].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true) rectangle[1].setFillColor(sf::Color::Green);
		else rectangle[1].setFillColor(sf::Color::Blue);

		//obsluga przycisku zakoncz
		if (rectangle[2].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			game_window.close();
		}
		else if (rectangle[2].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true) rectangle[2].setFillColor(sf::Color::Green);
		else rectangle[2].setFillColor(sf::Color::Blue);
		
		game_window.clear(sf::Color(255, 0, 255));
		game_window.draw(rectangle[0]);
		game_window.draw(rectangle[1]);
		game_window.draw(rectangle[2]);
		game_window.draw(text[0]);
		game_window.draw(text[1]);
		game_window.draw(text[2]);
		game_window.draw(text[3]);
		game_window.display();
	}
}
void Menu::loading_menu()
{
	rectangle[0].setSize(sf::Vector2f{ 500,100 });
	rectangle[0].setPosition(200, 200);

	rectangle[1].setSize(sf::Vector2f{ 500,100 });
	rectangle[1].setPosition(200, 350);

	text[0].setString("Z jakiego pliku wczytac?");
	text[0].setPosition(190, 50);

	text[1].setString("Automatyczny zapis");
	text[1].setPosition(235, 220);

	text[2].setString("Reczny zapis");
	text[2].setPosition(300, 365);
	Sleep(100);
	while (game_window.isOpen())
	{
		sf::Event game_event;
		while (game_window.pollEvent(game_event))
		{
			if (game_event.type == sf::Event::Closed)
			{
				game_window.close();
			}
			if (game_event.type == sf::Event::KeyPressed && game_event.key.code == sf::Keyboard::Escape)
			{
				game_window.close();
			}
			sf::Vector2i mouse_position = sf::Mouse::getPosition(game_window);
			if (rectangle[0].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				choice = 2;
				Game game{};
				game.play(game_window, choice);
				return;
			}
			else if (rectangle[0].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true) rectangle[0].setFillColor(sf::Color::Green);
			else rectangle[0].setFillColor(sf::Color::Blue);

			if (rectangle[1].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				choice = 3;
				Game game{};
				game.play(game_window, choice);
				return;
			}
			else if (rectangle[1].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true) rectangle[1].setFillColor(sf::Color::Green);
			else rectangle[1].setFillColor(sf::Color::Blue);
			
		}
		game_window.clear(sf::Color(255, 0, 255));
		game_window.draw(rectangle[0]);
		game_window.draw(rectangle[1]);
		game_window.draw(text[0]);
		game_window.draw(text[1]);
		game_window.draw(text[2]);
		game_window.display();
	}
}
Menu::~Menu() {}
