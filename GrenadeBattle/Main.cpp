#include <SFML/Graphics.hpp>
#include "Game.h"
#include <stdlib.h>
#include <time.h>
#include "AssetManager.h"


int main()

{
    //initalise the random number generator
    srand(time(NULL));

    //Create game

    Game gameInstance;

    gameInstance.RunGameLoop();


    AssetManager::DestroyAllAssets();

    //if we get here game is over end program by returning

    return 0;
}