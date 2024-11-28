#pragma once
#include "Person.h"
#include "Object.h"

class Player : public Person
{
public:
	Player(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime);

	void update(float time) override;
	void draw(RenderWindow& window);

	void attack(Enemy& enemy);
	void superattack(Enemy& enemy);
	void addEnemy(Enemy* enemy);
	void removeEnemy(Enemy* enemy);
	std::vector<Enemy*> getEnemies() const;
	void collectCoin(Object& coin);
	void applyBonus(Object& bonus);
	void applyHeart(Object& heart);
	void jump(float time);



	Vector2f getSize() const;
	unsigned int getAnimCount() const;
	float getJumpHeight() const;

private:
	bool isBlocking;
	bool blockBonus;
	bool isJumpKeyPressed;
	bool wasJumpKeyPressed;
	float jumpHeight = 36.0f;
	Texture bubbleTexture;
	Sprite bubble;
	std::vector<Enemy*> enemiesPtr; // 
};

