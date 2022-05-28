#include <iostream>
#include "Tridy.h"

// OSETRIT KDYZ NEEXISTUJE START/CIL
// pridat cisla kroku


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

Program vykresli cely proces hledani cile (vsechny pozice agenta 'a') a nasledne zobrazi pouze finalni optimalni trasu (oznacena pomoci 'O').)" << std::endl;
	
	std::cout << "Pro nacteni vstupniho souboru stisknete klavesu [Enter]..." << std::endl;
	std::cin.ignore();
	
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
		std::cin.ignore();
	}

//	matice->vypsatNejkratsiCestu(matice->ziskatNejkratsiCestu());
	std::cout << ">Cesta: \n" << std::endl;
	matice->vykreslitNejkratsiCestu(matice->ziskatNejkratsiCestu());
	std::cout << ">Pocet kroku: " << matice->ziskatNejkratsiCestu().size() << std::endl;
	return 0;
}
