#include "Game.h"

Game::Game(const std::string& iconPath, const std::string& coinSheetPath, const std::string& bonusSheetPath, \
	const std::string& backgroundPath, unsigned int levelIndex) : levelIndex(levelIndex), \
	level(coinSheetPath, bonusSheetPath, backgroundPath, levelIndex), \
	window(VideoMode(1024, 1024), L"Игра", Style::Default), \
	gameState(GameState::Game),
	menu(window),
	timeStep(1.0f / 60.0f),
	accumulator(0.0f),
	isPaused(false),
	levelView(Vector2f(0.0f, 0.0f), Vector2f(LevelViewHeight, LevelViewHeight)),
	menuView(Vector2f(0.0f, 0.0f), Vector2f(MenuViewHeight, MenuViewHeight))
{
	Image icon;
	if (icon.loadFromFile(iconPath)) 
	{
		window.setIcon(512, 512, icon.getPixelsPtr());
	}

	levelView.setCenter(level.getPlayerPosition());

	Vector2i viewRectSize(LevelViewHeight * 1.0f, LevelViewHeight * 1.0f);
	IntRect viewRectBounds(Vector2i(level.getPlayerPosition().x - viewRectSize.x / 2.0f, \
		level.getPlayerPosition().y - viewRectSize.y / 2.0f), viewRectSize);
	playerAndViewCollideSprite.setTextureRect(viewRectBounds);
	playerAndViewCollider = Collider(playerAndViewCollideSprite);
	backCollider = Collider(levelLimitViewSprite);
}

void Game::run()
{
	while (window.isOpen()) 
	{
		Time elapsed = clock.restart();
		accumulator += elapsed.asSeconds();

		processEvents();

		if (isPaused) 
		{
			gameState = GameState::Menu;
		}
		else
		{
			gameState = GameState::Game;
		}

		while (accumulator >= timeStep) 
		{
			update(timeStep);
			accumulator -= timeStep;
		}

		render();
	}
}

void Game::processEvents()
{
	Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			window.close();
			break;
		case Event::Resized:
			changeViewAspectRatio(window, levelView);
			break;
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape)
			{
				isPaused = !isPaused;
			}
			changeViewZoom(levelView);
			break;
		default:
			break;
		}
	}
}


void Game::update(float timeStep)
{
//	healthBar.update(playerPtr->getEnergy(), levelView.getCenter() - levelView.getSize() / 2.25f);
//	energyBar.update(playerPtr->getHealth(), levelView.getCenter() - levelView.getSize() / 2.25f \
            + Vector2f(0.0f, 6.0f));
	
	switch (gameState)
	{
	case GameState::Menu:
		menu.update();
		break;
	case GameState::Game:
		if (isPaused)
		{
			break;
		}
		if (!level.getComplete())
		{
			level.update(timeStep);
		}
		level.updatePlatfotmsCollide();
		level.updateCoinCollecting();
		level.updateColliders(levelView, backCollider, levelLimitViewSprite, \
			playerAndViewCollideSprite, playerAndViewCollider);
		break;
	case GameState::Settings:
		break;
	case GameState::Exit:
		break;
	default:
		break;
	}


}

void Game::render()
{
	window.clear(Color::White); // basic

	Font font;
	switch (gameState)
	{
	case GameState::Menu:
		menuView.setCenter(level.getCenter());
		window.setView(menuView);
		menu.render();

		break;
	case GameState::Game:
		window.setView(levelView); // в gameUpdate, при разных условиях разный вид

		level.draw(window);

		//healthBar.draw(window);
		//energyBar.draw(window);
		break;
	case GameState::Settings:
		break;
	case GameState::Exit:
		break;
	default:
		break;
	}
	window.display();
}

void Game::changeViewZoom(View& view)
{
	if (Keyboard::isKeyPressed(Keyboard::Equal)) {
		view.zoom(0.995f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Dash)) {
		view.zoom(1.005f);
	}
}

void Game::changeViewAspectRatio(const RenderWindow& window, View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(aspectRatio * LevelViewHeight, LevelViewHeight);
}


