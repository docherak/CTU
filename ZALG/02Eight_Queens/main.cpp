#include <functional>
#include <iostream>
#define TEST 1

const int N = 8;
int p[N];
int numOfSolutions = 0;

int calls[N] = { 0 };

void init() {
	for (int i = 0; i < N; i++) {
		p[i] = -1;
		// std::cout << p[i] << std::endl;
	}
}

void printResult() {
	for (int i = 0; i < N; i++) {
		std::cout << p[i] << " ";
	std::cout << " -> " << numOfSolutions << std::endl;
	}
}

void place(int col) {
	calls[col]++;

	// Row cycle
	for (int row = 0; row < N; row++) {
		bool ok = true;

		// Conflict check
		for (int v = 1; v <= col && ok; v++) {
			int queen = p[col - v];

			if (queen == row || queen == row + v || queen == row - v) {
				ok = false;
			}
		}

		// If no conflict
		if (ok) {
			
			// Place the queen
			p[col] = row;
			if (col == N - 1) {
				numOfSolutions++;
				printResult();
#if TEST
				std::cout << "Number of all solutions: " << numOfSolutions << std::endl;
				int numOfCalls = 0;
				for (int i = 0; i < N; i++) {
					numOfCalls += calls[i];
					std::cout << "Function place(" << i << ") was called " << calls[i] << "x" << std::endl;
				}
				std::cout << "Num of all calls: " << numOfCalls << std::endl;
				exit(0);
#endif
			} else if (col < N - 1) {
				place(col + 1);
			} else {
				std::cout << "This should be unreachable." << std::endl;
			}
		}
	}
}

int main() {
	init();
	place(0);
	return 0;
}
