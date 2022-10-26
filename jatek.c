//
// Created by StariGeri on 2021. 11. 06..
//

#include "jatek.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "debugmalloc.h"

//ez a fv felelos a dinamikusan foglalt kerdesek felszabaditasaert
void kerdes_felszabadit(Kerdes *kerdesek, int *din_meret) {
    for (int i = 0; i < *din_meret; i++) {
        free(kerdesek[i].kerdes);
    }
};

//ezzel a fv.-el olvassuk be a kerdesek.csv-t,es daraboljuk strukturakba
Kerdes *beolvas(Kerdes *kerdesek, int *idx) {
    debugmalloc_max_block_size(10000000); // a beolvasott kerdesek szama miatt boviteni kellett
    //fajl beolvasasa
    FILE *fp;
    fp = fopen("kerdesek.csv", "r");
    char sor[1024];
    *idx = 0;

    //beolvassuk a sorokat dinamikusan
    while (fgets(sor, 1024, fp) != NULL) {
        if (*idx == 0) {
            kerdesek = (Kerdes *) malloc(sizeof(Kerdes));
            if (kerdesek == NULL) {
                printf("Sajnos nem sikerult memoriat foglalni..\n");
            }
        }
        Kerdes *ujkerdesek = (Kerdes *) malloc(sizeof(Kerdes) * (*idx + 1));
        for (int i = 0; i < *idx; ++i) {
            ujkerdesek[i] = kerdesek[i];
        }
        free(kerdesek);
        kerdesek = ujkerdesek;
        //az alabbi kodreszlet segit abban, hogy minden egyes beolvasott sort, strukturaba tordeljunk
        char *pstr = strtok(sor, ";");
        if (pstr != NULL) {
            ujkerdesek[*idx].nehezseg = atoi(pstr);
        }

        pstr = strtok(NULL, ";");
        if (pstr != NULL) {
            int len = strlen(pstr);
            ujkerdesek[*idx].kerdes = malloc(len + 1); // a kerdes srtuktura kerdes parametere dinamikus foglalasa
            strcpy(ujkerdesek[*idx].kerdes, pstr);
        }

        //strukturaba tesszuk az 'a' opciot
        pstr = strtok(NULL, ";");
        if (pstr != NULL) {
            strcpy(ujkerdesek[*idx].a, pstr);

        }

        //strukturaba tesszuk a 'b' opciot
        pstr = strtok(NULL, ";");
        if (pstr != NULL) {
            strcpy(ujkerdesek[*idx].b, pstr);

        }

        //strukturaba tesszuk a 'c' opciot
        pstr = strtok(NULL, ";");
        if (pstr != NULL) {
            strcpy(ujkerdesek[*idx].c, pstr);

        }

        //strukturaba tesszuk a 'd' opciot
        pstr = strtok(NULL, ";");
        if (pstr != NULL) {
            strcpy(ujkerdesek[*idx].d, pstr);
        }

        //srukturaba tesszuk a jo valaszt
        pstr = strtok(NULL, ";");
        if (pstr != NULL) {
            ujkerdesek[*idx].jo_valasz = pstr[0];
            //strcpy(kerdesek[idx].jo_valasz, pstr);
        }
        (*idx)++;
    }
    fclose(fp);
    return kerdesek;
}

//ez a fv.valogat veletlenszeruen (a nehezsegi szintnek megfeleloen) kerdeseket es egy tombbe tolti azokat
void kerdesek_adasa(Kerdes *kerdesek, Kerdes *sorsolt, int szint, int *din_meret) {
    srand(time(0));

    // a while ciklus vizsgalja a kerdeseket es a megfeleloeket listaba tolti
    int szamlalo = 0;
    while (szamlalo < 14) {
        int generalt = rand() % (*din_meret) + 1;
        if (kerdesek[generalt].nehezseg == szint) {
            sorsolt[szamlalo] = kerdesek[generalt];
            szamlalo++;
        }
    }
}

//ezt a fv.-t hivjuk meg ha a jatek barmely pontjan jo valaszt ad a jatekos(kodrovidites celjabol)
int jo_valasz(int osszeg) {
    osszeg = osszeg + 50000;
    printf("Helyes valasz! Az eddigi ossznyeremenyed: %d Ft.\n", osszeg);
    return osszeg;
}

//ez a fv. kezeli a kozonseg altal kert segitseget a jatek soran
void kozonseg_segitseg(Kerdes sorsolt) {
    printf("A kozonseg szerint a jo valasz: %c\n", sorsolt.jo_valasz);
}

// a jatekban kerheto segitseg fuggvenye, a jo valasztol fuggoen valaszt ki es tart meg 2 valasz lehetoseget
void felezo_segitseg(Kerdes sorsolt) {
    if (sorsolt.jo_valasz == 'A') {
        printf("A felezes utan megmaradt valasz lehetosegek:\n");
        printf("A: %s\nD: %s\n", sorsolt.a, sorsolt.d);
    }
    if (sorsolt.jo_valasz == 'B') {
        printf("A felezes utan megmaradt valasz lehetosegek:\n");
        printf("B: %s\nD: %s\n", sorsolt.b, sorsolt.d);
    }
    if (sorsolt.jo_valasz == 'C') {
        printf("A felezes utan megmaradt valasz lehetosegek:\n");
        printf("B: %s\nC: %s\n", sorsolt.b, sorsolt.c);
    }
    if (sorsolt.jo_valasz == 'D') {
        printf("A felezes utan megmaradt valasz lehetosegek:\n");
        printf("A: %s\nD: %s\n", sorsolt.a, sorsolt.d);
    }
}

//ez a fv. felelos a jatek meneteert. Ez ad nekunk kerdeseket, és valasz lehetosegeket,illetve biztositja a segitsegek kereset
int jatek_menete(Kerdes *sorsolt) {
    int osszeg = 0;//szamoljuk a mar megnyert nyeremenyt
    bool segitsegf = true;// ha igaz, nincs felhasznalva(azaz elérhető) - ha hamis akkor fel van hasznalva
    bool segitsegk = true;// ugyanez ervenyes itt is
    int n = 10; //osszesen 10 generalt kerdest teszunk fel
    for (int i = 0; i < n; i++) {
        char valasz;
        printf("[%d.] %s \n A: %s \n B: %s \n C: %s \n D: %s \n", i + 1, sorsolt[i].kerdes, sorsolt[i].a, sorsolt[i].b,
               sorsolt[i].c, sorsolt[i].d);
        if (segitsegf) {
            printf(" ----------\n F: Felezes \n");
        }
        if (segitsegk) {
            printf(" ----------\n K: Kozonseg segitsege\n");
        }
        printf("---------\n E: Kilepes a Fomenube\n");
        while (true) {
            printf("Valasz: ");
            scanf(" %c", &valasz);
            valasz = toupper(valasz);
            // Választ adott meg a jatekos
            if (valasz == 'A' || valasz == 'B' || valasz == 'C' || valasz == 'D') {
                if (valasz == sorsolt[i].jo_valasz) {
                    osszeg = jo_valasz(osszeg);
                    if (i == n - 1) {
                        printf("Megnyerted a jatekot. Hihetetlen!\n");
                    }
                    break;
                } else {
                    printf("Sajnos ez most nem jott ossze,probalkozz ujra!\n");
                    printf("A jo valasz a(z): %c lett volna.\n", sorsolt[i].jo_valasz);
                    printf("Az ossznyeremenyed: %d Ft\n", osszeg);
                    return osszeg;
                }
            }
            // Segitseget kert a jatekos
            if (valasz == 'F' && segitsegf) {
                felezo_segitseg(sorsolt[i]);
                segitsegf = false;
                continue;
            }
            if (valasz == 'K' && segitsegk) {
                kozonseg_segitseg(sorsolt[i]);
                segitsegk = false;
                continue;
            }
            if (valasz == 'E') {
                return -1;
            }
            // Rossz bemenet visszajelzese
            fprintf(stderr, "Ajjaj, valami nem stimmel. Bizonyosodj meg arrol, hogy a fentiekbol valasztasz.\n");
        }
    }
    return osszeg;
}

//a jatekos altal elert errdemenyeket fajlba irja (nev,nyeremeny,jatekban toltott ido)
void dicstabla_fajlbairas(char *nev, int *osszeg, time_t ido) {
    float idoperc = (float) ido / 60;
    FILE *fv;
    fv = fopen("dicsosegtabla.txt", "a");
    if (fv == NULL) {
        perror("Nem lehetett megnyitni a fajlt\n");
        return;
    }
    fprintf(fv, "%s;%d;%.2f\n", nev, *osszeg, idoperc);
    fclose(fv);
}

// ez a fv. felelos azert,hogy a dicsosegtabla dinamikus legyen, igy akarmennyi rekord hozzaadhato
Jatekos *dicstabla_beolvasas(Jatekos *dicsosegtabla, int *db) {
    FILE *fk;
    fk = fopen("dicsosegtabla.txt", "r");
    char sor[1024];
    *db = 0;

    while (fgets(sor, 1024, fk) != NULL) {
        if (*db == 0) {
            dicsosegtabla = (Jatekos *) malloc(sizeof(Jatekos));
            if (dicsosegtabla == NULL) {
                printf("Sajnos nem sikerult memoriat foglalni..\n");
            }
        }
        Jatekos *ujdicsosegtabla = (Jatekos *) malloc(sizeof(Jatekos) * (*db + 1));
        for (int i = 0; i < *db; ++i) {
            ujdicsosegtabla[i] = dicsosegtabla[i];
        }
        free(dicsosegtabla);
        dicsosegtabla = ujdicsosegtabla;

        //strukturaba tordeljuk a beolvasott sorokat
        //eloszor a jatekos nevet
        char *pstr = strtok(sor, ";");
        if (pstr != NULL) {
            strcpy(ujdicsosegtabla[*db].nev, pstr);
        }

        //majd a jatekos nyeremenyet
        pstr = strtok(NULL, ";");
        if (pstr != NULL) {
            ujdicsosegtabla[*db].nyeremeny = atoi(pstr);
        }

        //vegul pedig a jatekos jatekban toltott idejet
        pstr = strtok(NULL, ";");
        if (pstr != NULL) {
            ujdicsosegtabla[*db].idoperc = atof(pstr);
        }


        (*db)++;
    }
    fclose(fk);
    return dicsosegtabla;

}

//ezt a fv.-t hivjuk meg a fomenubol, amikor jatekot kezdunk. Ez fogja ossze az osszes jatekkezelo es dicsosegtabla keszito fv.-t
Kerdes *uj_jatek(Kerdes *kerdesek, Kerdes *sorsolt, int osszeg, int *din_meret, Jatekos **dicsosegtabla, int *dics_meret) {
    time(0);
    int szint;
    char nev[100];

    printf("Mi legyen a jatekos neved? \n");
    scanf(" %s", nev);
    printf("Milyen szinten szeretnel jatszani ?(1-10) \n");
    scanf("%d", &szint);

    time_t begin, end;
    time(&begin);
    //feljebb megirt fobb fuggvenyek meghivasa
    kerdesek = beolvas(kerdesek, din_meret);
    kerdesek_adasa(kerdesek, sorsolt, szint, din_meret);
    osszeg = jatek_menete(sorsolt);

    //a dicsosegtablahoz hasznalt ido konvertalasa
    time(&end);
    time_t ido = (end - begin);
    dicstabla_fajlbairas(nev, &osszeg, ido);
    if (*dics_meret == 0) {
        *dicsosegtabla = dicstabla_beolvasas(*dicsosegtabla, dics_meret);
    }

    kerdes_felszabadit(kerdesek, din_meret);
    free(kerdesek);

    return kerdesek;

}