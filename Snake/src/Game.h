/**
 * @file Game.h
 *
 * @brief Header file for Game class. Handles game loop and user inputs.
 *
 * @author Luke Lo Presti
 * Date: 23-Oct-2020
 *
 */

#pragma once
#include <SFML/Graphics.hpp>

#include "Board.h"

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	// private constants
	static const uint32_t kWindowWidth;
	static const uint32_t kWindowHeight;

	static const float kPadding;
	static const float kCellSize;

	static const float kFramerate;
	static const sf::Time kTimePerFrame;

	// private funtions
	void loadResources();

	void processEvents();
	void update(sf::Time deltaTime);
	void render();

	void drawScore();
	void drawGameOver();
	sf::Text createText(const std::string& text, uint32_t characterSize);
	void centerText(sf::Text& text, float xOffset, float yOffset);

	bool isRunning();
	void handlePlayerInput(const sf::Keyboard::Key& key);

	// member variables
	sf::RenderWindow mWindow;
	sf::Font mFont;

	Board mBoard;
};
