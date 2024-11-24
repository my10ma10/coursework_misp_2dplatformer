#include "Level.h"

Level::Level(const std::string filePathToCoinTexture, const std::string filePathToBonusTexture, \
    const std::string filePathToBackGroundTexture, int numberOfLevel) : \
    isComplete(false), numberOfLevel(numberOfLevel), tileSize(16, 16), tilesAmount(48, 48),\
    mapSize(tileSize.x * tilesAmount.x, tileSize.y * tilesAmount.y), levelSize(WINDOW_WIDTH, WINDOW_HEIGHT)
{

    tileLevel = setTileLevel();
    for (int i = 0; i < tileLevel.size(); ++i)
    {
        div_t tileArr = div(i, 48);
        Vector2f tilePosition(tileSize.x * tileArr.rem + tileSize.x / 2.0f, \
            tileSize.y * tileArr.quot + tileSize.x / 2.0f);
        if (tileLevel[i] == 0)
            continue;
        platforms.push_back(Platform(Vector2f(tileSize.x, tileSize.y), Vector2f(tilePosition.x, tilePosition.y)));
    }
    if (!map.load("Image\\test_tiles-Sheet.png", tileSize, tileLevel, tilesAmount.x, tilesAmount.y))
    {
        std::cerr << "Can't load the level";
    }

    platformSprite.setTextureRect(IntRect(0, 0, 16, 16));

    if (!coinTexture.loadFromFile(filePathToCoinTexture))
    {
        std::cerr << "Can't load an image";
    }
    coinSprite.setTextureRect(IntRect(Vector2i(coinSprite.getPosition()), 
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
    window.draw(map);
}

std::vector<int> Level::setTileLevel()
{
    std::ifstream tileStream("tileMapLevel" + std::to_string(numberOfLevel) + ".txt");
    if (!tileStream) {
        std::cerr << "Can't open a file";
    }

    std::vector<int> vec;
    std::string tempLine;
    while (std::getline(tileStream, tempLine))
    {
        std::istringstream iss(tempLine);
        int num;
        while (iss >> num) {
            vec.push_back(num);
        }
    }
    tileStream.close();
    return vec;
}

//void Level::setPlatforms()
//{
//    switch (numberOfLevel) 
//    {
//        case 1:
//            break;
//            
//        case 2:
//            break;
//
//        case 3:
//            break;
//
//        case 4:
//            break;
//
//        case 5:
//            break;
//    }
//}

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

Vector2u Level::getSize() const
{
    return levelSize;
}

Vector2f Level::getCenter() const
{
    return backGroundSprite.getGlobalBounds().getSize() / 2.0f;
}



