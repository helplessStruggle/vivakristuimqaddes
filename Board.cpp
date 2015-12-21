#include "Board.h"
#include <cmath>
//true white top x
//false red bottom o
//i = yaxis
//j = xaxis
Board::Board() {
	for (int i = 0; i < 8; i++) {
	for (int j = 0; j < 8; j++) {
	if (i < 3) {
		if (i % 2 == 0) {
			if (j % 2 == 0) {
				Board::board[i][j] = new Piece(j, i, true);
			}
			else {
				Board::board[i][j] = nullptr;
			}
		}
		else {
			if (j % 2 != 0) {
				Board::board[i][j] = new Piece(j, i, true);
			}
			else {
				Board::board[i][j] = nullptr;
			}
		}

	}
	else if (i >= 5) {
		if (i % 2 == 0) {
			if (j % 2 == 0) {
				Board::board[i][j] = new Piece(j, i, false);
			}
			else {
				Board::board[i][j] = nullptr;
			}
		}
		else {
			if (j % 2 != 0) {
				Board::board[i][j] = new Piece(j, i, false);
			}
			else {
				Board::board[i][j] = nullptr;
			}
		}
	}
	else {
		Board::board[i][j] = nullptr;
	}
}
	}
}


Board::~Board() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board::board[i][j] != nullptr) {
				delete[] Board::board[i][j];
			}
		}
	}
}

std::string Board::toString() {
	std::string temp = "";
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (Board::board[i][j] != nullptr) {
				if (Board::board[i][j]->getColor() == true) {
					temp += "x ";
				}
				else {
					temp += "o ";
				}
			}
			else {
				temp += ". ";
			}
		}
		temp += "\n";
	}
	return temp;
}
//user jitfa (ij,xy)
bool Board::isValid(int i, int j, bool getColor, int dest_x, int dest_y) {
	Piece *tmpPiece = Board::board[i][j];
	if (tmpPiece == nullptr) {
		return false;
	}
	else if ((dest_x > 8) || (dest_y > 8) || (dest_x < 0) || (dest_y < 0)) {
		return false;
	}
	else if (((dest_x - i) == std::abs(1) || ((dest_y - j)) == std::abs(1))) { //making sure a piece can only move 1 square, 1 up or 1 down
		return false;
	}
}

bool Board::movePiece(int i, int j, bool getColor, int dest_x, int dest_y) {
	if (Board::isValid(i, j, getColor, dest_x, dest_y) == true) {
		board[dest_y][dest_x] = board[i][j];
		board[i][j] = nullptr;
	}
	return true;
}

bool Board::isKingValid(int i, int j, bool getColor) {
	if ((Board::board[i][j]->getColor() == true) && (i == 7)) {
		return true;
	}
	else if ((Board::board[i][j]->getColor() == false) && (i == 0)) {
		return true;
	}
	else return false;
}

bool Board::letsGetFat(int i, int j, bool getColor) { //is their a piece of opposing color ahead 
	Piece* tmpPiece = Board::board[i][j];
	if (tmpPiece->getColor() == true) { //regarding white piece, goes down 
		if ((Board::board[i + 1][j + 1] != nullptr) && (Board::board[i + 1][j + 1]->getColor() == false)) { // theres a red piece bottom right
			return true;
		}
		else if ((Board::board[i + 1][j - 1] != nullptr) && (Board::board[i + 1][j - 1]->getColor() == false)) { //theres a red piece bottom left
			return true;
		}
		else if ((tmpPiece->getColor() == true) && (Board::isKingValid(i, i, true) == true)) { //if the piece is a white king
			if ((Board::board[i - 1][j + 1] != nullptr) && (Board::board[i - 1][j + 1]->getColor() == false)) { //theres a red piece top right
			return true;
		}
			else if ((Board::board[i - 1][j - 1] != nullptr) && (Board::board[i - 1][j - 1]->getColor() == false)) { //theres a red piece top left
				return true;
			}
		}
		else return false;
	}
	else if (tmpPiece->getColor() == false) { //regarding red piece, goes up
			if ((Board::board[i - 1][j + 1] != nullptr) && (Board::board[i - 1][j + 1]->getColor() == true)) { //theres a white piece top right
				return true;
			}
			else if ((Board::board[i - 1][j - 1] != nullptr) && (Board::board[i - 1][j - 1]->getColor() == true)) { //theres a white piece top left
				return true;
			}
			else if (Board::isKingValid(i, j, false) == true) { //if its a red king
				if ((Board::board[i + 1][j + 1] != nullptr) && (Board::board[i + 1][j + 1]->getColor() == true)) { //theres a white piece bottom right
					return true;
				}
				else if ((Board::board[i + 1][j - 1] != nullptr) && (Board::board[i + 1][j - 1]->getColor() == true)) { //theres a white piece bottom left
					return true;
				}
			}
			else return false;
	}
}
