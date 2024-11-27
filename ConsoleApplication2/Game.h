#pragma once
#include "Level.h"
#include "View.h"
class Game
{

};


static void updateColliders(View& levelView, const Sprite& playerAndViewCollideSprite, Vector2u levelSize, \
    Collider& playerColliderForView, Collider& backCollider, const Collider& playerCollider, \
    const Collider& ghostCollider, Sprite& levelLimitViewSprite)
{
    levelLimitViewSprite.setPosition(levelView.getCenter());
    levelLimitViewSprite.setTextureRect(IntRect(Vector2i(levelView.getCenter()), \
        Vector2i(levelView.getSize())));
    backCollider.levelCollision(playerCollider, Vector2f(16.0f, 16.0f)); // магия
    backCollider.levelCollision(ghostCollider, Vector2f(16.0f, 16.0f)); // магия
}

