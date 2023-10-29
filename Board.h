#ifndef _BOARD_H_
#define _BOARD_H_
#include "Point.h"
#include "Symbols.h"

class BoardGame
{
private:
	Point score;
	Point lives;
	Point size;
	Point playerCoord;
	string screenName;
	vector<Point> ghostsArr;
	vector<vector<char>> board;
	int scoreWin;
	bool isValid;
public:
	BoardGame(const string& screenName);
	//sets
	void setScore(const int& x, const int& y);
	void setLives(const int& x, const int& y);
	void setScreenName(const string& name);
	bool setBoard();

	//gets
	char getBlock(const int& x, const int& y) const;
	int getScoreWin()const;
	const Point& getPacmanCoords()const;
	int getGhostArrLen()const;
	const Point& getGhostCoords(const int& i)const;
	const Point& getBoardSize()const;
	bool getVaildity() const;

	//utiles
	void printScore(const int& counter) const;
	void printLives(const int& counter) const;
	void printBoard(const int& score, const int& lives) const;
	void updateBoard(const int& x, const int& y, const char& ch);
	
	
};

#endif