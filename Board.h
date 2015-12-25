#pragma once
#include "Piece.h"

class Board
{
public:
	Piece *board[8][8];
	Piece *getPiece(int x, int y) { return Board::board[y][x]; }
	//returns a pointer to a piece
	 Board();
	~Board();
	std::string toString();
	bool isValid(int, int, int, int, bool);
	bool movePiece(int, int, int, int, bool);
	bool isKingValid(int, int, bool);
	bool eat(int, int, int, int, bool);
	bool gameOver();
	bool checkCanEat(int, int, bool);
	bool isCoordValid(int, int);
	bool checkBlank(int, int, bool);
	bool eat2(int i, int j, int dest_x, int dest_y, bool color);

private:
	int whitePiece = 0;
	int redPiece = 0;
};
