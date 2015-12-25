#include "Piece.h"
#include "Board.h"
//Constuctor
Piece::Piece(int g_x, int g_y, bool g_color, bool g_kingBool)
{
	Piece::x = g_x;
	Piece::y = g_y;
	Piece::color = g_color;
	Piece::kingBool = g_kingBool;
}

//Setters and Getters
void Piece::setX(int g_x) {
	Piece::x = g_x;
}

void Piece::setY(int g_y) {
	Piece::y = g_y;
}

void Piece::setColor(bool g_color) {
	Piece::color = g_color;
}

int Piece::getX() {
	return x;
}

int Piece::getY() {
	return y;
}

bool Piece::getColor() {
	return color;
}
