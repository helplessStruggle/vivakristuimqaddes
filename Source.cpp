#include "Board.h"
#include "Player.h"
#include "fstream"
#include <string>
#include "Game.h"
Game *myGame = new Game();
Board *myBoard = new Board();

int main() {
	int userInput = 0;
	switch (userInput) {
	case 1: std::cout << "Start a new game" << std::endl;
		break;
	case 2: std::cout << "Save current game" << std::endl;
		break;
	case 3: std::cout << "Load a saved game" << std::endl;
		break;
	case 4: std::cout << "Exit" << std::endl;;
		break;
	default: std::cout << "Only numbers between 1 and 4 please" << std::endl;;
	}
	std::cout << "Please enter a number" << std::endl;
	std::cin >> userInput;
	if (userInput == 1) {
		Board myBoard = Board();
		std::cout << myBoard.toString() << std::endl;
	}

	if (userInput == 2) {
		if (myGame->saveGame()) {
			std::cout << "File saved successfully" << std::endl;
		}
		else { std::cout << "Error.Saving unsuccessful" << std::endl; }
	}
	return 0;
}

