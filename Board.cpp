
#include "Board.h"

void Board::DoMove(Point pt, int color)
{
	if (color == 1) pos[pt.X][pt.Y].state = 1;
	else pos[pt.X][pt.Y].state = 2;
} 