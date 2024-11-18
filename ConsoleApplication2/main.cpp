#include "Animation.h"
#include "Consts.h"
#include "Enemy.h"
#include "Level.h"
#include "Object.h"
#include "Player.h"
#include "Platform.h"
#include "View.h"


int main()
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), L"Игра", Style::Default);

    Image icon;
    if (!icon.loadFromFile("Image\\icon.png")) {
        return 1;
    }
    window.setIcon(512, 512, icon.getPixelsPtr());


    //Time
    Clock clock;
    float timePlayer;
    float animationTime;

    //player
    Texture playerTexture;
    if (!playerTexture.loadFromFile("Image\\player-Sheet.png")) {
        std::cerr << "Can't load an image";
    }
    Player player(&playerTexture, Vector2f(180, 340), Vector2u(12, 7), 0.1f);

    // darkGhost
    Texture darkGhostTexture;
    if (!darkGhostTexture.loadFromFile("Image\\dark_ghost-Sheet.png")) {
        std::cerr << "Can't load an image";
    }
    Enemy darkGhost(&darkGhostTexture, Vector2f(280, 470), Vector2u(8, 4), 0.1f, EnemyName::Ghost, &player);

    //level
    Level level("Image\\platform_test.png", "Image\\coin-Sheet.png", \
        "Image\\potion-Sheet.png", "Image\\a78a2b.jpg", 1);
    FloatRect levelBounds(0, 0, level.getSize().x, level.getSize().y); // ОК

    
    // view collide
    IntRect viewRectBounds(Vector2i(player.getPosition()),\
        Vector2i(VIEW_HEIGHT * 1.5f, VIEW_HEIGHT * 1.0f));// ОК
    Sprite playerAndViewCollideSprite; 
    playerAndViewCollideSprite.setTextureRect(viewRectBounds);
    Collider playerColliderForView(playerAndViewCollideSprite);
    view.setCenter(player.getPosition());


    // level collide
    Vector2f levelCenter(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
    Sprite levelLimitViewShape;
    Collider backCollider(levelLimitViewShape);


    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); 
        timePlayer = time / 1000;
        animationTime = clock.restart().asSeconds();
        clock.restart();
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
                changeViewZoom(view);
                break;
            default:
                break;
            }
        }
        // game.update(time1, time2)
        darkGhost.update(animationTime);
        level.update(animationTime);
        player.update(timePlayer); // может в level.update

        //collider
        Vector2f collideDirection(0.0f, 0.0f);
        for (Platform& platform : level.getPlatforms()) 
        {
            //std::cout << view.getCenter().x << std::endl;
            if (platform.getCollider().externalCollider(player.getCollider(), collideDirection, \
                Vector2f(7.0f, 22.0f))) 
            {
                player.OnCollition(collideDirection);
            }
            if (platform.getCollider().externalCollider(darkGhost.getCollider(), collideDirection, \
                Vector2f(16.0f, 16.0f)))
            {
                darkGhost.OnCollition(collideDirection);
            }
        }
        //std::cout << player.getHealth() << " " << player.getCurrentFrame() << std::endl;

        if (darkGhost.intersects(player.getSprite().getGlobalBounds()))
        {
            darkGhost.setRow(2);
            darkGhost.attack();
        }

        // в структуру коллайдеров в Гейме?
        playerColliderForView.internalCollider(player.getCollider());
        levelLimitViewShape.setPosition(view.getCenter());
        levelLimitViewShape.setTextureRect(IntRect(Vector2i(view.getCenter().x, view.getCenter().y),\
            Vector2i(view.getSize().x, view.getSize().y)));
        backCollider.levelCollision(player.getCollider(), Vector2f(16.0f, 16.0f));
        backCollider.levelCollision(darkGhost.getCollider(), Vector2f(16.0f, 16.0f));


        view.setCenter(playerAndViewCollideSprite.getPosition());
        //view.setCenter(player.getPosition());


        window.clear(Color::White); // basic
        window.setView(view); // basic
        level.draw(window); // basic
        darkGhost.draw(window);
        player.draw(window); //пока непонятно, может потом в level

        window.display();
    }
    return 0;
}