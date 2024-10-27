#include "Platform.h"
#include <iostream>
Platform::Platform(Vector2f size, Vector2f position) {
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setPosition(position);
}

Platform::Platform(Texture* texture, Vector2f size, Vector2f position) : Platform(size, position)
{
    body.setTexture(texture);
}


RectangleShape Platform::getBody() const {
    return body;
}

void Platform::draw(RenderWindow& window)
{
    window.draw(body);
}

Collider Platform::getCollider()
{
    return Collider(body);
}
