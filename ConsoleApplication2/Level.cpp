#include "Level.h"

Level::Level(int numberOfLevel) : isComplete(false), numberOfLevel(numberOfLevel)
{
}

Level::Level(const std::string filePathToPlatfomsTexture, const std::string filePathToCoinTexture, \
    const std::string filePathToBonusTexture, const std::string filePathToBackGroundTexture, int numberOfLevel) \
    : isComplete(false), numberOfLevel(numberOfLevel)
{


    if (!platformTexture.loadFromFile(filePathToPlatfomsTexture))
    {
        std::cerr << "Can't load an image";
    }

    platformSprite.setTexture(platformTexture);
    platformSprite.setTextureRect(IntRect(0, 0, 64, 32));

    if (!coinTexture.loadFromFile(filePathToCoinTexture))
    {
        std::cerr << "Can't load an image";
    }
    coinSprite.setTexture(coinTexture);
    coinSprite.setPosition(Vector2f(200, 430));

    if (!bonusTexture.loadFromFile(filePathToBonusTexture))
    {
        std::cerr << "Can't load an image";
    }
    bonusSprite.setTexture(bonusTexture);

    if (!backGroundTexture.loadFromFile(filePathToBackGroundTexture))
    {
        std::cerr << "Can't load an image";
    }
    backGroundSprite.setTexture(backGroundTexture);
    size = Vector2f(backGroundSprite.getGlobalBounds().getSize());
    setPlatforms();
}


void Level::draw(RenderWindow& window)
{
    window.draw(backGroundSprite);
    for (Platform& platform : platforms)
    {
        platform.draw(window);
    }
    //window.draw(coinSprite);
}

void Level::setPlatforms()
{
    switch (numberOfLevel) 
    {
        case 1:
            platforms.push_back(Platform(&platformTexture, Vector2f(32, 64), Vector2f(80, 80)));
            platforms.push_back(Platform(&platformTexture, Vector2f(WINDOW_WIDTH, 40), Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 1.5f)));
            platforms.push_back(Platform(&platformTexture, Vector2f(32, 16), Vector2f(190, (WINDOW_HEIGHT / 1.5f) - 44)));
            platforms.push_back(Platform(&platformTexture, Vector2f(16, 32), Vector2f(240, (WINDOW_HEIGHT / 1.5f) - 52)));
            platforms.push_back(Platform(&platformTexture, Vector2f(64, 16), Vector2f(156, (WINDOW_HEIGHT / 1.5f) - 80)));
            break;
        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;
    }
}

Sprite Level::getBackGroundSprite() const
{
    return backGroundSprite;
}

std::vector<Platform>& Level::getPlatforms()
{
    return platforms;
}

Vector2f Level::getSize() const
{
    return size;
}

Vector2f Level::getCenter() const
{
    return backGroundSprite.getGlobalBounds().getSize() / 2.0f;
}


