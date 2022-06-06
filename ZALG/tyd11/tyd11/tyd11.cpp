#include <iostream>
//Lexik. trid.

using namespace std;

const int D = 20;
const int K = 256;

struct Item                             // uzel spojoveho seznamu - uklada samotne retezce
{
    char key[D + 1];                    // null-terminated string wiki; '\0'
    Item* next;
};

struct List                             // prihradka
{
    Item* first;
    Item* last;
};

List inp;                               // vstup/vystup
List tab[K];                            // prihradky pro vsechny znaky

void init(List &a)
{
    a.first = a.last = nullptr;
}

void add(List &a, Item *p)
{
    if (a.first == nullptr)             // pres tecku, neposilam pointer, ale primo odkaz
        a.first = p;
    else
        a.last->next = p;
    a.last = p;
    p->next = nullptr;
}

void link(List& a, List& b)             // optimalizace rychlosti, neovlivni slozitost
{
    if (b.first != nullptr)             // kdyz chci pripojit prazdny seznam, nic nedelam
    {
        if (a.first == nullptr)
            a.first = b.first;
        else
            a.last->next = b.first;
        a.last = b.last;
    }
}

void sort(int r)                        // radime podle r-teho znaku
{
    for (int i = 0; i < K; i++)         // init na vsechny prvky tabu
        init(tab[i]);

    Item* p = inp.first;
    while (p != nullptr)
    {
        Item *t = p->next;
        
        int index = p->key[r];          // kdyby key[r] byl eg 'A', ulozi se 65 -- win1250
        add(tab[index], p);

        p = t;
    }

    init(inp);
    for (int i = 0; i < K; i++)
    {
        /*
        // pomalejsi kod
        Item* p = tab[i].first;
        while (p)                       // p != nullptr
        {
            Item* t = p->next;
            add(inp, p);
            p = t;
        }
        */
        link(inp, tab[i]);
    }

}

Item* create(int c)
{
    Item* p = new Item;                 // odkaz na item dynamicky alokovanej
    for (int i = D - 1; i >= 0; i--)
    {
        p->key[i] = '0' + c % 10;
        c /= 10;                        // c/10
    }
    p->key[D] = '0';                    // '\0'

    return p;
}

Item* create(string str)
{
    Item* p = new Item;                 
    for (int i = D - 1; i >= 0; i--)
    {
        if (i > str.size() - 1)
            p->key[i] = '-';
        else
            p->key[i] = str.at(i);
    }
    p->key[D] = '0';                    

    return p;
}

void print(List& a)
{
    Item* p = a.first;
    cout << "Vypis: " << endl;
    while (p)                            // != nullptr
    {
        for (int i = 0; i < D; i++)
        {
            cout << p->key[i];
        }
        cout << endl;
        p = p->next;
    }
}

int main()
{
    //char znak = 'A';
    //cout << znak << endl;               // A
    //cout << (int)znak << endl;          // 65
    //znak += 32;
    //cout << znak << endl;               // a
    //cout << (int)znak << endl;          // 65

    add(inp, create('A'));
    add(inp, create("krk"));
    add(inp, create("koruna"));
    add(inp, create(27));
    add(inp, create("kolo"));
    add(inp, create("kolek"));
    add(inp, create("kola"));
    add(inp, create(24));
    add(inp, create(27));
    add(inp, create(37));
    add(inp, create(31));
    add(inp, create(36));
    add(inp, create(23));
    add(inp, create(3));
    add(inp, create(2));

    print(inp);

    for (int i = D - 1; i >= 0; i--)
        sort(i);
    print(inp);

}
