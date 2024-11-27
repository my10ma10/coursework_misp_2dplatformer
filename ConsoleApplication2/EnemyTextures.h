#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>

using namespace sf;

struct EnemyTextures
{
	EnemyTextures();

	Texture* skeletonTexture = nullptr;
	Texture* wizardTexture = nullptr;
	Texture* tankTexture = nullptr;
	Texture* dragonTexture = nullptr;
	Texture* ghostTexture = nullptr;
	Texture* darkKnightTexture = nullptr;
};

