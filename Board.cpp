#include "Board.h"
#include <cmath>
#include <string>
#include <iostream>
#include <exception>
//true white top x
//false red bottom o
//i = yaxis
//j = xaxis

//Constructor
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

//Destructor
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
			//selected a non-existent piece
			std::cout << "Piece does not exist." << std::endl;
			return false;
		}
		else if ((dest_x > 8) || (dest_y > 8) || (dest_x < 0) || (dest_y < 0)) { 
			//outside of board
			std::cout << "Co-ordinates entered are outside the board." << std::endl;
			return false;
		}
		else if (((dest_x - j) != std::abs(1) || ((dest_y - i)) != std::abs(1))) { 
			//making sure a piece can only move 1 square, 1 up or 1 down
			std::cout << "You can only move one box at a time." << std::endl;
			return false;
		}
	else return true;
}

bool Board::movePiece(int i, int j, bool getColor, int dest_x, int dest_y) {
	if (Board::isValid(i, j, getColor, dest_x, dest_y) == true) {
		//if isValid gives the go-ahead, move the piece
		board[dest_y][dest_x] = board[i][j];
		//copy the piece to the new location
		board[i][j] = nullptr;
		//point previous piece to null pointer
	}
	return true;
}

bool Board::isKingValid(int i, int j, bool getColor) {
	if ((Board::board[i][j]->getColor() == true) && (i == 7)) {
		//if a white piece reacher the end of the board, promote to king
		return true;
	}
	else if ((Board::board[i][j]->getColor() == false) && (i == 0)) {
		//if redpiece reaches end of board, promote to king
		return true;
	}
	//else no promotion available
	else return false;
}

bool Board::eat(int i, int j, bool color, int dest_x, int dest_y) { //if this returns false, then dx dy is empty, use movePiece and put the piece there (i.e. no eating available)
	//if returns true, a piece was eaten 
	if (board[dest_y][dest_x] != nullptr) { 
		//there exists a piece to potentially eat
		if (color == true) { // top, white, x	
			if ((board[dest_y][dest_x]->getColor()) == false) {
				//user wants position of a red piece
				if (j - dest_x == -1) { //red piece is to the right of (i,j) piece
					if (board[i - 2][j + 2] == nullptr) {
						//vacant spot after red piece, o, bottom right
						std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat and go to " << i - 2 << j + 2 << ", n to stay" << std::endl;
						char x1 = 0;
						std::cin >> x1;
						if (x1 == 'y') {
							board[i - 2][j + 2] = board[i][j]; //initial piece copied to new position
							board[i][j] = nullptr; //initial piece 'moved', so delete the 'old' piece
							board[dest_y][dest_x] = nullptr; //piece eaten, removed from board
							return true;
						}
						else {
							return false; //user doesnt want to eat, 
						}
					}
				}
				else if (j - dest_x == 1) {
					//piece to be eaten is at the left of (i,j) piece
					if ((board[i - 2][j - 2]) == nullptr) {
						//vacant spot after red piece, o, bottom left
						std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat and go to " << i + 2 << j - 2 << ", n to stay" << std::endl;
						char x2 = 0;
						std::cin >> x2;
						if (x2 == 'y') {
							board[i - 2][j - 2] = board[i][j];
							board[i][j] = nullptr;
							board[dest_y][dest_x] = nullptr;
							return true;
						}

						else return false;
					}
				}
				else if (board[i][j]->isKing() == true) { //if piece is a white king, it can move backwards as well
					if (j - dest_x == -1) {
						//then piece is to the right of king piece
						if (board[i + 2][j + 2] == nullptr) {
							std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat and go to " << i + 2 << j + 2 << ", n to stay" << std::endl;
							char x5 = 0;
							std::cin >> x5;
							if (x5 == 'y') {
								board[i + 2][i + 2] = board[i][j];
								board[i][j] = nullptr;
								board[dest_y][dest_x] = nullptr;
								return true;
							}
							else return false;
						}
					}
					else if (j - dest_x == 1) {
						//piece to be eaten is to the left of (i,j) piece
						if ((board[i + 2][j - 2]) == nullptr) {
							//vacant spot after red, o, top left
							std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat and go to " << i + 2 << j - 2 << ", n to stay" << std::endl;
							char x6 = 0;
							std::cin >> x6;
							if (x6 == 'y') {
								board[i + 2][j - 2] = board[i][j];
								board[i][j] = nullptr;
								board[dest_y][dest_x] = nullptr;
								return true;
							}
							else return false;
						}
					}
				}
				else return false; //if not a king, then we have exhausted all our options. User just wants to move the piece
			} //then pieces are of the same color. cannot eat

		}
		if (color == false) { //red piece, bottom, o
			if ((board[dest_y][dest_x]->getColor()) == false){ //space occupies a white piece
				if (j - dest_x == -1) { //destination space is top right of current piece
					if ((board[i + 2][j + 2]) == nullptr) { //if space after opponent piece is empty, let's eat
						std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat and go to " << i + 2 << j + 2 << ", n to stay" << std::endl;
						char x3 = 0;
						std::cin >> x3;
						if (x3 == 'y') {
							board[i + 2][j + 2] = board[i][j];
							board[i][j] = nullptr;
							board[dest_y][dest_x] = nullptr;
							return true;
						}
						else return false; //user doesn't want to eat and move
					}
				}
				else if (j - dest_x == 1) { //destination space is top left of current piece
					if ((board[i + 2][j - 2]) == nullptr) { //we can eat and occupy new place
						std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat and go to " << i + 2 << j - 2 << ", n to stay" << std::endl;
						char x4 = 0;
						std::cin >> x4;
						if (x4 == 'y') {
							board[i + 2][j - 2] = board[i][j];
							board[i][j] = nullptr;
							board[dest_y][dest_x] = nullptr;
							return true;
						}
						else return false;
					}
				}
				if (board[i][j]->isKing() == true) { //then it can move backwards too
					if (j - dest_x == -1) {
						if ((board[i - 2][j + 2]) == nullptr) {
							std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat and go to " << i - 2 << j + 2 << ", n to stay" << std::endl;
							char x7 = 0;
							std::cin >> x7;
							if (x7 == 'y') {
								board[i - 2][j + 2] = board[i][j];
								board[i][j] = nullptr;
								board[dest_y][dest_x] = nullptr;
								return true;
							}
							else return false; //user doesn't want to eat piece
						}
					}
					else if (j - dest_x == 1) {
						if ((board[i - 2][j - 2]) == nullptr) {
							std::cout << "You can eat piece at position " << dest_y << dest_x << ". Press y to eat and go to " << i - 2 << j - 2 << ", n to stay" << std::endl;
							char x8 = 0;
							std::cin >> x8;
							if (x8 == 'y') {
								board[i - 2][j - 2] = board[i][j];
								board[i][j] = nullptr;
								board[dest_y][dest_x] = nullptr;
								return true;
							}
							else return false;
						}
					}
				}
				//then it's not a king either
			}//both colors covered
		}
	} //no piece exists, no eating available, basic move
	else return false;
}
	
bool Board::gameOver() {
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++) {
			if (Board::board[i][j]->getColor() == false) {
				Board::redPiece++;
			}
			else if (Board::board[i][j]->getColor() == true) {
				Board::whitePiece++;
			}
		}
	}
	if (Board::redPiece == 0) {
		std::cout << "White won!" << std::endl;
		return true;
	}
	else if (Board::whitePiece = 0) {
		std::cout << "Red won!" << std::endl;
		return true;
	}
	else return false;
}

