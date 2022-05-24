// IMPORT
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// STRUKTURA
struct kniha {
	string nazev;
	string autor;
	string zanr;
	int pocetStran;
	int rokVydani;
	double hodnoceni;
	kniha* dalsi;
};

// TRIDA - HLAVICKA
class ctenarskyDenik
{
private:
	kniha* prvni;
	kniha* posledni;
	unsigned int pocet;
	unsigned int filtrPocet;
public:
	ctenarskyDenik();  
	~ctenarskyDenik();

	// PRO PRACI SE SEZNAMEM

	// 1. funkce - PRIDAVANI PRVKU

	void pridatNaZacatek(kniha* p);							// Prida novou knihu s danymi atributy na zacatek
	void pridatNaKonec(kniha* p);							// Prida novou knihu s danymi atributy na konec

	// 2. funkce - ODSTRANOVANI PRVKU

	void odstranitPrvni();									// Odstrani prvni knihu
	void odstranitPosledni();								// Odstrani posledni knihu

	// 3. funkce - DESTRUKCE, VYPSANI, POCET

	void fahrenheit();										// Odstrani vsechny knihy
	void vypisKnih();										// Vypise vsechny knihy vcetne atributu
	void atributyKnihy(kniha* p);							// Vypise atributy knihy
	int pocetKnih();										// Vypise pocet knih

	// 4. funkce - FILTROVANI

	void filtrovani();										// Interaktivni metoda pro filtrovani
	void vypsatDleZanru(string zanr);						// Vyhleda knihy podle zanru + nabidne export do .csv
	void vypsatDleHodnoceni(double dolMez, double horMez);	// Vyhleda knihy podle hodnoceni + nabidne export do .csv
	void vypsatDleRokuVydani(int rok);						// Vyhleda knihy podle roku vydani + nabidne export do .csv
	void vypsatDleAutora(string autor);						// Vyhleda knihy podle autora + nabidne export do .csv
	
	// 5. funkce - PRACE SE SOUBORY

	void txtExport();										// Vypise seznam knih do .txt souboru
	void csvExport();										// Vytvori seznam knih v .csv formatu, lze importovat e.g. do Google Sheets
	void csvImport(string csvSoubor);						// Nacte .csv soubor (pokud je ve stejnem formatu)

	// PRO PRACI S PROGRAMEM
	 
	// 6. funkce - FUNKCE PRO OVLADANI PROGRAMU

	void vypsatDoSouboru();									// Vyvola moznost vypsat knihy do souboru
	void pridatKnihu();										// Interaktivni pridavani knih			
	void pridatKnihu(kniha* p);								// Interaktivni pridavani knih, pomocna metoda pro csvImport()
	void vybratAkci();										// Otevre interaktivni menu
	void odstranitKnihu();									// Interaktivni odstranovani knih

	// "NAVIC"

	// 7. funkce - EXPORT DOPLNEK PRO FILTROVANI

	void csvFiltrExportZanr(string podminka);
	void csvFiltrExportAutor(string podminka);
	void csvFiltrExport(int rok);
	void csvFiltrExport(double dolMez, double horMez);

	// 8. funkce - ODSTRANIT DLE NAZVU
	void odstranitKnihu(string nazev);
};

