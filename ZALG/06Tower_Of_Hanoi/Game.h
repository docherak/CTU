#include "Tower.h"

class Game
{
public:
	Tower *A, *B, *C;
	int discAmount;
	int stepsAmount;

	Game() = default;
	Game(int _discAmount);
	~Game() = default;

	void print();
	void step(Tower* X, Tower* Y);	
	void play(Tower* X, Tower* Y, Tower* Z, int k);	
	int play();
};
