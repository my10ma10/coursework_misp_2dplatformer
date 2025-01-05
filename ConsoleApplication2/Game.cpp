#include "Game.h"

Game::Game(const std::string& iconPath, const std::string& coinSheetPath, const std::string& bonusSheetPath, \
	const std::string& backgroundPath, unsigned int levelIndex) : currentLevel(levelIndex),
	level(coinSheetPath, bonusSheetPath, backgroundPath, levelIndex),
	window(VideoMode(1024, 1024), L"Игра", Style::Default),
	gameState(GameState::Main),
	menu(window),
	timeStep(1.0f / 60.0f),
	accumulator(0.0f),
	isProcessPaused(false),
	pauseState(true), 
	availableLevel(1),
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
			changeViewAspectRatio(window, menuView);
			break;
		case Event::KeyPressed:
			if (event.key.code == Keyboard::Escape)
			{
				isProcessPaused = !isProcessPaused; 
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
	if (gameState == GameState::Game)
	{
		if (!isProcessPaused)
		{
			switch (level.getState())
			{
			case LevelState::Failed:
				menu.setState(GameState::GameOver);
				break;
			case LevelState::Complete:
				menu.setState(GameState::Complete);
				break;
			case LevelState::Passing:
				level.update(timeStep, levelView);
				break;
			default:
				break;
			}
			level.updatePlatfotmsCollide();
			level.updateCoinCollecting();
			level.updateColliders(levelView, backCollider, levelLimitViewSprite, \
				playerAndViewCollideSprite, playerAndViewCollider);
		}
	}
	else
	{
		menu.update(availableLevel, currentLevel);
	}
	updateAvailables();
	currentLevel = level.getNumber();
	updateState();
	std::cout << static_cast<int>(menu.getState()) << std::endl;
}

void Game::render()
{
	window.clear(Color::White);

	Font font;
	if (gameState == GameState::Game)
	{
		window.setView(levelView);
		level.draw(window);
	}
	else
	{
		menuView.setCenter(menu.getCenter());
		window.setView(menuView);
		menu.render();
	}
	window.display();
}

void Game::updateAvailables()
{
	if (level.getState() == LevelState::Complete and level.getNumber() == availableLevel and availableLevel <= 5)
	{
		availableLevel = level.getNumber() + 1;
	}
}

void Game::updateState()
{
	gameState = menu.getState();
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

void Game::changeViewAspectRatio(const RenderWindow& window, View& view) const
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	if (gameState == GameState::Game)
	{
		view.setSize(aspectRatio * LevelViewHeight, LevelViewHeight);
	}
	else
	{
		view.setSize(aspectRatio * MenuViewHeight, MenuViewHeight);
	}
}

unsigned int Game::getCurrentLevel() const
{
	return currentLevel;
}
