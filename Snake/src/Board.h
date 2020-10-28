/**
 * @file Board.h
 *
 * @brief Header file for Board class. A Board keeps track of each cell of the game.
 *
 * @author Luke Lo Presti
 * Date: 23-Oct-2020
 *
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Cell.h"
#include "Snake.h"

class Board
{
public:
	Board(int columns, int rows, float offset, float cellSize);
	~Board();

	void update(sf::Time deltaTime);
	void draw(sf::RenderWindow* window);

	Snake* getSnake();

	void spawnFood();
	void checkForCollisions();
	void reset();

private:
	int mColumns;
	int mRows;
	float mOffset;
	float mCellSize;

	Snake mSnake;
	std::vector<Cell> mFoodCells;
};
