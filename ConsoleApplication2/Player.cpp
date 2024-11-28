#include "Player.h"
#include "Enemy.h"

Player::Player(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime) : \
	Person(texture, position, size, imageCount, switchTime)
{
	health = HEALTH_MAX;
	wasJumpKeyPressed = isJumpKeyPressed = isBlocking = blockBonus = false;
	sprite.setTextureRect(animation.getCurrentRect());
	personSpeed = 0.075f;
	if (!bubbleTexture.loadFromFile("Image\\bubble.png"))
	{
		std::cerr << "Can't load an image";
	}
	Sprite bubble = Sprite(bubbleTexture);
	bubble.setScale(Vector2f(1.5f, 1.5f));
}

void Player::update(float time)
{
	body.setPosition(sprite.getPosition());
	body.setTextureRect(IntRect(Vector2i(getPosition() - getSize() / 2.0f), Vector2i(getSize())));

	bubble.setPosition(getPosition() - Vector2f(24.0f, 25.0f)); // �����

	isJumpKeyPressed = Keyboard::isKeyPressed(Keyboard::W) or \
		Keyboard::isKeyPressed(Keyboard::Up);

	velocity.x = 0.0f;
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

	if (Keyboard::isKeyPressed(Keyboard::Down) or Keyboard::isKeyPressed(Keyboard::S))
	{
		isBlocking = true;
		setRow(6);
		velocity.x = 0.0f;
		for (Enemy* enemy : enemiesPtr)
		{
			enemy->setAttackPower(0);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		if (canJump)
		{
			velocity.x = 0.0f;
			for (Enemy* enemy : enemiesPtr)
			{
				attack(*enemy);
			}
		}

	}

	if (updateAnimation(time / 1000, faceRight))
	{
		setRow(5);
	}
	velocity.y += gravity * time;
	sprite.move(velocity * time);
	updateHealth();
}

void Player::draw(RenderWindow& window)
{
	if (life)
	{
		window.draw(sprite);
	}
	if (blockBonus)
	{
		//window.draw(bubble);
	}
}


void Player::attack(Enemy& enemy)
{
	row = 3;
	if (getCurrentFrame() == 5 and !isDamageTaking)
	{
		for (Enemy* enemy : enemiesPtr)
		{
			enemy->takeDamage(attackPower);
		}
		isDamageTaking = true;
	}
	if (getCurrentFrame() != 5)
	{
		isDamageTaking = false;
	}
}

void Player::superattack(Enemy& enemy)
{
	// 3 �������� ����� ������
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

std::vector<Enemy*> Player::getEnemies() const 
{
	return enemiesPtr;
}

void Player::collectCoin(Object& coin)
{
	if (0/*������� � ��������*/) 
	{
		// �������++;
		// ������� ��������
	}
}
void Player::applyBonus(Object& bonus)
{
	if (bonus.alive()) 
	{
		// ������� �����
		// ��������� ����� ������ (��������� �����)
	}
}

void Player::applyHeart(Object& heart)
{
	if (heart.alive())
	{
		if (health <= HEALTH_MAX)
		health += 20;
		// ������� ��������
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

