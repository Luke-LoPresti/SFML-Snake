/**
 * @file Board.cpp
 *
 * @brief Implementation of Board class. A Board keeps track of each cell of the game.
 *
 * @author Luke Lo Presti
 * Date: 23-Oct-2020
 *
 */

#include "Board.h"
#include "Random.h"

Board::Board(int columns, int rows, float offset, float cellSize)
	: mColumns(columns),
	  mRows(rows),
	  mOffset(offset),
	  mCellSize(cellSize),
	  mSnake(columns / 2, rows / 2, offset, cellSize)
{
	spawnFood();
}

Board::~Board()
{
}

void Board::update(sf::Time deltaTime)
{
	mSnake.update(deltaTime);

	checkForCollisions();

	spawnFood();
}

void Board::checkForCollisions()
{
	// check if the snake is outside the board 
	// or if the head is in the body (snake hit itself)
	if (mSnake.getHead().getX() >= mColumns || mSnake.getHead().getX() < 0 ||
		mSnake.getHead().getY() >= mRows || mSnake.getHead().getY() < 0 ||
		mSnake.isCellInSnakeBody(mSnake.getHead()))
	{
		// kill the snake
		mSnake.kill();
		return;
	}

	// check if snake is on a food cell
	for (auto it = mFoodCells.begin(); it < mFoodCells.end(); ++it)
	{
		if (mSnake.getHead().isAtPoint(it->getX(), it->getY()))
		{
			// increase the size of the snake and remove the food cell
			mSnake.grow();
			mFoodCells.erase(it);

			// snake head can only be on one food cell at a time so break loop
			break;
		}
	}
}

void Board::draw(sf::RenderWindow* window)
{
	// draw the board as a rectangle's outline
	sf::RectangleShape boardRect(sf::Vector2f(mCellSize * mColumns, mCellSize * mRows));
	boardRect.setPosition(sf::Vector2f(mOffset, mOffset));

	boardRect.setOutlineThickness(5.f);
	boardRect.setOutlineColor(sf::Color::White);

	boardRect.setFillColor(sf::Color::Black);

	window->draw(boardRect);

	// draw all food
	for (const auto& foodCell : mFoodCells)
	{
		foodCell.draw(window, sf::Color::Red);
	}

	// draw the snake
	mSnake.draw(window);
}

void Board::reset()
{
	// create a new snake
	mSnake = Snake(mColumns / 2, mRows / 2, mOffset, mCellSize);

	// remove all food and spawn a new piece of food
	mFoodCells.clear();
	spawnFood();
}

void Board::spawnFood()
{
	// we will spawn 1 extra piece of food when the player reaches a score that is a multiple of 10
	const int numberOfFoodToSpawn = mSnake.getScore() / 10 + 1;

	if (mFoodCells.size() == (size_t)numberOfFoodToSpawn)
	{
		return;
	}

	utility::Random r = utility::Random();
	int randomPosX;
	int randomPosY;

	// while there is food to spawn
	while (mFoodCells.size() < (size_t)numberOfFoodToSpawn)
	{
		Cell foodCell;

		// keep getting a food x/y point until we get one not already in the snake
		do
		{
			randomPosX = r.getRandomNumber(0, mColumns - 1);
			randomPosY = r.getRandomNumber(0, mRows - 1);
			foodCell = Cell(randomPosX, randomPosY, mOffset, mCellSize);

		} while (mSnake.isCellInSnake(foodCell));

		mFoodCells.push_back(foodCell);
	}
}

Snake* Board::getSnake()
{
	return &mSnake;
}