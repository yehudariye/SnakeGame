#include "Snake.h"
#include "Board.h"

Snake::Snake(int startX, int startY, int initialLength)
{
	board = new Board(blink);
	_length = initialLength;
	diraction = u;
	body.push_front(std::make_tuple(startX, startY)); // place the snake heads
}

Snake::~Snake()
{
	delete board;
}

void Snake::change_diraction(Dircation new_diraction)
{
	this->diraction = new_diraction;
}

bool Snake::move(void)
{	
	int x = std::get<0>(body.front()), y = std::get<1>(body.front());
	switch (diraction)
	{
	case u:
		y += 1;
		break;
	case d:
		x, y -= 1;
		break;
	case l:
		x -= 1;
		break;
	case r:
		x += 1;
		break;
	default:
		break;
	}

	// provent out of range case
	x = x % 100;   
	y = y % 100;

	switch (board->what_is_next_point(x, y))
	{
	// game ended cases
	case wall: 
		return false;
		break;
	case tail:
		return false;
		break;

	case food:
		eat(x, y);
		break;

	case empty:
		body.pop_back(); // move on
		break;
	}

	body.push_front(std::make_tuple(x, y));
	return true;
}

void Snake::eat(int x, int y)
{
	_length++;
}

std::list<std::tuple<int, int>> Snake::get_body(void) const
{
	return this->body;
}
