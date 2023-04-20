#include "Game.h"
#include "Screen.h"
//#include "LevelScreen.h"

Game::Game()
	:window(sf::VideoMode::getDesktopMode(), "Grenade Battle", sf::Style::Titlebar | sf::Style::Close)
	, gameClock()
	, currentScreen(nullptr)
{
	window.setMouseCursorVisible(false);
	//set up screen
	//currentScreen = new LevelScreen(this);
}

void Game::RunGameLoop()
{
	//repete as long as window is open
	while (window.isOpen())
	{
		Update();
		Draw();
		EventHandeling();
	}
}

void Game::EventHandeling()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		//close the game if esc is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}
}

void Game::Update()
{
	sf::Time frameTime = gameClock.restart();

	// Update current screen
	if (currentScreen != nullptr)
		currentScreen->Update(frameTime);
}

void Game::Draw()
{
	window.clear();

	// Draw current screen
	if (currentScreen != nullptr)
		currentScreen->Draw(window);

	window.display();
}

sf::RenderWindow* Game::GetWindow()
{
	return &window;
}
