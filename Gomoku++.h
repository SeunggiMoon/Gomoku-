#pragma once

#include "Board.h"

class Gomokupp
{
public:
	Gomokupp();
	~Gomokupp();

	Point GetMove();
	void Move(Point pt, int color);
	void Process();
	int CheckWinner();
	Board* board;
private:

};
  