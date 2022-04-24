#Popis projektu

Cílem projektu je vytvořit program, který na vstupu dostane sadu hesel a pro každé z nich ověří, jestli heslo splňuje všechna (pevně zadaná) požadovaná pravidla. Ta hesla, která projdou kontrolou, budou vypisována na výstup, ostatní budou zahozena.

#Detailní specifikace
Program implementujte ve zdrojovém souboru "pwcheck.c". Vstupní data (seznam hesel) budou čtena ze standardního vstupu (stdin), výstup (filtrovaný seznam hesel) bude tisknut na standardní výstup (stdout).

#Překlad a odevzdání zdrojového souboru
Odevzdání: Odevzdejte zdrojový soubor pwcheck.c prostřednictvím informačního systému.

Překlad: Program překládejte s následujícími argumenty:

$ gcc -std=c99 -Wall -Wextra -Werror pwcheck.c -o pwcheck

#Syntax spuštění
Program se spouští v následující podobě: (./pwcheck značí umístění a název programu):

./pwcheck LEVEL PARAM [--stats] 
Program je spouštěn se dvěma pevně zadanými argumenty LEVEL a PARAM a s jedním volitelným argumentem --stats, případně zadaným na třetí pozici:

LEVEL
celé číslo v intervalu [1, 4], které určuje požadovanou úroveň bezpečnosti (viz níže)
PARAM
kladné celé číslo, které určuje dodatečný parametr pravidel (viz níže)
--stats
pokud je zadané, určuje, zda se na konci programu mají vypsat souhrnné statistiky analyzovaných hesel
Úrovně bezpečnosti (kontrolovaná pravidla)
Jsou definovány celkem 4 úrovně bezpečnosti vyjádřeny pomocí 4 pravidel. Úroveň bezpečnosti určuje, že hesla musí splňovat všechna pravidla na dané a nižší úrovni. Tzn. např. úroveň bezpečnosti 3 specifikuje, že hesla musí splňovat pravidla 1, 2 a 3.

Některá pravidla jsou parametrizovatelná celým číslem zadaným pomocí argumentu programu PARAM. V následujícím seznamu je tento parametr označen jako X.

#Seznam pravidel:

Heslo obsahuje alespoň 1 velké a 1 malé písmeno.
Heslo obsahuje znaky z alespoň X skupin (v případě, že je číslo X větší než 4, myslí se tím všechny skupiny). Uvažované skupiny jsou:
malá písmena (a-z)
velká písmena (A-Z)
čísla (0-9)
speciální znaky (podporované musí být alespoň nealfanumerické znaky z ASCII tabulky na pozicích 33-126 32-126, tedy včetně mezery)
Heslo neobsahuje sekvenci stejných znaků délky alespoň X.
Heslo neobsahuje dva stejné podřetězce délky alespoň X.
