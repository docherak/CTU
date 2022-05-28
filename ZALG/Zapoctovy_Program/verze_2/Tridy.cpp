#include "Tridy.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm> //iterace pres vektor
#include <vector>
#include <cmath>

//			
//			
//			
//	DLAZDICE
//		
//		
//		

Dlazdice::Dlazdice(int _i, int _j, bool _prekazka, bool _pocatek, bool _cil, char _status) :
	i(_i),
	j(_j),
	prekazka(_prekazka),
	pocatek(_pocatek),
	cil(_cil),
	status(_status)
{
}

// Getters
int Dlazdice::ziskatG() const {return gCost;}
int Dlazdice::ziskatH() const {return hCost;}
int Dlazdice::ziskatF() const {return gCost + hCost;}
int Dlazdice::ziskatPoziciRadek() const {return i;}
int Dlazdice::ziskatPoziciSloupec() const {return j;}
char Dlazdice::ziskatStatus() const {return status;}
Dlazdice* Dlazdice::ziskatRodice() const {return rodic;}

// Bools
bool Dlazdice::jePrekazkou() const {return prekazka;}
bool Dlazdice::jePocatek() const {return pocatek;}
bool Dlazdice::jeCil() const {return cil;}

// Setters
void Dlazdice::nastavGH(int _gCost, int _hCost) {
	gCost = _gCost;
	hCost = _hCost;
}

void Dlazdice::nastavRodice(Dlazdice *_rodic) {
	rodic = _rodic;
}

void Dlazdice::nastavStatus(char _status) {
	status = _status;	
}
//
//
//
//	MATICE
//
//
//

Matice::Matice() {
	zpracovatVstup();
}

Matice::~Matice() {
	vymazatData();
}

void Matice::obnovit() {
	vymazatData();
	zpracovatVstup();
}

bool Matice::jeKompletni() const {return maticeKompletni;}
bool Matice::jeNemozne() const {return nemozne;}
int Matice::ziskejRadky() const {return m;}
int Matice::ziskejSloupce() const {return n;}

void Matice::krok() {
	if (!maticeKompletni && toEval.size() < 1) {
		std::cout << "nejde" << std::endl;
		nemozne = true;
		return;
	}

	if (maticeKompletni || toEval.size() < 1) {
		return;
	}
	
	// A*
	Dlazdice *agent = toEval.at(0);
	
	for (Dlazdice *d : toEval) {
		if (*d < *agent) {
			agent = d;
		}
	}

	// <algorithm>
	toEval.erase(std::remove(toEval.begin(), toEval.end(), agent), toEval.end());
	evald.push_back(agent);

	// uspech
	if (agent == cilovaDlazdice) {
		trasovat();
		return;
	}

	// sousedi
	std::vector<Dlazdice*> sousedniDlazdice = najdiSousedy(agent);	
	
	for (Dlazdice *soused : sousedniDlazdice) {
//		std::cout << agent->ziskatPoziciRadek() << "," << agent->ziskatPoziciSloupec() << std::endl;	
//		std::cout << soused->ziskatPoziciRadek() << "," << soused->ziskatPoziciSloupec() << std::endl;	
		if (soused->jePrekazkou() || std::count(evald.begin(), evald.end(), soused)) continue;
		bool uvnitrToEval = std::count(toEval.begin(), toEval.end(), soused);
		int novySousedCost = agent->ziskatG() + vzdalenostDlazdic(agent, soused);
		if (novySousedCost < soused->ziskatG() || !uvnitrToEval) {
			soused->nastavGH(novySousedCost, vzdalenostDlazdic(soused,cilovaDlazdice));
			soused->nastavRodice(agent);
			if (!uvnitrToEval) toEval.push_back(soused); 
		}
	}
	if (agent == startovniDlazdice || agent == cilovaDlazdice) {
		vykresliCestu();
	} else {
		agent->nastavStatus('a');	
		vykresliCestu();
	}
	
}

void Matice::vymazatData() {
	for (int r = 0; r < pole.size(); ++r) {
		std::vector<Dlazdice*> &radek = pole.at(r);
		for (Dlazdice *d : radek) {
			delete d;
		}
		radek.clear();
	}
	pole.clear(); toEval.clear(); evald.clear(); nejkratsiCesta.clear();
	m = n = 0;
	nemozne = false;
	startovniDlazdice = cilovaDlazdice = nullptr;
	maticeKompletni = false;
}

void Matice::zpracovatVstup() {
	std::ifstream vstup(VSTUPNI_SOUBOR);
	std::string radek;
	bool prvniRadekNacten = false;
	int cRadku = 0;

	if (!vstup.is_open()) {
		throw std::string("Soubor nelze nacist.");	
	}

	while (std::getline(vstup, radek)) {
		if (!prvniRadekNacten) {
			prvniRadekNacten = true;
			std::stringstream ss(radek);
			ss >> m;	//precteni
			ss >> n;
		}
		else {
			std::vector<Dlazdice*> radekDlazdice;
			std::stringstream ss(radek);
			
			char hodnotaDlazdice;

			for (int s = 0; s < n; ++s) {
				bool _prekazka = false;
				bool _pocatek = false;
				bool _cil = false;
				char _status = '.';
				int _m = cRadku;
				int _n = s;

				ss >> hodnotaDlazdice;
				switch (hodnotaDlazdice) {
					case '.':		// pruchozi
						break;
					case 'X':		// prekazka
						_prekazka = true;
						_status = 'X';
						break;
					case 's':		// start
						_pocatek = true;
						_status = 's';
						break;
					case 'c':		// cil
						_cil = true;
						_status = 'c';
						break;
					default:
						throw std::string("Neznama hodnota ve vstupnim souboru: ") + std::to_string(hodnotaDlazdice);
				}

				Dlazdice *r = new Dlazdice(_m, _n, _prekazka, _pocatek, _cil, _status);

				if (hodnotaDlazdice == 's') {
					if (startovniDlazdice) throw std::string("Nalezeno vice startovnich pozic!");	
					startovniDlazdice = r; 
				}
				if (hodnotaDlazdice == 'c') {
					if (cilovaDlazdice) throw std::string("Nalezeno vice cilovych pozic!");	
					cilovaDlazdice = r; 
				}

				radekDlazdice.push_back(r);
			}
			pole[cRadku] = radekDlazdice;
			++cRadku;
		}
	}
	toEval.push_back(startovniDlazdice);
	std::cout << ">Soubor uspesne nacten!" << std::endl;
	std::cout << ">Matice typu " << m << 'x' << n << ".\n" << std::endl;	
}

std::vector<Dlazdice*> Matice::najdiSousedy(Dlazdice *_agent) {
	std::vector<Dlazdice*> sousedi;
//	const int r = _agent->ziskatPoziciRadek();
//	const int s = _agent->ziskatPoziciSloupec();	
	
	for (int r = -1; r <= 1; r++) {
		for (int s = -1; s <= 1; s++) {
			if (s==0 && r==0) continue;
			
			int kontrolaR = _agent->ziskatPoziciRadek() + r;
			int kontrolaS = _agent->ziskatPoziciSloupec() + s;	

			if (kontrolaR >= 0 && kontrolaR < m && kontrolaS >= 0 && kontrolaS < n) {
				sousedi.push_back(pole[kontrolaR].at(kontrolaS));
			}	
		}
	}
	
	return sousedi;
}

int Matice::vzdalenostDlazdic(const Dlazdice *a, const Dlazdice *b) const {
	const int vzdalX = abs(a->ziskatPoziciRadek() - b->ziskatPoziciRadek());	
	const int vzdalY = abs(a->ziskatPoziciSloupec() - b->ziskatPoziciSloupec());
	
	if (vzdalX > vzdalY) return 14*vzdalY + 10*(vzdalX-vzdalY);
	return 14*vzdalX + 10*(vzdalY-vzdalX);
	
}

void Matice::trasovat() {
	maticeKompletni = true;
	Dlazdice *optimalniAgent = cilovaDlazdice;
	while (optimalniAgent != startovniDlazdice) {
		optimalniAgent = optimalniAgent->ziskatRodice();
//		optimalniAgent->nastavStatus('O');
		nejkratsiCesta.push_back(optimalniAgent);
	}
}

const std::vector<Dlazdice*>& Matice::ziskatNejkratsiCestu() const {
	return nejkratsiCesta;
}

void Matice::vypsatNejkratsiCestu(const std::vector<Dlazdice*> cesta) {
	std::vector<Dlazdice*> reversed = cesta;
	std::reverse(reversed.begin(), reversed.end());
	for (Dlazdice *a : reversed) {
		std::cout << a->ziskatPoziciRadek() << "," << a->ziskatPoziciSloupec() << std::endl;	
//		std::cout << a->ziskatStatus() << std::endl;	
	}
	std::cout << cilovaDlazdice->ziskatPoziciRadek() << "," << cilovaDlazdice->ziskatPoziciSloupec() << std::endl;	
}

void Matice::vykreslitNejkratsiCestu(const std::vector<Dlazdice*> cesta) {
	std::vector<Dlazdice*> reversed = cesta;
	std::reverse(reversed.begin(), reversed.end());
	for (Dlazdice *a : reversed) {
		a->nastavStatus('O');
		vykresliCestu();
		std::cin.ignore();
	}
	cilovaDlazdice->nastavStatus('O');
	vykresliCestu();
}

void Matice::vykresliCestu() {
	for (int r = 0; r < pole.size(); ++r) {
		std::vector<Dlazdice*> radek = pole.at(r);
		for (Dlazdice *d : radek) {
			std::cout << '{' << d->ziskatStatus() << '}';
		}
		std::cout << '\n' << std::endl;
		radek.clear();
	}
}

void Matice::menu() {
	
}
