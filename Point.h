#ifndef _POINT_H_
#define _POINT_H_

#include "io_utils.h"

class Point {
	unsigned int x;
	unsigned int y;
public:
	Point() : x(0), y(0) {} //default c'tor
	Point(const int& x, const int& y); //c'tor
	bool operator==(const Point& p)const;

	//set
	void setX(const int& x);
	void setY(const int& y);
	//get
	int getX() const;
	int getY() const;
	//utiles
	void draw(const char& ch);
	
	
	
};

#endif