#include "Player.h"
#include "Enemy.h"

Player::Player() : Player(Vector2f(0.0f, 0.0f))
{
}

Player::Player(Vector2f position) : Person(position), canJump(false), isBlocking(false)
{
}

Player::Player(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime): \
	Person(texture, position, imageCount, switchTime), canJump(false), isBlocking(false)
{
	sprite.setTextureRect(animation.getCurrentRect());
}


void Player::attack(Enemy& enemy)
{
	enemy.takeDamage(attackPower);
	// анимация атаки
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
		row = 1;
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
	if (Keyboard::isKeyPressed(Keyboard::Down)) 
	{
		isBlocking = true;
		// block
	}
	animation.updateAnimation(row, time, faceRight);
	sprite.setTextureRect(animation.getCurrentRect());
	velocity.y += gravity * time; // gravity
	sprite.move(velocity * time);
}

void Player::OnCollition(Vector2f direction)
{
	if (direction.x < 0.0f) 
	{ // collition on the left
		velocity.x = 0.0f;
		canJump = false;
	}
	else if (direction.x > 0.0f) 
	{ // collition on the right
		velocity.x = 0.0f;
		canJump = false;
	}
	if (direction.y < 0.0f) 
	{ // collition on the bottom
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f) 
	{ // collition on the top
		velocity.y = 0.0f;
		canJump = false;
	}
	if (direction.x != 0.0f)
	{
		canJump = false;
	}

}

