#include "Board.h"
//ctor
BoardGame::BoardGame(const string& screenName)
{
	board.resize(MAXROWS);
	for (int i = 0; i < board.size(); i++)
		board[i].resize(MAXCOLS);
	this->screenName = screenName;
	isValid = setBoard();
}
//updating the score of a user in the game
void BoardGame::setScore(const int& x, const int& y)
{
	score.setX(x);
	score.setY(y);
}
//updating the lives of a user in the game
void BoardGame::setLives(const int& x, const int& y)
{
	lives.setX(x);
	lives.setY(y);
}
//Choosing a screen to play with
void BoardGame::setScreenName(const string& name)
{
	screenName = name;
}
//initializing the board
bool BoardGame::setBoard()
{
	fstream file;
	Point ghostPos;
	int len, i = 0, j = 0, count = 0, vecSize = 0, maxCol=0, k=0;
	char c, prevC = 0;
	char score[] = "SCORE = 0           ";
	char lives[] = "LIVES = 0           ";
	file.open(screenName, ios::in);
	if (!file)
	{
		cout << "file is not open!" << endl;
		return false;
	}
	while (((c = char(file.get())) != EOF) && (i < MAXROWS))
	{
		if (c == '\n')
		{
			if (i == 0)
			{
				maxCol = j;
				j = 0;
			}
			else
			{
				if (j < maxCol)
					for (j; j < maxCol; j++)
						board[i][j] = SPACE;
				j = 0;
			}
			i++;
		}
		else
		{
			if (i < MAXROWS)
			{
				board[i][j] = c;
				prevC = c;
				j++;
			}
		}
	}
	k = i;
	i++;
	if (i > MAXROWS)
	{
		i = MAXROWS;
	}
	size.setX(maxCol);
	size.setY(i);
	for (i = 0; i < board.size(); i++)
	{
		for (j = 0; j < maxCol; j++)
		{
			switch (board[i][j])
			{
			case ' ':
				board[i][j] = FOOD;
				count++;
				break;
			case '%':
				board[i][j] = SPACE;
				break;
			case '@':
				playerCoord.setX(j);
				playerCoord.setY(i);
				board[i][j] = SPACE;
				break;
			case '$':
				ghostPos.setX(j);
				ghostPos.setY(i);
				ghostsArr.push_back(ghostPos);
				board[i][j] = SPACE;
				break;
			default:
				break;
			}
		}
	}
	scoreWin = count;
	j = 0;
	len = int(strlen(score));
	unsigned int textHeight = this->getBoardSize().getY() + 2;
	for (i = 0; i < len; i++)
	{
		if (score[j] == '0')
		{
			setScore(i + 10, textHeight);
			setLives(i + 59, textHeight);
		}
		
		j++;
	}
	
	file.close();
	return true;
}

char BoardGame::getBlock(const int& x, const int& y) const
{
	return board[y][x];
}
//get the winning score of the game
int BoardGame::getScoreWin() const
{
	return scoreWin;
}
//get position of pacman
const Point& BoardGame:: getPacmanCoords()const
{
	return playerCoord;
}
//get Ghost Size 
int BoardGame::getGhostArrLen()const
{
	return int(ghostsArr.size());
}
//get Ghost position 
const Point& BoardGame::getGhostCoords(const int& i)const
{
	return ghostsArr[i];
}
//get board size
const Point& BoardGame::getBoardSize()const
{
	return size;
}
//get validity of board
bool BoardGame::getVaildity() const
{
	return isValid;
}
//print user score on screen
void BoardGame::printScore(const int& counter) const
{
	gotoxy(score.getX(), score.getY());
	cout << counter;
}
//print lives of pacmen in screen 
void BoardGame::printLives(const int& counter) const
{
	gotoxy(lives.getX(), lives.getY());
	cout << counter;
}
//print the board on screen 
void BoardGame::printBoard(const int& score, const int& lives) const
{
	int i, j;
	for (i = 0; i < size.getY(); i++)
	{
		for (j = 0; j < size.getX(); j++)
			cout << board[i][j];
		cout << endl;
	}

	cout << "                                                                                \n"
		"                                PACMAN GAME                                     \n"
		"          SCORE =                                         LIVES =               \n"
		"                                                                                \n";
	printScore(score);
	printLives(lives);
}
//update the board
void BoardGame::updateBoard(const int& x, const int& y, const char& ch)
{
	board[y][x] = ch;
}


