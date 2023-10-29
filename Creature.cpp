#include "Creature.h"

//c'tor
Creature::Creature(const Point& body, const char& figure)
{
	setBody(body);
	setFigure(figure);
}

//return the figure of the creature
char Creature::getFigure()const
{
	return figure;
}

//set the loction body of the creature
void Creature::setBody(const Point& body)
{
	this->body.setX(body.getX());
	this->body.setY(body.getY());
}

//set figure of creature
void Creature::setFigure(const char& figure)
{
	this->figure = figure;
}

// new arr possible possition for creature steps
int* Creature::newPosDir(const int& direction)
{
	int* arr = new int[3];
	switch (direction)
	{
	case 0:
		arr[0] = DOWN;
		arr[1] = LEFT;
		arr[2] = RIGHT;
		break;
	case 1:
		arr[0] = UP;
		arr[1] = LEFT;
		arr[2] = RIGHT;
		break;
	case 2:
		arr[0] = UP;
		arr[1] = DOWN;
		arr[2] = RIGHT;
		break;
	case 3:
		arr[0] = UP;
		arr[1] = DOWN;
		arr[2] = LEFT;
		break;
	default:
		break;
	}
	return arr;
}

//return the location of the creature
const Point& Creature::getPoint() const
{
	return body;
}

//return the direction of the creature
int Creature::getDirection() const
{
	return direction;
}

//draw the creature in current possition
void Creature::show(const int& x, const int& y) const
{
	gotoxy(x, y);
	cout << figure;
}

//check if the next step of creature is wall
bool Creature::isWall(const BoardGame& board, const int& direction, const int& x, const int& y)const
{
	char c = '0';
	switch (direction) {
	case 0: // UP
		if (y == 0)
			c = board.getBlock(x, board.getBoardSize().getY() - 1);
		else
			c = board.getBlock(x, y - 1);
		break;
	case 1: // DOWN
		if (y == board.getBoardSize().getY() - 1)
			c = board.getBlock(x, 0);
		else
			c = board.getBlock(x, y + 1);
		break;
	case 2: // LEFT
		if (x == 0)
			c = board.getBlock(board.getBoardSize().getX() - 1, y);
		else
			c = board.getBlock(x - 1, y);
		break;
	case 3: // RIGHT
		if (x == (board.getBoardSize().getX() - 1))
			c = board.getBlock(0, y);
		else
			c = board.getBlock(x + 1, y);
		break;
	case 4: // STAY
		break;
	default:
		break;
	}
	return(c == WALL);
}

//check the validity of creture movement
bool Creature::moveValid(const int& direction, const BoardGame& board)
{
	int x = body.getX();
	int y = body.getY();
	switch (direction)
	{
	case UP:
		y = y - 1;
		break;
	case DOWN:
		y = y + 1;
		break;
	case LEFT:
		x = x - 1;
		break;
	case RIGHT:
		x = x + 1;
		break;
	case STAY:
		break;
	default:
		break;
	}
	return (isValid(y, x, board));
}

//check the validity of creture movement
bool Creature::isValid(const int& row, const int& col, const BoardGame& board)const
{
	if (row >= board.getBoardSize().getY() || col >= board.getBoardSize().getX() || row <= 0 || col <= 0)
		return false;

	if (board.getBlock(col, row) == WALL)
		return false;

	return true;
}