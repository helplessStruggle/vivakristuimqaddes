#pragma once
#include "Board.h"
class Game
{
public:
	Game();
	~Game();
	void startGame();	
	bool currentPlayer = false;
	bool getCurrentPlayer() {return currentPlayer; }
	void setCurrentPlayer(bool) { this->currentPlayer; }
	bool saveGame();
private:
	Board *myBoard;
	int i, j, dest_x, dest_y;
	bool currentPlayer = false;
};

