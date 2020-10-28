/**
 * @file Snake.h
 *
 * @brief Implementation of Snake class.
 *
 * @author Luke Lo Presti
 * Date: 23-Oct-2020
 *
 */

#include "Snake.h"

const int Snake::kInitialLength = 3;

Snake::Snake(int initialX, int initialY, float offset, float cellSize)
	: mSpeed(0.f),
	  mAlive(true),
      mCurrentDirection(Direction::kRight),
	  mHead(initialX, initialY, offset, cellSize),
	  mTimeSinceLastUpdate(sf::Time::Zero)
{
	for (int i = 1; i < kInitialLength; ++i)
	{
		mBody.emplace_back(initialX - i, initialY, offset, cellSize);
	}
}

Snake::~Snake()
{
}

void Snake::update(sf::Time deltaTime)
{
	if (mSpeed == 0.f)
	{
		// no need to update
		return;
	}

	// only update if the time elaspsed it greater than the update speed
	mTimeSinceLastUpdate += deltaTime;
	if (mTimeSinceLastUpdate > sf::seconds(1.f / mSpeed))
	{
		// push the current head into the body
		mBody.push_front(mHead);

		// remove the tail
		mBody.pop_back();

		auto nextDirection = mCurrentDirection;

		// get the next direction from the queue. the next direction cannot be the same as the current direction
		while (!mNextDirectionQueue.empty() && (nextDirection == mCurrentDirection))
		{
			// if the direction is not valid, just skip it
			if (validDirection(mNextDirectionQueue.front()))
			{ 
				nextDirection = mNextDirectionQueue.front();
			}
			
			mNextDirectionQueue.pop();
		}

		// update the new head to the new location
		switch (nextDirection)
		{
			case Direction::kUp:
				mHead.setY(mHead.getY() - 1);
				break;

			case Direction::kDown:
				mHead.setY(mHead.getY() + 1);
				break;

			case Direction::kLeft:
				mHead.setX(mHead.getX() - 1);
				break;

			case Direction::kRight:
				mHead.setX(mHead.getX() + 1);
				break;
		}

		mCurrentDirection = nextDirection;

		mTimeSinceLastUpdate = sf::Time::Zero;
	}
}

void Snake::draw(sf::RenderWindow* window)
{
	// draw each snake cell as a different colour based on it's index
	// Y = Yellow, L = Lime, G = Green, DG = Dark Green
	// h, 0, 1,  2, 3, 4, 5,  6, 7, 8,  9
	// Y, L, G, DG, G, L, G, DG, L, G, DG

	for (size_t i = 0; i < mBody.size(); ++i)
	{
		sf::Color c;
		if (i % 4 == 0)
		{
			// lime
			c = sf::Color(20, 200, 40);
		}
		else if (i % 4 == 1 || i % 4 == 3)
		{
			// green
			c = sf::Color(20, 160, 40);
		}
		else
		{
			// dark green
			c = sf::Color(20, 120, 40);
		}

		mBody[i].draw(window, c);
	}

	mHead.draw(window, sf::Color::Yellow);
}

void Snake::queueNextDirection(const Direction& direction)
{
	// if not moving, check that the first move is a valid direction
	if (mSpeed == 0)
	{
		if (validDirection(direction))
		{
			// increase the speed so the snake can start moving
			mSpeed = 5.f;
		}
	}

	// queue the move
	mNextDirectionQueue.push(direction);
}

void Snake::grow()
{
	// add a new part to the end of the snake
	mBody.emplace_back(mBody.back());

	// start increasing speed after a score of 5
	// cap max speed at 60
	if (getScore() > 5 && mSpeed < 60.f)
	{
		mSpeed += 0.5f;
	}
}

void Snake::kill()
{
	mAlive = false;
}

const Cell& Snake::getHead() const
{
	return mHead;
}

int Snake::getScore() const
{
	return mBody.size() - kInitialLength + 1;
}

bool Snake::isAlive() const
{
	return mAlive;
}

bool Snake::isCellInSnake(const Cell& cell) const
{
	// check if the cell is at the head
	if (isCellAtSnakeHead(cell))
	{
		return true;
	}

	// otherwise check if the cell is anywhere in the snake body
	return isCellInSnakeBody(cell);
}

bool Snake::isCellAtSnakeHead(const Cell& cell) const
{
	return mHead.isAtPoint(cell);
}

bool Snake::isCellInSnakeBody(const Cell& cell) const
{
	for (const auto& bodyCell : mBody)
	{
		if (bodyCell.isAtPoint(cell))
		{
			return true;
		}
	}

	return false;
}

bool Snake::validDirection(const Direction& direction)
{
	switch (direction)
	{
		case Direction::kUp:
			return mCurrentDirection != Direction::kDown;

		case Direction::kDown:
			return mCurrentDirection != Direction::kUp;

		case Direction::kLeft:
			return mCurrentDirection != Direction::kRight;

		case Direction::kRight:
			return mCurrentDirection != Direction::kLeft;
	}

	return false;
}