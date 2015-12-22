#include "Board.h"
#include <cmath>
#include <string>
#include <iostream>
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
	//iccekkja di ma adrian
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

/*bool Board::eat(int i, int j, bool color) { //returns true if a piece of opposing getColor is ahead
	Piece* tmpPiece = Board::board[i][j];
	if (tmpPiece->getColor() == true) { //regarding white piece, goes down 
		if ((Board::board[i + 1][j + 1] != nullptr) && (Board::board[i + 1][j + 1]->getColor() == false)) { // a red piece exists bottom right of the current piece
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

bool Board::letsGetFatter(int dest_x, int dest_y, bool color) {
	if (color == true) { //piece is white, x, goes down
		//if there is no piece at the destination coordinates, then no double jump is available, return false
		if (Board::board[dest_x][dest_y] == nullptr) {
			return false;
		}
		//else if there is a piece of a different color at the destination coordinates, check if double jump is available
		else if (Board::board[dest_x][dest_y]->getColor() !color ) {

		}
	}

}
*/

bool Board::eat(int i, int j, bool color, int dest_x, int dest_y) { //if this returns false, then dx dy is empty, use movePiece and put the piece there (i.e. no eating available)
	//if returns true, a piece was eaten 
	if (Board::board[dest_y][dest_x] != nullptr) { //there exists a piece to potentially eat
		if (color == true) { // top, white, x	
			if ((Board::board[dest_y][dest_x]->getColor()) == false) {
				if (Board::board[dest_y - 1][dest_x + 1] == nullptr) {
					//vacant spot after red piece, o, bottom right
					std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat, n to stay" << std::endl;
					char x1 = 0;
					std::cin >> x1;
					if (x1 == 'y') {
						board[dest_y - 1][dest_x + 1] = board[i][j];
						board[i][j] = nullptr;
						board[dest_y][dest_x] = nullptr;
						return true;
					}
					else {
						return false; //just move piece to dx dy, no eating.
					}
				}
				else if ((Board::board[dest_y - 1][dest_x - 1]) == nullptr) {
					//vacant spot after red piece, o, bottom left
					std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat, n to stay" << std::endl;
					char x2 = 0;
					std::cin >> x2;
					if (x2 == 'y') {
						board[dest_y - 1][dest_x - 1] = board[i][j];
						board[i][j] = nullptr;
						board[dest_y][dest_x] = nullptr;
						return true;
					}

					else return false;
				}
				else return false;
			}
			return false;
			//colors are both white. 
		}
		else if (color == false) { //bottom, red, o
			if ((Board::board[dest_y][dest_x]->getColor()) == true) {
				if (Board::board[dest_y + 1][dest_x + 1] == nullptr) {
					//vacant spot after white piece, x, top right
					std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat, n to stay" << std::endl;
					char x3 = 0;
					std::cin >> x3; 
					if (x3 == 'y') {
						board[dest_y + 1][dest_x + 1] = board[i][j];
						board[i][j] = nullptr;
						board[dest_y][dest_x] = nullptr;
						return true;
					}
					else return false;
				}
				else if ((Board::board[dest_y + 1][dest_x - 1]) == nullptr) {
					//vacant spot after white piece, x, top left
					std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat, n to stay" << std::endl;
					char x4 = 0;
					std::cin >> x4;
					if (x4 == 'y') {
						board[dest_y + 1][dest_x - 1] = board[i][j];
						board[i][j] = nullptr;
						board[dest_y][dest_x] = nullptr;
						return true;
					}
					else return false;
				}
				else return false;
			}
			else return false; //if the piece at the destination isnt of opposite color, then you cant eat
		}
	}
	else return false; //no eating available since there was no piece to potentially eat in the first place
}
