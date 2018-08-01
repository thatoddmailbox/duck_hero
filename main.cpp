#include <iostream>

#include <cstdlib>
#include <ctime>

#include "game.hpp"

int main(int argc, char * argv[])
{
	srand(time(NULL));

	std::cout << "duck hero" << std::endl;

	duckhero::Game game = duckhero::Game();
	return game.Run();
}
