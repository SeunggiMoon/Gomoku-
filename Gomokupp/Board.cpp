#include "Board.h"

void Board::Put(State state, int x, int y)
{
	Board::pos[x][y].ifOccupied = true;
	Board::pos[x][y].state = state;
}