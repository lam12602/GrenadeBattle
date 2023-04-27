#include "Player.h"
#include "SpriteObject.h"
#include "AssetManager.h"


enum class PhysicsType {
	FORWARD_EULER,
	BACKWARD_EULER,
	VELOCITY_VERLET

};

Player::Player()
	: SpriteObject()
	, twoFramOldPos(100, 300)
	, velocity()
	, acceleration()
	, playerNO(1)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/player_1_stand.png"));

	collisionoffset = sf::Vector2f(0, 30);
	collisionscale = sf::Vector2f(0.5f, 0.5f);
	collisionType = CollisionType::CIRCLE;
}

void Player::Update(sf::Time frameTime)
{
	const float DRAG_MULT = 10.0f;
	const PhysicsType physics = PhysicsType::FORWARD_EULER;

	
	switch (physics)
	{

	case PhysicsType::FORWARD_EULER:
	{
		SetPosition(GetPosition() + velocity * frameTime.asSeconds());
		velocity = velocity + acceleration * frameTime.asSeconds();


		velocity = velocity - velocity * DRAG_MULT * frameTime.asSeconds();


		UpdateAcceleration();
	}
	break;

	//Practical Task - Physics Alternatives
	case PhysicsType::BACKWARD_EULER:
	{
		UpdateAcceleration();

		velocity = velocity + acceleration * frameTime.asSeconds();


		velocity = velocity * DRAG_MULT;

		SetPosition(GetPosition() + velocity * frameTime.asSeconds());
	}
	break;



	case PhysicsType::VELOCITY_VERLET:
	{
		sf::Vector2f halfFramVelocity = velocity + acceleration * frameTime.asSeconds() / 2.0f;

		SetPosition(GetPosition() + halfFramVelocity * frameTime.asSeconds());
		UpdateAcceleration();

		velocity = halfFramVelocity + acceleration * frameTime.asSeconds() / 2.0f;

		velocity = velocity * DRAG_MULT;

	}
	break;

	default:
		break;
	}
}

void Player::HandelCollision(SpriteObject& other)
{
}

void Player::UpdateAcceleration()
{
	const float ACCEL = 1000;
	//const float GRAVITY = 3000;

	acceleration.x = 0;
	//acceleration.y = GRAVITY;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		acceleration.x = -ACCEL;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		acceleration.x = ACCEL;
	}
}





	





