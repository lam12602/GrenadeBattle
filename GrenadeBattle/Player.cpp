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
	, pips()
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/player_1_stand.png"));

	collisionoffset = sf::Vector2f(0, 0);
	collisionscale = sf::Vector2f(1.0f, 1.0f);
	collisionType = CollisionType::CIRCLE;

	//add sprite to my pips
	const int NUMPIPS = 5;
	for (int i = 0; i < NUMPIPS; ++i)
	{
		pips.push_back(sf::Sprite());
		pips[i].setTexture(AssetManager::RequestTexture("Assets/Graphics/pip.png"));
	}
}

void Player::Update(sf::Time frameTime)
{
	float pipTime = 0;
	float pipTimeStep = 1.0f;
	for (int i = 0; i < pips.size(); ++i)
	{
		pips[i].setPosition(GetPipPosition(pipTime));
		pipTime += pipTimeStep;
	}

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

void Player::Draw(sf::RenderTarget& target)
{
	for (int i = 0; i < pips.size(); ++i)
	{
		target.draw(pips[i]);
	}
}

void Player::HandelCollision(SpriteObject& other)
{
	sf::Vector2f depth = GetCollisionDepth(other);
	sf::Vector2f newPos = GetPosition();

	if (abs(depth.x) < abs(depth.y))
	{
		newPos.x += depth.x;
		velocity.x = 0;
		acceleration.x = 0;
	}
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

sf::Vector2f Player::GetPipPosition(float pipTime)
{
	sf::Vector2f pipPosiiton;

	pipPosiiton = sf::Vector2f(0, 1000) * pipTime * pipTime + sf::Vector2f(500, -1000) * pipTime + sf::Vector2f(500, 500);



	return pipPosiiton;
}





	





