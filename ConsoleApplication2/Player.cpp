#include "Player.h"
#include "Enemy.h"

Player::Player(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime): \
	Person(texture, position, imageCount, switchTime), isBlocking(false)
{
	sprite.setTextureRect(animation.getCurrentRect());
	personSpeed = 0.05f;
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
	if (blockBonus)
	{
		//window.draw(bubble);
	}
}


void Player::attack(Enemy& enemy)
{
	enemy.takeDamage(attackPower);
	// анимация атаки
}

void Player::superattack(Enemy& enemy)
{
	// 3 анимации атаки подряд
}

void Player::collectCoin(Object& coin)
{
	if (0/*коллайд с монеткой*/) 
	{
		// счётчик++;
		// монетка исчезает
	}
}

void Player::applyBonus(Object& bonus)
{
	if (bonus.getLife()) 
	{
		// удалить бонус
		// назначить бонус игроку (отдельный метод)
	}
}

void Player::applyHeart(Object& heart)
{
	if (heart.getLife())
	{
		if (health <= HEALTH_MAX)
		health += 20;
		// удалить сердечко
	}
}

void Player::update(float time)
{
	bubble.setPosition(getPosition() - Vector2f(24.0f, 25.0f));
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

	if ((Keyboard::isKeyPressed(Keyboard::Up) or Keyboard::isKeyPressed(Keyboard::W)) && canJump) 
	{
		canJump = false;
		velocity.y = -sqrtf(2.0f * gravity * jumpHeight);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) or Keyboard::isKeyPressed(Keyboard::S))
	{
		isBlocking = true;
		setRow(6);
		velocity.x = 0.0f;
		// block
	}
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		setRow(3);
		velocity.x = 0.0f;

	}
	if (updateAnimation(time / 1000, faceRight))
	{
		setRow(5);
	}
	velocity.y += gravity * time; // gravity
	sprite.move(velocity * time);
}

Vector2f Player::getSize() const
{
	return Vector2f(7.0f, 22.0f);
}

unsigned int Player::getAnimCount() const
{
	return animation.animationCount;
}

