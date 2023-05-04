#pragma once
#include "Screen.h"
#include <SFML/Graphics.hpp>
#include "Player.h"


class Platform;

class LevelScreen :
    public Screen
{
public:
    LevelScreen(Game* newGamepointer);
    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

    void TriggerEndState(bool _win);

    bool LoadNextLevel();



private:

    void Restart();

    bool LoadLevel(int levelNumber);
    bool LoadLevel(std::string fileName);


    Player player;
    std::vector<Platform*> platforms;
    
    bool gameRunning;

 

    //sf::View camera;
    //int currentLevel;

};