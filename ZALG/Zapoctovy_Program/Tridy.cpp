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
	matice = new Dlazdice[m * n]();	
}

Matice::~Matice() {
	delete[] matice;
	matice = NULL;
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
//			std::cout << "| [" << matice[r * m +s].ziskejG() << "],[" << matice[r * m + s].ziskejH() << "] |"; 	
//			matice[r * m + s].vypisPozici();
			matice[r * m + s].ziskejStatus();
			matice[r * m + s].vypisStatus();
		}
		std::cout << "\n" << std::endl;
	}
	std::cout << "\n" << std::endl;	
}

void Matice::zobrazCosts() {
	for (int r = 0; r < m; r++) {
		for (int s = 0; s < n; s++) {
			std::cout << "| [" << matice[r * m +s].ziskejG() << "],[" << matice[r * m + s].ziskejH() << "] |"; 	
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
	matice[_i * m + _j].nastavPruchozi(true);
}

std::vector<Dlazdice> Matice::najdiSousedy(Dlazdice *aktualni) {
	std::vector<Dlazdice> sousedi;// = new std::vector<Dlazdice>;

	for (int r = -1; r <= 1; r++) {
		for (int s = -1; s <= 1; s++) {
			if (s==0 && r==0) continue;
			
			int kontrolaX = aktualni->ziskejRadek() + r;
			int kontrolaY = aktualni->ziskejSloupec() + s;

			if (kontrolaX >= 0 && kontrolaX < m && kontrolaY >= 0 && kontrolaY < n) {
				sousedi.push_back(matice[kontrolaX * m + kontrolaY]);
			}	
		}
	}

	return sousedi;
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

void Matice::najitCestu() {

	// Start a cil
	Dlazdice *start = najitStart();
	Dlazdice *cil = najitCil();

	// K vyhodnoceni
	std::vector<Dlazdice> *toEval = new std::vector<Dlazdice>();
	std::vector<Dlazdice> *evald = new std::vector<Dlazdice>();

	// Kroky
	toEval->push_back(*start);

	while (toEval->size() > 0) {
		std::cin.ignore();

		Dlazdice agent = toEval->at(0);

		for (int i = 1; i < toEval->size(); i++) {
			if ((toEval->at(i).fCost() < agent.fCost()) || (toEval->at(i).fCost() == agent.fCost() && toEval->at(i).ziskejH() < agent.ziskejH())) {
				agent = toEval->at(i);
//				break;
			}	
		}

//		// Odstranit ji z k vyhodnoceni
		for(std::vector<Dlazdice>::size_type i = 0; i != toEval->size(); i++) {
    			if(toEval->at(i) == agent) {
        			toEval->erase(toEval->begin()+i);
        			break;
   			}
		}
		
		evald->push_back(agent);
		if (agent == *cil) {
			std::cout << "SUCCESS" << std::endl;
			return;	
		}
		
		// Soused loop
		std::vector<Dlazdice> sousedi = najdiSousedy(&agent);
	//	(&agent)->vypisPozici();	
		for (Dlazdice soused: sousedi) {
//			soused.vypisPozici();
			if (!soused.ziskejPruchozi() || jeUvnitrVektoru(soused, *evald)) {
				continue;
			} 	
//			soused.vypisPozici();	
			int novySousedCost = agent.ziskejG() + ziskejVzdalenost(&agent, &soused);
//			std::cout << ":" << novySousedCost << std::endl;
			if (novySousedCost < soused.ziskejG() || !jeUvnitrVektoru(soused, *toEval)) {
				soused.nastavG(novySousedCost);
				soused.nastavH(ziskejVzdalenost(&soused,cil));
				matice[soused.ziskejRadek() * m + soused.ziskejSloupec()].nastavG(novySousedCost);
				matice[soused.ziskejRadek() * m + soused.ziskejSloupec()].nastavH(ziskejVzdalenost(&soused, cil));
//				std::cout << soused.ziskejG() << " " << soused.ziskejH() << std::endl;
				
				if(!jeUvnitrVektoru(soused, *toEval)) {
					toEval->push_back(soused);
				}
			}
		}
		if (agent == *start || agent == *cil) {
			zobraz();
		} else {
			ziskejMatici(agent.ziskejRadek(), agent.ziskejSloupec())->nastavStatus('a');
			zobraz();	
			zobrazCosts();
		}
		//PRIDAT COUNTER KOLIKRAT BYL EVALUATED	


		
	}
	std::cout << "NO PATH" << std::endl;
	return;	
}

void Matice::pridelGH(){
	for (int r = 0; r < m; r++) {
		for (int s = 0; s < n; s++) {
			matice[r * m + s].nastavG(ziskejVzdalenost(najitStart(), &matice[r*m+s]));
			matice[r * m + s].nastavH(ziskejVzdalenost(najitCil(), &matice[r*m+s]));
		}
	}
}
