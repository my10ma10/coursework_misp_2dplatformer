#include "Consts.h"
#include "Player.h"
#include "Platform.h"
#include "View.h"
#include <vector>
#include <cmath>


int main()
{
    RenderWindow window(VideoMode(widht, height), L"Тест", Style::Default);

    Image icon;
    if (!icon.loadFromFile("Image\\icon.png")) {
        return 1;
    }
    window.setIcon(512, 512, icon.getPixelsPtr());
    
    Texture back;
    back.loadFromFile("Image\\a78a2b.jpg");
    RectangleShape backgroundShape(Vector2f(widht, height));
    backgroundShape.setTexture(&back);
    backgroundShape.setPosition(Vector2f(0,0));
    //backgroundShape.setOrigin(widht / 2.0f, height / 2.0f);
    Collider backCollider(backgroundShape);
    Vector2f levelCenter(widht / 2.0f, height / 2.0f);

    //Time
    Clock clock;
    float timePlayer;

    
    //player
    Texture playerTexture;
    playerTexture.loadFromFile("Image\\rectangle_test.png");
    Player player(&playerTexture, Vector2f(16, 16), Vector2f(120, 488));


    //platforms
    Texture platTexture;
    platTexture.loadFromFile("Image\\platform_test.png");

    std::vector<Platform> platforms; // size, position
    platforms.push_back(Platform(&platTexture, Vector2f(32, 64), Vector2f(80, 80)));
    platforms.push_back(Platform(&platTexture, Vector2f(widht, 40), Vector2f(widht / 2 + 18, height / 1.5f)));
    platforms.push_back(Platform(&platTexture, Vector2f(32, 16), Vector2f(190, (height / 1.5f) - 44)));
    platforms.push_back(Platform(&platTexture, Vector2f(16, 32), Vector2f(240, (height / 1.5f) - 52)));



    //coin
    Texture cointexture;
    if (!cointexture.loadFromFile("Image\\coin-Sheet.png")) {
        return 1;
    }
    const int coinsize = 32;
    RectangleShape sheetcoin(Vector2f(coinsize*8, coinsize));
    Sprite coin;
    coin.setTextureRect(IntRect(0, 0, coinsize, coinsize));
    coin.setTexture(cointexture);
    coin.setPosition(200, 230);

    
    // view shape
    RectangleShape viewShape(Vector2f(48.0f, 48.0f));
    viewShape.setFillColor(Color::Magenta);
    viewShape.setOrigin(player.getBody().getSize() * (viewShape.getSize().x / (player.getSize().y * 2.0f)));
    viewShape.setPosition(Vector2f(player.getPosition().x, player.getPosition().y));
    Collider viewCollider(viewShape);
    


    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds(); 
        timePlayer = time / 1000;
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
                resizeView(window, view);
                break;
            case Event::KeyPressed:
                changeView(view);
                setViewBorders(view, player);
                break;
            default:
                break;
            }
        }
        //std::cout << backgroundShape.getPosition().x - player.getPosition().x << " " << backgroundShape.getPosition().y - player.getPosition().y << std::endl;

        player.update(timePlayer);
        //collider
        Vector2f direction_collide_with_platforms;
        for (Platform& platform : platforms) {
            if (platform.getCollider().checkCollision(player.getCollider(), direction_collide_with_platforms, 1.0f)) {
                player.OnCollition(direction_collide_with_platforms);
            }
        }

        Vector2f velocity_level_collide;
        viewCollider.viewCollision(player.getCollider());
        backCollider.levelCollision(player.getCollider(), levelCenter, velocity_level_collide);
        std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;

        window.clear(Color::White);

        view.setCenter(viewShape.getPosition());
        window.setView(view);
        window.draw(backgroundShape);

        for (Platform& platform : platforms) {
            window.draw(platform.getBody());
        }
        window.draw(coin);
        window.draw(player.getBody());
        window.display();
    }
    return 0;
}