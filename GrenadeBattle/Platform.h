#pragma once
#include "SpriteObject.h"
class Platform :
    public SpriteObject
{
public:
    Platform(sf::Vector2f newPos);


protected:
    sf::Vector2f position;

};

