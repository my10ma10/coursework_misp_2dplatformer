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
    RenderWindow window(VideoMode(widht, height), L"Игра", Style::Default);

    Image icon;
    if (!icon.loadFromFile("Image\\icon.png")) {
        return 1;
    }
    window.setIcon(512, 512, icon.getPixelsPtr());


    Level level("Image\\platform_test.png", "Image\\coin-Sheet.png", \
        "Image\\rectangle_test.png", "Image\\a78a2b.jpg", 1);


    //Time
    Clock clock;
    float timePlayer;
    float animationTime;


    //coin
    //Texture cointexture;
    //if (!cointexture.loadFromFile("Image\\coin-Sheet.png")) {
    //    std::cerr << "Can't load an image";
    //}
    //Object coinobj(&cointexture, Vector2f(16, 16), Vector2f(200, 430));
    //coinobj.setTexture(cointexture);
    //coinobj.setAnimation(Vector2u(8, 1), 0.1f);


    Texture darkGhostTexture;

    if (!darkGhostTexture.loadFromFile("Image\\dark_ghost-Sheet.png")) {
        std::cerr << "Can't load an image";
    }
    Object darkGhost(&darkGhostTexture, Vector2f(140, 410), Vector2u(8, 4), 0.1f);
    darkGhost.setTexture(darkGhostTexture);

    //player
    Texture playerTexture;
    if (!playerTexture.loadFromFile("Image\\rectangle_test.png")) {
        return 1;
    }
    Player player(&playerTexture, Vector2f(120, 480), Vector2u(1, 1), 0.0f);



    view.setCenter(player.getPosition());

    //level

    // view shape
    //Sprite playerLimitViewShape;
    //playerLimitViewShape.setPosition(player.getPosition());
    //playerLimitViewShape.setOrigin(player.getBody().getSize() * (playerLimitViewShape.getSize().x / (player.getSize().y * 2.0f)));
    Collider playerLimitViewCollider(player.getSprite());
    
    // view level collide
    //IntRect levelLimitViewShape(view.getCenter().x - view.getSize().x / 2.0f, view.getCenter().y - view.getSize().y / 2.0f, view.getSize().x, view.getSize().y);
    //Sprite levelSprite;
    //levelSprite.setTextureRect(levelLimitViewShape);
    //Collider levelLimitViewCollider(levelSprite);





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
        //coinobj.setTextureRect(coinobj.getCurrentRect());
        //coinobj.updateAnimation(animationTime, false);

        player.update(timePlayer);
        //collider
        Vector2f direction_collide_with_platforms(0.0f, 0.0f);
        for (Platform& platform : level.getPlatforms()) {
            if (platform.getCollider().checkCollision(player.getCollider(), direction_collide_with_platforms, 1.0f)) {
                player.OnCollition(direction_collide_with_platforms);
            }
        }



        //Vector2f tempViewCenter(view.getCenter());
        //levelLimitViewShape.setPosition(view.getCenter());
        //levelLimitViewShape.setSize(view.getSize());
        //backCollider.levelCollisionWithPlayer(player.getCollider(), levelCenter);
        //backCollider.levelCollisionWithView(levelLimitViewCollider, levelCenter, tempViewCenter, view);


        //playerLimitViewCollider.viewCollision(player.getCollider());
        //view.setCenter(playerLimitViewShape.getPosition());
        view.setCenter(player.getPosition());


        window.clear(Color::White);
        window.setView(view);
        level.draw(window);
        darkGhost.draw(window);
        player.draw(window);
        

        window.display();
    }
    return 0;
}