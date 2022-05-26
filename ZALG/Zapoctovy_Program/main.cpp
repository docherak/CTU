#include <iostream>
#include "Tridy.h"

void spustitProgram() {
}

int main() {

	Matice *path = new Matice(5,5);
	path->priradPozice(); // funguje to!!! volejte slava a tri dny se radujte!
	path->pridejPrekazky(5);
	path->pridejStart(0,0);
	path->pridejCil(3,4);
	std::cout << "Grid: " << std::endl;
	path->zobraz(); // funguje to!!! volejte slava a tri dny se radujte!
	path->najitStart()->vypisPozici();
	path->najitCil()->vypisPozici();
	if (path->najitCil() == path->najitCil()) {
		std::cout << "gello" << std::endl;
	} else {
		std::cout << "diff" << std::endl;
	}
	int dist = path->ziskejVzdalenost(path->najitStart(),path->najitCil());
	std::cout << dist << std::endl;
}
