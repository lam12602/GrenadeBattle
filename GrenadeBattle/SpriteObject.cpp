#include "SpriteObject.h"
#include "VectorHelper.h"
#include <algorithm>

SpriteObject::SpriteObject()
	: sprite()
	, position(0, 0)
	, colliding(false)
	, collisionoffset(0, 0)
	, collisionscale(1, 1)
	, collisionType(CollisionType::AABB)
	, alive(true)
{
}

void SpriteObject::Update(sf::Time frameTime)
{
}

void SpriteObject::Draw(sf::RenderTarget& target)
{
	if (!alive)
	{
		return;
	}


	target.draw(sprite);

	bool drawCollider = true;

	if (drawCollider)
	{

		switch (collisionType)
		{
		case CollisionType::CIRCLE:
		{



			sf::CircleShape circle;

			sf::Vector2f shapePosition = GetCollisionCentre();
			shapePosition.x -= GetCircleColliderRadius();
			shapePosition.y -= GetCircleColliderRadius();

			circle.setPosition(shapePosition);
			circle.setRadius(GetCircleColliderRadius());
			sf::Color collisioncolor = sf::Color::Green;
			if (colliding)
			{
				collisioncolor = sf::Color::Red;
			}
			collisioncolor.a = 100;
			circle.setFillColor(collisioncolor);

			target.draw(circle);
		}
		break;

		case CollisionType::AABB:
		{
			sf::RectangleShape rectangle;
			sf::FloatRect bounds = GetAABB();
			rectangle.setPosition(bounds.left, bounds.top);
			rectangle.setSize(sf::Vector2f(bounds.width, bounds.height));
			sf::Color collisioncolor = sf::Color::Green;
			if (colliding)
			{
				collisioncolor = sf::Color::Red;
			}
			collisioncolor.a = 100;
			rectangle.setFillColor(collisioncolor);
			target.draw(rectangle);

		}
		break;
		}

	}
	;

}

sf::Vector2f SpriteObject::GetPosition()
{
	return position;
}

void SpriteObject::SetPosition(sf::Vector2f newPosition)
{

	position = newPosition;
	sprite.setPosition(newPosition);
}

void SpriteObject::SetPosition(float newx, float newy)
{
	SetPosition(sf::Vector2f(newx, newy));
}

bool SpriteObject::CheckCollision(SpriteObject other)
{
	if (!alive || !other.alive)
		return false;


	switch (collisionType)
	{
	case CollisionType::CIRCLE:
	{
		if (other.collisionType == CollisionType::CIRCLE)
		{
			sf::Vector2f displacement = GetCollisionCentre() - other.GetCollisionCentre();


			float squaredistance = VectorHelper::SquareMagnitude(displacement);

			float combineRadii = GetCircleColliderRadius() + other.GetCircleColliderRadius();



			return squaredistance <= combineRadii * combineRadii;
		}
		else
		{
			sf::Vector2f nearestPointToCirlcle = GetCollisionCentre();
			sf::FloatRect otherAABB = other.GetAABB();

			nearestPointToCirlcle.x = fmaxf(otherAABB.left, fminf(nearestPointToCirlcle.x, otherAABB.left + otherAABB.width));
			nearestPointToCirlcle.y = fmaxf(otherAABB.top, fminf(nearestPointToCirlcle.y, otherAABB.top + otherAABB.height));

			sf::Vector2f displacement = nearestPointToCirlcle - GetCollisionCentre();
			float squareDistance = VectorHelper::SquareMagnitude(displacement);
			float circleRadius = GetCircleColliderRadius();
			return squareDistance <= circleRadius * circleRadius;
		}


	}
	break;
	case CollisionType::AABB:
	{
		if (other.collisionType == CollisionType::AABB)
		{
			return GetAABB().intersects(other.GetAABB());
		}
		else
		{
			sf::Vector2f nearestPointToCirlcle = other.GetCollisionCentre();
			sf::FloatRect thisAABB = GetAABB();

			nearestPointToCirlcle.x = fmaxf(thisAABB.left, fminf(nearestPointToCirlcle.x, thisAABB.left + thisAABB.width));
			nearestPointToCirlcle.y = fmaxf(thisAABB.top, fminf(nearestPointToCirlcle.y, thisAABB.top + thisAABB.height));

			sf::Vector2f displacement = nearestPointToCirlcle - other.GetCollisionCentre();
			float squareDistance = VectorHelper::SquareMagnitude(displacement);
			float circleRadius = other.GetCircleColliderRadius();
			return squareDistance <= circleRadius * circleRadius;

		}
	}
	break;

	}

}

void SpriteObject::SetColliding(bool newColliding)
{
	colliding = newColliding;
}

sf::Vector2f SpriteObject::GetCollisionDepth(SpriteObject other)
{
	sf::FloatRect thisAABB = GetAABB();
	sf::FloatRect otherAABB = other.GetAABB();

	sf::Vector2f thisCentre = GetCollisionCentre();
	sf::Vector2f otherCentre = other.GetCollisionCentre();

	sf::Vector2f minDistance;
	minDistance.x = thisAABB.width * 0.5f + otherAABB.width * 0.5f;
	minDistance.y = thisAABB.height * 0.5f + otherAABB.height * 0.5f;

	sf::Vector2f actualDistance = otherCentre - thisCentre;

	if (actualDistance.x < 0)
	{
		minDistance.x = -minDistance.x;
	}
	if (actualDistance.y < 0)
	{
		minDistance.y = -minDistance.y;
	}




	return actualDistance - minDistance;
}

void SpriteObject::HandelCollision(SpriteObject& other)
{
	//do nothing handled in child class
}

void SpriteObject::SetAlive(bool newalive)
{
	alive = newalive;
}

sf::Vector2f SpriteObject::GetCollisionCentre()
{
	sf::Vector2f centre = position;
	sf::FloatRect bounds = sprite.getLocalBounds();

	centre.x += bounds.width * 0.5f;
	centre.y += bounds.height * 0.5f;

	centre.x += collisionoffset.x;
	centre.y += collisionoffset.y;

	return centre;
}

float SpriteObject::GetCircleColliderRadius()
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	bounds.width = bounds.width * collisionscale.x;
	bounds.height = bounds.height * collisionscale.y;


	if (bounds.width > bounds.height)
	{
		return bounds.width * 0.5f;
	}
	else
	{
		return bounds.height * 0.5f;
	}

}

sf::FloatRect SpriteObject::GetAABB()
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	bounds.width = bounds.width * collisionscale.x;
	bounds.height = bounds.height * collisionscale.y;

	sf::Vector2f centre = GetCollisionCentre();


	bounds.top = centre.y - bounds.height * 0.5f;
	bounds.left = centre.x - bounds.width * 0.5f;

	return bounds;
}