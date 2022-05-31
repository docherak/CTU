#include <iostream>
#include "Tridy.h"

int main() {
	std::cout << R"(
		|				|
		|	A* 	algoritmus	|
		|_______________________________|
	)" << std::endl;
	std::cout << "Program nacita maticove bludiste ze spravne naformatovaneho textoveho souboru a nasledne vyuziva A* algoritmus pro co nejkratsi pruchod bludistem od oznaceneho pocatku az do cile." << std::endl;

	std::cout << R"(
Vstupni soubor s pevnym nazvem vstup.txt je nutne dat do stejne slozky jako program a pro spravne fungovani musi byt obsah v nasledujicim formatu:
	
		m n				// prvni radek souboru
		p[1,1]	.....	p[1,n]
		.   .		.
		.	.	.
		.	    .	.	
		p[m,1]	.....	p[m,n]		// posledni radek souboru

		m - pocet radku v matici
		n - pocet sloupcu v matici
		p[i,j] - ij-te prvky matice, pro ktere plati:
			- '.' znaci volny prostor
			- 'X' znaci prekazku
			- 's' znaci start
			- 'c' znaci cil 
	
		napr.:
		2 3
		. . .
		s X c

Program vykresli cely proces hledani cile (vsechny pozice agenta 'a') a nasledne zobrazi pouze finalni optimalni trasu (oznacena pomoci 'O').
Kazdy dalsi krok se vykresli po stisknuti [Enter].)" << std::endl;
	
	std::cout << "Pro nacteni vstupniho souboru stisknete klavesu [Enter]..." << std::endl;
	std::cin.ignore();
	
	Matice *matice = nullptr;
	
	// Pokus o nacteni matice:
	try {
		matice = new Matice();
	} catch (std::string &chyba) {
		std::cout << chyba << std::endl;
		return -1;
	}

	// Volani jednotlivych kroku agenta A*:
	int krok = 1;
	while(!matice->jeKompletni()) {
		if (matice->jeNemozne()) break;
		std::cout << "Krok no. " << krok << ":" << std::endl;
		matice->krok();
		krok++;
		std::cin.ignore();
	}
	std::cout << ">Pocet kroku: " << krok-1 << '\n' << std::endl;

	// Vykresleni nejkratsi cesty:
	std::cout << ">Nejkratsi cesta:" << std::endl;
	std::cin.ignore();
	matice->vykreslitNejkratsiCestu(matice->ziskatNejkratsiCestu());
	std::cout << ">Pocet kroku: " << matice->ziskatNejkratsiCestu().size() << std::endl;

	return 0;
}
