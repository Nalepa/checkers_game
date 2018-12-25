#include "stdafx.h"
#include "List_Item_Headline.h"

List_Item::List_Item(): Previous(nullptr), Next(nullptr), Actual_Board("plansza.jpg"), next_move_colour(black)
{
	

}
void List_Item::add_board()
{
	std::cout << "tworze element listy" << std::endl;
	Next = new List_Item();
	if (next_move_colour == white) Next->next_move_colour = black;
	else Next->next_move_colour = white;
	Next->Actual_Board = Actual_Board;
	Next->Previous = this;
}
void List_Item::delete_last_board()
{
	Next->Previous = nullptr;
	delete Next->Actual_Board.Tab;
	delete Next;
	Next = nullptr;
}
List_Item & List_Item::operator =(const List_Item  list_item1)
{
	next_move_colour = list_item1.next_move_colour;
	Previous = list_item1.Previous;
	Next = list_item1.Next;
	Actual_Board = list_item1.Actual_Board;
	std::cout << "Nie wywolam sie" << std::endl;
	return *this;
}
void List_Item::forward()
{

}
//List_Item::~List_Item(){}