#include "Fruit.h"

// c'tor for fruit
Fruit::Fruit(const Point& body, const char& figure): Creature(body, figure)
{
	setPossibleDir();
	setFigureArr();
	setDirection();
}

//init the figure array by the values 5-9
void Fruit::setFigureArr()
{
	figureArr = new char[SIZEFIGUREARR];
	for (int i = 0; i < SIZEFIGUREARR; i++)
	{
		figureArr[i] = i + '5';
	}
}

//set the figure of fruit randomize from figure arrray
void Fruit::setFigure()
{
	int i;
	srand((unsigned int)time(NULL));
	i = rand() % SIZEFIGUREARR;
	figure = figureArr[i];
}

//set array possible direction of fruit
void Fruit::setPossibleDir()
{
	possibleDir = new int[SIZEDIR];
	possibleDir[UP] = UP;
	possibleDir[DOWN] = DOWN;
	possibleDir[LEFT] = LEFT;
	possibleDir[RIGHT] = RIGHT;
}

//set direction of fruit randomize from possible direction array
void Fruit::setDirection()
{
	srand((unsigned int)time(NULL));
	direction = possibleDir[rand() % SIZEDIR];
}

//this function create new arr of possible possition of next step for fruit
void Fruit::setDirection(const int& direction)
{
	int* posDir;
	posDir = newPosDir(direction);
	srand((unsigned int)time(NULL));
	this->direction = posDir[rand() % (SIZEDIR - 1)];
	delete[] posDir;
}

//move and draw the fruit
void Fruit::move(const char& ch, const BoardGame& board)
{
	body.draw(ch);
	moveFruit(direction, board);
	body.draw(figure);
}

//move the fruit
void Fruit::moveFruit(const int& direction, const BoardGame& board)
{
	int x = body.getX();
	int y = body.getY();
	if (!moveValid(direction, board))
		setDirection();
	else
	{
		switch (direction)
		{
		case UP:
			body.setY(--y);
			break;
		case DOWN:
			body.setY(++y);
			break;
		case LEFT:
			body.setX(--x);
			break;
		case RIGHT:
			body.setX(++x);
			break;
		case STAY:
			break;
		default:
			break;
		}
	}
}
