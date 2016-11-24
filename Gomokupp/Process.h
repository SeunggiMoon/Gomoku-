#pragma once

#include "Board.h"

void setWeight(Board *board);

void doPut(State state, Board *board, Point pt);

State getWinner(Board board);