#include <stdlib.h>
#include "megjelenites.h"
#include "debugmalloc.h"


int main(void) {
    //letrehozzuk a kerdes tipusu tombot amibe beolvassuk az osszes kerdest dinamikusan
    Kerdes *kerdesek = NULL;
    //letrehozzuk a jatekos tipusu tombot, ide lesznek beolvasva a jatekosok adatai a dics.tablahoz
    Jatekos *dicsosegtabla = NULL;
    int din_meret = 0; // mindket tomb merete kezdesenk 0
    int dics_meret = 0;
    //letrehozunk egy Kerdes tipusu tombot ahova a megadott szintnek megfeleloen sorsolunk
    Kerdes sorsolt[15];

    //meghivjuk a mindent osszefogo fomenu fv.-t
    fomenu(kerdesek, sorsolt, &din_meret, &dicsosegtabla, &dics_meret);
    free(dicsosegtabla);

    return 0;
}