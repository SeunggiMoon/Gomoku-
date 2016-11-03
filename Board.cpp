
#include "Board.h"

void Board::DoMove(Point pt, int color)
{
	if (color == 1) pos[pt.X][pt.Y].state = 1;
	else pos[pt.X][pt.Y].state = 2;
}

void Board::Clear()
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			pos[i][j].ifOccupied = false;
			pos[i][j].state = 0;
			pos[i][j].weight = 0.0;
		}
	}

	ex = ey = 7;
}