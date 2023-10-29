#ifndef GHOST_H_
#define GHOST_H_

#include "Point.h"
#include "Creature.h"

class Ghost : public Creature
{
private:
	int possibleDir[SIZEDIR];
public:
	Ghost(const Point& body, const char& figure);//ctor
	//set
	void setPossibleDir();
	void setDirection();
	void setSmartDirection(const int& direction);
	//get

	//utiles
	
	void move(const char& ch, const BoardGame& board, const Point& pacPoint, const int& level, const int& numOfGhosts);
	void moveByLevel(const BoardGame& board, const Point& pacmanPoint, const int& level, const int& numOfGhosts);
	void moveGhost(const int& direction, const BoardGame& board);
	void smartMove(const BoardGame& board, const Point& pacmanPoint);
	bool isValidStep(const vector<vector<bool>>& visit, const int& row, const int& col, const BoardGame& board)const;
	Point BFS(const BoardGame& board, vector<vector<bool>>& visit, const Point& pacPoint)const;
	virtual void notPureVirtual() const {} //Makes Ghost not pure virtual
};
#endif 

