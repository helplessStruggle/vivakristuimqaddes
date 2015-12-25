#include "Game.h"
#include "Board.h"
#include "Piece.h"
#include "fstream"
#include <string>
Game::Game()
{
	Game::myBoard = new Board();
}


Game::~Game()
{
}

Game *myGame = new Game();
void Game::startGame() {
	while (myBoard->gameOver() == false) {
		if (myGame->getCurrentPlayer()) {
			//then player 1 turn, white, true
			std::cout << "Player 1, enter move" << std::endl;
			std::cin >> j >> i >> dest_y >> dest_x;
			if (std::abs(j-dest_x) == 2){
				//if user tried to move 2 boxes, check if he tried to eat something
				myBoard->eat(i, j, dest_x, dest_y, true);
				if (myBoard->eat(i, j, dest_x, dest_y, true) == false) {
					std::cout << "You can only move one box at a time unless you intend to capture a piece. Try again with new coordinates " << std::endl;
					std::cin >> j >> i >> dest_y >> dest_x;
				}
			}
			else { myBoard->movePiece(i, j, dest_x, dest_y, true);} 
			while (myBoard->checkCanEat(i, j, true) == true) {
				//while there are still piece we can eat, keep executing this
				myBoard->checkBlank(i, j, true);
			}
			if (myBoard->isKingValid(i, j, true) == true) {
				myBoard->getPiece(j, i)->setKing(true);
			}
			myGame->setCurrentPlayer(false);
			//player 2's turn
		}
		if (myGame->getCurrentPlayer() == false) {
			//then player 2 turn, red, false
			std::cout << "Player 2, enter move" << std::endl;
			std::cin >> j >> i >> dest_y >> dest_x;
			//player 1's turn
		}
	}
}

bool Game::saveGame() {
	std::cout << "Enter a name for the file to be saved" << std::endl;
	std::string x = "";
	std::cin >> x;
	std::ofstream myfile(x);
	if (myfile.is_open()) {
		//if file opens successfully
		if (myGame->getCurrentPlayer()) {
			myfile << "Current Player: White. \n";
		}
		if (myGame->getCurrentPlayer() == false) {
			myfile << "Current Player: Red. \n";
		}
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (myBoard->getPiece(j, i)->getColor() == true) {
					myfile << "x: " << j << i << ". \n";
					if (myBoard->getPiece(j, i)->isKing()) {
						myfile << "*: " << j << i << ". \n";
					}
				}
				if (myBoard->getPiece(j, i)->getColor() == false) {
					myfile << "o: " << j << i << ". \n";
					if (myBoard->getPiece(j, i)->isKing()) {
						myfile << "#: " << j << i << ". \n";
					}
				}
			}
		}
		myfile.close();
		return true;
	}
	else return false;
}
