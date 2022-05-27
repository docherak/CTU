#include <map>
#include <vector>

class Dlazdice {
	bool prekazka;
	bool pocatek;
	bool cil;

	int i, j;

	int gCost = 0;
	int hCost = 0;

	char status;

	Dlazdice *rodic = nullptr;

public:
	Dlazdice(int _i, int _j, bool _prekazka, bool _pocatek, bool _cil, char _status);
	~Dlazdice() = default;

	int ziskatG() const;
	int ziskatH() const;
	int ziskatF() const;
	int ziskatPoziciRadek() const;
	int ziskatPoziciSloupec() const;
	char ziskatStatus() const;
	Dlazdice *ziskatRodice() const;

	void nastavGH(int _gCost, int _hCost);
	void nastavRodice(Dlazdice *_rodic);
	void nastavStatus(char _status);

	bool jePrekazkou() const;
	bool jePocatek() const;
	bool jeCil() const;
	
	inline bool operator<(const Dlazdice &d) const {
		const int fCost = ziskatF(), d_fCost = d.ziskatF();
		return fCost < d_fCost || (fCost == d_fCost &&	hCost < d.ziskatH());
	}
};


using Pole = std::map<int, std::vector<Dlazdice*>>;

class Matice {
	static constexpr const char *VSTUPNI_SOUBOR = "./vstup.txt";

	int m, n;
	bool nemozne = false;

	Dlazdice *startovniDlazdice = nullptr;
	Dlazdice *cilovaDlazdice = nullptr;

	Pole pole;

	std::vector<Dlazdice*> toEval;
	std::vector<Dlazdice*> evald;

	bool maticeKompletni = false;
	std::vector<Dlazdice*> nejkratsiCesta;
public:
	Matice();
	~Matice();
	
	bool jeNemozne() const;
	bool jeKompletni() const;
	int ziskejRadky() const;
	int ziskejSloupce() const;

	const std::vector<Dlazdice*> &ziskatNejkratsiCestu() const;

	void krok();
	
	void vypsatNejkratsiCestu(const std::vector<Dlazdice*> cesta); 
	void vykreslitNejkratsiCestu(const std::vector<Dlazdice*> cesta); 

	void vykresliCestu();

	void obnovit();

	void menu();
private:
	int vzdalenostDlazdic(const Dlazdice *a, const Dlazdice *b) const;
	void vymazatData();
	void zpracovatVstup();
	void trasovat();
	std::vector<Dlazdice*> najdiSousedy(Dlazdice *_agent);

};
