#pragma once
#include <SFML/Graphics.hpp>>


enum class CollisionType
{
	CIRCLE,
	AABB
};

class SpriteObject
{
public:
	SpriteObject();


	virtual void Update(sf::Time frameTime);
	virtual void Draw(sf::RenderTarget& target);

	sf::Vector2f GetPosition();
	virtual void SetPosition(sf::Vector2f newPosition);
	void SetPosition(float newx, float newy);

	bool CheckCollision(SpriteObject other);
	void SetColliding(bool newColliding);

	sf::Vector2f GetCollisionDepth(SpriteObject other);

	virtual void HandelCollision(SpriteObject& other);

	void SetAlive(bool newalive);


protected:
	sf::Sprite sprite;

	sf::Vector2f collisionoffset;
	sf::Vector2f collisionscale;

	CollisionType collisionType;

	bool alive;

private:

	sf::Vector2f GetCollisionCentre();
	float GetCircleColliderRadius();
	sf::FloatRect GetAABB();

	sf::Vector2f position;
	bool colliding;


};

