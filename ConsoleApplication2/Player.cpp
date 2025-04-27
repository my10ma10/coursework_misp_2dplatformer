#include "Player.h"
#include "Enemy.h"

Player::Player(): Person()
{
	wasJumpKeyPressed = isJumpKeyPressed = isBlocking = changedRow = false;
}

Player::Player(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime) : \
	Person(texture, position, size, imageCount, switchTime)
{
	health = HealthMax;
	energy = EnergyMax / 2.0f;
	wasJumpKeyPressed = isJumpKeyPressed = isBlocking = changedRow = false;

	bonusStates[ObjectType::Armor] = false;
	bonusStates[ObjectType::Bubble] = false;
	bonusStates[ObjectType::Boot] = false;
	if (!bubbleTexture.loadFromFile("Image\\bubble.png"))
	{
		std::cerr << "Can't load an image";
	}
}

void Player::draw(RenderWindow& window)
{
	if (life)
	{
		window.draw(sprite);
	}
	if (bonusStates[ObjectType::Bubble])
	{
		window.draw(bubble);
	}
}

void Player::update(float time)
{
	body.setPosition(sprite.getPosition());
	velocity.x = 0.0f;
	for (Enemy* enemy : enemiesPtr)
	{
		if (!enemy->alive())
		{
			removeEnemy(enemy);
		}
	}
	keyProcessing();
	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 5;
		if (velocity.x > 0.0f)
		{
			faceRight = true;
		}
		else
		{
			faceRight = false;
		}
	}
	if (velocity.y > speed)
	{
		canJump = false;
	}
	if (isJumpKeyPressed and !wasJumpKeyPressed)
	{
		this->jump(time);
	}
	wasJumpKeyPressed = isJumpKeyPressed;

	attackUpdate();
	blockUpdate();
	updateAnimation(time / 1000, faceRight);
	updateHealth();
	updateBonuses();
	if (energy < EnergyMax)
	{
		energy += 0.2f;
	}
	velocity.y += gravity * time;
	sprite.move(velocity * time);
}

void Player::attackUpdate()
{
	if (faceRight)
	{
		attackRange = FloatRect(Vector2f(getSprite().getPosition() - Vector2f(0, (getSpriteSize().y - getBodySize().y) / 2.0f)),
			Vector2f(getSpriteSize() / 2.0f));
	}
	else
	{
		attackRange = FloatRect(Vector2f(getSprite().getPosition() - Vector2f(getSpriteSize().x / 2.0f, (getSpriteSize().y - getBodySize().y) / 2.0f)),
			Vector2f(getSpriteSize() / 2.0f));
	}

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		attackState = true;
		superAttackState = false;
	}
	if (Keyboard::isKeyPressed(Keyboard::LControl))
	{
		superAttackState = true;
		attackState = false;
	}
	if (canJump)
	{
		if (superAttackState and !attackState)
		{
			superAttack();
		}
		if (attackState and !superAttackState)
		{
			velocity.x = 0.0f;
			row = 3;
			attack();
		}
	}
}

void Player::blockUpdate()
{
	if (Keyboard::isKeyPressed(Keyboard::Down) or Keyboard::isKeyPressed(Keyboard::S))
	{
		isBlocking = true;
		row = 6;
		velocity.x = 0.0f;
		for (Enemy* enemy : enemiesPtr)
		{
			enemy->setAttackPower(0);
		}
	}
}

void Player::updateHealth()
{
	if (health <= 0 and life)
	{
		life = false;
	}
	
	health = std::max(0, health);
	if (health < HealthMax)
	{
		health += 0.05f;
	}
}

void Player::keyProcessing()
{
	isJumpKeyPressed = Keyboard::isKeyPressed(Keyboard::W) or Keyboard::isKeyPressed(Keyboard::Up);
	if ((Keyboard::isKeyPressed(Keyboard::Left) or Keyboard::isKeyPressed(Keyboard::A))
		and !attackState and !superAttackState)
	{
		velocity.x -= speed;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Right) or Keyboard::isKeyPressed(Keyboard::D))
		and !attackState and !superAttackState)
	{
		velocity.x += speed;
	}
}

void Player::takeDamage(int damageAmount)
{
	if (bonusStates[ObjectType::Armor])
	{
		damageAmount /= 2.0f;
	}
	if (!bonusStates[ObjectType::Bubble])
	{
		health -= damageAmount;
	}
}

void Player::attack()
{
	if (energy > energyDelta)
	{
		attacking = true;
	}
	if (getCurrentFrame() == 0 and row == 1)
	{
		energy = std::max(0.0f, energy - energyDelta);
		energyChanged = true;
	}
	if (enemiesPtr.size() != 0)
	{
		for (Enemy* enemy : enemiesPtr)
		{
			if (getCurrentFrame() == 7 and !isDamageTaking and enemy->alive())
			{
				enemy->takeDamage(attackPower);
				isDamageTaking = true;
			}
		}
	}
	if (getCurrentFrame() == 11)
	{
		attackState = false;
		energyChanged = false;
	}
	if (getCurrentFrame() != 7)
	{
		isDamageTaking = false;
	}

}

void Player::superAttack()
{
	superAttackAnimation();
	if (energy > energyDelta * 5)
	{
		attacking = true;
	}
	if (enemiesPtr.size() != 0)
	{
		for (Enemy* enemy : enemiesPtr)
		{
			if (getCurrentFrame() == 3 and !isDamageTaking and enemy->alive() and row != 4)
			{
				enemy->takeDamage(attackPower);
				isDamageTaking = true;
			}
		}
	}
	if (getCurrentFrame() != 3)
	{
		isDamageTaking = false;
	}
	if (getCurrentFrame() == 11 and row == 5)
	{
		superAttackState = false;
		attacking = false;
		energyChanged = false;
	}
	if (getCurrentFrame() == 3 and row == 1 and !energyChanged)
	{
		energy = std::max(0.0f, energy - energyDelta * 5);
		energyChanged = true;
	}

}

void Player::superAttackAnimation()
{
	if (superAttackRow == 5)
	{
		superAttackRow = 1;
		superAttackState = false;
	}
	if (getCurrentFrame() == 0)
	{
		changedRow = false;
	}
	if (getCurrentFrame() == 11 and !changedRow)
	{
		changedRow = true;
		superAttackRow++;
	}
	
	velocity.x = 0.0f;
	row = superAttackRow;
}

void Player::addEnemy(Enemy* enemy)
{
	if (std::find(enemiesPtr.begin(), enemiesPtr.end(), enemy) == enemiesPtr.end()) 
	{
		enemiesPtr.push_back(enemy);
	}
}

void Player::removeEnemy(Enemy* enemy) 
{
	enemiesPtr.erase(std::remove(enemiesPtr.begin(), enemiesPtr.end(), enemy), enemiesPtr.end());
}

void Player::collectCoin(Object& coin)
{
	if (coin.alive())
	{
		coinCounter++;
		coin.kill();
	}
}
void Player::applyBonus(Object& bonus)
{
	if (bonus.alive()) 
	{
		activateBonus(bonus.getType());
		bonus.kill();
	}
}

void Player::applyPotion(Object& potion)
{
	if (potion.alive())
	{
		if (health <= HealthMax)
		{
			health = std::min(HealthMax, health + 20);
			potion.kill();
		}
	}
}

void Player::activateBonus(ObjectType type)
{
	bonusStates[type] = true;
	if (type == ObjectType::Armor)
	{
		armorClock.restart().asSeconds();
	}
	if (type == ObjectType::Boot)
	{
		this->speed = PersonSpeed * 1.25f;
		bootClock.restart().asSeconds();
	}
	if (type == ObjectType::Bubble)
	{
		bubbleClock.restart().asSeconds();
	}
}

void Player::deactivateBonus(ObjectType type)
{
	bonusStates[type] = false;
	this->speed = PersonSpeed / 1.25f;
}

void Player::updateBonuses()
{
	if (armorClock.getElapsedTime().asSeconds() > bonusDeltaTime and bonusStates[ObjectType::Armor])
	{
		deactivateBonus(ObjectType::Armor);
	}
	else if (bubbleClock.getElapsedTime().asSeconds() > bonusDeltaTime and bonusStates[ObjectType::Bubble])
	{
		deactivateBonus(ObjectType::Bubble);
	}
	else if (bootClock.getElapsedTime().asSeconds() > bonusDeltaTime and bonusStates[ObjectType::Boot])
	{
		deactivateBonus(ObjectType::Boot);
	}

	if (bonusStates[ObjectType::Bubble])
	{
		bubble = Sprite(bubbleTexture);
		bubble.setPosition(Vector2f(
			this->getPosition().x - this->getBodySize().x - 4.0f,
			this->getPosition().y - this->getBodySize().y));
	}
}

void Player::jump(float time)
{
	if ((Keyboard::isKeyPressed(Keyboard::Up) or Keyboard::isKeyPressed(Keyboard::W)) and canJump)
	{
		canJump = false;
		velocity.y = -sqrtf(2.0f * gravity * jumpHeight);
	}
}

const FloatRect& Player::getAttackRange() const
{
	return attackRange;
}

std::vector<Enemy*> Player::getEnemies() const
{
	return enemiesPtr;
}

bool Player::getInvulnerability()
{
	return bonusStates[ObjectType::Bubble];
}

bool Player::getProtection()
{
	return bonusStates[ObjectType::Armor];
}

Vector2f Player::getBodySize() const
{
	return body.getGlobalBounds().getSize();
}

unsigned int Player::getAnimCount() const
{
	return animation.animationCount;
}

float Player::getJumpHeight() const
{
	return jumpHeight;
}

