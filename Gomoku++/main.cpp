#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>

#define MAX 19

struct space
{
	int state;
	double weight;
};

space pos[MAX][MAX] = { 0, 1.0 };
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

void AI()
{
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			if (pos[i][j].state == 1)
			{
				for (int k = 0; k < 8; k++)
				{
					if (i + checkpos[k][0] >= 0 && j + checkpos[k][1] >= 0 && i + checkpos[k][0] <= MAX && j + checkpos[k][1] <= MAX)
						pos[i + checkpos[k][0]][j + checkpos[k][1]].weight *= 1.05;
				}
				for (int k = 0; k < 8; k++)
				{
					int cnt = 0;
					int tx = i, ty = j;
					while (pos[tx][ty].state == 1 &&
					tx >= 0 && ty >= 0 && tx <= MAX && ty <= MAX)
					{
						cnt++;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX && j - checkpos[k][1] <= MAX)
						for (int l = 0; l < cnt; l++) pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(3.2, (cnt + 1));
					if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX && ty + checkpos[k][1] <= MAX)
						for (int l = 0; l < cnt; l++) pos[tx][ty].weight *= pow(3.2, (cnt + 1));
				}
			}

			if (pos[i][j].state == 2)
			{
				for (int k = 0; k < 8; k++)
				{
					if (i + checkpos[k][0] >= 0 && j + checkpos[k][1] >= 0 && i + checkpos[k][0] <= MAX && j + checkpos[k][1] <= MAX)
						pos[i + checkpos[k][0]][j + checkpos[k][1]].weight *= 1.02;
				}
				for (int k = 0; k < 8; k++)
				{
					int cnt = 0;
					int tx = i, ty = j;
					while (pos[tx][ty].state == 2 &&
						tx >= 0 && ty >= 0 && tx <= MAX && ty <= MAX)
					{
						cnt++;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX && j - checkpos[k][1] <= MAX)
						for (int l = 0; l < cnt; l++) pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(2.0, (cnt));
					if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX && ty + checkpos[k][1] <= MAX)
					for (int l = 0; l < cnt; l++) pos[tx][ty].weight *= pow(2.0, (cnt));
				}
			}
		}
	}
}

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main(void)
{

	int x, y, ex, ey, tx, ty, cnt;
	bool put, p1win, p2win;
	double max_weight;

	printf("\n Gomoku++ v1.0\n\n ⓒ 2016 Naissoft all rights reserved.\n\n 조작키 : w, s, a, d, 돌 놓기 Space\n");
	printf("\n 시작하려면 Enter를 누르세요.");
	getchar();

	while (1)
	{
		system("cls");

		for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			pos[i][j].state = 0, pos[i][j].weight = 1.0;

		for (int i = 0; i < MAX * 2; i += 2)
		{
			for (int j = 0; j < MAX; j++)
				gotoxy(i, j), printf("·");
			printf("\n");
		}

		x = y = ex = ey = tx = ty = 0;
		p1win = p2win = false;
		max_weight = 0.0;

		while (1)
		{
			gotoxy(1, 20); printf("Your turn");
			gotoxy(x * 2, y);

			put = false;
			while (!put)
			{
				switch (getch())
				{
				case 'w':
					if (y > 0) y--;
					gotoxy(x * 2, y);
					break;
				case 's':
					if (y < MAX) y++;
					gotoxy(x * 2, y);
					break;
				case 'a':
					if (x > 0) x--;
					gotoxy(x * 2, y);
					break;
				case 'd':
					if (x < MAX) x++;
					gotoxy(x * 2, y);
					break;
				case ' ':
					if (pos[x][y].state == 0)
					{
						pos[x][y].state = 1;
						printf("●");
						gotoxy(x * 2, y);
						put = true;
					}
					break;
				}
			}

			put = false;

			for (int i = 0; i < MAX; i++)
			{
				for (int j = 0; j < MAX; j++)
				{
					if (pos[i][j].state == 1)
					{
						for (int k = 0; k < 8; k++)
						{
							cnt = 0;
							tx = i, ty = j;
							while (pos[tx][ty].state == 1 &&
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
			if (p1win) break;
			Sleep(500);

			gotoxy(1, 20); printf("AI's turn");

			for (int i = 0; i < MAX; i++)
			for (int j = 0; j < MAX; j++)
				pos[i][j].weight = 1.0;

			put = false;
			while (!put)
			{
				AI();
				ex = ey = 0;
				max_weight = 0.0;

				for (int i = 0; i < MAX; i++)
				{
					for (int j = 0; j < MAX; j++)
					{
						if (pos[i][j].weight > max_weight && pos[i][j].state == 0)
						{
							ex = i, ey = j;
							max_weight = pos[i][j].weight;
						}
					}
				}
				
				if (pos[ex][ey].state == 0)
				{
					pos[ex][ey].state = 2;
					gotoxy(ex * 2, ey);
					printf("○");
					put = true;
				}
			}

			put = false;

			for (int i = 0; i < MAX; i++)
			{
				for (int j = 0; j < MAX; j++)
				{
					if (pos[i][j].state == 2)
					{
						for (int k = 0; k < 8; k++)
						{
							cnt = 0;
							tx = i, ty = j;
							while (pos[tx][ty].state == 2 &&
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
			if (p2win) break;
			Sleep(500);
		}
		Sleep(1000);
		gotoxy(1, 20);
		printf(" %s가 우승했습니다!", (p1win > p2win) ? "플레이어" : "AI");
		printf("\n\n 다시 하시겠습니까? Y / N");

		if (getch() == 'N') break;
		else system("cls");
	}
	return 0;
}
