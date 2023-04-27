#include "LevelScreen.h"
#include "AssetManager.h"
#include "Game.h"
#include <fstream>
#include <iostream>

LevelScreen::LevelScreen(Game* newGamepointer)
	:Screen(newGamepointer)
	, player()
	, gameRunning(true)
{
	//Restart();
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{

		player.Update(frameTime);

	}
}


void LevelScreen::Draw(sf::RenderTarget& target)
{
	player.Draw(target);
}



