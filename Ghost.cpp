#include "Ghost.h"

//c'tor 
Ghost::Ghost(const Point& body, const char& figure) : Creature(body, figure)
{ 
	setPossibleDir(); 
	setDirection();
}

//this function move and draw the ghost
void Ghost::move(const char& ch, const BoardGame& board, const Point& pacPoint, const int& level, const int& numOfGhosts)
{
	body.draw(ch);
	moveByLevel(board, pacPoint, level, numOfGhosts);
	body.draw(figure);
}

//comtroling ilustration of levet of the game
void Ghost::moveByLevel(const BoardGame& board, const Point& pacmanPoint, const int& level, const int& numOfGhosts)
{
	static int countBest, countGood, countGoodRandom, countNovice;
	static bool flagGood;
	switch (level)
	{
	case BEST:
		if (countBest < numOfGhosts)
		{
			setDirection();
			moveGhost(direction, board);
		}
		else
			smartMove(board, pacmanPoint);
		if (countBest == 20 * numOfGhosts)
			countBest = 0;
		countBest++;
		break;
	case GOOD:
		if (countGood == (20*numOfGhosts))
		{
			flagGood = true;
		}
		if (flagGood)
		{
			if (countGoodRandom < numOfGhosts)
			{
				setDirection();
				moveGhost(direction, board);
			}
			else
			{
				moveGhost(direction, board);
				countGood = 0;
			}
			countGoodRandom++;
		}
		else
			smartMove(board, pacmanPoint);
		if (countGoodRandom == (10*numOfGhosts))
		{
			flagGood = false;
			countGoodRandom = 0;
		}
		countGood++;
		break;
	case NOVICE:
		if(countNovice < numOfGhosts)
			setDirection();
		moveGhost(direction, board);
		if(countNovice == (20*numOfGhosts))
		{ 
			countNovice = 0;
		}
		countNovice++;
		break;
	}
}

//moving the gost on screen 
void Ghost::moveGhost(const int& direction, const BoardGame& board)
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

//sugesting posible goest direction
void Ghost::setPossibleDir()
{
	possibleDir[UP] = UP;
	possibleDir[DOWN] = DOWN;
	possibleDir[LEFT] = LEFT;
	possibleDir[RIGHT] = RIGHT;
}

//setting the gost direction
void Ghost::setDirection()
{
	srand((unsigned int)time(NULL));
	direction = possibleDir[rand() % SIZEDIR];
}

//setting smart direction for goest
void Ghost::setSmartDirection(const int& direction)
{
	this->direction = direction;
}

//the function move the smart ghost by bfs algorithem
void Ghost::smartMove(const BoardGame& board, const Point& pacmanPoint)
{
    int xGhostPos = getPoint().getX(), yGhostPos = getPoint().getY();
    vector<vector<bool>> visit(board.getBoardSize().getY(), vector<bool>(board.getBoardSize().getX(), false));
    Point newPoint = BFS(board, visit, pacmanPoint);

    if (newPoint.getX() == xGhostPos - 1) //left
		body.setX(--xGhostPos);
		
    else if (newPoint.getX() == xGhostPos + 1) //right
		body.setX(++xGhostPos);

    else if (newPoint.getY() == yGhostPos - 1) //up
		body.setY(--yGhostPos);

    else 
		body.setY(++yGhostPos); // down
}

//check the validity of smart ghost next step 
bool Ghost::isValidStep(const vector<vector<bool>>& visit, const int& row, const int& col, const BoardGame& board)const
{
    if (row >= board.getBoardSize().getY() || col >= board.getBoardSize().getX() || row <= 0 || col <=0)
        return false;

	if (board.getBlock(col, row) == WALL)
		return false;

    if (visit[row][col])
        return false;

    return true;
}

//bfs algorithem
Point Ghost::BFS(const BoardGame& board, vector<vector<bool>>& visit, const Point& pacPoint)const
{
	Point ghostPoint = getPoint();
    int dirRow[] = { -1, 0, 1, 0 };
    int dirCol[] = { 0, 1, 0, -1 };
    // Stores indices of the matrix cells
    queue<Point> q;
    // Mark the starting cell as visited and push it into the queue
	Point currPos;
	currPos.setX((pacPoint.getX()));
	currPos.setY((pacPoint.getY()));
    q.push(currPos);
    visit[pacPoint.getY()][pacPoint.getX()] = true;
    // Iterate while the queue is not empty
    while (!q.empty()) 
	{
        Point currCell = q.front();
        int x = currCell.getX();
        int y = currCell.getY();
        q.pop();
        // Go to the adjacent cells
        for (int i = 0; i < 4; i++) {
            int adjY = y + dirRow[i];
            int adjX = x + dirCol[i];
			Point adjPoint(adjX, adjY);
            if (adjPoint == ghostPoint)
                return Point(x, y);
            else if (isValidStep(visit, adjY, adjX, board)) {
                q.push(adjPoint);
                visit[adjY][adjX] = true;
            }
        }
    }

    // if short way has not found - return the curr position
    return getPoint();
}