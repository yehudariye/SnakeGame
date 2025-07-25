#include "Board.h"
#include "Snake.h"
#include <exception>

Board::Board(MT mapType)
{
	this->_width = 100;
	this->_height = 100;
	switch (mapType)
	{	   
	case blink:
		for (int i = 0; i < _width; i++)
		{
			for (int j = 0; j < _height; j++)
			{
				this->_grid[i][j] = empty;
			}
		}
		break;
	default:
		break;
	}

}

Board::~Board()
{
}

cell Board::what_is_next_point(int x, int y)
{
	if (x >= 100 || y >= 100)
	{
		throw std::exception("illigel pos");
	}
	else
	{
		return this->_grid[x][y];
	}
	return wall;
}

void Board::draw(Snake& sk)
{
}
