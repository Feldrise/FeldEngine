#include <FeldEngine/Core/FeldEngineErrors.h>

#include <cstdlib>
#include <SDL/SDL.h>

namespace Fd 
{
	//function used to print out an error message and exit the game
	void fatalError(std::string const& errorString) {
		log(errorString + '\n');
		log("Press any key to exit...");
		
		char key;
		std::cin >> key;
		
		SDL_Quit();
		abort();
	}
}
