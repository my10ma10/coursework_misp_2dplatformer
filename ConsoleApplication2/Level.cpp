#include "Level.h"

Level::Level(const std::string filePathToCoinTexture, const std::string filePathToBonusTexture, \
    const std::string filePathToBackGroundTexture, Player* playerPtr, int numberOfLevel) : \
    isComplete(false), numberOfLevel(numberOfLevel), tileSize(16, 16), tilesAmount(48, 48), \
    mapSize(tileSize.x * tilesAmount.x, tileSize.y * tilesAmount.y), levelSize(WINDOW_WIDTH, WINDOW_HEIGHT)
{
    loadTextures(filePathToCoinTexture, filePathToBonusTexture, filePathToBackGroundTexture);

    setTileMap();
    setBackground();
    setBonuses();
    setCoins();
    setEnemies(playerPtr);
    portal = Object(&portalTexture, Vector2f(170, 460), Vector2u(8, 1), 0.1f, Vector2f(20, 32));
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
    for (Enemy& enemy : enemies)
    {
        enemy.update(time);
    }
    portal.updateAnimation(time, true);
}

void Level::draw(RenderWindow& window)
{
    window.draw(backGroundSprite);
    window.draw(tileMap);
    portal.draw(window);
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
    for (Enemy& enemy : enemies)
    {
        enemy.draw(window);
    }
}

void Level::loadTextures(const std::string filePathToCoinTexture, const std::string filePathToBonusTexture, \
    const std::string filePathToBackGroundTexture)
{
    if (!bonusTexture.loadFromFile(filePathToBonusTexture))
    {
        std::cerr << "Can't load an image";
    }
    bonusSprite.setTexture(bonusTexture);

    if (!backgroundTexture.loadFromFile(filePathToBackGroundTexture))
    {
        std::cerr << "Can't load an image";
    }
    if (!coinTexture.loadFromFile(filePathToCoinTexture))
    {
        std::cerr << "Can't load an image";
    }
    if (!portalTexture.loadFromFile("Image\\portal-Sheet.png"))
    {
        std::cerr << "Can't load an image";
    }
    loadEnemyTextures();
}

void Level::loadEnemyTextures()
{
    std::queue <std::string> enemiesFilePaths;

    std::ifstream pathsStream("Files\\enemiesTexturesFilePaths.txt");
    if (!pathsStream.is_open())
    {
        std::cerr << "Can't open a file";
        return;
    }
    std::string tempLine;
    while (pathsStream >> tempLine)
    {
        enemiesFilePaths.push(tempLine);
    }
    pathsStream.close();

    int i = 0;
    while (!enemiesFilePaths.empty()) {
        std::string path = enemiesFilePaths.front();
        sf::Texture tempTexture;
        if (!tempTexture.loadFromFile(path))
        {
            std::cerr << "Can't load an image";
        }
        i++;
        enemyTextures.insert(std::pair<EnemyName, Texture>(static_cast<EnemyName>(i), tempTexture));
        enemiesFilePaths.pop();
    }

}

void Level::setEnemies(Player* playerPtr)
{
    for (auto& pair : enemyTextures)
    {
        switch (pair.first)
        {
        case EnemyName::Skeleton:
            break;

        case EnemyName::Wizard:
            break;

        case EnemyName::Tank:
            break;

        case EnemyName::Dragon:
            break;

        case EnemyName::Ghost:
            enemies.push_back(Enemy(&pair.second, Vector2f(280, 480), Vector2u(8, 4), 0.1f, pair.first, playerPtr));
            enemies.push_back(Enemy(&pair.second, Vector2f(380, 470), Vector2u(8, 4), 0.1f, pair.first, playerPtr));
            break;

        case EnemyName::darkKnight:
            enemies.push_back(Enemy(&pair.second, Vector2f(310, 480), Vector2u(8, 4), 0.1f, pair.first, playerPtr, \
                Vector2f(16, 16)));

            break;

        default:
            break;
        }
    }
}

void Level::setBackground()
{
    Vector2f BackGroundScale(static_cast<float>(WINDOW_WIDTH) / backgroundTexture.getSize().x, \
        static_cast<float>(WINDOW_HEIGHT) / backgroundTexture.getSize().y);
    backGroundSprite.setTexture(backgroundTexture);
    backGroundSprite.setScale(BackGroundScale);
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

void Level::setCoins()
{
    coinSprite.setTextureRect(IntRect(Vector2i(coinSprite.getPosition()),
        Vector2i(16, 16)));
    coinSprite.setTexture(coinTexture);
    coinSprite.setPosition(Vector2f(200, 430));
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

void Level::setTileMap()
{
    std::ifstream tileStream("Files\\tileMapLevel" + std::to_string(numberOfLevel) + ".txt");
    if (!tileStream) {
        std::cerr << "Can't open a file";
    }

    std::vector<int> vec;
    int num = 0;
    while (tileStream >> num)
    {
        vec.push_back(num);
    }
    tileStream.close();
    this->tileLevel = std::move(vec);

    for (int i = 0; i < tileLevel.size(); ++i)
    {
        div_t tileArr = div(i, 48);
        Vector2f tilePosition(tileSize.x * tileArr.rem + tileSize.x / 2.0f, \
            tileSize.y * tileArr.quot + tileSize.x / 2.0f);
        if (tileLevel[i] == 0)
            continue;
        platforms.push_back(Platform(Vector2f(tileSize.x, tileSize.y), Vector2f(tilePosition.x, tilePosition.y)));
    }
    if (!tileMap.load("Image\\test_tiles-Sheet.png", tileSize, tileLevel, tilesAmount.x, tilesAmount.y))
    {
        std::cerr << "Can't load the level";
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

std::vector<Enemy>& Level::getEnemies()
{
    return enemies;
}

Vector2u Level::getSize() const
{
    return levelSize;
}

Vector2f Level::getCenter() const
{
    return backGroundSprite.getGlobalBounds().getSize() / 2.0f;
}

