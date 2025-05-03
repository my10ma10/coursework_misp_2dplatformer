#include "TileMap.h"


bool TileMap::load(const std::string& tileset, Vector2u tileSize, std::vector<int> tiles, \
    unsigned int width, unsigned int height)
{
    if (!tileTexture.loadFromFile(tileset))
        return false;

    vertices.setPrimitiveType(Triangles);
    vertices.resize(width * height * 6);

    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            int tileNumber = tiles[i + j * width];

            int tu = tileNumber % (tileTexture.getSize().x / tileSize.x);
            int tv = tileNumber / (tileTexture.getSize().x / tileSize.x);

            Vertex* triangles = &vertices[(i + j * width) * 6];

            triangles[0].position = Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            triangles[0].texCoords = Vector2f(tu * tileSize.x, tv * tileSize.y);
            triangles[1].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[2].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[3].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            triangles[4].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            triangles[5].texCoords = Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        }
    return true;
}

void TileMap::draw(RenderTarget& target, RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = &tileTexture;
    target.draw(vertices, states);
}