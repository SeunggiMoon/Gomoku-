#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>

#define MAX 19

struct space
{
	int state;
	double weight;
	bool checked;
};

space pos[MAX][MAX] = { 0, 1.0, false };
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

int record[361][2] = { 0 };

void AI()
{
	for (int k = 0; k < 4; k++)
	{
		for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			pos[i][j].checked = false;

		for (int i = 0; i < MAX; i++)
		{
			for (int j = 0; j < MAX; j++)
			{
				if (pos[i][j].state == 1 && pos[i][j].checked == false)
				{
					int cnt = 0;
					int tx = i, ty = j;
					while (pos[tx][ty].state == 1 &&
						tx >= 0 && ty >= 0 && tx <= MAX && ty <= MAX)
					{
						cnt++;
						pos[tx][ty].checked = true;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX && j - checkpos[k][1] <= MAX)
					{
						if (pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0) pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(2.1, cnt * cnt);
						else pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.8, cnt * cnt);
					}
					if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX && ty + checkpos[k][1] <= MAX)
					{
						if (pos[i - checkpos[k][0]][j - checkpos[k][1]].state == 0 &&
							pos[tx + checkpos[k][0]][ty + checkpos[k][1]].state == 0) pos[tx][ty].weight *= pow(2.1, cnt * cnt);
						else pos[tx][ty].weight *= pow(1.8, cnt * cnt);
					}
				}

				if (pos[i][j].state == 2 && pos[i][j].checked == false)
				{
					for (int l = 0; l < 8; l++)
					{
						if (i + checkpos[l][0] >= 0 && j + checkpos[l][1] >= 0 && i + checkpos[l][0] <= MAX && j + checkpos[l][1] <= MAX)
							pos[i + checkpos[l][0]][j + checkpos[l][1]].weight *= 1.08;
					}

					int cnt = 0;
					int tx = i, ty = j;
					while (pos[tx][ty].state == 2 &&
						tx >= 0 && ty >= 0 && tx <= MAX && ty <= MAX)
					{
						cnt++;
						pos[tx][ty].checked = true;
						tx += checkpos[k][0];
						ty += checkpos[k][1];
					}
					if (cnt > 1)
					{
						if (i - checkpos[k][0] >= 0 && j - checkpos[k][1] >= 0 && i - checkpos[k][0] <= MAX && j - checkpos[k][1] <= MAX)
							pos[i - checkpos[k][0]][j - checkpos[k][1]].weight *= pow(1.2, cnt * cnt * 2);
						if (tx + checkpos[k][0] >= 0 && ty + checkpos[k][1] >= 0 && tx + checkpos[k][0] <= MAX && ty + checkpos[k][1] <= MAX)
							pos[tx][ty].weight *= pow(1.2, cnt * cnt * 2);
					}
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
	int x, y, ex, ey, tx, ty, cnt, putcnt;
	bool put, p1win, p2win;
	double max_weight;
	char playerName[512] = "";

	printf("\n Gomoku++ v1.2\n\n ⓒ 2016 Naissoft all rights reserved.\n\n 조작키 : w, s, a, d, 돌 놓기 Space\n");
	printf("\n 시작하려면 플레이어 이름을 입력하시고 Enter를 누르세요.");
	scanf(" %s", playerName);

	while (1)
	{
		system("cls");

		for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			pos[i][j].state = 0, pos[i][j].weight = 1.0;

		for (int i = 0; i < 361; i++) record[i][0] = record[i][1] = 0;

		for (int i = 0; i < MAX * 2; i += 2)
		{
			for (int j = 0; j < MAX; j++)
				gotoxy(i, j), printf("·");
			printf("\n");
		}

		x = y = ex = ey = tx = ty = putcnt = 0;
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
						record[putcnt][0] = x, record[putcnt][1] = y;
						putcnt++;
						pos[x][y].state = 1;
						printf("●");
						gotoxy(x * 2, y);
						put = true;
					}
					break;
				}
				gotoxy(1, 21); printf(" Weight : %f                                   ", pos[x][y].weight);
				gotoxy(x * 2, y);
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
					record[putcnt][0] = ex, record[putcnt][1] = ey;
					putcnt++;
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
		printf(" %s이(가) %d수 만에 우승했습니다!", (p1win > p2win) ? playerName : "AI", putcnt);
		printf("\n\n 다시 하시겠습니까? Y / N, 리플레이 : R");

		char ch;
		scanf(" %c", &ch);

		if (ch == 'N') break;
		else if (ch == 'Y') system("cls");
		else if (ch == 'R')
		{
			system("cls");
			for (int i = 0; i < MAX * 2; i += 2)
			{
				for (int j = 0; j < MAX; j++)
					gotoxy(i, j), printf("·");
				printf("\n");
			}

			for (int i = 0; i < putcnt; i++)
			{
				gotoxy(record[i][0] * 2, record[i][1]);
				if (pos[record[i][0]][record[i][1]].state == 1)
					printf("●");
				else if (pos[record[i][0]][record[i][1]].state == 2)
					printf("○");
				getch();
			}
		}
	}
	return 0;
}