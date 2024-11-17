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
    if (!playerTexture.loadFromFile("Image\\rectangle_test.png")) {
        std::cerr << "Can't load an image";
    }
    Player player(&playerTexture, Vector2f(120, 470), Vector2u(1, 1), 0.0f);

    // darkGhost
    Texture darkGhostTexture;
    if (!darkGhostTexture.loadFromFile("Image\\dark_ghost-Sheet.png")) {
        std::cerr << "Can't load an image";
    }
    Enemy darkGhost(&darkGhostTexture, Vector2f(140, 410), Vector2u(8, 4), 0.1f, EnemyName::Ghost, &player);


    //level
    Level level("Image\\platform_test.png", "Image\\coin-Sheet.png", \
        "Image\\potion-Sheet.png", "Image\\a78a2b.jpg", 1);
    FloatRect levelBounds(0, 0, level.getSize().x, level.getSize().y); // ОК


    
    // view collide
    IntRect viewRectBounds(Vector2i(player.getPosition()),\
        Vector2i(VIEW_HEIGHT / 4, VIEW_HEIGHT / 4));// ОК
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
        player.update(timePlayer);

        //collider
        Vector2f direction_collide_with_platforms(0.0f, 0.0f);
        for (Platform& platform : level.getPlatforms()) 
        {
            if (platform.getCollider().checkCollision(player.getCollider(), direction_collide_with_platforms, 1.0f)) 
            {
                player.OnCollition(direction_collide_with_platforms);
            }
        }
        if (darkGhost.intersects(player.getSprite().getGlobalBounds()))
        {
            darkGhost.setRow(2);
            darkGhost.attack();
        }
        std::cout << player.getHealth() << std::endl;

        // в структуру коллайдеров в Гейме?
        playerColliderForView.viewCollision(player.getCollider());
        levelLimitViewShape.setPosition(view.getCenter());
        levelLimitViewShape.setTextureRect(IntRect(Vector2i(view.getCenter().x, view.getCenter().y),\
            Vector2i(view.getSize().x, view.getSize().y)));
        backCollider.levelCollisionWithPlayer(player.getCollider(), levelCenter);


        view.setCenter(playerAndViewCollideSprite.getPosition());


        window.clear(Color::White); // basic
        window.setView(view); // basic
        level.draw(window); // basic
        darkGhost.draw(window);
        player.draw(window); //пока непонятно, может потом в level

        window.display();
    }
    return 0;
}