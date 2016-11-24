
#include "AI.h"

Point AISetPos(Board board)
{
	int ex, ey;
	double max_weight;

	ex = ey = 0;
	max_weight = 1.0;

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (board.pos[i][j].weight > max_weight && board.pos[i][j].state == 0)
			{
				ex = i, ey = j;
				max_weight = board.pos[i][j].weight;
			}
		}
	}

	Point pt = std::make_pair(ex, ey);
	return pt;
}