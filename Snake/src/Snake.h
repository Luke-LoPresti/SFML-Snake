/**
 * @file Snake.h
 *
 * @brief Header file for Snake class.
 *
 * @author Luke Lo Presti
 * Date: 23-Oct-2020
 *
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <queue>

#include "Cell.h"

class Snake
{
public:
	// enum for snake's direction
	enum class Direction
	{
		kUp,
		kDown,
		kLeft,
		kRight,
		kUnknown
	};

	Snake() = default;
	Snake(int initialX, int initialY, float offset, float cellSize);
	~Snake();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* window);

	void queueNextDirection(const Direction& direction);

	void grow();
	void kill();

	const Cell& getHead() const;
	int getScore() const;

	bool isAlive() const;
	bool isCellInSnake(const Cell& cell) const;
	bool isCellAtSnakeHead(const Cell& cell) const;
	bool isCellInSnakeBody(const Cell& cell) const;

private:
	// private constants
	static const int kInitialLength;

	// private functions
	bool validDirection(const Direction& direction);

	// member variables
	float mSpeed;
	bool mAlive;

	Direction mCurrentDirection;
	std::queue<Direction> mNextDirectionQueue;

	Cell mHead;
	std::deque<Cell> mBody;

	sf::Time mTimeSinceLastUpdate;
};
