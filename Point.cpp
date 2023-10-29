#include "Point.h"

//c'tor 
Point::Point(const int& x, const int& y) : x(x), y(y) {}

//draw the char appears on the screen 
void Point::draw(const char& ch) {
	gotoxy(x, y);
	cout << ch << endl;
}

//set x point
void Point::setX(const int& x)
{
	this->x = x;
}

//set y point
void Point::setY(const int& y)
{
	this->y = y;
}

//get x point
int Point::getX() const
{
	return x;
}

//get y point
int Point::getY() const
{
	return y;
}

//opertor compare between two points
bool Point::operator==(const Point& p)const
{
	return((this->getX() == p.getX()) && this->getY() == p.getY());
}
