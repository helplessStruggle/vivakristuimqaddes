#include "Piece.h"


//Constuctor
Piece::Piece(int g_x, int g_y, bool g_color)
{
	Piece::x = g_x;
	Piece::y = g_y;
	Piece::color = g_color;
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

bool Piece::movePiece(int x, int y) {
	getPiece(x1, y1);
}
