#include "stdafx.h"
#include"Field_Headline.h"
#include"Board_Headline.h"
#include"Game_Headline.h"
#include"Automatic_Game_Saving_Headline.h"
#include "Game_Loading_Headline.h"

Game::Game():Ptr(new List_Item), during_the_beating(false), is_move(false), dx(0), dy(0)
{
	if (!font.loadFromFile("contm.ttf")) std::cout << "Nie udalo sie poprawnie wczytac czcionki" << std::endl;

	text[0].setString("Ruch maja pionki biale");
	text[0].setFont(font);
	text[0].setCharacterSize(50);
	text[0].setPosition(200, 0);
	text[0].setFillColor(sf::Color::Black);

	text[1].setString("Cofnij");
	text[1].setFont(font);
	text[1].setCharacterSize(45);
	text[1].setPosition(20, 150);
	text[1].setFillColor(sf::Color::Black);

	text[2].setString("Zapisz");
	text[2].setFont(font);
	text[2].setCharacterSize(40);
	text[2].setPosition(20, 250);
	text[2].setFillColor(sf::Color::Black);

	text[3].setString("Menu");
	text[3].setFont(font);
	text[3].setCharacterSize(40);
	text[3].setPosition(25, 350);
	text[3].setFillColor(sf::Color::Black);

	text[4].setString("zapisano gre");
	text[4].setFont(font);
	text[4].setCharacterSize(25);
	text[4].setPosition(2, 450);
	text[4].setFillColor(sf::Color::Black);

	rectangle[0].setSize(sf::Vector2f{ 120,60 });
	rectangle[0].setPosition(15, 150);
	rectangle[0].setFillColor(sf::Color::Blue);

	rectangle[1].setSize(sf::Vector2f{ 120,60 });
	rectangle[1].setPosition(15, 250);
	rectangle[1].setFillColor(sf::Color::Blue);

	rectangle[2].setSize(sf::Vector2f{ 120,60 });
	rectangle[2].setPosition(15, 350);
	rectangle[2].setFillColor(sf::Color::Blue);

	Ptr->Actual_Board.checkers_board.setPosition(sf::Vector2f(150, 70));
}
void Game::play(sf::RenderWindow &game_window, const int &choice)
{
	Automatic_Game_Saving auto_save{};

	if(choice == 1) add_new_game();
	else if(choice == 2) load_game("auto_save_data.txt");
	else load_game("save_data.txt");
	Ptr->Actual_Board.Display(); // pomocnicze na konsoli

	while (game_window.isOpen())
	{
		if (Ptr->Previous == nullptr)
		{
			Ptr->add_board();
			Ptr = Ptr->Next;
			Ptr->Actual_Board.check_clashing_posibility();
			statement_change();
		}
		if (auto_save.check_time() == true)
		{
			auto_save.set("auto_save_data.txt", Ptr);
			auto_save.Save();
		}
		mouse_position = sf::Mouse::getPosition(game_window);

		while (game_window.pollEvent(game_event))
		{
			//obsluga przycisku cofnij
			if (rectangle[0].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (Ptr->Previous->Previous != nullptr)
				{
					if (during_the_beating == true) Ptr = Ptr->Previous;
					else Ptr = Ptr->Previous->Previous;
					Ptr->delete_last_board();
					Ptr->add_board();
					Ptr = Ptr->Next;
					for (int i = 0; i < size*size; i++)
					{
						if (Ptr->Actual_Board.Tab[i].Pawn_ptr == nullptr) continue;
						float x_pos = Ptr->Actual_Board.Tab[i].default_circle_position_x;
						float y_pos = Ptr->Actual_Board.Tab[i].default_circle_position_y;
						Ptr->Actual_Board.Tab[i].Pawn_ptr->Circle_set_position(x_pos, y_pos);
					}
					during_the_beating = false;
					statement_change();
				}
				else std::cout << "nic sie nie stalo" << std::endl;
			}
			else if (rectangle[0].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true) rectangle[0].setFillColor(sf::Color::Green);
			else rectangle[0].setFillColor(sf::Color::Blue);

			//obsluga przycisku zapisz
			if (rectangle[1].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				Game_Saving save{ "save_data.txt", Ptr };
				save.Save();
			}
			else if (rectangle[1].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true) rectangle[1].setFillColor(sf::Color::Green);
			else rectangle[1].setFillColor(sf::Color::Blue);

			//obsluga przycisku menu
			if (rectangle[2].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				game_window.close();
				sf::ContextSettings settings;
				settings.antialiasingLevel = 8;

				Menu Menu1{ settings };
				Menu1.main_menu();
			}
			else if (rectangle[2].getGlobalBounds().contains(mouse_position.x, mouse_position.y) == true) rectangle[2].setFillColor(sf::Color::Green);
			else rectangle[2].setFillColor(sf::Color::Blue);
			
			if (game_event.type == sf::Event::Closed)
			{
				game_window.close();
			}
			if (game_event.type == sf::Event::KeyPressed && game_event.key.code == sf::Keyboard::Escape)
			{
				game_window.close();
			}

						if (game_event.type == sf::Event::MouseButtonPressed)
						{
							if (game_event.key.code == sf::Mouse::Left)
							{
								for (int line = 0; line < size; line++)
								{
									for(int column = 0; column < size; column++)
									{
										if (Ptr->Actual_Board.Tab[index(column,line,size)].Pawn_ptr != nullptr)
										{
											if (Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->Circle_getGlobalBounds_contains(mouse_position.x, mouse_position.y) == true)
											{
												is_move = true;
												first_index.column = column;
												first_index.line = line;
												dx = mouse_position.x - Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->Circle_get_position_x();
												dy = mouse_position.y - Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->Circle_get_position_y();
											}
										}
									}
								}
							}
						}

						if (game_event.type == sf::Event::MouseButtonReleased)
						{
							if (game_event.key.code == sf::Mouse::Left)
							{
								if (is_move == true)
								{
									is_move = false;
									
									movement_support(first_index, Ptr->Actual_Board.check_mouse_position(mouse_position.x, mouse_position.y));
								}
							}
						}
						if (is_move == true) Ptr->Actual_Board.Tab[index(first_index.column,first_index.line,size)].Pawn_ptr->Circle_set_position(mouse_position.x - dx, mouse_position.y - dy);
					}
					
			game_window.clear(sf::Color(156, 164, 214));
			game_window.draw(Ptr->Actual_Board.checkers_board);
			game_window.draw(rectangle[0]);
			game_window.draw(rectangle[1]);
			game_window.draw(rectangle[2]);
			game_window.draw(text[0]);
			game_window.draw(text[1]);
			game_window.draw(text[2]);
			game_window.draw(text[3]);

			if (auto_save.get_statement_time() == true)
			{
				game_window.draw(text[4]);
			}
			for (int i = 0; i < size * size; i++)
			{
				if (Ptr->Actual_Board.Tab[i].Pawn_ptr == nullptr) continue;
				Ptr->Actual_Board.Tab[i].Pawn_ptr->draw(game_window);
			}
			game_window.display();
		}
	}
void Game::add_new_game()
{
	Ptr->Actual_Board.initial_positions();
}
void Game::load_game(const std::string &file_name)
{
	Game_Loading game_loading{ file_name };
	Ptr = game_loading.Load();
}
void Game::movement_support(const field_index &first_index, const field_index &second_index)
{
	std::cout << index(first_index, size) << " " << index(second_index,size) << std::endl;
	Ptr->Actual_Board.check_clashing_posibility();
	
	
		if (Ptr->Actual_Board.check_move(first_index, second_index, Ptr->next_move_colour, during_the_beating, beating_pawn) == false)
		{
			int circle_pom_x = Ptr->Actual_Board.Tab[index(first_index, size)].default_circle_position_x;
			int circle_pom_y = Ptr->Actual_Board.Tab[index(first_index, size)].default_circle_position_y;
			Ptr->Actual_Board.Tab[index(first_index, size)].Pawn_ptr->Circle_set_position(circle_pom_x, circle_pom_y);
		}
		else
		{
			if (during_the_beating == false)
			{
				check_pawn_to_queen_transformation(second_index);
				Ptr->Actual_Board;
				Ptr->add_board();
				Ptr = Ptr->Next;
			}
			else
			{
				int circle_pom_x = Ptr->Actual_Board.Tab[index(second_index, size)].default_circle_position_x;
				int circle_pom_y = Ptr->Actual_Board.Tab[index(second_index, size)].default_circle_position_y;
				Ptr->Actual_Board.Tab[index(second_index, size)].Pawn_ptr->Circle_set_position(circle_pom_x, circle_pom_y);
			}

		}
		statement_change();
		check_result();
		
}
void Game::statement_change()
{
	if (Ptr->next_move_colour == white)
	{

		text[0].setString("Ruch maja pionki biale");
		text[0].setPosition(200, 0);
	}
	else
	{

		text[0].setString("Ruch maja pionki czarne");
		text[0].setPosition(200, 0);
	}
}
void Game::check_result()
{
	int number_of_white = 0, number_of_black = 0;
	for (int line = 0; line < size; line++)
	{
		for (int column = 0; column < size; column++)
		{
			if (Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr != nullptr)
			{
				if (Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->get_colour() == white) number_of_white++;
				else number_of_black++;
			}
		}
	}
	if (number_of_white == 0)
	{
		text[0].setString("Wygrywaja pionki czarne");
		text[0].setPosition(200, 0);
		during_the_beating = false;
		return;
	}
	if (number_of_black == 0)
	{
		text[0].setString("Wygrywaja pionki biale");
		text[0].setPosition(200, 0);
		during_the_beating = false;
		return;
	}
	field_index temp_index;
	if (Ptr->next_move_colour == white) // ruch maja biale
	{
		for (int line = 0; line < size; line++)
		{
			for (int column = 0; column < size; column++)
			{
				if (Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr != nullptr)
				{
					if (Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->get_colour() == white)
					{
						temp_index.column = column;
						temp_index.line = line;
						if (Ptr->Actual_Board.check_clashing_posibility(temp_index) == true) return;
						if (Ptr->Actual_Board.check_move_posibility(temp_index) == true) return;
					}
				}
			}
		}
	}
	else // ruch maja czarne
	{
		for (int line = 0; line < size; line++)
		{
			for (int column = 0; column < size; column++)
			{
				if (Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr != nullptr)
				{
					if (Ptr->Actual_Board.Tab[index(column, line, size)].Pawn_ptr->get_colour() == black)
					{
						temp_index.column = column;
						temp_index.line = line;
						if (Ptr->Actual_Board.check_clashing_posibility(temp_index) == true) return;
						if (Ptr->Actual_Board.check_move_posibility(temp_index) == true) return;
					}
				}
			}
		}
	}
	if (Ptr->next_move_colour == white) text[0].setString("Wygrywaja czarne (biale zablokowane)");
	else text[0].setString("Wygrywaja biale (czarne zablokowane)");

	text[0].setPosition(25, 0);
	during_the_beating = false;
}
void Game::check_pawn_to_queen_transformation(const field_index &temp_index)
{
	if (Ptr->Actual_Board.Tab[index(temp_index, size)].Pawn_ptr->get_type() == pawn)
	{
		if (Ptr->Actual_Board.Tab[index(temp_index, size)].Pawn_ptr->get_colour() == white) // bialy pionek
		{
			if (temp_index.line == 0) Ptr->Actual_Board.Tab[index(temp_index, size)].Pawn_ptr->pawn_to_queen_transformation();
		}
		else // czarny pionek
		{
			if (temp_index.line == size - 1)  Ptr->Actual_Board.Tab[index(temp_index, size)].Pawn_ptr->pawn_to_queen_transformation();
		}
	}
}
Game::~Game()
{
	List_Item *Temp;
	while (Ptr != nullptr)
	{
		Temp = Ptr;
		Ptr = Temp->Previous;
		delete Temp;
	}
}
int index(const int &width,const int &height,const int &size)
{
	return height * size + width;
}
int index(const field_index &index_pom,const int &size)
{
	return index_pom.line * size + index_pom.column;
}
