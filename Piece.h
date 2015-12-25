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
	Piece(int, int, bool, bool kingBool = true); //what the fuck is this kingBOol doing here
	int getX();
	int getY();
	void setX(int);
	void setY(int);
	void setColor(bool color);
	bool getColor();
	bool kingBool = false;
	bool isKing() { return kingBool; }
	void setKing(bool value) { Piece::kingBool = value; }
};
