#include <iostream>
#include <random>
#include <chrono>

// Note: Operator overloading
using namespace std;

// Global
default_random_engine engine;
uniform_int_distribution<int> distribution(-1000, 1000);

const int N = 1'000'000;
int a[N];

int getRandomNumber()
{
	return distribution(engine);
}

void vypis()
{
	puts("------------");
	for (int i = 0; i < N; i++)
	{
		cout << "a[" << i << "] = " << a[i] << "\n";
	}
	puts("------------");
}

inline void swap_(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

void quicksort(int levy_zacatek, int pravy_zacatek)
{
	// vyber pivotu
	int pivot = a[(levy_zacatek + pravy_zacatek) / 2]; // prostredni prvek; celociselne deleni, zaokrouhli se dolu; hodnota, ne index
	
	int levy = levy_zacatek;
	int pravy = pravy_zacatek;

	while (levy <= pravy) // pojedu z obou stran indexovani, dokud se mi neprekrizi
	{
		while (a[levy] < pivot) levy++;
		while (a[pravy] > pivot) pravy--;

		if (levy <= pravy)
		{
			swap_(a[levy], a[pravy]);
			levy++; pravy--;
		}
	}

	// if() aby nebyla nekonecna rekurze
	if (levy_zacatek < pravy) quicksort(levy_zacatek, pravy); // prohodili se
	if (levy < pravy_zacatek) quicksort(levy, pravy_zacatek); // prohodili se
}

int main()
{
	for (int i = 0; i < N; i++)
	{
		a[i] = getRandomNumber();
	}
	// vypis();
	// Zmereni quicksortu
	auto start = std::chrono::high_resolution_clock::now();
	quicksort(0, N - 1);
	auto end = std::chrono::high_resolution_clock::now();

	auto duration = chrono::duration_cast<chrono::milliseconds> (end - start);

	cout << "Duration: " << duration.count() << " ms" << endl;
	// vypis();
}

