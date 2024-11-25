#include "Animation.h"
#include "Button.h"
#include "Consts.h"
#include "Enemy.h"
#include "Level.h"
#include "Object.h"
#include "Player.h"
#include "Platform.h"
#include "Tilemap.h"
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
    //bool isFocusLost = false;
    bool isPaused = false;

    //level
    Level level("Image\\coin-Sheet.png", \
        "Image\\potion-Sheet.png", "Image\\a78a2b.jpg", 1);
    FloatRect levelBounds(0, 0, level.getSize().x, level.getSize().y);

    //player
    Texture playerTexture;
    if (!playerTexture.loadFromFile("Image\\player-Sheet.png")) {
        std::cerr << "Can't load an image";
    }
    Player player(&playerTexture, Vector2f(180, 480), Vector2f(7.0f, 22.0f), Vector2u(12, 7), 0.1f);

    // darkGhost
    Texture darkGhostTexture;
    if (!darkGhostTexture.loadFromFile("Image\\dark_ghost-Sheet.png")) {
        std::cerr << "Can't load an image";
    }
    Enemy ghost(&darkGhostTexture, Vector2f(240, 470), Vector2u(8, 4), 0.1f, EnemyName::Ghost, &player);


    
    // view collide
    Vector2i viewRectSize(LEVEL_VIEW_HEIGHT * 1.5f, LEVEL_VIEW_HEIGHT * 1.0f);
    IntRect viewRectBounds(Vector2i(player.getPosition().x - viewRectSize.x / 2.0f, \
        player.getPosition().y - viewRectSize.y / 2.0f),viewRectSize);
    Sprite playerAndViewCollideSprite; 
    playerAndViewCollideSprite.setTextureRect(viewRectBounds);
    Collider playerColliderForView(playerAndViewCollideSprite);
    

    // level collide
    
    Sprite levelLimitViewShape;
    Collider backCollider(levelLimitViewShape);

    Button testButton("Click me!", player.getPosition(), Vector2f(32.0f, 16.0f));

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
            case Event::LostFocus:
                //isFocusLost = true;
                break;
            case Event::GainedFocus:
                //isFocusLost = false;
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
            if (/*!isFocusLost*/ true)
            {
                if (!isPaused)
                {
                    // game.update(time1, time2)
                    ghost.update(timeStep); // точно в level.update
                    level.update(timeStep);
                    player.update(timePlayer); // может в level.update


                    //collider
                    for (Platform& platform : level.getPlatforms())
                    {
                        if (platform.getCollider().externalCollider(player.getCollider(), player.getDirection(), \
                            player.getSize()))
                        {
                            player.onCollition();
                        }
                        if (platform.getCollider().externalCollider(ghost.getCollider(), player.getDirection(), \
                            Vector2f(16.0f, 16.0f)))
                        {
                            ghost.onCollition();
                        }
                    }
                    
                    if (ghost.attackRangeIntersect(FloatRect(player.getPosition() - player.getSize() / 2.0f, \
                        player.getSize())))
                    {
                        ghost.attack();
                    }

                    // в структуру коллайдеров в Гейме?
                    updateView(levelView, playerAndViewCollideSprite.getPosition(), Vector2f(level.getSize()));
                    playerColliderForView.internalCollider(player.getCollider());
                    levelLimitViewShape.setPosition(levelView.getCenter());
                    levelLimitViewShape.setTextureRect(IntRect(Vector2i(levelView.getCenter()), \
                        Vector2i(levelView.getSize())));
                    backCollider.levelCollision(player.getCollider(), Vector2f(16.0f, 16.0f));
                    backCollider.levelCollision(ghost.getCollider(), Vector2f(16.0f, 16.0f));
                }
                accumulator -= timeStep;
            }
            
        }                       

        //levelView.setCenter(playerAndViewCollideSprite.getPosition());
        window.clear(Color::White); // basic
        window.setView(levelView); // basic
        if (Keyboard::isKeyPressed(Keyboard::H))
        {
            window.setView(menuView);
        }
        //game.draw(window);
        level.draw(window); // basic
        ghost.draw(window);
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