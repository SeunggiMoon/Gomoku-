#pragma once

#include <utility>
#define MAX 19

typedef enum {BLANK, BLACK, WHITE} State;
typedef std::pair<int, int> Point;

struct Pos
{
	State state;
	bool checked;
	double weight;
};

class Board
{
public:
	Pos pos[MAX][MAX] = { BLANK, false, 1.0 };
public:
	void Put(State state, int x, int y);
};