#include "Gomoku++.h"

#include <random>
#include <ctime>

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

Gomokupp::Gomokupp()
{
	board = new Board;
}

Gomokupp::~Gomokupp()
{
	delete board;
}

Point Gomokupp::GetMove()
{
	Process();
	Point pt = Point(board->ex, board->ey);

	return pt;
}

void Gomokupp::Move(Point pt, int color)
{
	board->DoMove(pt, color);
}

void Gomokupp::Process()
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 15; j++)
			board->pos[i][j].weight = 1.0;

	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < 15; i++)
			for (int j = 0; j < 15; j++)
				board->pos[i][j].ifOccupied = false;

		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (board->pos[i][j].state == 1 && board->pos[i][j].ifOccupied == false)
				{
					int cnt = 0;
					int tx = i, ty = j;
					while (board->pos[tx][ty].state == 1 &&
						tx >= 0 && ty >= 0 && tx <= 15 && ty <= 15)
					{
						cnt++;
						board->pos[tx][ty].ifOccupied = true;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= 15 && j - checkpos[k][1] <= 15)
					{
						if (board->pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							board->pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0)board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(2.1, cnt * cnt);
						else board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.8, cnt * cnt);
					}
					if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= 15 && ty + checkpos[k][1] <= 15)
					{
						if (board->pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							board->pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0) board->pos[tx][ty].weight *= pow(2.1, cnt * cnt);
						else board->pos[tx][ty].weight *= pow(1.8, cnt * cnt);
					}
				}

				if (board->pos[i][j].state == 2 && board->pos[i][j].ifOccupied == false)
				{
					for (int l = 0; l < 8; l++)
					{
						if (i + checkpos[l][0] >= 0 && j + checkpos[l][1] >= 0 && i + checkpos[l][0] <= 15 && j + checkpos[l][1] <= 15)
							board->pos[i + checkpos[l][0]][j + checkpos[l][1]].weight *= 1.08;
					}

					int cnt = 0;
					int tx = i, ty = j;
					while (board->pos[tx][ty].state == 2 &&
						tx >= 0 && ty >= 0 && tx <= 15 && ty <= 15)
					{
						cnt++;
						board->pos[tx][ty].ifOccupied = true;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt > 1)
					{
						if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= 15 && j - checkpos[k][1] <= 15)
							board->pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.2, cnt * cnt * 2);
						if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= 15 && ty + checkpos[k][1] <= 15)
							board->pos[tx][ty].weight *= pow(1.2, cnt * cnt * 2);
					}
				}
			}
		}
	}

	double max_weight = 0.0;

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (board->pos[i][j].weight > max_weight && board->pos[i][j].state == 0)
			{
				board->ex = i, board->ey = j;
				max_weight = board->pos[i][j].weight;
			}
		}
	}

	board->pos[board->ex][board->ey].state = 2;
}