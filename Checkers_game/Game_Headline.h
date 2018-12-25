#pragma once
#include "List_Item_Headline.h"
//#include "Automatic_Game_Saving_Headline.h"

class Game
{
	int dx, dy;
	const int size = 8; // do usuniecia
	List_Item* Head;
	sf::Font font;
	sf::Text text[5];
	sf::RectangleShape rectangle[3];
	sf::Event game_event;
	sf::Vector2i mouse_position;
	bool during_the_beating, is_move;
	field_index beating_pawn, first_index;
public:
	Game();
	void add_new_game();
	void load_game(const std::string &file_name);
	void play(sf::RenderWindow &game_window, const int &choice);
	void movement_support(const field_index &first_index, const field_index &second_index);
	void statement_change();
	void check_result();
	void check_pawn_to_queen_transformation(const field_index &temp_index);
	~Game();
	friend class Field;
	friend class Board;
	friend class List_Item;
 };
int index(const int &height, const int &width, const int &size);
int index(const field_index &index_pom, const int &size);

