#include <vector>

class Dlazdice {
	int hCost;						// cena vzdalenosti dlazdice do cile
	int gCost;						// cena vzdalenosti trasy od pocatku
	int i, j;						// souradnice v matici
	bool pruchozi;						// prekazka ? pruchozi
	char status;						// start/cil/prekazka/pruchozi
public:
	Dlazdice();

	Dlazdice *rodic;	
	void nastavPozice(int _i, int _j);			
	void nastavG(int _gCost);
	void nastavH(int _hCost);
	void nastavStatus(char _status);
	void nastavPruchozi(bool _pruchozi);
	
	int fCost();						// vypocita a vrati F = G + H
	int ziskejG();
	int ziskejH();
	int ziskejRadek();
	int ziskejSloupec();
	bool ziskejPruchozi();
	char ziskejStatus();
	
	void vypisPozici();
	void vypisStatus();

	bool operator==(const Dlazdice& b);			// definice == pro porovnavani souradnic

//	friend class Matice;
};

class Matice {
	int m, n;
	Dlazdice *matice;					
public:
	Matice(int _m, int _n);
	~Matice();

	int ziskejPocRadku();
	int ziskejPocSloupcu();

	void zobraz();
	void zobrazCosts();

	void priradPozice();

	void pridejPrekazky(int pocet);
	void pridejStart(int _i, int _j);
	void pridejCil(int _i, int _j);

	Dlazdice* ziskejMatici(int _i, int _j);
	Dlazdice* najitCil();
	Dlazdice* najitStart();
	std::vector<Dlazdice> najdiSousedy(Dlazdice *aktualni);
	
	int ziskejVzdalenost(Dlazdice *mistoA, Dlazdice *mistoB);
	bool jeUvnitrVektoru(Dlazdice a, std::vector<Dlazdice> vektor);
	
	void trasovani(Dlazdice *zacatek, Dlazdice *cil);
	void najitCestu();
	void pridelGH();
};
