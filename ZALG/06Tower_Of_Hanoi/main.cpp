#include <iostream>
#include "Game.h"

int main() {
	Game game = Game(5);
	int amt = game.play();

	std::cout << "Disc amount: " << amt << std::endl;

	return 0;
}
