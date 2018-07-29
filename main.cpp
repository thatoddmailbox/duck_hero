#include <iostream>

#include "game.hpp"

int main(int argc, char * argv[])
{
	std::cout << "duck hero" << std::endl;

	duckhero::Game game = duckhero::Game();
	return game.Run();
}
