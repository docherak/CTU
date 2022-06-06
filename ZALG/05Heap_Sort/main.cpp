#include <iostream>
#include <random>

std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(0, 49);

const int N = 50;
int a[N];
int occurence[50] = { 0 };

/*		i[i]
 *	   |-----|-----|
 * 	i[2*i+1]  i[2*i+1+1]
 */

inline void _swap(int& x, int& y) {
	int tmp = x;
	x = y;
	y = tmp;
}

inline void swap_alt(int x, int y) {
	int tmp = a[x];
	a[x] = a[y];
	a[y] = tmp;
}

void heapify(int i, int k) {
	while(2 * i + 1 <= k) {
		int v = 2 * i + 1;
		if (v + 1 <= k)
			if (a[v+1] > a[v]) // if right child is larger than left
				v += 1; // I'm gonna use the right one
		if (a[v] > a[i] ) {
			_swap(a[v], a[i]);
			// swap_alt(v, i);
			i = v;  // reset start index
		} else {
			i = k + 1; // breaks cycle
			// break
		}
	}
}

void heapsort(int n) {
	for (int i = n-1; i >= 0; i--) // heapify array
		heapify(i, n-1);
	for (int i = n-1; i > 0; i--) {
		_swap(a[0], a[i]); // remove top value
		heapify(0, i - 1);
	}
}

void print() {
	for (int i = 0; i < N; i++) {
		std::cout << "a[" << i << "] = " << a[i] << "\n";
	}
}

void printOccurence() {
	std::cout << "Occurence:\n";
	for (int i = 0; i < 50; i++)
		std::cout << i << ": " << occurence[i] << "\n";

}

int main() {
	for (int i = 0; i < N; i++) {
		a[i] = distribution(generator);
		occurence[a[i]]++;
	}
	print();
	heapsort(N);
	print();
	// printOccurence();
	return 0;
}
