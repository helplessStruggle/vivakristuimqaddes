#pragma once
#include "Piece.h"

class Board
{
public:
	Piece *board[8][8];
	Board();
	~Board();
	std::string toString();
	bool isValid(int, int, bool, int, int);
	bool movePiece(int, int, bool, int, int);
	bool isKingValid(int, int, bool);
	bool letsGetFat(int, int, bool);
};
