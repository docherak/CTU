#include <iostream>
#include "Tridy.h"

#define N_ROWS 7
#define N_COLUMNS 7

void spustitProgram(int _sloupce, int _rady) {
	Matice *mrizka = new Matice(_sloupce, _rady);
	mrizka->priradPozice();
	mrizka->zobraz();	
	mrizka->pridejPrekazky(20); // je mozne, ze dve se prepisou
	mrizka->pridejStart(0,0);
	mrizka->pridejCil(4,6);
	std::cout << "Grid: " << std::endl;
	mrizka->pridelGH();
	mrizka->zobraz();
	mrizka->najitCestu();
}

int main(int argc, char *argv[]) {

	int sloupce = N_COLUMNS;
	int rady = N_ROWS;

	if (argc > 3) return 1;	
	if (argc == 3) {
		sloupce = atoi(argv[1]);
		rady = atoi(argv[2]);
		spustitProgram(sloupce, rady);
		return 0;
	}

	std::cout << sloupce;
	Matice *path = new Matice(sloupce, rady);
	path->priradPozice();
	path->pridejPrekazky(20); // je mozne, ze dve se prepisou
	path->pridejStart(0,0);
	path->pridejCil(4,6);
	std::cout << "Grid: " << std::endl;
	path->zobraz();
	path->najitCestu();
	return 0;
}
