#include "Animation.h"
#include "Button.h"
#include "Game.h"
#include "Level.h"
#include "View.h"

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


    //player
    Texture playerTexture;
    if (!playerTexture.loadFromFile("Image\\player-Sheet.png")) {
        std::cerr << "Can't load an image";
    }
    Player player(&playerTexture, Vector2f(180, 480), Vector2f(5.0f, 23.0f), Vector2u(12, 7), 0.1f);


    //level
    Level level("Image\\coin-Sheet.png", "Image\\potion-Sheet.png", \
        "Image\\back3.png", &player, 1);
    FloatRect levelBounds(0, 0, level.getSize().x, level.getSize().y);

    // view collide
    Vector2i viewRectSize(LEVEL_VIEW_HEIGHT * 1.0f, LEVEL_VIEW_HEIGHT * 1.0f);
    IntRect viewRectBounds(Vector2i(player.getPosition().x - viewRectSize.x / 2.0f, \
        player.getPosition().y - viewRectSize.y / 2.0f), viewRectSize);
    Sprite playerAndViewCollideSprite; 
    playerAndViewCollideSprite.setTextureRect(viewRectBounds);
    Collider playerColliderForView(playerAndViewCollideSprite);
    
    Sprite levelLimitViewSprite;
    Collider backCollider(levelLimitViewSprite);


    Button testButton("Click me!", Color::Green, Vector2f(32.0f, 16.0f), player.getPosition());
    
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
                // game.update(time1, time2)
                if (!level.getComplete())
                {
                    level.update(timeStep);
                    player.update(timePlayer); // может в level.update

                }
                testButton.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))));
                level.checkPortal(player.getPosition());

                //collider
                for (Platform& platform : level.getPlatforms())
                {
                    if (platform.getCollider().externalCollider(player.getSpriteCollider(), player.getDirection()))
                    {
                        player.onCollition();
                    }
                    if (player.getSprite().getGlobalBounds().intersects(platform.getSprite().getGlobalBounds()))
                    {
                        player.setAttackPower(0); 
                    }
                    else
                    {
                        player.setAttackPower(PLAYER_ATTACK_POWER);
                    }
                    for (Enemy& enemy : level.getEnemies())
                    {
                        if (platform.getCollider().externalCollider(enemy.getSpriteCollider(), enemy.getDirection()))
                        {
                            enemy.onCollition();
                        }
                    }
                    
                }
                for (Object& coin : level.getCoins())
                {
                    player.collectCoin(coin);
                }
                for (Enemy& enemy : level.getEnemies())
                {
                    if (enemy.attackRangeIntersect(FloatRect(player.getPosition() - player.getSize() / 2.0f, \
                        player.getSize())))
                    {
                        enemy.attack();
                    }
                    Sprite enemyBody(enemy.getSprite());
                    Collider enemyBodyCollider(enemyBody);
                    if (enemyBodyCollider.externalCollider(player.getBodyCollider(), player.getDirection()))
                    {
                        enemy.setSpeed(0.0f);
                    }
                    if (enemy.getBody().getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
                    {
                        player.addEnemy(&enemy);
                    }
                    else
                    {
                        player.removeEnemy(&enemy);
                    }
                    updateColliders(levelView, level.getSize(), backCollider, \
                        player.getSpriteCollider(), enemy.getSpriteCollider(), levelLimitViewSprite);
                }
            }
            updateView(levelView, playerAndViewCollideSprite.getPosition(), level.getSize());
            playerColliderForView.internalCollider(player.getSpriteCollider());
            accumulator -= timeStep;
        }                  
        
        window.clear(Color::White); // basic
        window.setView(levelView); // в gameUpdate, при разных условиях разный вид
        if (Keyboard::isKeyPressed(Keyboard::H))
        {
            window.setView(menuView);
        }

        // game.draw(window);
        if (player.alive())
        {
            //и level.update(time);
            level.draw(window); // basic
        }
        player.draw(window); //пока непонятно, может потом в level
        testButton.draw(window);

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