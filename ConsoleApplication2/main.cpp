#include "Animation.h"
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
    bool isFocusLost = false;
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
    Player player(&playerTexture, Vector2f(180, 480), Vector2u(12, 7), 0.1f);

    // darkGhost
    Texture darkGhostTexture;
    if (!darkGhostTexture.loadFromFile("Image\\dark_ghost-Sheet.png")) {
        std::cerr << "Can't load an image";
    }
    Enemy ghost(&darkGhostTexture, Vector2f(240, 470), Vector2u(8, 4), 0.1f, EnemyName::Ghost, &player);


    
    // view collide
    IntRect viewRectBounds(Vector2i(player.getPosition()),\
        Vector2i(VIEW_HEIGHT * 1.5f, VIEW_HEIGHT * 1.0f));
    Sprite playerAndViewCollideSprite; 
    playerAndViewCollideSprite.setTextureRect(viewRectBounds);
    Collider playerColliderForView(playerAndViewCollideSprite);

    // level collide
    Vector2f levelCenter(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    Sprite levelLimitViewShape;
    Collider backCollider(levelLimitViewShape);


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
                changeViewAspectRatio(window, view);
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Escape)
                {
                    isPaused = !isPaused;
                    event.GainedFocus;
                }
                changeViewZoom(view);
                break;
            case Event::LostFocus:
                isFocusLost = true;
                break;
            case Event::GainedFocus:
                isFocusLost = false;
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
            if (!isFocusLost)
            {
                if (!isPaused)
                {
                    // game.update(time1, time2)
                    ghost.update(timeStep); // точно в level.update
                    level.update(timeStep);
                    player.update(timePlayer); // может в level.update


                    //collider
                    Vector2f collideDirection(0.0f, 0.0f);
                    for (Platform& platform : level.getPlatforms())
                    {
                        if (platform.getCollider().externalCollider(player.getCollider(), collideDirection, \
                            player.getSize()))
                        {
                            player.OnCollition(collideDirection);
                        }
                        if (platform.getCollider().externalCollider(ghost.getCollider(), collideDirection, \
                            Vector2f(16.0f, 16.0f)))
                        {
                            ghost.OnCollition(collideDirection);
                        }
                    }

                    if (ghost.attackRangeIntersect(FloatRect(player.getPosition() - player.getSize() / 2.0f, player.getSize())))
                    {
                        ghost.attack();
                    }

                    // в структуру коллайдеров в Гейме?
                    playerColliderForView.internalCollider(player.getCollider());
                    levelLimitViewShape.setPosition(view.getCenter());
                    levelLimitViewShape.setTextureRect(IntRect(Vector2i(view.getCenter().x, view.getCenter().y), \
                        Vector2i(view.getSize().x, view.getSize().y)));
                    backCollider.levelCollision(player.getCollider(), Vector2f(16.0f, 16.0f));
                    backCollider.levelCollision(ghost.getCollider(), Vector2f(16.0f, 16.0f));
                }
                accumulator -= timeStep;
            }
            
        }
        view.setCenter(playerAndViewCollideSprite.getPosition());

        window.clear(Color::White); // basic
        window.setView(view); // basic
        level.draw(window); // basic
        ghost.draw(window);
        player.draw(window); //пока непонятно, может потом в level
        if (isPaused) {
            Font font;
            if (font.loadFromFile("Fonts\\arial.ttf")) { // Убедитесь, что шрифт доступен
                Text pauseText(L"Пауза", font, 10);
                pauseText.setFillColor(Color::Green);
                pauseText.setPosition(player.getPosition());
                window.draw(pauseText);
            }
        }
        window.display();
    }
    return 0;
}