
// IMPORT
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Seznam.h"

using namespace std;

// FUNKCE

// Inicializace programu
void spustitProgram() {

    cout << R"(
          ------------------------------
          | VITEJTE V OSOBNI KNIHOVNE! |
          ------------------------------
    )" << endl;

    cout << R"(
                  ______ ______
                _/      Y      \_
               // ~~ ~~ | ~~ ~  \\
              // ~ ~ ~~ | ~~~ ~~ \\      
             //________.|.________\\     
            `----------`-'----------'
    )" << endl;

    cout << R"(
              Program slouzi k praci
                se seznamem knih,
            ktery je diky .csv formatu
          mozny opakovane nacitat/ukladat. 
    )" << endl;
    //cout << "Program slouzi k jednorazovemu vytvoreni seznamu prectenych knih, ktery je nasledne mozne vyexportovat do .csv formatu." << endl;
    cout << "Pro inicializaci programu stisknete [Enter]." << endl;
    cin.ignore();
    ctenarskyDenik knihovna;    // vytvori seznam
    knihovna.vybratAkci();      // otevre hlavni menu programu v ramci vytvoreneho seznamu - odtud vetveni na dalsi metody podle inputu
}

int main()
{

    // VYKOMENTOVANY TEXT NEBUDE FUNGOVAT, SLOUZIL POUZE PRO TESTOVANI, VETSINA METOD JE NYNI ALE PRIVATE
    // SHORTCUTS AKA HISTORIE TESTOVANI SEZNAMU:
    //kniha* kna = new kniha{ "Serotonin", "Houellesadaf", "Roman", 223, 2019, 2.5, nullptr };
    //kniha* knb = new kniha{ "Bablbam", "NJeco", "Neco2", 223, 2019, 2.5, nullptr };
    //kniha* knc = new kniha{ "Popel", "Spalenyt", "Agaga", 223, 2019, 2.5, nullptr };
    //kniha* knd = new kniha{ "Slatanina", "Noa", "Roman", 223, 2019, 2.5, nullptr };
    //ctenarskyDenik s;
    //s.pridatNaZacatek(kna);
    //s.pridatNaZacatek(knb);
    //s.pridatNaKonec(knc);
    //s.pridatNaZacatek(knd);
    //s.vypisKnih();
    //s.csvImport("soubor.csv");
    //s.vypisKnih();
    //s.vypsatDoSouboru();
    //s.csvExport();

    //s.odstranitPrvni(); // done
    //s.odstranitPosledni(); // done
    //
    //s.odstranitKnihu(kna); // done
    //s.vypisKnih();
    //s.pocetKnih();

    //s.fahrenheit();
    //s.vypisKnih();

    //ctenarskyDenik s;
    //s.pridatKnihu();

    //s.vypisKnih();

    // PROGRAM:
    spustitProgram();


}
