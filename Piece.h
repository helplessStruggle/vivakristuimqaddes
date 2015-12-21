#pragma once
#include <string>
#include <iostream>

class Piece
{
private:
	bool color;
	int x;
	int y;

public:
	Piece(int,int,bool);
	int getX();
	int getY();
	void setX(int);
	void setY(int);
	void setColor(bool color);
	bool getColor();
	bool movePiece(int x, int y);
};
