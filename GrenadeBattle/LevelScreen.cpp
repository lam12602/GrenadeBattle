#include "LevelScreen.h"
#include "AssetManager.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include "Platform.h"

LevelScreen::LevelScreen(Game* newGamepointer)
	:Screen(newGamepointer)
	, player()
	, platforms()
	, gameRunning(true)
{
	//Restart();
	
}

void LevelScreen::Update(sf::Time frameTime)
{
	if (gameRunning)
	{

		player.Update(frameTime);
		
		/*for (int i = 0; i < platforms.size(); ++i)
		{
			platforms[i]->Update(frameTime);
		}
		
		for (int i = 0; i < platforms.size(); ++i)
		{
			platforms[i]->SetColliding(false);
		}
		*/
		player.SetColliding(false);
		



		for (int i = 0; i < platforms.size(); ++i)
		{
			if (platforms[i]->CheckCollision(player))
			{
				player.SetColliding(true);
				platforms[i]->SetColliding(true);
				player.HandelCollision(*platforms[i]);
				platforms[i]->HandelCollision(player);
			}
		}
		
	}
}


void LevelScreen::Draw(sf::RenderTarget& target)
{
	player.Draw(target);
	
	for (int i = 0; i < platforms.size(); ++i)
	{
		platforms[i]->Draw(target);
	}
}



