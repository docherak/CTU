##### ***Czech only***
# Zápočtový program pro Základy algoritmizace na FJFI ČVUT
Repozirář obsahuje zdrojové soubory pro kompilaci první a druhé (prozatím finální) verze programu pro hledání cesty z bludiště pomocí A star algoritmu.

> *“
All that is gold does not glitter.
Not all who wander are lost.
The old that is strong does not wither.
Deep roots are not reached by the frost. 
”*

Finální verze programu se pokusí načíst matici z textového souboru vstup.txt, uloženého ve stejné složce a následně s každým stisknutím klávesy *[Enter]* vykreslí:

- nejprve postup agenta v jeho snaze najít cíl
- následně cestu vyhodnocenou jako optimální

Instrukce k požadovanému formátu vstupního souboru a legenda jsou uvedeny v programu.

Pro jednoduchou kompilaci přes g++ lze využít Makefile:

```
make		// pro kompilaci
make all	// to samé
make clean	// odstraneni executables
```

Pro spuštění:

```
./astar
```

### Zadání zápočtového programu
A* algoritmus
- Vstupem je matice n x m, "X" označte zeď a "." označte volný prostor. Startovací pozici označte "s" a cílovou "c". Pozici agenta označte "a" 
- Úkolem je najít v takovém bludišti cestu
- Krokování pomocí nějakého vstupu, třeba ENTER
- Pozici během každého kroku vizualizujte - vykreslete pozici v bludišti
- Nebo možnost zvolit nekrokování a pouze vykreslete cestu do cíle
