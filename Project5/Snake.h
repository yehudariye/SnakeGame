#pragma once
#include <tuple>
#include <list>
#include "Board.h"	// error circle of refernece

class Snake
{
public:
	Snake(int startX, int startY, int initialLength = 5);
	~Snake();
	bool move(void);
	void eat(int x, int y);
private:
	int _length; // the length of the snake
	std::list<std::tuple<int, int>> body; // list of coordinates for the snake body nodes
	Dircation diraction;
	Board* board;
};

typedef enum diraction
{
	u,	// up
	d,	// down
	l,	// left
	r	// right
}Dircation;

