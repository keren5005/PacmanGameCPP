#ifndef CREATURE_H_
#define CREATURE_H_

#include "Point.h"
#include "Board.h"
#include "Symbols.h"

class Creature
{
protected:
	Point body;
	int direction;
	char figure;
public:
	Creature(const Point& body, const char& figure); //c'tor
	
	//sets
	virtual void setFigure(const char& figure);
	void setBody(const Point& body);

	//gets
	char getFigure()const;
	int getDirection() const;
	const Point& getPoint() const;

	//utiles
	int* newPosDir(const int& direction);
	void show(const int& x, const int& y) const;
	bool isWall(const BoardGame& board, const int& direction, const int& x, const int& y) const;
	bool isValid(const int& row, const int& col, const BoardGame& board) const;
	bool moveValid(const int& direction, const BoardGame& board);
	virtual void notPureVirtual() const = 0; //Creature should be a pure virtual class

};

#endif // !CREATURE_H_
