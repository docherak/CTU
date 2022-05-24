##### Czech only
# Zápočtový projekt pro Základy programování na FJFI ČVUT
Repozirář obsahuje zdrojové soubory pro kompilaci první verze jednoduchého programu, který může uživateli posloužit jako CML alternativa čtenářského deníku.

> *“There must be something in books, things we can’t imagine, to make a woman stay in a burning house; there must be something there. You don’t stay for nothing.”*

Jedná se o lineární spojový seznam v C++ s následujícími funkcemi:

- přidání knihy (na začátek/na konec)
- odstranění knihy (první/poslední/podle názvu)
- vypsání knih
- export do .txt nebo .csv
- import knih z .csv souboru
- hledání/filtrování s možností exportu
- vyprázdnění knihovny

Většina vstupů by měla být ošetřená. Pro zobrazení instrukcí mj. na import .csv souboru využijte možnost [0].

Pro jednoduchou kompilaci přes g++ lze využít Makefile:

```
make		// pro kompilaci
make all	// to samé
make clean	// odstraneni executables
```

### Zadání zápočtového programu
K nahlédnutí [zde](/assets/zadani.pdf).
