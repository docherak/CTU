#include <iostream>

const int N = 8;
const bool L = false;
const int limit = 2;

int p[N][N];

int bt_x[N][N];
int bt_y[N][N];

void init() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			p[i][j] = -1;
			bt_x[i][j] = -1;
			bt_y[i][j] = -1;
		}
	}
}

void jump(int x, int y, int distance, int x0 = -1, int y0 = -1) {
	if (x >= 0 && x < N && y >=0 && y < N && (distance <= limit || !L)) {
		if (p[x][y] == -1 || p[x][y] > distance) {
			p[x][y] = distance;
			
			bt_x[x][y] = x0;
			bt_y[x][y] = y0;

			jump(x + 2, y + 1, distance + 1, x, y);
			jump(x + 2, y - 1, distance + 1, x, y);
			jump(x - 2, y + 1, distance + 1, x, y);
			jump(x - 2, y - 1, distance + 1, x, y);
			
			jump(x + 1, y + 2, distance + 1, x, y);
			jump(x - 1, y + 2, distance + 1, x, y);
			jump(x + 1, y - 2, distance + 1, x, y);
			jump(x - 1, y - 2, distance + 1, x, y);
		}	
	}
}

void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (p[i][j] == -1)
				std::cout << ". ";
			else
				std::cout << p[i][j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

int maxLength() {
	int v = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (v < p[i][j]) v = p[i][j];
		}
	}
	return v;
}

void search(int x, int y) {
	while (x >= 0 && y >= 0) {
		std::cout << x << ", " << y << "\n";
		int tmp = bt_x[x][y];
		y = bt_y[x][y];
		x = tmp;
	}
}

void recursiveSearch(int x, int y) {
	if (x >= 0 && y >= 0) {
		recursiveSearch(bt_x[x][y], bt_y[x][y]);
		std::cout << x << ", " << y << "\n";
	}
}

int main() {
	init();
	print();
	jump(3, 3, 0);
	print();
	std::cout << "Longest path is " << maxLength() << " jumps." << std::endl;
	recursiveSearch(5,5);
	return 0;
}
