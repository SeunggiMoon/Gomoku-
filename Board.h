#pragma once

class Point
{
public:
	Point(int x, int y)
	{
		X = x;
		Y = y;
	}
	int X;
	int Y;
};

struct space
{
	int state;
	double weight;
	bool ifOccupied;
};

class Board
{
public:
	space pos[15][15] = { 0, 0.0, false };
	int ex = 7;
	int ey = 7;
	void DoMove(Point, int);
};