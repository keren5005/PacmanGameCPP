#ifndef _PACMAN_H_
#define _PACMAN_H_
#include "Creature.h"
#include "Point.h"

class Pacman : public Creature
{
private:
	char arrowKeys[SIZEARROWKEYS];
public:
	Pacman(const Point& body, const char& figure); //ctor

	//set
	void setArrowKeys(const char* keys);
	void setDirection(const int& direction);

	//get
	int getDirectionFromKB(const char& key) const;

	//utiles
	void move(const Point& size);
	void movePacman(const int& direction, const Point& size);
	virtual void notPureVirtual() const {} //Makes Pacman not pure virtual
};

#endif