#ifndef FRUIT_H_
#define FRUIT_H_

#include "Creature.h"

class Fruit : public Creature
{
private:
	int* possibleDir;
	char* figureArr;

public:
	Fruit(const Point& body, const char& figure);//ctor
	~Fruit() { delete[] possibleDir; delete[] figureArr; }

	//set
	void setFigure();
	void setPossibleDir();
	void setDirection();
	void setDirection(const int& direction);
	void setFigureArr();
	
	// utiles
	void move(const char& ch, const BoardGame& board);
	void moveFruit(const int& direction, const BoardGame& board);
	virtual void notPureVirtual() const {} //Makes Fruit not pure virtual
};


#endif
