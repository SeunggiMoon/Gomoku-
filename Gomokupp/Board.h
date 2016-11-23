#pragma once

#define MAX 19

typedef enum {BLANK, BLACK, WHITE} State;

struct Point
{
	State state;
	bool ifOccupied;
	double weight;
};

class Board
{
public:
	Point pos[MAX][MAX] = { BLANK, false, 0.0 };
public:
	Board();
	void Put(State state, int x, int y);
};