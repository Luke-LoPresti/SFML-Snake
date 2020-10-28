/**
 * @file Cell.h
 *
 * @brief Header file for Cell class. A Cell in an x/y point on a board.
 *
 * @author Luke Lo Presti
 * Date: 23-Oct-2020
 *
 */

#pragma once
#include <SFML/Graphics.hpp>

class Cell
{
public:
	Cell(int x, int y, float offset, float size);
	Cell() = default;
	~Cell();

	int getX() const;
	int getY() const;

	bool isAtPoint(int x, int y) const;
	bool isAtPoint(const Cell& cell) const;

	void setX(int x);
	void setY(int y);

	void draw(sf::RenderWindow* window, const sf::Color&) const;

private:
	int mX;
	int mY;
	float mOffset;
	float mSize;
};
