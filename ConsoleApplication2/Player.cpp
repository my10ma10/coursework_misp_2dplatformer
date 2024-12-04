#include "Player.h"
#include "Enemy.h"

Player::Player(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime) : \
	Person(texture, position, size, imageCount, switchTime)
{
	health = HealthMax;
	energy = EnergyMax / 2.0f;
	wasJumpKeyPressed = isJumpKeyPressed = isBlocking = bubbleBonusState = changedRow = false;
	personSpeed = 0.075f;
	if (!bubbleTexture.loadFromFile("Image\\bubble.png"))
	{
		std::cerr << "Can't load an image";
	}
	Sprite bubble = Sprite(bubbleTexture);
	bubble.setScale(Vector2f(1.5f, 1.5f));
}

void Player::draw(RenderWindow& window)
{
	if (life)
	{
		window.draw(sprite);
	}
	if (bubbleBonusState)
	{
		//window.draw(bubble);
	}
}

void Player::update(float time)
{
	body.setPosition(sprite.getPosition());
	velocity.x = 0.0f;
	updateBonuses();

	isJumpKeyPressed = Keyboard::isKeyPressed(Keyboard::W) or Keyboard::isKeyPressed(Keyboard::Up);

	if (Keyboard::isKeyPressed(Keyboard::Left) or Keyboard::isKeyPressed(Keyboard::A))
	{
		velocity.x -= personSpeed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) or Keyboard::isKeyPressed(Keyboard::D))
	{
		velocity.x += personSpeed;
	}
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
	if (velocity.y > personSpeed)
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
	velocity.y += gravity * time;
	sprite.move(velocity * time);
	updateHealth();
	if (energy < EnergyMax)
	{
		energy += 0.2f;
	}
	std::cout << enemiesPtr.size() << std::endl;
}

void Player::attackUpdate()
{
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
		std::cout << "change row\n";
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
	if (body.getGlobalBounds().intersects(coin.getSprite().getGlobalBounds()) and coin.alive())
	{
		coinCounter++;
		coin.kill();
	}
}
void Player::applyBonus(Object& bonus)
{
	if (bonus.alive()) 
	{
		// удалить бонус
		// назначить бонус игроку (отдельный метод)
	}
}

void Player::applyHeart(Object& heart)
{
	if (heart.alive())
	{
		if (health <= HealthMax)
		health += 20;
		// удалить сердечко
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

void Player::updateBonuses()
{
	bubble.setPosition(getPosition() - Vector2f(24.0f, 25.0f)); // магия
}

std::vector<Enemy*> Player::getEnemies() const
{
	return enemiesPtr;
}

Vector2f Player::getSize() const
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

