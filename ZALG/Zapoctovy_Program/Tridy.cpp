#include "Tridy.h"
#include <functional>
#include <iostream>
#include <random>
#include <cmath>
#include <algorithm>
#include <vector>

// DLAZDICE

Dlazdice::Dlazdice() {
	gCost = 0;
	hCost = 0;
	i = 0;
	j = 0;
	status = '.';
	pruchozi = true;
}

bool Dlazdice::operator==(const Dlazdice &b){
	if(b.i == this->ziskejRadek() && b.j == this->ziskejSloupec()) {
		return true;
	}
	return false;	
}

// Dlazdice::GETTERS

int Dlazdice::fCost() {
	return gCost + hCost;
}

int Dlazdice::ziskejRadek() {
	return i;
}

int Dlazdice::ziskejSloupec() {
	return j;
}

char Dlazdice::ziskejStatus() {
	return status;
}

int Dlazdice::ziskejG() {
	return gCost;
}

int Dlazdice::ziskejH() {
	return hCost;
}

bool Dlazdice::ziskejPruchozi() {
	return pruchozi;	
}

// Dlazdice::SETTERS

void Dlazdice::nastavPozice(int _i, int _j) {
	i = _i;
	j = _j;
}

void Dlazdice::nastavG(int _gCost) {
	gCost = _gCost;
}

void Dlazdice::nastavH(int _hCost) {
	hCost = _hCost;
}

void Dlazdice::nastavStatus(char _status) {
	status = _status;
}

void Dlazdice::nastavPruchozi(bool _pruchozi) {
	pruchozi = _pruchozi;
}

// Dlazdice::PRINTOUT

void Dlazdice::vypisStatus() {
	std::cout << "{" << status << "}";
}

void Dlazdice::vypisPozici() {
	std::cout << "| [" << i << "],[" << j << "] |"; 	
}

// MATICE

Matice::Matice(int _m, int _n) {
	m = _m;
	n = _n;
	matice = new Dlazdice[m * n];	
}

int Matice::ziskejPocRadku() {
	return m;
}

int Matice::ziskejPocSloupcu() {
	return n;
}

Dlazdice* Matice::ziskejMatici(int _i, int _j) {
	return &matice[_i * m + _j];
}

void Matice::zobraz() {
	for (int r = 0; r < m; r++) {
		for (int s = 0; s < n; s++) {
//			matice[r * m + s].vypisPozici();
			matice[r * m + s].ziskejStatus();
			matice[r * m + s].vypisStatus();
		}
		std::cout << "\n" << std::endl;
	}
	std::cout << "\n" << std::endl;	
}

void Matice::priradPozice() {
	for (int r = 0; r < m; r++) {
		for (int s = 0; s < n; s++) {
			matice[r * m + s].nastavPozice(r, s);
		}
	}
}

// Nahodne prekazky
void Matice::pridejPrekazky(int pocet) {
	if(pocet > m*n) {
		throw std::out_of_range("Vice prekazek nez dlazdic!");
	}
	
	int maxM = m-1;
	int maxN = n-1;
	int min = 0;
		
	std::random_device rd;
	std::mt19937 rng(rd());
	
	for (int p = 0; p < pocet; p++) {
		std::uniform_int_distribution<int> uniM(min, maxM);
		auto indM = uniM(rng);	
		std::uniform_int_distribution<int> uniN(min, maxN);
		auto indN = uniN(rng);
		if (matice[indM * m + indN].ziskejStatus() != 'X') {
			matice[indM * m + indN].nastavStatus('X');
			matice[indM * m + indN].nastavPruchozi(false);
			continue;
		};
		p--;
	}	
}

void Matice::pridejStart(int _i, int _j) {
	matice[_i * m + _j].nastavStatus('s');
}

void Matice::pridejCil(int _i, int _j) {
	matice[_i * m + _j].nastavStatus('c');
}

std::vector<Dlazdice> Matice::najdiSousedy(Dlazdice *aktualni) {
	std::vector<Dlazdice> *sousedi = new std::vector<Dlazdice>;

	for (int r = -1; r <= 1; r++) {
		for (int s = -1; s <= 1; s++) {
			if (s==0 && r==0) continue;
			
			int kontrolaX = aktualni->ziskejRadek() + r;
			int kontrolaY = aktualni->ziskejSloupec() + s;

			if (kontrolaX >= 0 && kontrolaX < m && kontrolaY >= 0 && kontrolaY < n) {
				sousedi->push_back(matice[kontrolaX * m + kontrolaY]);
			}	
		}
	}

	return *sousedi;
}

Dlazdice *Matice::najitStart() {
	for (int r = 0; r < m; r++) {
		for (int s = 0; s < n; s++) {
			if (matice[r * m + s].ziskejStatus() == 's') {
				return &matice[r * m + s];
			}
		}
	}
	throw std::out_of_range("S nelze nalezt"); //upravit
}

Dlazdice *Matice::najitCil() {
	for (int r = 0; r < m; r++) {
		for (int s = 0; s < n; s++) {
			if (matice[r * m + s].ziskejStatus() == 'c') {
				return &matice[r * m + s];
			}
		}
	}
	throw std::out_of_range("C nelze nalezt"); //upravit
}
int Matice::ziskejVzdalenost(Dlazdice *mistoA, Dlazdice *mistoB) {
	int vzdalX = abs(mistoA->ziskejRadek() - mistoB->ziskejRadek());	
	int vzdalY = abs(mistoA->ziskejSloupec() - mistoB->ziskejSloupec());
	
	if (vzdalX > vzdalY) return 14*vzdalY + 10*(vzdalX-vzdalY);
	return 14*vzdalX + 10*(vzdalY-vzdalX);
}

bool Matice::jeUvnitrVektoru(Dlazdice a, std::vector<Dlazdice> vektor) {
	for (Dlazdice i: vektor) {
		if (i == a) return true;	
	}	
	return false;
}
