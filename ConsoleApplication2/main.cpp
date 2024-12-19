#include "Game.h"

int main()
{
   Game game("Image\\icon.png", "Image\\coin-Sheet.png",
        "Image\\potion-Sheet.png", "Image\\back3.png", 1);
    game.run();/*
    RenderWindow window(VideoMode(1024, 1024), L"Игра", Style::Default);

    Image icon;
    if (!icon.loadFromFile("Image\\icon.png")) 
    {
        return 1;
    }
    window.setIcon(512, 512, icon.getPixelsPtr());

    GameState gameState = GameState::Game;
    if (gameState == GameState::Menu)
    {
        std::cout << "menu\n";
    }
    Menu menu(window);

    //Time
    Clock clock;
    const float timeStep = 1.0f / 60.0f;
    float accumulator = 0.0f;
    bool isPaused = false;


    Level level("Image\\coin-Sheet.png", "Image\\potion-Sheet.png", \
        "Image\\back3.png", 1);

    View levelView(Vector2f(0.0f, 0.0f), Vector2f(LevelViewHeight, LevelViewHeight));
    View menuView(Vector2f(0.0f, 0.0f), Vector2f(MenuViewHeight, MenuViewHeight));
    levelView.setCenter(level.getPlayerPosition());


    // view collide
    Vector2i viewRectSize(LevelViewHeight * 1.0f, LevelViewHeight * 1.0f);
    IntRect viewRectBounds(Vector2i(level.getPlayerPosition().x - viewRectSize.x / 2.0f, \
        level.getPlayerPosition().y - viewRectSize.y / 2.0f), viewRectSize);
    Sprite playerAndViewCollideSprite; 
    playerAndViewCollideSprite.setTextureRect(viewRectBounds);
    Collider playerAndViewCollider(playerAndViewCollideSprite);
    
    Sprite levelLimitViewSprite;
    Collider backCollider(levelLimitViewSprite);


    //Button testButton("Click me!", Color::Green, Vector2f(32.0f, 16.0f), player.getPosition());

    //Bar healthBar(Vector2f(32.0f, 4.0f), game.getPlayerPosition() + Vector2f(36.0f, -16.0f), Color::Red, HealthMax);
    //Bar energyBar(Vector2f(32.0f, 4.0f), game.getPlayerPosition() + Vector2f(30.0f, -16.0f), Color::Blue, EnergyMax);


    while (window.isOpen())
    {
        Time elapsed = clock.restart();
        accumulator += elapsed.asSeconds();
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



        if (isPaused) {
            // реализовать меню паузы
        }
    
        while (accumulator >= timeStep)
        {
            if (!isPaused)
            {
                //healthBar.update(game.getPlayerEnergy(), levelView.getCenter() - levelView.getSize() / 2.25f);
                //energyBar.update(game.getPlayerHealth(), levelView.getCenter() - levelView.getSize() / 2.25f \
                    + Vector2f(0.0f, 6.0f));

 
                if (!level.getComplete())
                {
                    level.update(timeStep);
                }
                level.updatePlatfotmsCollide();
                level.updateCoinCollecting();
                level.updateColliders(levelView, backCollider, \
                    levelLimitViewSprite, playerAndViewCollideSprite, \
                    playerAndViewCollider);
                
                //testButton.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))));
                if (gameState == GameState::Menu) 
                {
                    menu.update();
                }
            }


            accumulator -= timeStep;
        }                  
        
        window.clear(Color::White); // basic
        if (gameState == GameState::Menu)
        {
            menu.render();
            gameState = menu.getState();
        }
        else if (gameState == GameState::Game)
        {
            window.setView(levelView); // в gameUpdate, при разных условиях разный вид
            if (Keyboard::isKeyPressed(Keyboard::H))
            {
                window.setView(menuView);
            }
    
            level.draw(window);
            //testButton.draw(window);
    
            //healthBar.draw(window);
            //energyBar.draw(window);

            if (isPaused) {
                Font font;
                if (font.loadFromFile("Fonts\\arial.ttf")) {
                    Text pauseText(L"Пауза", font, 20);
                    pauseText.setFillColor(Color::Green);
                    pauseText.setPosition(levelView.getCenter() - pauseText.getGlobalBounds().getSize() / 2.0f);
                    window.draw(pauseText);
                }
            }
        }
        window.display();
    }*/
    return 0;
}

