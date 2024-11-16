#include "Animation.h"
#include "Consts.h"
#include "Object.h"
#include "Player.h"
#include "Platform.h"
#include "View.h"
#include "Level.h"
#include <cmath>



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



    // darkGhost
    Texture darkGhostTexture;

    if (!darkGhostTexture.loadFromFile("Image\\dark_ghost-Sheet.png")) {
        std::cerr << "Can't load an image";
    }
    Object darkGhost(&darkGhostTexture, Vector2f(140, 410), Vector2u(8, 4), 0.1f);

    // coin
    //Texture coinTexture;
    //if (!coinTexture.loadFromFile("Image\\coin-Sheet.png"))
    //{
    //    std::cerr << "Can't load an image";
    //}
    //Object coin1(&coinTexture, Vector2f(170, 436), Vector2u(8, 1), 0.1f);
    //Object coin2(&coinTexture, Vector2f(200, 436), Vector2u(8, 1), 0.1f);

    //player
    Texture playerTexture;
    if (!playerTexture.loadFromFile("Image\\rectangle_test.png")) {
        std::cerr << "Can't load an image";
    }
    Player player(&playerTexture, Vector2f(120, 470), Vector2u(1, 1), 0.0f);


    //level
    Level level("Image\\platform_test.png", "Image\\coin-Sheet.png", \
        "Image\\rectangle_test.png", "Image\\a78a2b.jpg", 1);
    FloatRect levelBounds(0, 0, level.getSize().x, level.getSize().y); // ОК





    
    // view collide
    IntRect viewRectBounds(Vector2i(player.getPosition()),\
        Vector2i(VIEW_HEIGHT / 4, VIEW_HEIGHT / 4));// ОК
    Sprite playerAndViewCollideSprite; 
    playerAndViewCollideSprite.setTextureRect(viewRectBounds);

    Collider playerColliderForView(playerAndViewCollideSprite);
    view.setCenter(player.getPosition());





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
        darkGhost.updateAnimation(animationTime, true);
        //coin1.updateAnimation(animationTime, false);
        //coin2.updateAnimation(animationTime, false);
        level.update(animationTime);
        player.update(timePlayer);

        //collider
        Vector2f direction_collide_with_platforms(0.0f, 0.0f);
        for (Platform& platform : level.getPlatforms()) {
            if (platform.getCollider().checkCollision(player.getCollider(), direction_collide_with_platforms, 1.0f)) {
                player.OnCollition(direction_collide_with_platforms);
            }
        }
        
        playerColliderForView.viewCollision(player.getCollider());
        
        //Vector2f tempViewCenter(view.getCenter());
        //levelLimitViewShape.setPosition(view.getCenter());
        //levelLimitViewShape.setSize(view.getSize());
        //backCollider.levelCollisionWithPlayer(player.getCollider(), levelCenter);
        //backCollider.levelCollisionWithView(levelLimitViewCollider, levelCenter, tempViewCenter, view);


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