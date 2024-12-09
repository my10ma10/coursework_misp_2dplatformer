#include "Game.h"
void checkViewIntersect(View& view, const Vector2u& levelSize);
void changeViewZoom(View& view);
void changeViewAspectRatio(const RenderWindow& window, View& view);

int main()
{
    RenderWindow window(VideoMode(1024, 1024), L"Игра", Style::Default);

    Image icon;
    if (!icon.loadFromFile("Image\\icon.png")) {
        return 1;
    }
    window.setIcon(512, 512, icon.getPixelsPtr());

    //Time
    Clock clock;
    const float timeStep = 1.0f / 60.0f;
    float accumulator = 0.0f;
    float timePlayer = 0.0f;
    bool isPaused = false;

    Game game(1);
    Level level("Image\\coin-Sheet.png", "Image\\potion-Sheet.png", \
        "Image\\back3.png", 1);

    View levelView(Vector2f(0.0f, 0.0f), Vector2f(LevelViewHeight, LevelViewHeight));
    View menuView(Vector2f(0.0f, 0.0f), Vector2f(MenuViewHeight, MenuViewHeight));
    levelView.setCenter(level.getPlayerPosition());


    // view collide
    Vector2i viewRectSize(LevelViewHeight * 1.0f, LevelViewHeight * 1.0f);
    IntRect viewRectBounds(Vector2i(game.getPlayerPosition().x - viewRectSize.x / 2.0f, \
        game.getPlayerPosition().y - viewRectSize.y / 2.0f), viewRectSize);
    Sprite playerAndViewCollideSprite; 
    playerAndViewCollideSprite.setTextureRect(viewRectBounds);
    Collider playerColliderForView(playerAndViewCollideSprite);
    
    Sprite levelLimitViewSprite;
    Collider backCollider(levelLimitViewSprite);


    //Button testButton("Click me!", Color::Green, Vector2f(32.0f, 16.0f), player.getPosition());

    //Bar healthBar(Vector2f(32.0f, 4.0f), game.getPlayerPosition() + Vector2f(36.0f, -16.0f), Color::Red, HealthMax);
    //Bar energyBar(Vector2f(32.0f, 4.0f), game.getPlayerPosition() + Vector2f(30.0f, -16.0f), Color::Blue, EnergyMax);


    while (window.isOpen())
    {
        Time elapsed = clock.restart();
        accumulator += elapsed.asSeconds();
        timePlayer = timeStep * 1000;

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


                //if (!game.getLevelComplete())
                //{
                //    game.updateLevel(timeStep*500);

                //}
                //game.update(backCollider, levelLimitViewSprite, levelView);
                if (!level.getComplete())
                {
                    level.update(timeStep);
                }
                level.updatePlatfotmsCollide();
                level.updateCoinCollecting();
                level.updateColliders(levelView, level.getSize(), backCollider, levelLimitViewSprite, playerAndViewCollideSprite, playerColliderForView);

                //testButton.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))));
            }

            levelView.setCenter(playerAndViewCollideSprite.getPosition());
            checkViewIntersect(levelView, level.getSize());
            accumulator -= timeStep;
        }                  
        
        window.clear(Color::White); // basic
        window.setView(levelView); // в gameUpdate, при разных условиях разный вид
        if (Keyboard::isKeyPressed(Keyboard::H))
        {
            window.setView(menuView);
        }

        level.draw(window);
        //game.render(window); // basic
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
        window.display();
    }
    return 0;
}


void checkViewIntersect(View& view, const Vector2u& levelSize)
{
    Vector2f viewCenter = view.getCenter();
    Vector2f viewSize = view.getSize();

    if (viewCenter.x - viewSize.x / 2.0f < 0)
    {
        viewCenter.x = viewSize.x / 2.0f;
    }
    if (viewCenter.x + viewSize.x / 2.0f > levelSize.x)
    {
        viewCenter.x = levelSize.x - viewSize.x / 2.0f;
    }
    if (viewCenter.y - viewSize.y / 2.0f < 0)
    {
        viewCenter.y = viewSize.y / 2.0f;
    }
    if (viewCenter.y + viewSize.y / 2.0f > levelSize.y)
    {
        viewCenter.y = levelSize.y - viewSize.y / 2.0f;
    }

    if (viewSize.x > levelSize.x)
    {
        viewSize.x = levelSize.x;
    }
    if (viewSize.y > levelSize.y)
    {
        viewSize.y = levelSize.y;
    }

    view.setSize(viewSize);
    view.setCenter(viewCenter);
}


void changeViewZoom(View& view)
{
    if (Keyboard::isKeyPressed(Keyboard::Equal)) {
        view.zoom(0.995f);
    }
    if (Keyboard::isKeyPressed(Keyboard::Dash)) {
        view.zoom(1.005f);
    }
}

void changeViewAspectRatio(const RenderWindow& window, View& view)
{
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(aspectRatio * LevelViewHeight, LevelViewHeight);
}
