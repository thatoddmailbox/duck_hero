#include <iostream>

#include "game.hpp"

int main() {
	std::cout << "duck hero" << std::endl;

	duckhero::Game game = duckhero::Game();
	return game.Run();
}
