#include "EnemyTextures.h"

EnemyTextures::EnemyTextures()
{
	if (!skeletonTexture->loadFromFile("Image\\rectangle_test.png"))
	{
		std::cerr << "Can't load an image";
	}
	if (!wizardTexture->loadFromFile("Image\\rectangle_test.png"))
	{
		std::cerr << "Can't load an image";
	}
	if (!tankTexture->loadFromFile("Image\\rectangle_test.png"))
	{
		std::cerr << "Can't load an image";
	}
	if (!dragonTexture->loadFromFile("Image\\rectangle_test.png"))
	{
		std::cerr << "Can't load an image";
	}
	if (!ghostTexture->loadFromFile("Image\\dark_ghost-Sheet.png")) 
	{
		std::cerr << "Can't load an image";
	}
	if (!darkKnightTexture->loadFromFile("Image\\dark_Knight.png"))
	{
		std::cerr << "Can't load an image";
	}
}
