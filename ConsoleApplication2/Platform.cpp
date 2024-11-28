#include "Platform.h"

Platform::Platform(Vector2f size, Vector2f position) 
{
    sprite.setOrigin(size / 2.0f);
    sprite.setPosition(position);
    sprite.setTextureRect(IntRect(0, 0, size.x, size.y));
}

Platform::Platform(Texture* texture, Vector2f size, Vector2f position) : Platform(size, position)
{
    sprite.setTexture(*texture);
    this->texture = *texture;
}

Sprite& Platform::getSprite() 
{
    return sprite;
}

void Platform::draw(RenderWindow& window)
{
    window.draw(sprite);
}

Collider Platform::getCollider()
{
    return Collider(sprite);
}
