
#include "Process.h"
#include <cmath>

int checkpos[8][2] = {
	{ -1, 1 },
	{ 0, 1 },
	{ 1, 1 },
	{ 1, 0 },
	{ 1, -1 },
	{ 0, -1 },
	{ -1, -1 },
	{ -1, 0 }
};

int lncheckpos[4][2] = {
	{ -1, 1 },
	{ 0, 1 },
	{ 1, 1 },
	{ 1, 0 },
};

void setWeight(Board *board)
{
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++) 
				board->pos[i][j].checked = false;

		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				if (board->pos[i][j].state == 1 && board->pos[i][j].checked == false)
				{
					/*
					int cnt = 0;
					int tx = i, ty = j;
					while (board->pos[tx][ty].state == 1 &&
						tx >= 0 && ty >= 0 && tx <= MAX && ty <= MAX)
					{
						cnt++;
						board->pos[tx][ty].checked = true;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX && j - checkpos[k][1] <= MAX)
					{
						if (board->pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							board->pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0) board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(2.1, cnt * cnt);
						else board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.8, cnt * cnt);
					}
					if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX && ty + checkpos[k][1] <= MAX)
					{
						if (board->pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							board->pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0) board->pos[tx][ty].weight *= pow(2.1, cnt * cnt);
						else board->pos[tx][ty].weight *= pow(1.8, cnt * cnt);
					}
					*/

					for (int k = 0; k < 8; k++)
					{
						int c = 1;
						int px = i, py = j;

						for (int n = 0; n < 4; n++)
						{
							px += checkpos[k][0];
							py += checkpos[k][1];

							if (board->pos[px][py].state == WHITE) break;

							if (board->pos[px][py].state == BLACK)
							{
								c++; n--;
								continue;
							}
							
							if (px >= 0 && py >= 0 && px < MAX && py < MAX)
							{
								if (board->pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 && c >= 2)
									board->pos[px][py].weight *= pow(1.3, ((double)(4.0 - n) * (double)c * c * c / 8.0));
								else
									board->pos[px][py].weight *= pow(1.3, ((double)(4.0 - n) * (double)c * c / 8.0));

							}
							else break;
						}
					}

					for (int k = 0; k < 8; k++)
					{
						int cnt = 0;
						int tx = i, ty = j;
						while (board->pos[tx][ty].state == BLACK &&
							tx >= 0 && ty >= 0 && tx < MAX && ty < MAX)
						{
							cnt++;
							tx += checkpos[k][0];
							ty += checkpos[k][1];
						}
						if (cnt == 4 && board->pos[tx][ty].state == 0) board->pos[tx][ty].weight *= 1000.0;
					}
				}

				if (board->pos[i][j].state == 2 && board->pos[i][j].checked == false)
				{
					for (int l = 0; l < 8; l++)
					{
						if (i + checkpos[l][0] >= 0 && j + checkpos[l][1] >= 0 && i + checkpos[l][0] < MAX && j + checkpos[l][1] < MAX)
							board->pos[i + checkpos[l][0]][j + checkpos[l][1]].weight *= 1.08;
					}

					int cnt = 0;
					int tx = i, ty = j;
					while (board->pos[tx][ty].state == 2 &&
						tx >= 0 && ty >= 0 && tx < MAX && ty < MAX)
					{
						cnt++;
						board->pos[tx][ty].checked = true;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					
					if (cnt > 1)
					{
						if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] < MAX && j - checkpos[k][1] < MAX)
							board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.1, cnt * cnt * 2);
						if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] < MAX && ty + checkpos[k][1] < MAX)
							board->pos[tx][ty].weight *= pow(1.1, cnt * cnt * 2);
					}

					for (int k = 0; k < 8; k++)
					{
						cnt = 0;
						tx = i, ty = j;
						while (board->pos[tx][ty].state == WHITE &&
							tx >= 0 && ty >= 0 && tx < MAX && ty < MAX)
						{
							cnt++;
							tx += checkpos[k][0];
							ty += checkpos[k][1];
						}
						if (cnt == 4 && board->pos[tx][ty].state == 0) board->pos[tx][ty].weight *= 1000.0;
					}
				}
			}
		}
	}
}

Point getMaxWeightPos(Board *board)
{
	double weight = 0.0;
	int x, y;

	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
		{
			if (board->pos[i][j].weight >= weight && board->pos[i][j].state == BLANK)
			{
				x = i, y = j;
				weight = board->pos[i][j].weight;
			}
		}
	return std::make_pair(x, y);
}

void doPut(State state, Board *board, Point pt)
{
	board->Put(state, pt.first, pt.second);
}

State getWinner(Board board)
{
	int cnt, tx, ty;
	bool p1win, p2win;

	p1win = p2win = false;

	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (board.pos[i][j].state == BLACK)
			{
				for (int k = 0; k < 8; k++)
				{
					cnt = 0;
					tx = i, ty = j;
					while (board.pos[tx][ty].state == BLACK &&
						tx >= 0 && ty >= 0 && tx < MAX && ty < MAX)
					{
						cnt++;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt == 5) p1win = true;
					else cnt = 0;
					if (p1win) break;
				}
			}
			if (p1win) break;
		}
		if (p1win) break;
	}
	if (p1win) return BLACK;


	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (board.pos[i][j].state == WHITE)
			{
				for (int k = 0; k < 8; k++)
				{
					cnt = 0;
					tx = i, ty = j;
					while (board.pos[tx][ty].state == WHITE &&
						tx >= 0 && ty >= 0 && tx < MAX && ty < MAX)
					{
						cnt++;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt == 5) p2win = true;
					else cnt = 0;
					if (p2win) break;
				}
			}
			if (p2win) break;
		}
		if (p2win) break;
	}
	if (p2win) return WHITE;
}