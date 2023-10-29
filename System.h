#ifndef _System_H_
#define _System_H_

#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include "Symbols.h"

class System {
	BoardGame board;
	vector<Ghost> ghostsArr;
public:
	System(const string& board) : board(board) {} //c'tor
	
	//utiles
	bool run(int* score, int* lives, const int& level);
	void initGhosts();
	Point locationForFruit()const;
	bool isFood(const int& x, const int& y)const;
	bool isKill(const Point& cretureCoords)const;
	bool isEaten(const Point& pacmanCoords, const Point& fruitCoords)const;
	void pauseGame() const;
	void draw(const int& x, const int& y, const char& ch)const;
	void showGhosts() const;
	bool isValidLoc(const int& x, const int& y)const;
	void handleKeyPress(Pacman& pacman, const int& scoreCount, const int& livesCount, const BoardGame& board);
	void handleFruitMovement(Fruit* newFruit, bool& fruitFlag, const Pacman& pacman, int& countFruit, int& timeFruit, bool& eatFruit);
	void handleFruitEating(Fruit*& newFruit, const bool& eatFruit, int& scoreCount, int& countFruit, int& timeFruit);
	void handleFoodEating(Pacman& pacman, int& scoreCount, int& checkScore, BoardGame& board);
	void handlePacmanKill(Pacman& pacman, int& livesCount, BoardGame& board, vector<Ghost>& ghostsArr);
};

#endif
