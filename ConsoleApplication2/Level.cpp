#include "Level.h"

Level::Level() : Òomplete(false), numberOfLevel(0), tileSize(16, 16), tilesAmount(48, 48), \
    mapSize(tileSize.x * tilesAmount.x, tileSize.y * tilesAmount.y), levelSize(WindowWidth, WindowHeight)
{
}

Level::Level(const std::string& filePathToCoinTexture, const std::string& filePathToBonusTexture, \
    const std::string& filePathToBackGroundTexture, int numberOfLevel) : \
    Òomplete(false), numberOfLevel(numberOfLevel), tileSize(16, 16), tilesAmount(48, 48), \
    mapSize(tileSize.x * tilesAmount.x, tileSize.y * tilesAmount.y), levelSize(WindowWidth, WindowHeight)
{
    loadTextures(filePathToCoinTexture, filePathToBonusTexture, filePathToBackGroundTexture);

    initTileMap();
    initBackground();
    initBonuses();
    initCoins();
    initEnemies();
    portal = Object(&portalTexture, Vector2f(470, 460), Vector2u(8, 1), 0.1f, Vector2f(20, 32));
    player = Player(&playerTexture, Vector2f(180, 480), Vector2f(5.0f, 23.0f), Vector2u(12, 7), 0.1f);
    healthBar = Bar(Vector2f(32.0f, 4.0f), player.getPosition() + Vector2f(36.0f, -16.0f), Color::Red, HealthMax);
    energyBar = Bar(Vector2f(32.0f, 4.0f), player.getPosition() + Vector2f(30.0f, -16.0f), Color::Blue, EnergyMax);

}


void Level::update(float time, const View& levelView)
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
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), \
        [](const Enemy& enemy) { return !enemy.alive(); }), enemies.end()); // erase dead enemies

    player.update(time*1000);
    portal.updateAnimation(time, true); 
    healthBar.update(player.getHealth(), levelView.getCenter() - levelView.getSize() / 2.25f);
    energyBar.update(player.getEnergy(), levelView.getCenter() - levelView.getSize() / 2.25f \
        + Vector2f(0.0f, 6.0f));

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
    player.draw(window);
    healthBar.draw(window);
    energyBar.draw(window);

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
    if (!playerTexture.loadFromFile("Image\\player-Sheet.png")) 
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
        Texture tempTexture;
        if (!tempTexture.loadFromFile(path))
        {
            std::cerr << "Can't load an image";
        }
        i++;
        enemyTextures.insert(std::pair<EnemyName, Texture>(static_cast<EnemyName>(i), tempTexture));
        enemiesFilePaths.pop();
    }

}

void Level::checkPortal(Vector2f playerPosition)
{
    if (portal.getSprite().getGlobalBounds().contains(playerPosition))
    {
        Òomplete = true;
    }
}

void Level::checkViewIntersect(View& view, const Vector2u& levelSize)
{
    Vector2f viewCenter = view.getCenter();
    Vector2f viewSize = view.getSize();

    if (viewCenter.x - viewSize.x / 2.0f < 0)
    {
        viewCenter.x = viewSize.x / 2.0f;
    }
    if (viewCenter.x + viewSize.x / 2.0f > levelSize.x)
    {
        viewCenter.x = levelSize.x - viewSize.x / 2.0f;
    }
    if (viewCenter.y - viewSize.y / 2.0f < 0)
    {
        viewCenter.y = viewSize.y / 2.0f;
    }
    if (viewCenter.y + viewSize.y / 2.0f > levelSize.y)
    {
        viewCenter.y = levelSize.y - viewSize.y / 2.0f;
    }

    if (viewSize.x > levelSize.x)
    {
        viewSize.x = levelSize.x;
    }
    if (viewSize.y > levelSize.y)
    {
        viewSize.y = levelSize.y;
    }

    view.setSize(viewSize);
    view.setCenter(viewCenter);
}


void Level::updatePlatfotmsCollide()
{
    for (Platform& platform : platforms)
    {
        if (platform.getCollider().externalCollider(player.getSpriteCollider(), player.getDirection()))
        {
            player.onCollition();
        }
        if (player.getSprite().getGlobalBounds().intersects(platform.getSprite().getGlobalBounds()))
        {
            player.setAttackPower(0);
        }
        else
        {
            player.setAttackPower(PlayerAttackPower);
        }
        for (Enemy& enemy : enemies)
        {
            if (platform.getCollider().externalCollider(enemy.getSpriteCollider(), enemy.getDirection()))
            {
                enemy.onCollition();
            }
        }
    }
}

void Level::updateCoinCollecting()
{
    for (Object& coin : coins)
    {
        player.collectCoin(coin);
    }
}

void Level::updateEnemies()
{
    for (Enemy& enemy : enemies)
    {
        if (enemy.attackRangeIntersect(FloatRect(player.getPosition() - player.getSize() / 2.0f, \
            player.getSize())))
        {
            enemy.attack();
        }
        Sprite enemyBody(enemy.getSprite());
        Collider enemyBodyCollider(enemyBody);
        if (enemyBodyCollider.externalCollider(player.getBodyCollider(), player.getDirection()))
        {
            enemy.setSpeed(0.0f);
        }
        if (enemy.getBody().getGlobalBounds().intersects(player.getSprite().getGlobalBounds()))
        {
            player.addEnemy(&enemy);
        }
        else
        {
            player.removeEnemy(&enemy);
        }
    }

}

void Level::updateColliders(View& levelView, Collider& backCollider, Sprite& levelLimitViewSprite,\
    Sprite& playerAndViewCollideSprite, Collider& playerColliderForView)
{
    playerColliderForView.internalCollider(player.getSpriteCollider());

    levelView.setCenter(playerAndViewCollideSprite.getPosition());

    levelLimitViewSprite.setPosition(levelView.getCenter());
    levelLimitViewSprite.setTextureRect(IntRect(Vector2i(levelView.getCenter()), \
        Vector2i(levelView.getSize())));
    backCollider.levelCollision(player.getSpriteCollider(), Vector2f(16.0f, 16.0f)); // Ï‡„Ëˇ

    for (Enemy& enemy : enemies)
    {
        backCollider.levelCollision(enemy.getSpriteCollider(), Vector2f(16.0f, 16.0f)); // Ï‡„Ëˇ
    }

    levelView.setCenter(playerAndViewCollideSprite.getPosition());
    checkViewIntersect(levelView, getSize());
}

void Level::initEnemies()
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
            enemies.push_back(Enemy(&pair.second, Vector2f(100, 500), Vector2u(8, 4), 0.13f, pair.first, &player, \
                Vector2f(24, 24)));
            break;

        case EnemyName::Ghost:
            //enemies.push_back(Enemy(&pair.second, Vector2f(280, 480), Vector2u(8, 4), 0.1f, pair.first, &player));
            //enemies.push_back(Enemy(&pair.second, Vector2f(380, 470), Vector2u(8, 4), 0.1f, pair.first, &player));
            break;

        case EnemyName::darkKnight:
            //enemies.push_back(Enemy(&pair.second, Vector2f(310, 480), Vector2u(8, 4), 0.1f, pair.first, &player, \
            //    Vector2f(16, 16)));

            break;

        default:
            break;
        }
    }
}

void Level::initBackground()
{
    Vector2f BackGroundScale(static_cast<float>(WindowWidth) / backgroundTexture.getSize().x, \
        static_cast<float>(WindowHeight) / backgroundTexture.getSize().y);
    backGroundSprite.setTexture(backgroundTexture);
    backGroundSprite.setScale(BackGroundScale);
}

void Level::initBonuses()
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

void Level::initCoins()
{
    coinSprite.setTextureRect(IntRect(Vector2i(coinSprite.getPosition()),
        Vector2i(16, 16)));
    coinSprite.setTexture(coinTexture);
    coinSprite.setPosition(Vector2f(200, 430));
    switch (numberOfLevel)
    {
    case 1:
        coins.push_back(Object(&coinTexture, Vector2f(170, 496), Vector2u(8, 1), 0.1f));
        coins.push_back(Object(&coinTexture, Vector2f(200, 496), Vector2u(8, 1), 0.1f));
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

void Level::initPlayer()
{
    player = Player(&playerTexture, Vector2f(180, 480), Vector2f(5.0f, 23.0f), Vector2u(12, 7), 0.1f);
}

void Level::initTileMap()
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

    for (int i = 0; i < tileLevel.size(); i++)
    {
        div_t tileArr = div(i, 48);
        Vector2f tilePosition(tileSize.x * tileArr.rem + tileSize.x / 2.0f, \
            tileSize.y * tileArr.quot + tileSize.y / 2.0f);
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

std::vector<Object>& Level::getCoins()
{
    return coins;
}

bool Level::getComplete() const
{
    return Òomplete;
}

Vector2u Level::getSize() const
{
    return levelSize;
}

Vector2f Level::getCenter() const
{
    return backGroundSprite.getGlobalBounds().getSize() / 2.0f;
}

Player& Level::getPlayer()
{
    return player;
}

Vector2f Level::getPlayerPosition()
{
    return player.getPosition();
}

int Level::getPlayerEnergy()
{
    return player.getEnergy();
}

int Level::getPlayerHealth()
{
    return player.getHealth();
}

Collider Level::getPlayerSpriteCollider()
{
    return player.getSpriteCollider();
}

