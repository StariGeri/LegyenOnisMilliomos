//
// Created by StariGeri on 2021. 11. 06..
//
#ifndef MAIN_C_JATEK_H
#define MAIN_C_JATEK_H


#include "time.h"

//kerdesek struktura --> a kerdeseket, es a hozzatartozo adatokat ilyen strukturakba toltjuk
typedef struct Kerdes {
    int nehezseg;
    char *kerdes;
    char a[51];
    char b[51];
    char c[51];
    char d[51];
    char jo_valasz;
} Kerdes;
//jatekos struktura --> ez a tipus segit majd a dicsosegtabla elkesziteseben, a jatekos jatekban kapott adatait tarolja
typedef struct Jatekos {

    char nev[51];
    int nyeremeny;
    float idoperc;
} Jatekos;

//a jatek.c fuggvenyeinek dekleralasa:
void kerdes_felszabadit(Kerdes *,int *); // a dinamikusan foglalt kerdeseket a kerdeseket tartalmazo felszabaditasa nem szabaditja fel

Kerdes *beolvas(Kerdes *, int *);

Kerdes *uj_jatek(Kerdes *, Kerdes *, int, int *, Jatekos **, int *);

void dicstabla_fajlbairas(char *, int *, time_t);

Jatekos *dicstabla_beolvasas(Jatekos *, int *);


#endif //MAIN_C_JATEK_H