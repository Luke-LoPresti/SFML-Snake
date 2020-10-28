/**
 * @file Cell.cpp
 *
 * @brief Implementation of Cell class. A Cell in an x/y point on a board.
 *
 * @author Luke Lo Presti
 * Date: 23-Oct-2020
 *
 */

#include "Cell.h"

Cell::Cell(int x, int y, float offset, float size)
	: mX(x),
	  mY(y),
	  mOffset(offset),
	  mSize(size)
{
}

Cell::~Cell()
{
}

int Cell::getX() const 
{
	return mX;
}

int Cell::getY() const
{
	return mY;
}

bool Cell::isAtPoint(int x, int y) const
{
	return mX == x && mY == y;
}

bool Cell::isAtPoint(const Cell& cell) const
{
	return mX == cell.mX && mY == cell.mY;
}

void Cell::setX(int x)
{
	mX = x;
}

void Cell::setY(int y)
{
	mY = y;
}

void Cell::draw(sf::RenderWindow* window, const sf::Color& colour) const
{
	// draw the cell as a rectangle with the specified colour
	sf::RectangleShape cellRect(sf::Vector2f(mSize, mSize));
	cellRect.setPosition(sf::Vector2f(mOffset, mOffset) + sf::Vector2f((float)mX, (float)mY) * mSize);

	cellRect.setOutlineThickness(-1.f);
	cellRect.setOutlineColor(sf::Color::Black);
	
	cellRect.setFillColor(colour);
	
	window->draw(cellRect);
}
