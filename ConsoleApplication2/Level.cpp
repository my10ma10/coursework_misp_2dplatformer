#include "Level.h"

Level::Level(int numberOfLevel) : isComplete(false), numberOfLevel(numberOfLevel)
{
}

Level::Level(const std::string filePathToPlatfomsTexture, const std::string filePathToCoinTexture, \
    const std::string filePathToBonusTexture, const std::string filePathToBackGroundTexture, int numberOfLevel) \
    : isComplete(false), numberOfLevel(numberOfLevel)
{
    size = Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT);


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
    coinSprite.setTextureRect(IntRect(Vector2i(coinSprite.getPosition().x, coinSprite.getPosition().y), 
        Vector2i(16, 16)));
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
    Vector2f BackGroundScale(static_cast<float>(WINDOW_WIDTH) / backGroundTexture.getSize().x, \
        static_cast<float>(WINDOW_HEIGHT) / backGroundTexture.getSize().y);
    backGroundSprite.setTexture(backGroundTexture);
    backGroundSprite.setScale(BackGroundScale);

    setPlatforms();
    setCoins();
    setBonuses();
}


void Level::update(float time)
{
    for (Object& coin : coins)
    {
        coin.updateAnimation(time, true);
    }
    for (Object& bonus : bonuses)
    {
        bonus.updateAnimation(time, true);
    }
}

void Level::draw(RenderWindow& window)
{
    window.draw(backGroundSprite);
    for (Platform& platform : platforms)
    {
        platform.draw(window);
    }
    for (Object& coin : coins)
    {
        coin.draw(window);
    }
    for (Object& bonus : bonuses)
    {
        bonus.draw(window);
    }
}

void Level::setPlatforms()
{
    switch (numberOfLevel) 
    {
        case 1:
            platforms.push_back(Platform(&platformTexture, \
                Vector2f(WINDOW_WIDTH, 40), Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 1.5f)));
            platforms.push_back(Platform(&platformTexture, \
                Vector2f(32, 16), Vector2f(190, (WINDOW_HEIGHT / 1.5f) - 54)));
            platforms.push_back(Platform(&platformTexture, \
                Vector2f(16, 32), Vector2f(240, (WINDOW_HEIGHT / 1.5f) - 72)));
            platforms.push_back(Platform(&platformTexture, \
                Vector2f(112, 16), Vector2f(130, (WINDOW_HEIGHT / 1.5f) - 96)));
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

void Level::setCoins()
{
    switch (numberOfLevel)
    {
    case 1:
        coins.push_back(Object(&coinTexture, Vector2f(170, 436), Vector2u(8, 1), 0.1f));
        coins.push_back(Object(&coinTexture, Vector2f(200, 436), Vector2u(8, 1), 0.1f));
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

void Level::setBonuses()
{
    switch (numberOfLevel)
    {
    case 1:
        bonuses.push_back(Object(&bonusTexture, Vector2f(260, 400), Vector2u(8, 1), 0.1f));
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

//std::vector<Enemy>& Level::getEnemies()
//{
//    return enemies;
//}

Vector2i Level::getSize() const
{
    return size;
}

Vector2f Level::getCenter() const
{
    return backGroundSprite.getGlobalBounds().getSize() / 2.0f;
}



