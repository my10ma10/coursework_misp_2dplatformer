#include "TileMap.h"


bool TileMap::load(const std::string& tileset, Vector2u tileSize, std::vector<int> tiles, \
    unsigned int width, unsigned int height)
{
    if (!tileTexture.loadFromFile(tileset))
        return false;

    // resize the vertex array to fit the level size
    vertices.setPrimitiveType(Triangles);
    vertices.resize(width * height * 6);

    // populate the vertex array, with two triangles per tile
    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            // find its position in the tileset texture
            int tu = tileNumber % (tileTexture.getSize().x / tileSize.x);
            int tv = tileNumber / (tileTexture.getSize().x / tileSize.x);

            // get a pointer to the triangles' vertices of the current tile
            Vertex* triangles = &vertices[(i + j * width) * 6];

            // define the 6 corners of the two triangles
            triangles[0].position = Vector2f(i * tileSize.x, j * tileSize.y);
            triangles[1].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[2].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[3].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
            triangles[4].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            triangles[5].position = Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);

            // define the 6 matching texture coordinates
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