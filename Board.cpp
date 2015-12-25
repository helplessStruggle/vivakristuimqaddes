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

//check dan
bool Board::isValid(int i, int j, int dest_x, int dest_y, bool color) {
	Piece *tmpPiece = Board::board[i][j];
		if (tmpPiece == nullptr) { 
			//selected a non-existent piece
			std::cout << "Piece does not exist." << std::endl;
			return false;
		}
		if ((std::abs(dest_x - j) != 1 || (std::abs(dest_y - i)) != 1)) {
			//making sure a piece can only move 1 square, 1 up or 1 down		
			std::cout << "You can only move one box at a time." << std::endl;
			return false;
		}
		if ((color) && (tmpPiece->isKing() == false)) {
			//normal white piece
			if ((dest_y - i) <= 0) {
				std::cout << "You cannot move backwards as a white piece unless you are king" << std::endl;
				return false;
			}
		}
		if ((!color) && (tmpPiece->isKing() == false)) {
			if ((dest_y - i) >= 0) {
				std::cout << "You cannot move backwards as a red piece unless you are king" << std::endl;
				return false;
			}
		}
	else return true;
}

bool Board::isCoordValid(int x, int y) {
	//checks if coordinates entered exist on the board
	if (x >= 0 && y >= 0 && x < 9 && y < 9) {
		return true;
	}
}

bool Board::movePiece(int i, int j, int dest_x, int dest_y, bool color) {
	if ((Board::isValid(i, j,dest_x, dest_y, color) == true) && (Board::isCoordValid(i,j) == true)) {
		//if isValid and coordValid gives the go-ahead, move the piece
		board[dest_y][dest_x] = board[i][j];
		//copy the piece to the new location
		board[i][j] = nullptr;
		//point previous piece to null pointer
	}
	return true;
}

bool Board::isKingValid(int i, int j, bool color) {
	if ((Board::board[i][j]->getColor() == true) && (i == 7)) {
		//if a white piece reaches the end of the board, promote to king
		return true;
	}
	else if ((Board::board[i][j]->getColor() == false) && (i == 0)) {
		//if redpiece reaches end of board, promote to king
		return true;
	}
	//else no promotion available
	else return false;
}

bool Board::eat(int i, int j, int dest_x, int dest_y, bool color) { 
	//if this returns false, then dx dy is empty, use movePiece and put the piece there (i.e. no eating available)
	//if returns true, a piece was eaten 
	if (board[dest_y][dest_x] == nullptr) { 
		//there exists a blank space at the destination
		if (color) { 
			// top, white, x	
			if (j - dest_x == -2) {
				//blank space is to the right of (i,j) piece
				if ((board[i + 1][j + 1] != nullptr) && (board[i + 1][j + 1]->getColor() == false)) { 
					//a piece exists between ij piece and dxdy of opposite color we can eat, bottom right
					std::cout << "You can eat piece at position " << j + 1 << i + 1 << ". Press y to eat and go to " << dest_y << dest_x << ", anything else to stay" << std::endl;
						char x1 = 0;
						std::cin >> x1;
						if (x1 == 'y') {
							board[dest_y][dest_x] = board[i][j]; 
							//initial piece copied to new position
							board[i][j] = nullptr; 
							//initial piece 'moved', so delete the 'old' piece
							board[i + 1][j + 1] = nullptr; 
							//piece eaten, removed from board
							return true;
						}
						else {
							return false;
							//user doesnt want to eat, 
						}
					}
				else if (j - dest_x == 2) {
					//vacant space after piece left side of current piece
					if ((board[i + 1][j - 1] != nullptr) && (board[i + 1][j - 1]->getColor() == false)) {
						//there exists a piece diagonally of initial piece and of opposite color
						std::cout << "You can eat piece at position " << j-1 << i + 1 << ". Press y to eat and go to " << dest_y << dest_x << ", n to stay" << std::endl;
						char x2 = 0;
						std::cin >> x2;
						if (x2 == 'y') {
							board[dest_y][dest_x] = board[i][j];
							board[i][j] = nullptr;
							board[i + 1][j - 1] = nullptr;
							return true;
						}
						else return false;
					}
				}
				else if (board[i][j]->isKing() == true) { //if piece is a white king, it can move backwards as well
					if (j - dest_x == -2) {
						//then piece is to the right of king piece
						if ((board[i - 1][j + 1] != nullptr && board[i - 1][j + 1]->getColor() == false)) {
							std::cout << "You can eat piece at position " << j+1 << i-1 << ". Press y to eat and go to " << dest_y << dest_x << ", n to stay" << std::endl;
							char x5 = 0;
							std::cin >> x5;
							if (x5 == 'y') {
								board[dest_y][dest_x] = board[i][j];
								board[i-1][j+1] = nullptr;
								board[i][j] = nullptr;
								return true;
							}
							else return false;
						}
					}
					else if (j - dest_x == 2) {
						//vacant space is to the left of (i,j) piece
						if ((board[i - 1][j - 1]) != nullptr && board[i - 1][j - 1]->getColor() == false) {
							//red piece, o, top left
							std::cout << "You can eat piece at position " << j-1 << i-1 << ". Press y to eat and go to " << dest_y << dest_x << ", n to stay" << std::endl;
							char x6 = 0;
							std::cin >> x6;
							if (x6 == 'y') {
								board[dest_y][dest_x] = board[i][j];
								board[i][j] = nullptr;
								board[i - 1][j - 1] = nullptr;
								return true;
							}
							else return false;
						}
					}
				}
				else return false; //if not a king, then we have exhausted all our options. User just wants to move the piece
			} //then pieces are of the same color. cannot eat

		}
		if (!color) { //red piece, bottom, o
				if (j - dest_x == -2) { //destination space is top right of current piece
					if ((board[i - 1][j + 1] != nullptr) && (board[i - 1][j + 1]->getColor() == true)) {
						//there exists an opponent piece between current coordinates and destination coordinates, 2 blocks afar
						std::cout << "You can eat piece at position " << j+1 << i-1 << ". Press y to eat and go to " << dest_y << dest_x << ", n to stay" << std::endl;
						char x3 = 0;
						std::cin >> x3;
						if (x3 == 'y') {
							board[dest_y][dest_x] = board[i][j];
							board[i][j] = nullptr;
							board[i - 1][j + 1] = nullptr;
							return true;
						}
						else return false; //user doesn't want to eat and move
					}
				}
				else if (j - dest_x == 2) { 
					//destination is to the left of current position
					if ((board[i - 1][j - 1] != nullptr) && (board[i - 1][j - 1]->getColor() == true)) {
						std::cout << "You can eat piece at position " << j-1 << i-1 << ". Press y to eat and go to " << dest_y << dest_x << ", n to stay" << std::endl;
						char x4 = 0;
						std::cin >> x4;
						if (x4 == 'y') {
							board[dest_y][dest_x] = board[i][j];
							board[i - 1][j - 1] = nullptr;
							board[i][j] = nullptr;
							return true;
						}
						else return false;
					}
				}
				if (board[i][j]->isKing() == true) { //then it can move backwards too
					if (j - dest_x == -2) {
						if ((board[i + 1][j + 1] != nullptr) && (board[i + 1][j + 1]->getColor() == true)) {
							//piece at bottom right side
							std::cout << "You can eat piece at position " << j + 1 << i + 1 << ". Press y to eat and go to " << dest_y << dest_x << ", n to stay" << std::endl;
							char x7 = 0;
							std::cin >> x7;
							if (x7 == 'y') {
								board[dest_y][dest_x] = board[i][j];
								board[i][j] = nullptr;
								board[i + 1][j + 1] = nullptr;
								return true;
							}
							else return false; //user doesn't want to eat piece
						}
					}
					else if (j - dest_x == 2) {
						//regarding left side
						if ((board[i + 1][j - 1] != nullptr) && (board[i + 1][j - 1]->getColor() == true)) {
							std::cout << "You can eat piece at position " << j - 1 << i + 1 << ". Press y to eat and go to " << dest_y << dest_x << ", n to stay" << std::endl;
							char x8 = 0;
							std::cin >> x8;
							if (x8 == 'y') {
								board[dest_y][dest_x] = board[i][j];
								board[i][j] = nullptr;
								board[i+1][j-1] = nullptr;
								return true;
							}
							else return false;
						}
					}
				}
				//then it's not a king either
		}
		//tackled both colors
	} 
	//else there is a piece, cannot eat 2 exactly after each other
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

bool Board::checkCanEat(int cX, int cY, bool color) {
	//if this returns true, alert user that he can eat a piece
	if (color) { 
		//regarding white piece
		if (Board::isCoordValid(cX - 1, cY + 1)) {
			if (Board::board[cY + 1][cX - 1]->getColor() == false) {  
				//there's a piece bottom left you can potentially eat
				if ((Board::isCoordValid(cX - 2, cY + 2) == true) && (Board::board[cY + 2][cX - 2] == nullptr)) {
					//then you can eat piece at cY+1 cX-2
					std::cout << "You can eat another piece at " << cY + 1 << cX - 1 << ". Press y to eat or anything else to stay" << std::endl;
					char a = 0;
					std::cin >> a;
					if (a == 'y') {
						board[cY + 2][cX - 2] = board[cY][cX];
						board[cY][cX] = nullptr;
						board[cY + 1][cX - 1] = nullptr;
						return true;
					}
					else return false;
				}
			}
		}
		if (Board::isCoordValid(cX + 1, cY + 1)) {
			if (Board::board[cY + 1][cX + 1]->getColor() == false) { 
				//there's a piece bottom right you can potentially eat
				if ((Board::isCoordValid(cX + 2, cY + 2) == true) && (Board::board[cY + 2][cX + 2] == nullptr)) {
					std::cout << "You can eat another piece at " << cY + 1 << cX + 1 << ". Press y to eat or anything else to stay" << std::endl;
					char a = 0;
					std::cin >> a;
					if (a == 'y') {
						board[cY + 2][cX + 2] = board[cY][cX];
						board[cY][cX] = nullptr;
						board[cY + 1][cX + 1] = nullptr;
						return true;
					}
					else return false;
				}
			}
		}
		if (board[cY][cX]->isKing()) {
			//if the piece selected is king piece, you can move backwards as well
			if (Board::isCoordValid(cX - 1, cY - 1)) {
				if (Board::board[cY - 1][cX - 1]->getColor() == false) { 
					//there's a piece top left you can potentially eat
					if ((Board::isCoordValid(cX - 2, cY - 2) == true) && (Board::board[cY - 2][cX - 2] == nullptr)) {
						std::cout << "You can eat another piece at " << cY - 1 << cX - 1 << ". Press y to eat or anything else to stay" << std::endl;
						char a = 0;
						std::cin >> a;
						if (a == 'y') {
							board[cY - 2][cX - 2] = board[cY][cX];
							board[cY][cX] = nullptr;
							board[cY - 1][cX - 1] = nullptr;
							return true;
						}
						else return false;
					}
				}
			}
			if (Board::isCoordValid(cX + 1, cY - 1)) {
				if (Board::board[cY - 1][cX + 1]->getColor() == false) {
					//there's a piece top right you can potentially eat
					if ((Board::isCoordValid(cX + 2, cY - 2) == true) && (Board::board[cY - 2][cX + 2] == nullptr)) {
						std::cout << "You can eat another piece at " << cY - 1 << cX + 1 << ". Press y to eat or anything else to stay" << std::endl;
						char a = 0;
						std::cin >> a;
						if (a == 'y') {
							board[cY - 2][cX + 2] = board[cY][cX];
							board[cY][cX] = nullptr;
							board[cY - 1][cX + 1] = nullptr;
							return true;
						}
						else return false;
					}
				}
			}
		}
	}
	else { 
		//regarding red piece
		if (Board::isCoordValid(cX - 1, cY - 1)) {
			if (Board::board[cY - 1][cX - 1]->getColor() == true) {  
				//there's a piece top left you can eat
				if ((Board::isCoordValid(cX - 2, cY - 2) == true) && (Board::board[cY - 2][cX - 2] == nullptr)) {
					//you can eat piece at cY-1 cX-1
					std::cout << "You can eat another piece at " << cY - 1 << cX - 1 << ". Press y to eat or anything else to stay" << std::endl;
					char a = 0;
					std::cin >> a;
					if (a == 'y') {
						board[cY - 2][cX - 2] = board[cY][cX];
						board[cY][cX] = nullptr;
						board[cY - 1][cX - 1] = nullptr;
						return true;
					}
					else return false;
				}
			}
		}
		if (Board::isCoordValid(cX + 1, cY - 1)) {
			if (Board::board[cY - 1][cX + 1]->getColor() == true) { 
				//there's a piece top right you can eat
				if ((Board::isCoordValid(cX + 2, cY - 2) == true) && (Board::board[cY - 2][cX + 2] == nullptr)) {
					//you can eat piece at cY-1 cX+1
					std::cout << "You can eat another piece at " << cY - 1 << cX + 1 << ". Press y to eat or anything else to stay" << std::endl;
					char a = 0;
					std::cin >> a;
					if (a == 'y') {
						board[cY - 2][cX + 2] = board[cY][cX];
						board[cY][cX] = nullptr;
						board[cY - 1][cX + 1] = nullptr;
						return true;
					}
					else return false;
				}
			}
		}
		if (board[cY][cX]->isKing()) {
			if (Board::isCoordValid(cX - 1, cY + 1)) {
				if (Board::board[cY + 1][cX - 1]->getColor() == false) { 
					//there's a piece bottom left you can eat
					if ((Board::isCoordValid(cX - 2, cY + 2) == true) && (Board::board[cY + 2][cX - 2] == nullptr)) {
						//you can eat piece at cY+1 cX-1
						std::cout << "You can eat another piece at " << cY + 1 << cX - 1 << ". Press y to eat or anything else to stay" << std::endl;
						char a = 0;
						std::cin >> a;
						if (a == 'y') {
							board[cY + 2][cX - 2] = board[cY][cX];
							board[cY][cX] = nullptr;
							board[cY + 1][cX - 1] = nullptr;
							return true;
						}
						else return false;
					}
				}
			}
			if (Board::isCoordValid(cX + 1, cY + 1)) {
				if (Board::board[cY + 1][cX + 1]->getColor() == false) { 
					//there's a piece bottom right you can eat
					if ((Board::isCoordValid(cX + 2, cY + 2) == true) && (Board::board[cY + 2][cX + 2] == nullptr)) {
						//you can eat piece at cY+1 cX+1
						std::cout << "You can eat another piece at " << cY + 1 << cX + 1 << ". Press y to eat or anything else to stay" << std::endl;
						char a = 0;
						std::cin >> a;
						if (a == 'y') {
							board[cY + 2][cX + 2] = board[cY][cX];
							board[cY][cX] = nullptr;
							board[cY + 1][cX + 1] = nullptr;
							return true;
						}
						else return false;
					}
				}
			}
		}
	}
	return false;
}

bool Board::checkBlank(int cX, int cY, bool color) {
	if (color) {
		if (Board::board[cY - 1][cX - 1]->getColor() == true) {
			//there's a piece top left you can eat
			if ((Board::isCoordValid(cX - 2, cY - 2) == true) && (Board::board[cY - 2][cX - 2] == nullptr)) {
				return true;
				//you can eat piece at cY-1 cX-1
			}
		}
	}
}

bool Board::eat2(int i, int j, int dest_x, int dest_y, bool color) {
	if (color) {
		if (Board::isCoordValid(i, j)) {
			if ((Board::board[dest_y][dest_x] != nullptr) && (Board::board[dest_y][dest_x]->getColor() == false)) {
				board[dest_y][dest_x] = board[i][j];
				board[i][j] = nullptr;
			}
		}
	}
}
