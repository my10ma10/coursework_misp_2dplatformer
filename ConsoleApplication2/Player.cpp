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

	updateBonusStates();
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
	std::cout << speed << std::endl;
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
	if (!attacking)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			attackState = true;
			superAttackState = false;
			attacking = true;
		}

		if (energy >= energyDelta * 5 && Keyboard::isKeyPressed(Keyboard::LControl) && canJump)
		{
			if (attackState)
			{
				attackState = false;
				row = 0;
			}
			superAttackState = true;
			attackState = false;
			changedRow = false;
		}
	}
	if (canJump)
	{
		if (superAttackState and !attackState)
		{
			superAttack();
		}
		if (attackState and !superAttackState)
		{
			row = 3;
			attack();
		}
	}
	else
	{
		
	}
	if (canJump && attacking && getCurrentFrame() == 0)
	{
		attacking = false;
		attackState = false;
		superAttackState = false;
		energyChanged = false;
		isDamageTaking = false;
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
			if (enemy->getFaceRight() != faceRight)
			{
				enemy->setAttackPower(0);
			}
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
	if ((Keyboard::isKeyPressed(Keyboard::Left) or Keyboard::isKeyPressed(Keyboard::A)))
	{
		velocity.x -= speed;
	}
	if ((Keyboard::isKeyPressed(Keyboard::Right) or Keyboard::isKeyPressed(Keyboard::D)))
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
	if (getCurrentFrame() == 0 and row == 1)
	{
		energy = std::max(0.0f, energy - energyDelta);
		energyChanged = true;
	}

	if (enemiesPtr.size() != 0 && getCurrentFrame() == 7 && !isDamageTaking && !superAttackState)
	{
		for (Enemy* enemy : enemiesPtr)
		{
			if (enemy->alive())
			{
				enemy->takeDamage(attackPower);
			}
		}
		isDamageTaking = true;
	}
	if (getCurrentFrame() == 11)
	{
		attackState = false;
		energyChanged = false;
		attacking = false;
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
	if (enemiesPtr.size() != 0 && getCurrentFrame() == 3 && !isDamageTaking && row != 5)
	{
		for (Enemy* enemy : enemiesPtr)
		{
			if (enemy->alive())
			{
				enemy->takeDamage(attackPower);
			}
		}
		isDamageTaking = true;
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
	if (!canJump)
	{
		superAttackRow = 1;
		superAttackState = false;
		changedRow = false;
		row = 0;
		return;
	}
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

void Player::updateBonusStates()
{
	if (attackState or superAttackState)
	{
		speed = PersonSpeed / 3.0f;
	}
	else
	{
		if (bonusStates[ObjectType::Bubble] && bonusStates[ObjectType::Boot])
		{
			speed = PersonSpeed;
		}
		else if (bonusStates[ObjectType::Boot])
		{
			speed = PersonSpeed * 1.25f;
		}
		else if (bonusStates[ObjectType::Bubble])
		{
			speed = PersonSpeed / 1.25f;
		}
		else
		{
			speed = PersonSpeed;
		}
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

