#include <iostream>
#include "Tridy.h"

void pathfinder() {
	std::cout << R"(
		|				|
		|	A* 	algoritmus	|
		|_______________________________|
	)" << std::endl;
	std::cout << R"(
	Program nacita maticove bludiste ze spravne naformatovaneho textoveho souboru
a nasledne vyuziva A* algoritmus pro co nejkratsi pruchod bludistem od oznaceneho
pocatku az do cile.
	)" << std::endl;
	std::cout << "Pro spusteni programu stisknete klavesu [Enter]..." << std::endl;
	std::cin.ignore();
}

int main() {

	pathfinder();

	Matice *matice = nullptr;
	
	try {
		matice = new Matice();
	} catch (std::string &chyba) {
		std::cout << chyba << std::endl;
		return -1;
	}

	while(!matice->jeKompletni()) {
		if (matice->jeNemozne()) break;
		matice->krok();
		puts("----------------");
		std::cin.ignore();
	}

	std::cout << "Pocet kroku: " << matice->ziskatNejkratsiCestu().size() << std::endl;
	std::cout << "Cesta: " << std::endl;
	matice->vypsatNejkratsiCestu(matice->ziskatNejkratsiCestu());
	matice->vykreslitNejkratsiCestu(matice->ziskatNejkratsiCestu());
	return 0;
}
