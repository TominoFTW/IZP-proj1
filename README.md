# Popis projektu

Cílem projektu je vytvořit program, který na vstupu dostane sadu hesel a pro každé z nich ověří, jestli heslo splňuje všechna (pevně zadaná) požadovaná pravidla. Ta hesla, která projdou kontrolou, budou vypisována na výstup, ostatní budou zahozena.


# Detaily specifikace

Vstupní data (seznam hesel) budou čtena ze standardního vstupu (stdin), výstup (filtrovaný seznam hesel) bude tisknut na standardní výstup (stdout).

## Překlad

Program překládejte s následujícími argumenty:

`$ gcc -std=c99 -Wall -Wextra -Werror pwcheck.c -o pwcheck`

## Syntax spuštění

`./pwcheck LEVEL PARAM [--stats]`\
\
Program je spouštěn se dvěma pevně zadanými argumenty LEVEL a PARAM a s jedním volitelným argumentem --stats, případně zadaným na třetí pozici:
**LEVEL**
celé číslo v intervalu [1, 4], které určuje požadovanou  _úroveň bezpečnosti_  (viz níže)

**PARAM**
kladné celé číslo, které určuje dodatečný  _parametr pravidel_  (viz níže)

**-\-stats**
pokud je zadané, určuje, zda se na konci programu mají vypsat souhrnné statistiky analyzovaných hesel

## Úrovně bezpečnosti (kontrolovaná pravidla)

Jsou definovány celkem 4 úrovně bezpečnosti vyjádřeny pomocí 4 pravidel. Úroveň bezpečnosti určuje, že hesla musí splňovat všechna pravidla na dané a nižší úrovni. Tzn. např. úroveň bezpečnosti 3 specifikuje, že hesla musí splňovat pravidla 1, 2 a 3.

Některá pravidla jsou parametrizovatelná celým číslem zadaným pomocí argumentu programu  PARAM. V následujícím seznamu je tento parametr označen jako X.

Seznam pravidel:
1.  Heslo obsahuje alespoň 1 velké a 1 malé písmeno.
2.  Heslo obsahuje znaky z alespoň X skupin  (v případě, že je číslo X větší než 4, myslí se tím všechny skupiny). Uvažované skupiny jsou:
    -   malá písmena (a-z)
    -   velká písmena (A-Z)
    -   čísla (0-9)
    -   speciální znaky (podporované musí být alespoň nealfanumerické znaky z ASCII tabulky na pozicích  33-126  32-126, tedy včetně mezery)
3.  Heslo neobsahuje sekvenci stejných znaků délky alespoň X.
4.  Heslo neobsahuje dva stejné podřetězce délky alespoň X.

## Stats

Pokud je zadaný argument programu  --stats, program musí na konec výstupu vypsat celkové statistiky ve formátu:

`Ruznych znaku: NCHARS`\
`Minimalni delka: MIN`\
`Prumerna delka: AVG`

kde  NCHARS  je  _počet různých znaků_  vyskytujících se napříč všemi hesly,  MIN  je  _délka nejkratšího hesla_  (resp. hesel) a  AVG  je  _průměrná délka hesla_  (aritmetický průměr) zaokrouhlená na 1 desetiné místo. Statistiky zahrňují i hesla, která byla zahozena.

## Omezení projektu

Je zakázané použít následující funkce:

-   volání funkcí z knihoven  string.h  a  ctype.h  - cílem projektu je naučit se implementovat dané funkce ručně,
-   volání z rodiny  malloc  a  free  - práce s dynamickou pamětí není v tomto projektu zapotřebí,
-   volání z rodiny  fopen,  fclose,  fscanf, ... - práce se soubory (dočasnými) není v tomto projektu žádoucí,
-   volání funkce  exit  - cílem projektu je naučit se vytvořit programové konstrukce, které dokáží zpracovat neočekávaný stav programu a případně program řádně ukončit návratem z funkce main.


