#include "System.h"

//the start run function of the game - controls the function that implements the game
bool System::run(int* score, int* lives, const int& level)
{
	int key = 0, tempKey, dir, movePac = 0, scoreCount, livesCount, i, countFruit = 0, timeFruit = 0, moveGhost = 0, fruitScore, checkScore;
	bool flagGhost = false, eatFruit = false, fruitFlag = false, flag = false;
	char c;
	Pacman pac(board.getPacmanCoords(), PACMAN);
	Point location;
	Fruit* newFruit = new Fruit(location, '0');

	if (!board.getVaildity())
		return false;

	initGhosts();

	checkScore = board.getScoreWin();
	scoreCount = *score;
	livesCount = *lives;
	
	hideCursor();
	board.printBoard(scoreCount, livesCount);
	showGhosts();

	location = locationForFruit();
	newFruit->setFigure();
	newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());

	do {
		board.printScore(scoreCount);
		board.printLives(livesCount);
		handleKeyPress(pac, scoreCount, livesCount, board);
		handleFruitMovement(newFruit, fruitFlag, pac, countFruit, timeFruit, eatFruit);
		handleFruitEating(newFruit, eatFruit, scoreCount, countFruit, timeFruit);
		handleFoodEating(pac, scoreCount, checkScore, board);
		handlePacmanKill(pac, livesCount, board, ghostsArr);

		if (pac.isWall(board, pac.getDirection(), pac.getPoint().getX(), pac.getPoint().getY()))
			pac.setDirection(STAY);
		else
		{
			pac.move(board.getBoardSize());
			movePac++;
			countFruit++;
			timeFruit++;
			if (movePac == 2)
			{
				flagGhost = true;
				movePac = 0;
			}
			if (flagGhost)
			{
					for (i = 0; i < board.getGhostArrLen(); i++)
						ghostsArr[i].move(board.getBlock(ghostsArr[i].getPoint().getX(), ghostsArr[i].getPoint().getY()), board, pac.getPoint(), level, board.getGhostArrLen());
				moveGhost++;
			
				flagGhost = false;
			}
			if (moveGhost == 2)
			{
				fruitFlag = true;
				moveGhost = 0;
			}
			Sleep(100);

		}
	} while (checkScore > 0 && livesCount != 0);

	clear_screen();
	*score = scoreCount;
	*lives = livesCount;
	if (livesCount == 0)
		return false;
	else
		return true;
}

//initialise ghosts in positionsr
void System::initGhosts()
{
	for (int i = 0; i < board.getGhostArrLen(); i++)
	{
		ghostsArr.push_back(Ghost(board.getGhostCoords(i), GHOST));
	}
}

//print pause game
void System::pauseGame() const
{
	clear_screen();
	cout << "Game paused, press ESC again to continue.";
	_kbhit();
}

//boolean check if the pacman eat breadcramb in current point
bool System::isFood(const int& x, const int& y)const
{
	char ch = board.getBlock(x, y);
	return(ch == FOOD);
}

//boolean check if the ghosts eats the pacman or fruit
bool System::isKill(const Point& creatureCoords)const
{
	for (int i = 0; i < board.getGhostArrLen(); i++)
		if(creatureCoords == ghostsArr[i].getPoint())
			return true;
	return false;
}

//boolean check if the pacman eat the fruit
bool System::isEaten(const Point& pacmanCoords, const Point& fruitCoords)const
{
	Point temp;
	int i, j;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			temp.setX(pacmanCoords.getX() + i);
			temp.setY(pacmanCoords.getY() + j);
			if (temp == fruitCoords)
				return true;
		}
	}
	return false;
}

//draw the char that received to the screen
void System::draw(const int& x, const int& y, const char& ch)const
{
	gotoxy(x, y);
	cout << ch << endl;
}

//showing ghosts
void System::showGhosts() const
{
	for (int i = 0; i < board.getGhostArrLen(); i++)
		ghostsArr[i].show(board.getGhostCoords(i).getX(), board.getGhostCoords(i).getY());
}

//randomizing valid location for the fruit
Point System::locationForFruit()const
{
	Point temp;
	int x, y;
	srand((unsigned int)time(NULL));
	x = rand() % board.getBoardSize().getX();
	y = rand() % board.getBoardSize().getY();
	while (!isValidLoc(x, y))
	{
		x = rand() % board.getBoardSize().getX();
		y = rand() % board.getBoardSize().getY();
	}
	temp.setX(x);
	temp.setY(y);
	return temp;
}

//boolean check if the location for the fruit is valid
bool System::isValidLoc(const int& x, const int& y)const
{
	return ((board.getBlock(x, y) == FOOD) || (board.getBlock(x, y) == SPACE));
}

//controling the kee press of the user and implementing the outcome tof the press
void System::handleKeyPress(Pacman& pacman, const int& scoreCount, const int& livesCount, const BoardGame& board)
{
	if (_kbhit())
	{
		int key = _getch();
		if (key == ESC)
		{
			pauseGame();
			key = _getch();
			while (key != ESC)
			{
				_kbhit();
				key = _getch();
			}
			clear_screen();
			board.printBoard(scoreCount, livesCount);
		}
		else
		{
			int tempKey = key;
			if (isupper(tempKey))
				key = tolower(tempKey);

			int dir = pacman.getDirectionFromKB(key);
			if (dir != -1)
			{
				pacman.setDirection(dir);
			}
		}
	}
}

//controling fruit movement
void System::handleFruitMovement(Fruit* newFruit, bool& fruitFlag, const Pacman& pacman, int& countFruit, int& timeFruit, bool& eatFruit)
{
	if (newFruit && fruitFlag)
	{
		fruitFlag = false;
		newFruit->move(board.getBlock(newFruit->getPoint().getX(), newFruit->getPoint().getY()), board);
		eatFruit = isEaten(pacman.getPoint(), newFruit->getPoint());
	}
}

//controling fruit eating and outcomes in the game
void System::handleFruitEating(Fruit*& newFruit, const bool& eatFruit, int& scoreCount, int& countFruit, int& timeFruit)
{
	if (countFruit == 100 || eatFruit || (newFruit && isKill(newFruit->getPoint())))
	{
		if (newFruit)
		{
			if (eatFruit)
			{
				int fruitScore = int(newFruit->getFigure() - '0');
				scoreCount += fruitScore;
			}
			char ch = board.getBlock(newFruit->getPoint().getX(), newFruit->getPoint().getY());
			newFruit->Creature::setFigure(ch);
			newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());
			delete newFruit;
			newFruit = nullptr;
		}
		else if (timeFruit == 200)
		{
			timeFruit = 0;
			Point location = locationForFruit();
			newFruit = new Fruit(location, '0');
			newFruit->setFigure();
			newFruit->show(newFruit->getPoint().getX(), newFruit->getPoint().getY());
		}
		countFruit = 0;
	}
}

//controling food eating and outcomes in the game
void System::handleFoodEating(Pacman& pacman, int& scoreCount, int& checkScore, BoardGame& board)
{
	if (isFood(pacman.getPoint().getX(), pacman.getPoint().getY()))
	{
		if (pacman.getDirection() != STAY)
		{
			scoreCount++;
			checkScore--;
			board.updateBoard(pacman.getPoint().getX(), pacman.getPoint().getY(), SPACE);
		}
	}
}

//controling pacmen lives and outcomes in the game
void System::handlePacmanKill(Pacman& pacman, int& livesCount, BoardGame& board, vector<Ghost>& vecGhosts)
{
	if (isKill(pacman.getPoint()))
	{
		livesCount--;
		draw(pacman.getPoint().getX(), pacman.getPoint().getY(), SPACE);
		for (int i = 0; i < board.getGhostArrLen(); i++)
			draw(vecGhosts[i].getPoint().getX(), vecGhosts[i].getPoint().getY(), board.getBlock(vecGhosts[i].getPoint().getX(), vecGhosts[i].getPoint().getY()));
		pacman.setBody(board.getPacmanCoords());
		pacman.setDirection(STAY);
		for (int i = 0; i < board.getGhostArrLen(); i++)
			vecGhosts[i].setBody(board.getGhostCoords(i));
		showGhosts();
	}
}
