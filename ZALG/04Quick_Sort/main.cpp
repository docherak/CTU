#include <iostream>
#include <random>
#include <chrono>

std::default_random_engine engine;
std::uniform_int_distribution<int> distribution(-100, 100);

const int N = 9;

int a[N];

int getRandomNumber() {
	return distribution(engine);
}

void print() {
	puts("=====");
	for (int i = 0; i < N; i++) {
		std::cout << "a{" << i << "] = " << a[i] << "\n";
	}
	puts("=====");
}

inline void _swap(int& x, int& y) {
	int tmp = x;
	x = y;
	y = tmp;
}

void quicksort(int leftStart, int rightStart) {
	// Select pivot
	int pivot = a[(leftStart+rightStart)/2]; // value of the "middle" elem
	
	int left = leftStart;
	int right = rightStart;

	while (left <= right) {
		while (a[left] < pivot) left ++;
		while (a[right] > pivot) right--;

		if (left <= right) {
			_swap(a[left], a[right]);
			left++; right--;
		}
	}
	// if() so there would be no infinite recursion
	if (leftStart < right) quicksort(leftStart, right);
	if (left < rightStart) quicksort(left, rightStart);
}

void init() {
	for (int i = 0; i < N; i++) {
		a[i] = getRandomNumber();
	}
}

int main() {
	init();
	print();

	auto start = std::chrono::high_resolution_clock::now();
	quicksort(0, N-1);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (end-start);

	print();
}



