#include "Level.h"

Level::Level() : levelState(LevelState::Passing), levelNumber(1), tileSize(16, 16), tilesAmount(48, 48), \
    mapSize(tileSize.x * tilesAmount.x, tileSize.y * tilesAmount.y), levelSize(WindowWidth, WindowHeight)
{
    levelIndex = levelNumber - 1;
}

Level::Level(const std::string& filePathToBackGroundTexture, int numberOfLevel) : \
    levelState(LevelState::Passing), levelNumber(numberOfLevel), tileSize(16, 16), tilesAmount(48, 48), \
    mapSize(tileSize.x * tilesAmount.x, tileSize.y * tilesAmount.y), levelSize(WindowWidth, WindowHeight)
{
    levelIndex = levelNumber - 1;
    loadTextures(filePathToBackGroundTexture);
    initLevel(numberOfLevel);
}

void Level::initLevel(int number)
{
    this->levelNumber = number;
    platforms.resize(5);
    bonuses.resize(5);
    enemies.resize(5);
    initPositions("Files\\objectsLevel", allLevelsObjectsPositions);
    initPositions("Files\\enemiesLevel", allLevelsEnemiesPositions);
    initTileMap();
    initBackground();
    initBonuses();
    initEnemies();
    player = Player(&playerTexture, Vector2f(playerPosition), Vector2f(8.0f, 20.0f), Vector2u(12, 7), 0.1f);
    healthBar = Bar(Vector2f(32.0f, 4.0f), player.getPosition() + Vector2f(36.0f, -16.0f), Color::Red, HealthMax);
    energyBar = Bar(Vector2f(32.0f, 4.0f), player.getPosition() + Vector2f(30.0f, -16.0f), Color::Blue, EnergyMax);
}

void Level::update(float time, const View& levelView)
{
    checkPortal(getPlayerPosition());
    if (!player.alive())
    {
        levelState = LevelState::Failed;
    }
    updateBonuses(time);
    updateEnemies(time);
    enemies[levelIndex].erase(std::remove_if(enemies[levelIndex].begin(), enemies[levelIndex].end(), \
        [](const Enemy& enemy) { return !enemy.alive(); }), enemies[levelIndex].end());

    player.update(time*1000);
    portal.update(time); 
    healthBar.update(player.getHealth(), levelView.getCenter() - levelView.getSize() / 2.25f);
    energyBar.update(player.getEnergy(), levelView.getCenter() - levelView.getSize() / 2.25f \
        + Vector2f(0.0f, 6.0f));
}

void Level::draw(RenderWindow& window)
{
    window.draw(backGroundSprite);
    window.draw(tileMap);
    portal.draw(window);
    for (Platform& platform : platforms[levelIndex])
    {
        platform.draw(window);
    }
    for (Object& bonus : bonuses[levelIndex])
    {
        bonus.draw(window);
    }
    for (Enemy& enemy : enemies[levelIndex])
    {
        enemy.draw(window);
    }
    player.draw(window);
    healthBar.draw(window);
    energyBar.draw(window);

}

void Level::restart() {
    levelState = LevelState::Passing;
    enemies.clear();
    platforms.clear();
    bonuses.clear();
    initLevel(levelNumber);
}

void Level::changeLevel(int number)
{
    levelNumber = number;
    restart();
}

template<>
ObjectType Level::stringToType<ObjectType>(const std::string& name)
{
    static const std::map<std::string, ObjectType> objects = {
        {"Coin", ObjectType::Coin},
        {"Potion", ObjectType::Potion},
        {"Armor", ObjectType::Armor},
        {"Bubble", ObjectType::Bubble},
        {"Boot", ObjectType::Boot},
        {"Portal", ObjectType::Portal}
    };

    auto it = objects.find(name);
    if (it == objects.end()) {
        std::cerr << "An object doesn't find by name:" << name << "\n";
        return ObjectType::Coin;
    }
    return it->second;
}


template<>
EnemyName Level::stringToType<EnemyName>(const std::string& name)
{
    static const std::map<std::string, EnemyName> enemyEntities = {
        {"Skeleton", EnemyName::Skeleton},
        {"Tank", EnemyName::Tank},
        {"Wizard", EnemyName::Wizard},
        {"Ghost", EnemyName::Ghost},
        {"Dragon", EnemyName::Dragon},
        {"DarkKnight", EnemyName::DarkKnight}
    };

    auto it = enemyEntities.find(name);
    if (it == enemyEntities.end()) {
        std::cerr << "An enemy doesn't find by name:" << name << "\n";
        return EnemyName::Basic; 
    }
    return it->second;
}

void Level::loadTextures(const std::string backGroundTexturePath)
{
    if (!backgroundTexture.loadFromFile(backGroundTexturePath))
    {
        std::cerr << "Can't load an image";
    }
    if (!playerTexture.loadFromFile("Image\\player-Sheet.png")) 
    {
        std::cerr << "Can't load an image";
    }

    loadInMap("Files\\enemiesTexturesFilePaths.txt", enemyTextures);
    loadInMap("Files\\bonusesTexturesFilePaths.txt", bonusTextures);
}

template<typename T>
inline void Level::loadInMap(const std::string& path, std::map<T, Texture>& textures)
{
    std::ifstream pathsStream(path);
    if (!pathsStream.is_open())
    {
        std::cerr << "Can't open the file: " << path << std::endl;
        return;
    }
    std::string tempLine;
    int i = 0;
    while (std::getline(pathsStream, tempLine))
    {
        Texture tempTexture;
        if (!tempTexture.loadFromFile(tempLine))
        {
            std::cerr << "Can't load the image: " << tempLine << std::endl;
        }
        textures.emplace(static_cast<T>(i), std::move(tempTexture));
        ++i;
    }
}

void Level::checkPortal(Vector2f playerPosition)
{
    if (portal.getSprite().getGlobalBounds().contains(playerPosition))
    {
        levelState = LevelState::Complete;
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
    for (Platform& platform : platforms[levelIndex])
    {
        if (platform.getCollider().externalCollider(
            player.getSpriteCollider(), player.getDirection()))
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
        for (Enemy& enemy : enemies[levelIndex])
        {
            if (platform.getCollider().externalCollider(
                enemy.getSpriteCollider(), enemy.getDirection()))
            {
                enemy.onCollition();
            }
        }
    }
}

void Level::updateBonuses(float time)
{
    for (Object& bonus : bonuses[levelIndex])
    {
        bonus.update(time);
        if (player.getBody().getGlobalBounds().intersects(bonus.getBody().getGlobalBounds()))
        {
            if (bonus.getType() == ObjectType::Coin)
            {
                player.collectCoin(bonus);
            }
            else if (bonus.getType() == ObjectType::Potion)
            {
                player.applyPotion(bonus);
            }
            else if (bonus.getType() == ObjectType::Portal)
            {
                continue;
            }
            else
            {
                player.applyBonus(bonus);
            }
        }
    }
}

void Level::updateEnemies(float time)
{
    for (Enemy& enemy : enemies[levelIndex])
    {
        if (enemy.attackRangeIntersect(player.getBody().getGlobalBounds()))
        {
            enemy.attack();
        }
        Sprite enemyBody(enemy.getSprite());
        Collider enemyBodyCollider(enemyBody);
        if (enemyBodyCollider.externalCollider(player.getBodyCollider(), player.getDirection()))
        {
            enemy.setSpeed(0.0f);
        }
        if (enemy.getBody().getGlobalBounds().intersects(player.getAttackRange()))
        {
            player.addEnemy(&enemy);
        }
        else
        {
            player.removeEnemy(&enemy);
        }
        enemy.update(time);

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
    backCollider.levelCollision(
        player.getSpriteCollider(), player.getBody().getGlobalBounds().getSize());

    for (Enemy& enemy : enemies[levelIndex])
    {
        backCollider.levelCollision(
            enemy.getSpriteCollider(), enemy.getBody().getGlobalBounds().getSize());
    }

    levelView.setCenter(playerAndViewCollideSprite.getPosition());
    checkViewIntersect(levelView, getSize());
}

void Level::initEnemies()
{
    enemiesSize = {
        {EnemyName::Skeleton, Vector2i(10, 19)},
        {EnemyName::Wizard, Vector2i(14, 20)},
        {EnemyName::Tank, Vector2i(17, 17)},
        {EnemyName::Dragon, Vector2i(24, 24)},
        {EnemyName::Ghost, Vector2i(16, 16)},
        {EnemyName::DarkKnight, Vector2i(12, 16)}
    };


    std::map < EnemyName, std::vector <Vector2i> > levelEnemiesPositions = allLevelsEnemiesPositions[levelIndex];
    for (auto& typeTexturePair : enemyTextures)
    {
        for (Vector2i position : levelEnemiesPositions[typeTexturePair.first]) {
            enemies[levelIndex].push_back(Enemy(&typeTexturePair.second, Vector2f(position),
                Vector2u(8, 4), 0.1f, typeTexturePair.first, &player));
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
    std::map < ObjectType, std::vector <Vector2i> > levelObjectsPositions = allLevelsObjectsPositions[levelIndex];
    for (auto& typeTexturePair : bonusTextures)
    {
        if (typeTexturePair.first == ObjectType::Portal) {
            portal = Object(&typeTexturePair.second, Vector2f(portalPosition), Vector2u(8, 1), 0.1f,
                ObjectType::Portal, Vector2f(20, 32));
        }

        /// all other bonuses
        for (Vector2i position : levelObjectsPositions[typeTexturePair.first /*vector of positions for type*/]) {
            bonuses[levelIndex].push_back(Object(&typeTexturePair.second, Vector2f(position),
                Vector2u(8, 1), 0.1f, typeTexturePair.first));
        }
    }
}

void Level::initTileMap()
{
    std::ifstream tileStream("Files\\tileMapLevel" + std::to_string(levelNumber) + ".txt");
    if (!tileStream)
    {
        std::cerr << "Can't open a file: Files\\tileMapLevel" + std::to_string(levelNumber) + ".txt\n";
        return;
    }

    std::vector<int> vec;
    int num = 0;
    while (tileStream >> num)
    {
        vec.push_back(num);
    }
    tileStream.close();


    if (tileLevel.size() <= levelIndex)
    {
        tileLevel.resize(levelIndex + 1);
    }
    tileLevel[levelIndex] = std::move(vec);

    for (size_t i = 0; i < tileLevel[levelIndex].size(); i++)
    {
        div_t tileArr = div(static_cast<int>(i), 48);
        Vector2f tilePosition(tileSize.x * tileArr.rem + tileSize.x / 2.0f,
            tileSize.y * tileArr.quot + tileSize.y / 2.0f);
        if (tileLevel[levelIndex][i] == 0)
        {
            continue;
        }
        platforms[levelIndex].emplace_back(
            Platform(Vector2f(tileSize.x, tileSize.y), tilePosition));
    }

    if (!tileMap.load("Image\\test_tiles-Sheet.png", tileSize, tileLevel[levelIndex],
        tilesAmount.x, tilesAmount.y))
    {
        std::cerr << "Can't load the level\n";
    }
}


void Level::initPositions(std::string filePath, 
    std::map<unsigned int, std::map<ObjectType, std::vector<Vector2i>>>& positionsMap)
{
    std::map <ObjectType, std::vector <Vector2i> > tempMap;
    std::vector <Vector2i> coords;
    std::string objectName, line;
    ObjectType objType;

    std::ifstream file(filePath + std::to_string(levelNumber) + ".txt");
    if (!file.is_open()) {
        std::cerr << "File Executer can't open a file\n";
    }

    std::getline(file, objectName);
    file >> playerPosition.x >> playerPosition.y;
    file.ignore();

    std::getline(file, objectName);
    file >> portalPosition.x >> portalPosition.y;
    file.ignore();


    for (int i = 1; i <= ExecutedObjectTypesCount; ++i) {
        coords.clear();
        tempMap.clear();

        std::getline(file, objectName);
        objType = stringToType<ObjectType>(objectName);


        while (std::getline(file, line) && !line.empty() && std::any_of(line.begin(), line.end(), ::isdigit)) {
            if (!line.empty()) {
                Vector2i position;
                std::istringstream iss(line);
                iss >> position.x >> position.y;
                coords.push_back(position);
            }
            else {
                break;
            }
        }
        allLevelsObjectsPositions[levelIndex][objType] = std::move(coords);
    }
    file.close();
}


void Level::initPositions(std::string filePath,
    std::map<unsigned int, std::map<EnemyName, std::vector<Vector2i>>>& positionsMap)
{
    std::map<EnemyName, std::vector<Vector2i>> tempMap;
    std::vector<Vector2i> coords;
    std::string entityName, line;
    EnemyName entityType;

    std::ifstream file(filePath + std::to_string(levelNumber) + ".txt");
    if (!file.is_open()) {
        std::cerr << "File Executer can't open a file\n";
        return;
    }


    size_t limit = 6; 
    for (int i = 1; i <= limit; ++i) {
        coords.clear();
        tempMap.clear();

        std::getline(file, entityName);
        entityType = stringToType<EnemyName>(entityName);

        while (std::getline(file, line) && !line.empty() && std::any_of(line.begin(), line.end(), ::isdigit)) {
            if (!line.empty()) {
                Vector2i position;
                std::istringstream iss(line);
                iss >> position.x >> position.y;
                coords.push_back(position);
            }
            else {
                break;
            }
        }
        positionsMap[levelIndex][entityType] = std::move(coords);
    }

    file.close();
}


Sprite Level::getBackGroundSprite() const
{
    return backGroundSprite;
}

std::vector<Platform>& Level::getPlatforms(unsigned int number)
{
    return platforms[number];
}

std::vector<Enemy>& Level::getEnemies(unsigned int number)
{
    return enemies[number];
}

LevelState Level::getState() const
{
    return levelState;
}

Vector2u Level::getSize() const
{
    return levelSize;
}

Vector2f Level::getCenter() const
{
    return backGroundSprite.getGlobalBounds().getSize() / 2.0f;
}

unsigned int Level::getNumber() const
{
    return levelNumber;
}

bool Level::getPlayerLife() const
{
    return player.alive();
}

Vector2f Level::getPlayerPosition()
{
    return player.getPosition();
}



