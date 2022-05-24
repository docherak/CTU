// IMPORT
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include "Seznam.h"

using namespace std;

// METODY

// KONSTRUKTOR
ctenarskyDenik::ctenarskyDenik() {
	prvni = nullptr;
	posledni = nullptr;
	pocet = 0;
	filtrPocet = 0;
}

// DESTRUKTOR
ctenarskyDenik::~ctenarskyDenik() {
	// Cyklus, ktery odstrani vsechny knihy
	fahrenheit();
}

// ODSTRANENI VSECH KNIH
void ctenarskyDenik::fahrenheit() {
	// Cyklus, ktery odstranuje prvni prvek, dokud nejaky je
	while (prvni != nullptr) {
		odstranitPrvni();
	}
	cout << "It was a pleasure to burn." << endl;
}

// ODSTRANENI PRVNI KNIHY
void ctenarskyDenik::odstranitPrvni() {
	// Pokud je seznam prazdny:
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}
	// Pokud ma seznam nejake prvky:
	pocet--;													// sice odectu pocet pred realnym odstranenim knihy, ale zaroven po validaci neprazdnosti
	kniha* pom = prvni;											// ulozeni ukazatel na prvek, ktery chci smazat
	prvni = prvni->dalsi;										// prehozeni ukazatele na zacatek seznamu na dalsi prvek
	delete pom;													// odstraneni puvodniho prvku
	// Pokud to byl jediny prvek v seznamu:
	if (prvni == nullptr) {
		posledni = nullptr;
	}
}

// ODSTRANENI POSLEDNI KNIHY
void ctenarskyDenik::odstranitPosledni() {
	// Pokud je seznam prazdny:
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}
	pocet--;
	// Pokud je v seznamu jediny prvek:
	if (prvni == posledni) {
		delete posledni;
		prvni = nullptr;
		posledni = nullptr;
		return;
	}
	// Pokud je v seznamu nejaky prvek:
	kniha* pom = prvni;											// najdu predchozi, abych znicil pointer na posledni
	while (pom != nullptr && pom->dalsi != posledni)
		pom = pom->dalsi;
	// Pote muzu odstranit pointer a nakonec posledni prvek
	if (pom != nullptr) {
		delete pom->dalsi;
		pom->dalsi = nullptr;
		posledni = pom;
	}
}

//  INTERAKTIVNI ODSTRANOVANI KNIH

void ctenarskyDenik::odstranitKnihu() {
	// Pokud je seznam prazdny:
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}
	bool tf = true;

	// Pokud ne, tak cyklus pro odstranovani:
	while (tf) {

		int i, errora, errorb;
		string dalsi;
		cout << "Odstranit prvni/posledni knihu/podle nazvu?" << endl;

		// Validator vstupu:
		do {
			errora = 0;
			cout << "[0] prvni [1] posledni [2] podle nazvu" << endl;
			cin >> i;
			if (cin.fail() || ((i != 0) && (i != 1) && (i != 2))) {
				cout << "Chyba! Zadejte cislo moznosti." << endl;
				errora = 1;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (errora == 1);

		// Odstraneni prvku:
		if (i == 0) {
			odstranitPrvni();
		}
		else if (i == 1) {
			odstranitPosledni();
		}
		else if (i == 2) {
			string nazev;
			cin.ignore();										
			getline(cin, nazev);
			//cout << nazev << endl;
			odstranitKnihu(nazev);
		}

		// Kontrola jestli ma seznam stale nejaky prvek:
		if (prvni == nullptr) {
			cout << "Knihovna je prazdna." << endl;
			return;
		}

		// Odstranit dalsi? + Validator vstupu:
		do {
			errorb = 0;
			cout << "Odstranit dalsi? [y/n]" << endl;
			cin >> dalsi;
			if (cin.fail() || ((dalsi != "y") && (dalsi != "n"))) {
				cout << "Chyba! Zadejte 'y' pro odstraneni dalsi knihy, pripadne 'n' pro navrat do hlavniho menu." << endl;
				errorb = 1;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (errorb == 1);

		if (dalsi == "n") {										// nic dalsiho nez n/y by se pres validator snad nemelo dostat,
			tf = false;											// tudiz nemusim resit else
		}
		else if (dalsi == "y") {
			continue;
		}
	}
}

// BLOK

void ctenarskyDenik::atributyKnihy(kniha* p) {
	cout << "--------------------" << endl;
	cout << "Nazev: " << p->nazev << endl;
	cout << "Autor: " << p->autor << endl;
	cout << "Zanr: " << p->zanr << endl;
	cout << "Pocet stran: " << p->pocetStran << endl;
	cout << "Rok vydani: " << p->rokVydani << endl;
	cout << "Hodnoceni: " << p->hodnoceni << endl;
	cout << "--------------------" << endl;
}

// VYPIS VSECH KNIH DO KONZOLE

void ctenarskyDenik::vypisKnih() {
	// Pokud je seznam prazdny:
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}

	// Pokud obsahuje prvky:
	cout << "--------------------" << endl;
	cout << "VYPIS KNIH: " << endl;
	cout << "--------------------" << endl;
	kniha* pom = prvni;

	// Dokud neni seznam prazdny, tak vypisu nasledujici "blok":
	while (pom != nullptr) {
		atributyKnihy(pom);
		pom = pom->dalsi;										// presun na dalsi prvek
	}
}

// VYPIS POCTU VSECH KNIH DO KONZOLE

int ctenarskyDenik::pocetKnih() {
	cout << "--------------------" << endl;
	cout << "POCET KNIH: " << pocet << endl;
	cout << "--------------------" << endl;
	return pocet;												// private atribut, pricita/odecita 1 pri pridani/odebrani knihy
}

// METODA PRO PRIDANI KNIHY NA ZACATEK

void ctenarskyDenik::pridatNaZacatek(kniha* p) {
	pocet++;
	// Pokud zatim nemam v seznamu prvek:
	if (prvni == nullptr) {
		prvni = p;
		posledni = p;
		return;
	}
	// Pokud mam:
	p->dalsi = prvni;
	prvni = p;
}

// METODA PRO PRIDANI KNIHY NA KONEC

void ctenarskyDenik::pridatNaKonec(kniha* p) {
	pocet++;
	// Pokud zatim nemam v seznamu prvek:
	if (prvni == nullptr) {
		prvni = p;
		posledni = p;
		return;
	}
	// Pokud mam:
	posledni->dalsi = p;
	posledni = p;
}

// INTERAKTIVNI VYPSANI DO SOUBORU

void ctenarskyDenik::vypsatDoSouboru() {
	// Kontrola neprazdnosti:
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}

	int i, error;
	cout << "Exportovat do .csv/.txt?" << endl;
	
	// Validace inputu:
	do {
		error = 0;
		cout << "[0] csv [1] txt" << endl;
		cin >> i;
		if (cin.fail() || ((i != 0) && (i != 1))) {
			cout << "Chyba! Zadejte cislo moznosti." << endl;
			error = 1;
			cin.clear();
			cin.ignore(256, '\n');
		}
	} while (error == 1);

	// Vyvolani funkce na zaklade inputu:
	if (i == 0) {
		csvExport();
	}
	else if (i == 1) {
		txtExport();
	}
}

// EXPORT DO .TXT

void ctenarskyDenik::txtExport() {
	// Kontrola nezpradnosti:
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}

	// Input a vytvoreni formatu "nazev_souboru.txt"
	string nazevSouboru, bezPripony;
	cout << "Zadejte nazev souboru: " << endl;
	cin >> bezPripony;
	nazevSouboru = bezPripony.append(".txt");

	// Vytvoreni souboru se zadanym nazvem
	ofstream outSoubor(nazevSouboru);
	if (outSoubor.is_open()) {
		// Vlozeni textu do souboru ve stejnem formatu jako metoda pro vypis knih
		outSoubor << "--------------------" << endl;
		outSoubor << "PRECTENE KNIHY: " << endl;
		kniha* pom = prvni;
		while (pom != nullptr) {
			outSoubor << "--------------------" << endl;
			outSoubor << "Nazev: " << pom->nazev << endl;
			outSoubor << "Autor: " << pom->autor << endl;
			outSoubor << "Zanr: " << pom->zanr << endl;
			outSoubor << "Pocet stran: " << pom->pocetStran << endl;
			outSoubor << "Rok vydani: " << pom->rokVydani << endl;
			outSoubor << "Hodnoceni: " << pom->hodnoceni << endl;
			pom = pom->dalsi;
		}
		outSoubor.close();
	}
}

// EXPORT DO .CSV

void ctenarskyDenik::csvExport() {
	// Kontrola neprazdnosti:
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}

	// Input a vytvoreni formatu "nazev_souboru.csv"
	string nazevSouboru, bezPripony;
	cout << "Zadejte nazev souboru: " << endl;
	cin >> bezPripony;
	nazevSouboru = bezPripony.append(".csv");

	// Export seznamu v csv formatu, oddelovac ",", vcetne headeru:
	ofstream outSoubor(nazevSouboru);
	if (outSoubor.is_open()) {
		
		outSoubor << "Nazev,Autor,Zanr,Pocet_stran,Rok_vydani,Hodnoceni" << endl;
		kniha* pom = prvni;
		while (pom != nullptr) {
			outSoubor << pom->nazev << "," << pom->autor << "," << pom->zanr << "," << pom->pocetStran << "," << pom->rokVydani << "," << pom->hodnoceni << endl;
			
			pom = pom->dalsi;
		}
		outSoubor.close();
	}
}

// IMPORT .CSV

void ctenarskyDenik::csvImport(string csvSoubor) {
	// Import .csv souboru ve spravnem formatu - muze/nemusi mit header, ale pro spravne fungovani je nutne dodrzet format "Nazev,Autor,Zanr,Pocet_stran,Rok_vydani,Hodnoceni"
	ifstream inSoubor(csvSoubor);
	if (inSoubor.is_open()) {
		string radek, slovo;
		string nadpis = "Nazev,Autor,Zanr,Pocet_stran,Rok_vydani,Hodnoceni\0";

		// Vytvoreni formatu vektoru
		vector<string> atributy;

		while (getline(inSoubor, radek)) {
			// Na zacatku promazu SLOZKY vektoru
			atributy.clear();

			// Initially written in VS2019 - in g++ I had an issue with string comparisons - ? nullbyte? newline? - anyway fixed it for now using substring comparison
			//cout << '/' << radek.substr(0,40).c_str() << '/' << endl;
			//cout << '/' << nadpis.substr(0,40).c_str() << '/' << endl;
			//cout << radek.length() << ' ' << nadpis.length() << endl;
			//cout << strcmp(radek.c_str(), nadpis.c_str()) << endl;

			// Nadpis (ve spravnem formatu) preskocim
			//if (radek == "Nazev,Autor,Zanr,Pocet_stran,Rok_vydani,Hodnoceni") {
			if (strcmp(radek.substr(0,40).c_str(), nadpis.substr(0,40).c_str()) == 0) {
				cout << radek << endl;
				continue;
			}

			// Prevedu na stream format, abych z neho mohl cist pomoci getline(), ktera funguje napr i na cin
			stringstream s(radek);

			// Vemu kazde slovo zvlast (',' oddelovac) a hodim ho jako posledni prvek vektoru
			while (getline(s, slovo, ',')) {
				atributy.push_back(slovo);
			}

			// Vyvolam pridani knihy s nami ulozenymi atributy
		//	pridatKnihu(new kniha{ atributy[0], atributy[1], atributy[2], 3, 4, 5, nullptr }); // stoX() fce pro prevod na int/double
			pridatKnihu(new kniha{ atributy[0], atributy[1], atributy[2], stoi(atributy[3]), stoi(atributy[4]), stod(atributy[5]), nullptr }); // stoX() fce pro prevod na int/double

		}
		inSoubor.close();
	}
}

// INTERAKTIVNI PRIDANI JIZ VYTVORENE KNIHY (POUZITO PRO ZARAZENI KNIH Z .CSV IMPORTU)

void ctenarskyDenik::pridatKnihu(kniha* p) {
	int i, error;
	cout << "Pridat knihu '" << p->nazev << "' na zacatek/konec?" << endl;
	
	// Validace inputu:
	do {
		error = 0;
		cout << "[0] zacatek [1] konec" << endl;
		cin >> i;
		if (cin.fail() || ((i != 0) && (i != 1))) {
			cout << "Chyba! Zadejte cislo moznosti." << endl;
			error = 1;
			cin.clear();
			cin.ignore(256, '\n');
		}
	} while (error == 1);

	// Pokud projde validace, tak muzu pridat knihu:
	if (i == 0) {
		pridatNaZacatek(p);
	}
	else if (i == 1) {
		pridatNaKonec(p);
	}
}

// INTERAKTIVNI PRIDAVANI NOVYCH KNIH

void ctenarskyDenik::pridatKnihu() {

	bool tf = true;
	while (tf) {

		string nazev, autor, zanr, dalsi;
		int pocetStran, rokVydani, i, errora, errorb;
		int errorS, errorH, errorR;
		double hodnoceni;

		// String vstupy
		cout << "Zadejte nazev knihy: " << endl;
		cin.ignore();										// aby nedochazelo k preskakovani
		getline(cin, nazev);								// getline() mi umoznuje zadavat strings s mezerami, pricemz dalsi cin by nemel preskocit
		cout << "Zadejte autora: " << endl;
		getline(cin, autor);
		cout << "Vyberte zanr: " << endl;
		getline(cin, zanr);

		// Ciselne vstupy
		cout << "Zadejte pocet stran: " << endl;
		do {
			errorS = 0;
			cin >> pocetStran;
			if (cin.fail()) {
				cout << "Chyba! Zadejte cele cislo." << endl;
				errorS = 1;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (errorS == 1);

		cout << "Zadejte rok vydani: " << endl;
		do {
			errorR = 0;
			cin >> rokVydani;
			if (cin.fail()) {
				cout << "Chyba! Zadejte cele cislo." << endl;
				errorR = 1;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (errorR == 1);

		cout << "Hodnoceni: " << endl;
		do {
			errorH = 0;
			cin >> hodnoceni;
			if (cin.fail()) {
				cout << "Chyba! Zadejte cele cislo." << endl;
				errorH = 1;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (errorH == 1);

		cout << "Pridat na zacatek/konec?" << endl;

		// Validace vstupu
		do {
			errora = 0;
			cout << "[0] zacatek [1] konec" << endl;
			cin >> i;
			if (cin.fail() || ((i != 0) && (i != 1))) {
				cout << "Chyba! Zadejte cislo moznosti." << endl;
				errora = 1;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (errora == 1);

		// Pokud projde, tak pridam na zacatek/konec
		if (i == 0) {
			pridatNaZacatek(new kniha{ nazev, autor, zanr, pocetStran, rokVydani, hodnoceni, nullptr });
		}
		else if (i == 1) {
			pridatNaKonec(new kniha{ nazev, autor, zanr, pocetStran, rokVydani, hodnoceni, nullptr });
		}

		// Validace vstupu
		do {
			errorb = 0;
			cout << "Pridat dalsi? [y/n]" << endl;
			cin >> dalsi;
			if (cin.fail() || ((dalsi != "y") && (dalsi != "n"))) {
				cout << "Chyba! Zadejte 'y' pro pridani dalsi knihy, pripadne 'n' pro navrat do hlavniho menu." << endl;
				errorb = 1;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (errorb == 1);

		// Pokud projde, tak ukoncim/pokracuju v pridavani
		if (dalsi == "n") {
			tf = false;
		}
		else if (dalsi == "y") {
			continue;
		}
	}
}

// HLAVNI MENU PROGRAMU

void ctenarskyDenik::vybratAkci() {

	int i, error;

	// Loop interaktivniho menu, vcetne validaci vstupu
	bool cyklus = true;
	while (cyklus) {
		cout << R"(
	Vyberte akci: )";

		do {
			error = 0;
			cout << R"(
	[1] pridat knihu		[5] hledat	
	[2] odstranit knihu		[6] nacist knihy z .csv
	[3] vypsat knihy		[7] spalit knihy
	[4] exportovat

	[Ctrl+C] pro ukonceni		[0] info
)" << endl;
			cin >> i;
			if (cin.fail() || ((i != 0) && (i != 1) && (i != 2) && (i != 3) && (i != 4) && (i != 5) && (i != 6) && (i != 7))) {
				cout << "Chyba! Zadejte cislo moznosti, pripadne stisknete [Ctrl+C] pro ukonceni programu." << endl;
				error = 1;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (error == 1);

		cout << endl;

		// Switch s moznostmi
		switch (i) {
		case 1: {
			pridatKnihu();
			break;
		}
		case 2: {
			odstranitKnihu();
			break;
		}
		case 3: {
			if (prvni == nullptr) {
				cout << "Knihovna je prazdna." << endl;
				continue;
			}
			pocetKnih();
			vypisKnih();
			break;
		}
		case 4: {
			vypsatDoSouboru();
			break;
		}
		case 6: {
			string csvNazev;
			cout << "Zadejte nazev souboru (vcetne pripony .csv): " << endl;
			cin >> csvNazev;
			csvImport(csvNazev);
			break;
		}
		case 7: {
			fahrenheit();
			break;
		}
		case 5: {
			filtrovani();
			break;
		}
		case 0: {
			cout << R"(
	Knihy je mozna manualne pridat, pripadne nacist z .csv souboru,
	ktery mas sloupce ve formatu (pripadne nadpis odpovidajici:):

		'Nazev,Autor,Zanr,Pocet_stran,Rok_vydani,Hodnoceni'

	Pri importu i manualnim pridani je nutne manualne rozhodnout
	o pozici kazde z knih - zacatek/konec seznamu. Knihy je mozne
	odstranovat na zaklade stejneho principu, pripadne znicit
	celou knihovnu najednou. Seznam je mozny vypsat cely,
	pripadne filtrovat na zaklade maximalne jednoho !presne! 
	napsaneho argumentu (v pripade autora: Tolkien != J.R.R. Tolien). Vetsina
	ostatnich vstupu je osetrena. Knihy - vsechny/vyfiltrovane - je mozne 
	exportovat do .csv formatu, je tedy mozne opakovane pracovat
	s jednim .csv souborem, ktery je mozny nahrat napr. i do Google Sheets.
	V pripade vypisu vsech knih je take mozne exportovat je jako .txt.

	PRO TESTOVANI JE PRILOZEN SOUBOR knihy.csv!
    )" << endl;
		}
		}

		// Nakonec me napadlo dat switch, ale puvodni kod zde:

		//if (i == 1) {
		//	pridatKnihu();
		//}
		//else if (i == 2) {
		//	odstranitKnihu();
		//}
		//else if (i == 3) {
		//	vypisKnih(); // vyvorit fci, ktera se zepta na to jestli csv nebo txt
		//}
		//else if (i == 4) {
		//	vypsatDoSouboru();
		//}
		//else if (i == 5) {
		//	string csvNazev;
		//	cout << "Zadejte nazev souboru (vcetne pripony .csv): " << endl;
		//	cin >> csvNazev;
		//	csvImport(csvNazev);
		//}
		//else if (i == 6) {
		//	fahrenheit();
		//}
	}
}

// INTERAKTIVNI FUNKCE PRO HLEDANI

void ctenarskyDenik::filtrovani() {
	// Pokud je seznam prazdny:
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}
	bool tf = true;

	// Pokud ne:	
	cout << "Na zaklade ceho filtrovat vypis?" << endl;

	string autor, zanr;
	int error, i, rokVydani, errora, errorb, errorc;
	double d, h;

	// Validace vstupu
	do {
		error = 0;
		cout << "[0] autor [1] zanr [2] rok vydani [3] hodnoceni" << endl;
		cin >> i;
		if (cin.fail() || ((i != 0) && (i != 1) && (i != 2) && (i != 3))) {
			cout << "Chyba! Zadejte cislo moznosti." << endl;
			error = 1;
			cin.clear();
			cin.ignore(256, '\n');
		}
	} while (error == 1);

	// Moznosti filtrovani, vcetne validace
	switch (i) {
	case 0: {
		cout << "Zadejte jmeno autora: " << endl;
		cin.ignore();
		getline(cin, autor);
		vypsatDleAutora(autor);
		if (filtrPocet > 0) csvFiltrExportAutor(autor);
		break;
	}
	case 1: {
		cout << "Zadejte nazev zanru: " << endl;
		cin.ignore();
		getline(cin, zanr);
		vypsatDleZanru(zanr);
		if (filtrPocet > 0) csvFiltrExportZanr(zanr);
		break;
	}
	case 2: {
		cout << "Zadejte rok vydani: " << endl;

		do {
			errora = 0;
			cin >> rokVydani;
			if (cin.fail()) {
				cout << "Chyba! Zadejte cele cislo!" << endl;
				errora = 1;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (errora == 1);
		
		vypsatDleRokuVydani(rokVydani);
		if (filtrPocet > 0) csvFiltrExport(rokVydani);
		break;
	}
	case 3: {
		cout << "Zadejte dolni mez pro hodnoceni (vcetne): " << endl;

		do {
			errorb = 0;
			cin >> d;
			if (cin.fail()) {
				cout << "Chyba! Zadejte cislo!" << endl;
				errorb = 1;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (errorb == 1);

		cout << "Zadejte horni mez pro hodnoceni (vcetne): " << endl;

		do {
			errorc = 0;
			cin >> h;
			if (cin.fail()) {
				cout << "Chyba! Zadejte cislo!" << endl;
				errorc = 1;
				cin.clear();
				cin.ignore(256, '\n');
			}
		} while (errorc == 1);
		
		vypsatDleHodnoceni(d, h);
		if (filtrPocet > 0) csvFiltrExport(d, h);
		break;
	}
	}
}

// METODY K FILTROVANI

void ctenarskyDenik::vypsatDleAutora(string autor) {
	filtrPocet = 0;												// pomocny ukazatel - v pripade, ze filtr vyhodi 0 knih chci zaroven, abych nedostal prompt na csv export, filtrPocet pouziju v podmince u switche na filtrovani 

	// Aby se usetril zbytecny cyklus
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}

	kniha* pom = prvni;
	int pocitadlo = 0;											// sel by pouzit filtrPocet, ale imo je fajn to vzhledem k ucelum oddelit + jsem nechtel prip zbytecne rozvrtat kod

	// Dokud neni seznam prazdny, tak vypisu nasledujici "blok":
	while (pom != nullptr) {
		if (autor == pom->autor) {
			pocitadlo++;
			filtrPocet++;
			atributyKnihy(pom);
		}
		pom = pom->dalsi;										// presun na dalsi prvek
	}
	cout << endl;
	if (pocitadlo == 0) cout << "Podminkam nevyhovuji zadne knihy" << endl;
}

void ctenarskyDenik::vypsatDleHodnoceni(double dolMez, double horMez) {
	filtrPocet = 0;

	// Aby se usetril zbytecny cyklus
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}

	kniha* pom = prvni;
	int pocitadlo = 0;

	// Dokud neni seznam prazdny, tak vypisu nasledujici "blok":
	while (pom != nullptr) {
		if (pom->hodnoceni >= dolMez && pom->hodnoceni <= horMez) {
			pocitadlo++;
			filtrPocet++;
			atributyKnihy(pom);
		}
		pom = pom->dalsi;										
	}
	cout << endl;
	if (pocitadlo == 0) cout << "Podminkam nevyhovuji zadne knihy" << endl;
}

void ctenarskyDenik::vypsatDleRokuVydani(int rok) {
	filtrPocet = 0;

	// Aby se usetril zbytecny cyklus
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}

	kniha* pom = prvni;
	int pocitadlo = 0;

	// Dokud neni seznam prazdny, tak vypisu nasledujici "blok":
	while (pom != nullptr) {
		if (rok == pom->rokVydani) {
			pocitadlo++;
			atributyKnihy(pom);
			filtrPocet++;
		}
		pom = pom->dalsi;
	}
	cout << endl;
	if (pocitadlo == 0) cout << "Podminkam nevyhovuji zadne knihy." << endl;
}

void ctenarskyDenik::vypsatDleZanru(string zanr) {
	filtrPocet = 0;

	// Aby se usetril zbytecny cyklus
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}
	
	kniha* pom = prvni;
	int pocitadlo = 0;

	// Dokud neni seznam prazdny, tak vypisu nasledujici "blok":
	while (pom != nullptr) {
		if (zanr == pom->zanr) {
			pocitadlo++;
			filtrPocet++;
			atributyKnihy(pom);
		}
		pom = pom->dalsi;
	}
	cout << endl;
	if (pocitadlo == 0) cout << "Podminkam nevyhovuji zadne knihy." << endl;
}

// NASLEDUJICI METODY NEJSOU MOC EFFICIENT, PROTOZE OPAKUJI STEJNY CYKLUS JAKO vypsatDleXY METODY, ALE PRISLO MI UZITECNE JE NAKONEC TAKY PRIDAT
// V pripade, ze filtrum nevyhovuji zadne vysledky, program se stejne zepta na .csv export

void ctenarskyDenik::csvFiltrExportZanr(string podminka) {
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}

	// Takhle metoda je primarne myslena jako optional doplnek k filtrovani, nikoliv jako samostatna, proto validace:
	int error;
	string dalsi;
	do {
		error = 0;
		cout << "Exportovat do .csv? [y/n]" << endl;
		cin >> dalsi;
		if (cin.fail() || ((dalsi != "y") && (dalsi != "n"))) {
			cout << "Chyba! Zadejte 'y' pro export, pripadne 'n' pro navrat do hlavniho menu." << endl;
			error = 1;
			cin.clear();
			cin.ignore(256, '\n');
		}
	} while (error == 1);

	if (dalsi == "n") {
		return;
	}
	else if (dalsi == "y") {
		// Input a vytvoreni formatu "nazev_souboru.csv"
		string nazevSouboru, bezPripony;
		cout << "Zadejte jednoslovny nazev souboru: " << endl;
		cin >> bezPripony;
		nazevSouboru = bezPripony.append(".csv");

		// Export seznamu v csv formatu, oddelovac ",", vcetne headeru:
		ofstream outSoubor(nazevSouboru);
		if (outSoubor.is_open()) {

			outSoubor << "Nazev,Autor,Zanr,Pocet_stran,Rok_vydani,Hodnoceni" << endl;
			kniha* pom = prvni;

			while (pom != nullptr) {
				if (podminka == pom->zanr) {
					outSoubor << pom->nazev << "," << pom->autor << "," << pom->zanr << "," << pom->pocetStran << "," << pom->rokVydani << "," << pom->hodnoceni << endl;
				}
				pom = pom->dalsi;
			}
			outSoubor.close();
		}
	}
}

void ctenarskyDenik::csvFiltrExportAutor(string podminka) {
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}

	// Takhle metoda je primarne myslena jako optional doplnek k filtrovani, nikoliv jako samostatna, proto validace:
	int error;
	string dalsi;
	do {
		error = 0;
		cout << "Exportovat do .csv? [y/n]" << endl;
		cin >> dalsi;
		if (cin.fail() || ((dalsi != "y") && (dalsi != "n"))) {
			cout << "Chyba! Zadejte 'y' pro export, pripadne 'n' pro navrat do hlavniho menu." << endl;
			error = 1;
			cin.clear();
			cin.ignore(256, '\n');
		}
	} while (error == 1);

	if (dalsi == "n") {										
		return;											
	}
	else if (dalsi == "y") {
		// Input a vytvoreni formatu "nazev_souboru.csv"
		string nazevSouboru, bezPripony;
		cout << "Zadejte jednoslovny nazev souboru: " << endl;
		cin >> bezPripony;
		nazevSouboru = bezPripony.append(".csv");

		// Export seznamu v csv formatu, oddelovac ",", vcetne headeru:
		ofstream outSoubor(nazevSouboru);
		if (outSoubor.is_open()) {

			outSoubor << "Nazev,Autor,Zanr,Pocet_stran,Rok_vydani,Hodnoceni" << endl;
			kniha* pom = prvni;

			while (pom != nullptr) {
				if (podminka == pom->autor) {
					outSoubor << pom->nazev << "," << pom->autor << "," << pom->zanr << "," << pom->pocetStran << "," << pom->rokVydani << "," << pom->hodnoceni << endl;
				}
				pom = pom->dalsi;
			}
			outSoubor.close();
		}
	}
}

void ctenarskyDenik::csvFiltrExport(int rok) {
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}

	// Takhle metoda je primarne myslena jako optional doplnek k filtrovani, nikoliv jako samostatna, proto validace:
	int error;
	string dalsi;
	do {
		error = 0;
		cout << "Exportovat do .csv? [y/n]" << endl;
		cin >> dalsi;
		if (cin.fail() || ((dalsi != "y") && (dalsi != "n"))) {
			cout << "Chyba! Zadejte 'y' pro export, pripadne 'n' pro navrat do hlavniho menu." << endl;
			error = 1;
			cin.clear();
			cin.ignore(256, '\n');
		}
	} while (error == 1);

	if (dalsi == "n") {
		return;
	}
	else if (dalsi == "y") {
		// Input a vytvoreni formatu "nazev_souboru.csv"
		string nazevSouboru, bezPripony;
		cout << "Zadejte jednoslovny nazev souboru: " << endl;
		cin >> bezPripony;
		nazevSouboru = bezPripony.append(".csv");

		// Export seznamu v csv formatu, oddelovac ",", vcetne headeru:
		ofstream outSoubor(nazevSouboru);
		if (outSoubor.is_open()) {

			outSoubor << "Nazev,Autor,Zanr,Pocet_stran,Rok_vydani,Hodnoceni" << endl;
			kniha* pom = prvni;

			while (pom != nullptr) {
				if (rok == pom->rokVydani) {
					outSoubor << pom->nazev << "," << pom->autor << "," << pom->zanr << "," << pom->pocetStran << "," << pom->rokVydani << "," << pom->hodnoceni << endl;
				}
				pom = pom->dalsi;
			}
			outSoubor.close();
		}
	}
}

void ctenarskyDenik::csvFiltrExport(double dolMez, double horMez) {
	if (prvni == nullptr) {
		cout << "Knihovna je prazdna." << endl;
		return;
	}

	// Takhle metoda je primarne myslena jako optional doplnek k filtrovani, nikoliv jako samostatna, proto validace:
	int error;
	string dalsi;
	do {
		error = 0;
		cout << "Exportovat do .csv? [y/n]" << endl;
		cin >> dalsi;
		if (cin.fail() || ((dalsi != "y") && (dalsi != "n"))) {
			cout << "Chyba! Zadejte 'y' pro export, pripadne 'n' pro navrat do hlavniho menu." << endl;
			error = 1;
			cin.clear();
			cin.ignore(256, '\n');
		}
	} while (error == 1);

	if (dalsi == "n") {
		return;
	}
	else if (dalsi == "y") {
		// Input a vytvoreni formatu "nazev_souboru.csv"
		string nazevSouboru, bezPripony;
		cout << "Zadejte jednoslovny nazev souboru: " << endl;
		cin >> bezPripony;
		nazevSouboru = bezPripony.append(".csv");

		// Export seznamu v csv formatu, oddelovac ",", vcetne headeru:
		ofstream outSoubor(nazevSouboru);
		if (outSoubor.is_open()) {

			outSoubor << "Nazev,Autor,Zanr,Pocet_stran,Rok_vydani,Hodnoceni" << endl;
			kniha* pom = prvni;

			while (pom != nullptr) {
				if (pom->hodnoceni >= dolMez && pom->hodnoceni <= horMez) {
					outSoubor << pom->nazev << "," << pom->autor << "," << pom->zanr << "," << pom->pocetStran << "," << pom->rokVydani << "," << pom->hodnoceni << endl;
				}
				pom = pom->dalsi;
			}
			outSoubor.close();
		}
	}
}

// DODATEK: ODSTRANENI KNIHY DLE NAZVU

void ctenarskyDenik::odstranitKnihu(string nazev) {

	kniha* hledana = prvni;
	int pocitadlo = 0;

	// Fce je primitivni, vezme prvni knihu s timto nazvem:
	while (hledana != nullptr) {
		if (nazev == hledana->nazev) {
			pocitadlo++;
			break;
		}
		hledana = hledana->dalsi;										// presun na dalsi prvek
	}
	cout << endl;
	if (pocitadlo == 0) {
		cout << "Podminkam nevyhovuji zadne knihy." << endl;
		return;
	}

	// Kniha je na zacatku:
	if (hledana == prvni) {
		odstranitPrvni();
		return;
	}
	// Je na konci:
	if (hledana == posledni) {
		odstranitPosledni();
		return;
	}
	// Random pozice:
	pocet--;
	kniha* pom = prvni;
	while (pom != nullptr && pom->dalsi != hledana) {
		pom = pom->dalsi;
	}
	if (pom != nullptr) {
		pom->dalsi = hledana->dalsi;
		delete hledana;
	}
}
