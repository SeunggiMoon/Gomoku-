
#include "AI.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

void gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main(void)
{
	while (true)
	{
		Board board;
		int record[361][2] = { 0 };

		int x, y, putcnt;
		bool put;
		bool helpMode = false;
		char playerName[512] = "";

		Point helpPos;
		Point prevHelpPos = std::make_pair(0, 0);

		system("cls");
		setColor(7);

		printf("\n Gomoku++ v3.2\n\n ⓒ 2016~2018 Naissoft. All rights reserved.\n\n 조작키 : w, s, a, d, 돌 놓기 : Space, Assistance Mode : H\n");
		printf("\n 시작하려면 플레이어 이름을 입력하시고 Enter를 누르세요.\n");
		scanf(" %s", playerName);

		system("cls");

		for (int i = 0; i < MAX * 2; i += 2)
		{
			for (int j = 0; j < MAX; j++)
				gotoxy(i, j), printf("┼");
			printf("\n");
		}

		x = y = putcnt = 0;

		while (true)
		{
			gotoxy(1, 20); printf("%s's turn", playerName);
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
					if (y < MAX - 1) y++;
					gotoxy(x * 2, y);
					break;
				case 'a':
					if (x > 0) x--;
					gotoxy(x * 2, y);
					break;
				case 'd':
					if (x < MAX - 1) x++;
					gotoxy(x * 2, y);
					break;
				case ' ':
					if (board.pos[x][y].state == BLANK)
					{
						record[putcnt][0] = x, record[putcnt][1] = y;
						putcnt++;
						doPut(BLACK, &board, std::make_pair(x, y));
						printf("●");
						gotoxy(x * 2, y);
						put = true;
					}
					break;
				case 'h':
				case 'H':
					(helpMode) ? helpMode = false : helpMode = true;
					break;
				}
				gotoxy(1, 21); printf(" Weight : %f                                   ", board.pos[x][y].weight);
				gotoxy(x * 2, y);

				if (helpMode)
				{
					if (board.pos[prevHelpPos.first][prevHelpPos.second].state == BLANK)
					{
						gotoxy(prevHelpPos.first * 2, prevHelpPos.second);
						printf("┼");
					}
					helpPos = getMaxWeightPos(&board);
					gotoxy(helpPos.first * 2, helpPos.second);
					setColor(4);
					printf("┼");
					setColor(7);

					prevHelpPos = helpPos;
					gotoxy(x * 2, y);
				}
			}

			put = false;

			if (getWinner(board) == BLACK) break;
			Sleep(500);

			gotoxy(1, 20); printf("AI's turn                                    ");
				
			for (int i = 0; i < MAX; i++)
				for (int j = 0; j < MAX; j++)
					board.pos[i][j].weight = 1.0;

			put = false;
			while (!put)
			{
				setWeight(&board);
				Point pt = AISetPos(board);

				if (board.pos[pt.first][pt.second].state == BLANK)
				{
					
					record[putcnt][0] = pt.first, record[putcnt][1] = pt.second;
					putcnt++;
					doPut(WHITE, &board, pt);
					gotoxy(pt.first * 2, pt.second);
					printf("○");
					put = true;
				}
			}
			put = false;

			if (getWinner(board) == WHITE) break;
			Sleep(500);
		}
		Sleep(500);
		gotoxy(1, 20);
		printf(" %s이(가) %d수 만에 우승했습니다!", (getWinner(board) == BLACK) ? playerName : "AI", putcnt);
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
					gotoxy(i, j), printf("┼");
				printf("\n");
			}

			for (int i = 0; i < putcnt; i++)
			{
				gotoxy(record[i][0] * 2, record[i][1]);
				if (board.pos[record[i][0]][record[i][1]].state == 1)
					printf("●");
				else if (board.pos[record[i][0]][record[i][1]].state == 2)
					printf("○");
				getch();
			}
		}
	}	
	return 0;
}
