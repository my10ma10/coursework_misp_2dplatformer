#include "Animation.h"
#include "Consts.h"
#include "Enemy.h"
#include "Level.h"
#include "Object.h"
#include "Player.h"
#include "Platform.h"
#include "Tilemap.h"
#include "View.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

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


    std::ifstream tileStream("tileMapLevel1.txt");
    if (!tileStream) {
        std::cerr << "Ошибка: не удалось открыть файл!" << std::endl;
        return 1;
    }

    std::vector<int> tileLevel;
    std::string tempLine;

    while (std::getline(tileStream, tempLine))
    {
        std::istringstream iss(tempLine);
        int num;
        while (iss >> num) {
            tileLevel.push_back(num);
        }
    }
    tileStream.close();

    Vector2u tileSize(16, 16);
    Vector2u tilesAmount(48, 48);
    Vector2u mapSize(tileSize.x * tilesAmount.x, tileSize.y * tilesAmount.y); //768 768


    TileMap map;
    if (!map.load("Image\\test_tiles-Sheet.png", tileSize, tileLevel, tilesAmount.x, tilesAmount.y))
    {
        return -1;
    }

    for (int i = 0; i < tileLevel.size(); ++i)
    {
        div_t tileArr = div(i, 48);
        Vector2f tilePosition(tileSize.x * tileArr.rem + tileSize.x / 2.0f, \
            tileSize.y * tileArr.quot + tileSize.x / 2.0f);
    }

    //level
    Level level("Image\\platform_test.png", "Image\\coin-Sheet.png", \
        "Image\\potion-Sheet.png", "Image\\a78a2b.jpg", 1);
    FloatRect levelBounds(0, 0, level.getSize().x, level.getSize().y); // ОК

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
            if (platform.getCollider().externalCollider(player.getCollider(), collideDirection, \
                player.getSize())) 
            {
                player.OnCollition(collideDirection);
            }
            if (platform.getCollider().externalCollider(darkGhost.getCollider(), collideDirection, \
                Vector2f(16.0f, 16.0f)))
            {
                darkGhost.OnCollition(collideDirection);
            }
        }


        if (darkGhost.attackRangeIntersect(FloatRect(player.getPosition() - player.getSize() / 2.0f, player.getSize())))
        {
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

        window.clear(Color::White); // basic
        window.setView(view); // basic
        level.draw(window); // basic
        window.draw(map);
        darkGhost.draw(window);
        player.draw(window); //пока непонятно, может потом в level
        window.display();
    }
    return 0;
}