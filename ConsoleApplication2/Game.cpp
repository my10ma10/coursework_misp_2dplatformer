#include "Game.h"

Game::Game(GameState& gameState, const std::string& iconPath, const std::string& backgroundPath, unsigned int& levelIndex) : 
	currentState(gameState),
	currentLevel(levelIndex),
	level(backgroundPath, levelIndex),
	window(VideoMode(1080, 1080), L"Игра", Style::Default),
	prevState(GameState::Main),
	menu(window, gameState, levelIndex),
	timeStep(1.0f / 60.0f),
	accumulator(0.0f),
	availableLevel(1),
	levelView(Vector2f(0.0f, 0.0f), Vector2f(LevelViewHeight, LevelViewHeight)),
	menuView(Vector2f(0.0f, 0.0f), Vector2f(MenuViewHeight, MenuViewHeight))
{
	window.setVerticalSyncEnabled(true);
	Image icon;
	if (icon.loadFromFile(iconPath)) 
	{
		window.setIcon(512, 512, icon.getPixelsPtr());
	}
	initView();
	Vector2i viewRectSize(LevelViewHeight * 1.0f, LevelViewHeight * 1.0f);
	IntRect viewRectBounds(Vector2i(level.getPlayerPosition().x - viewRectSize.x / 2.0f, \
		level.getPlayerPosition().y - viewRectSize.y / 2.0f), viewRectSize);
	playerAndViewCollideSprite.setTextureRect(viewRectBounds);
	playerAndViewCollider = Collider(playerAndViewCollideSprite);
	backCollider = Collider(levelLimitViewSprite);

	menu.setCallback([this](bool pred) 
		{
			isProcessPaused = pred;
		}
	);
}

void Game::run()
{
	while (window.isOpen()) 
	{
		Time elapsed = clock.restart();
		accumulator += elapsed.asSeconds();

		processEvents();

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
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape)
			{
				isProcessPaused = !isProcessPaused; 
			}
			break;
		default:
			break;
		}
	}
}


void Game::update(float timeStep)
{
	changeViewAspectRatio(levelView);
	changeViewAspectRatio(menuView);
	processPause();

	currentLevel = menu.getLevelNumber();

	if (currentState == GameState::Game)
	{
		switch (level.getState())
		{
		case LevelState::Failed:
			currentState = GameState::GameOver;
			break;
		case LevelState::Complete:
			currentState = GameState::Complete;
			updateAvailables();
			level.changeLevel(currentLevel);
			break;
		case LevelState::Passing:
			level.update(timeStep, levelView);
			break;
		default:
			break;
		}

		level.updatePlatfotmsCollide();
		level.updateColliders(levelView, backCollider, levelLimitViewSprite,
			playerAndViewCollideSprite, playerAndViewCollider);
	}
	else
	{
		menu.update(currentState, availableLevel, currentLevel);
		if (level.getNumber() != menu.getLevelNumber())
		{
			level.changeLevel(currentLevel);
		}
		checkState();

	}
	//std::cout << "Level Num: " << level.getNumber() \
	//	<< ", Available: " << availableLevel \
	//	<< ", Menu num: " << menu.getLevelNumber() << std::endl;
}

void Game::render()
{
	window.clear(Color::White);
	Font font;
	if (currentState == GameState::Game)
	{
		window.setView(levelView);
		level.draw(window);
	}
	else
	{
		menuView.setCenter(menu.getCenter());
		window.setView(menuView);
		menu.render(currentState);
	}
	window.display();
}

void Game::updateAvailables()
{
	if (level.getState() == LevelState::Complete and level.getNumber() == availableLevel)
	{
		availableLevel += 1;
	}
}

void Game::initView()
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	levelView.setSize(aspectRatio * LevelViewWidth, LevelViewHeight);
	menuView.setSize(aspectRatio * MenuViewWidth, MenuViewHeight);
}

void Game::changeViewAspectRatio(View& view) const
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	if (currentState == GameState::Game)
	{
		view.setSize(aspectRatio * LevelViewWidth, LevelViewHeight);
	}
	else
	{
		view.setSize(aspectRatio * MenuViewWidth, MenuViewHeight);
	}
}

void Game::checkState()
{
	if (level.getState() != LevelState::Passing ||
		(currentState == GameState::Main && prevState == GameState::Paused))
	{
		level.restart();
	}
	if (prevState != currentState)
	{
		prevState = currentState;
		menu.setClickable(false);
	}
}

void Game::processPause()
{
	if (isProcessPaused and currentState == GameState::Game)
	{
		currentState = GameState::Paused;
	}
	else if (!isProcessPaused and currentState == GameState::Paused)
	{
		currentState = GameState::Game;
	}
}

unsigned int Game::getCurrentLevel() const
{
	return currentLevel;
}
