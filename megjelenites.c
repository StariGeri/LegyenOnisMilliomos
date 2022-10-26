//
// Created by StariGeri on 2021. 11. 06..
//
#include "megjelenites.h"
#include <stdio.h>
#include "debugmalloc.h"

//a fomenu fuggveny fogja ossze a programot, idekerül a játékos a program indulasakor
Kerdes *fomenu(Kerdes *kerdesek, Kerdes *sorsolt, int *din_meret, Jatekos **dicsosegtabla, int *dics_meret) {


    int input;
    printf("                 Legyen On is Milliomos! \n \n");
    printf("                 Ez a Fomenu,tovabblepeshez valassz az alabbi menupontok kozul:\n \n");

    do {
        printf("                 Uj Jatek(1)\n");
        printf("                 Dicsosegtabla(2)\n");
        printf("                 Kilepes a Jatekbol(3)\n");

        scanf("%d", &input);

        //a fomenuben torteno menupont valasztas alapjan meghivjuk az illetekes fuggvenyt
        switch (input) {
            case 1:
                printf("Kezdodjon a jatek!\n");
                kerdesek = uj_jatek(kerdesek, sorsolt, 2, din_meret, dicsosegtabla, dics_meret);
                break;
            case 2:
                fodicsosegtabla(*dicsosegtabla, dics_meret);
                break;
            case 3:
                printf("\nKar,hogy elmesz. Ugyesen jatszottal!");
                break;
            default:
                fprintf(stderr, "Ajjaj, nincs ilyen menunpont.  Az alabbiakbol valassz: \n");
                break;
        }
    } while (input != 3);
    return kerdesek;
}

//a fomenuben torteno dicsoseglista menupont valasztas utan ez a fv- hivodik meg
// az ebben a fv.-ben használt algoritmust a https://www.geeksforgeeks.org/find-the-largest-three-elements-in-an-array/ webcikkben talaltam
//majd az igenyeim szerint atalakitottam
void fodicsosegtabla(Jatekos *dicsoseglista, int *dics_meret) {

    Jatekos elso, masodik, harmadik;
    printf("Ez a dicsosegtabla!\n");

    //ha nincs elem a tombben
    if (*dics_meret == 0) {
        printf("Ures a hiressegek csarnoka. Jatssz es legyel te az elso!\n");
        return;
    }

    //egyenlőre és -1re állítjuk kezdésként
    //erre azért van szükség, hogy 0 Ft nyeremeny is felkerulhessen(esetlegesen)
    harmadik.nyeremeny = elso.nyeremeny = masodik.nyeremeny = -1;
    //keressuk meg a 3 legjobb erdemenyt
    for (int i = 0; i < *dics_meret; i++) {
        if (dicsoseglista[i].nyeremeny > elso.nyeremeny ||
            dicsoseglista[i].nyeremeny == elso.nyeremeny && dicsoseglista[i].idoperc < elso.idoperc) { //az egyenlo nyeremenyu jatekosok az ido alapjan rangsorolodnak
            harmadik = masodik;
            masodik = elso;
            elso = dicsoseglista[i];
        }
            //ha az aktualis nyeremeny osszege az elso es masodik kozott van
        else if (dicsoseglista[i].nyeremeny > masodik.nyeremeny ||
                 dicsoseglista[i].nyeremeny == masodik.nyeremeny && dicsoseglista[i].idoperc < masodik.idoperc) {
            harmadik = masodik;
            masodik = dicsoseglista[i];
        } else if (dicsoseglista[i].nyeremeny > harmadik.nyeremeny ||
                   dicsoseglista[i].nyeremeny == harmadik.nyeremeny && dicsoseglista[i].idoperc < harmadik.idoperc) {
            harmadik = dicsoseglista[i];
        }
    }
    printf("[1.] %s , %d Ft , %.2f perc\n", elso.nev, elso.nyeremeny, elso.idoperc);//1 rekord mindig lesz
    if (*dics_meret > 1) {
        printf("[2.] %s , %d Ft , %.2f perc\n", masodik.nev, masodik.nyeremeny, masodik.idoperc); //ha 2 rekord van
    }
    if (*dics_meret > 2) {
        printf("[3.] %s , %d Ft , %.2f perc\n\n", harmadik.nev, harmadik.nyeremeny, harmadik.idoperc); //ha 3 rekord van
    }


}