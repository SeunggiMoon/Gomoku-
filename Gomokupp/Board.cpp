
#include "Board.h"

void Board::Put(State state, int x, int y)
{
	Board::pos[x][y].state = state;
}