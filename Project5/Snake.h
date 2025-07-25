#pragma once
#include <tuple>
#include <list>
class Board; // Forward declaration

typedef enum diraction
{
	u,	// up
	d,	// down
	l,	// left
	r	// right
}Dircation;

class Snake
{
public:
	Snake(int startX, int startY, int initialLength = 5);
	~Snake();
	void change_diraction(Dircation new_diraction);
	bool move(void);
	void eat(int x, int y);
	std::list<std::tuple<int, int>> get_body(void) const;
private:
	int _length; // the length of the snake
	std::list<std::tuple<int, int>> body; // list of coordinates for the snake body nodes
	Dircation diraction;
	Board* board;
};


