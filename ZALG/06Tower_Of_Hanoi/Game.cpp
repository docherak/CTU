#include "Game.h"
#include <iostream>

Game::Game(int _discAmount) : discAmount(_discAmount), stepsAmount(0) {
	A = new Tower(_discAmount);
	B = new Tower(_discAmount);
	C = new Tower(_discAmount);
}

void Game::print() {
	A->print(discAmount);
	std::cout << " : ";
	B->print(discAmount);
	std::cout << " : ";
	C->print(discAmount);
	std::cout << std::endl;
	getchar(); // steps
}

void Game::step(Tower* X, Tower* Y) {
	stepsAmount++;
	int disc = X->discs.at(X->height - 1); // backup disc

	X->discs[X->height - 1] = 0; // nullify
	X->height -= 1; // substract height

	Y->height += 1; // add height
	Y->discs[Y->height - 1] = disc; // add new disc
}

void Game::play(Tower* X, Tower* Y, Tower* Z, int k) {
	if (k > 1)
		play(X, Z, Y, k - 1);
	step(X, Z);
	print();
	if (k > 1)
		play(Y, X, Z, k - 1);
}

int Game::play() {
	A->init();
	B->nullify();
	C->nullify();
	play(A, B, C, discAmount);
	return stepsAmount;
}
