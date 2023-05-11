#pragma once
#include "SpriteObject.h"
class Player :
    public SpriteObject
{

public:

    Player();

    void Update(sf::Time frameTime) override;
    
    void Draw(sf::RenderTarget& target) override;

    void HandelCollision(SpriteObject& other) override;

private:

    void UpdateAcceleration();

    sf::Vector2f GetPipPosition(float pipTime);


    int playerNO;
    sf::Vector2f twoFramOldPos;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    std::vector<sf::Sprite> pips;



};
