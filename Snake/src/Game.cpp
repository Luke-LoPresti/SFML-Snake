/**
 * @file Game.cpp
 *
 * @brief Implementation of Game class. Handles game loop and user inputs.
 *
 * @author Luke Lo Presti
 * Date: 23-Oct-2020
 *
 */

#include "Game.h"

#include <iostream>

const uint32_t Game::kWindowWidth = 640;
const uint32_t Game::kWindowHeight = 480;

const float Game::kPadding = 40.f;
const float Game::kCellSize = 20.f;

// 60 frames per second
const float kFrameRate = 60.f;	
const sf::Time Game::kTimePerFrame = sf::seconds(1.f / kFrameRate);

Game::Game()
	: mWindow(sf::VideoMode(kWindowWidth, kWindowHeight), "SFML Snake"),
	  mBoard((int)((kWindowWidth - 2 * kPadding) / kCellSize), 
		     (int)((kWindowHeight - 2 * kPadding) / kCellSize), 
		     kPadding, 
		     kCellSize)
{
	loadResources();
}

Game::~Game()
{
}

void Game::run()
{
	// game loop
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;	// init to 0

	while (isRunning())
	{
		timeSinceLastUpdate += clock.restart();

		// perform the updates for each frame since the last update
		while (timeSinceLastUpdate > kTimePerFrame)
		{
			timeSinceLastUpdate -= kTimePerFrame;
			processEvents();
			update(kTimePerFrame);
		}

		render();
	}
}

void Game::loadResources()
{
	if (!mFont.loadFromFile("resources/font/calibri.ttf"))
	{
		std::cout << "Failed to load font." << std::endl;
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code);
				break;

			case sf::Event::Closed:
				// close the window - exits game loop
				mWindow.close();
				break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	if (mBoard.getSnake()->isAlive())
	{
		// only update if snake is alive
		mBoard.update(deltaTime);
	}
}

void Game::render()
{
	mWindow.clear();

	if (mBoard.getSnake()->isAlive())
	{
		// draw board if snake is alive
		mBoard.draw(&mWindow);
		drawScore();
	}
	else
	{
		drawGameOver();
	}

	mWindow.display();
}

void Game::drawScore()
{
	sf::Text scoreText = createText("Score: " + std::to_string(mBoard.getSnake()->getScore()), 20);
	scoreText.setPosition(kPadding, 5.f);
	mWindow.draw(scoreText);
}

void Game::drawGameOver()
{
	sf::Text finalScoreText = createText("Final Score: " + std::to_string(mBoard.getSnake()->getScore()), 40);
	centerText(finalScoreText, 0.f, -60.f);		// center text and shift it 60 units up from the center
	mWindow.draw(finalScoreText);

	sf::Text playAgainText = createText("Press 'SPACE' to Play Again", 40);
	centerText(playAgainText, 0.f, 20.f);		// center text and shift it 20 units down from the center
	mWindow.draw(playAgainText);
}

sf::Text Game::createText(const std::string& text, uint32_t characterSize)
{
	sf::Text sfText;
	sfText.setFont(mFont);
	sfText.setCharacterSize(characterSize);
	sfText.setString(text);

	return sfText;
}

void Game::centerText(sf::Text& text, float xOffset, float yOffset)
{
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f((kWindowWidth / 2.0f) + xOffset, (kWindowHeight / 2.0f) + yOffset));
}

bool Game::isRunning()
{
	return mWindow.isOpen();
}

void Game::handlePlayerInput(const sf::Keyboard::Key& key)
{
	switch (key)
	{
		case sf::Keyboard::Up:
			mBoard.getSnake()->queueNextDirection(Snake::Direction::kUp);
			break;

		case sf::Keyboard::Down:
			mBoard.getSnake()->queueNextDirection(Snake::Direction::kDown);
			break;

		case sf::Keyboard::Left:
			mBoard.getSnake()->queueNextDirection(Snake::Direction::kLeft);
			break;

		case sf::Keyboard::Right:
			mBoard.getSnake()->queueNextDirection(Snake::Direction::kRight);
			break;

		case sf::Keyboard::Space:
			if (!mBoard.getSnake()->isAlive())
			{
				// only processes the space key press if the snake is dead
				mBoard.reset();
			}
			break;
	}
}
