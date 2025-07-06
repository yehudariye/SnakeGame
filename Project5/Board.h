#pragma once
#include "Snake.h"
class Board
{
public:
	Board(MT mapType);
	~Board();
	cell what_is_next_point(int x, int y);
	void draw(Snake& sk);


private:
	int _width;
	int _height;
	cell _grid[100][100];
};

typedef enum MapType
{
	squre,
	blink
}MT;

typedef enum cell
{
	food,
	wall,
	tail,
	empty
}cell;

