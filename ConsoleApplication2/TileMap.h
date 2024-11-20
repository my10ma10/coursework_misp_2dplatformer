#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

class TileMap : public Drawable, public Transformable
{
public:
    bool load(const std::string& tileset, Vector2u tileSize, std::vector<int> tiles, unsigned int width, unsigned int height);
private:
    virtual void draw(RenderTarget& target, RenderStates states) const;
    VertexArray vertices;
    Texture tileTexture;
};

