#include <FeldEngine/Base/FeldEngineErrors.h>

#include <cstdlib>
#include <iostream>

#include <SDL/SDL.h>

namespace Fd 
{
	//function for print out a error message and exit the game
	void fatalError(std::string errorString) {
		std::cout << errorString << std::endl;
		std::cout << std::endl << "Press any key to exit...";
		int k;
		std::cin >> k;
		SDL_Quit();
		exit(69);
	}

	//Some other errors funtion will come
}