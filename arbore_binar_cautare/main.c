//ARBORE BINAR DE CAUTARE - BINARY SEARCH TREE (BST)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int zi, luna, an;
} dataExpirare;

typedef struct {
    int id;
    char *denumire;
    char *producator;
    float pret;
    dataExpirare expirare;
} software;

typedef struct {
    software inf;
    struct nodArb *stanga, *dreapta;
} nodArb;

//CREARE NOD
nodArb *creareNod(software s, nodArb *st, nodArb *dr) {
    nodArb *nou = (nodArb *) malloc(sizeof(nodArb));
    nou->inf.id = s.id;
    nou->inf.denumire = (char *) malloc((strlen(s.denumire) + 1) * sizeof(char));
    strcpy(nou->inf.denumire, s.denumire);
    nou->inf.producator = (char *) malloc((strlen(s.producator) + 1) * sizeof(char));
    strcpy(nou->inf.producator, s.producator);
    nou->inf.pret = s.pret;
    nou->inf.expirare.zi = s.expirare.zi;
    nou->inf.expirare.luna = s.expirare.luna;
    nou->inf.expirare.an = s.expirare.an;
    nou->stanga = st;
    nou->dreapta = dr;
    return nou;
}

//INSERARE NOD
//Insereaza software-ul in arbore dupa id: stanga < id < dreapta; ignora duplicatele
nodArb *inserareNod(nodArb *rad, software s) {
    if (rad != NULL) {
        if (s.id < rad->inf.id) {
            rad->stanga = inserareNod(rad->stanga, s);
            return rad;
        } else {
            if (s.id > rad->inf.id) {
                rad->dreapta = inserareNod(rad->dreapta, s);
                return rad;
            } else {
                return rad;
            }
        }
    } else {
        return creareNod(s, NULL, NULL);
    }
}

//RSD
void preordine(nodArb *rad) {
    if (rad != NULL) {
        printf("\nID = %d, Denumire = %s, Producator = %s, Pret = %5.2f, Data expirare = %d/%d/%d",
               rad->inf.id, rad->inf.denumire, rad->inf.producator, rad->inf.pret,
               rad->inf.expirare.zi, rad->inf.expirare.luna, rad->inf.expirare.an);
        preordine(rad->stanga);
        preordine(rad->dreapta);
    }
}

//SRD
void inordine(nodArb *rad) {
    if (rad != NULL) {
        inordine(rad->stanga);
        printf("\nID = %d, Denumire = %s, Producator = %s, Pret = %5.2f, Data expirare = %d/%d/%d",
               rad->inf.id, rad->inf.denumire, rad->inf.producator, rad->inf.pret,
               rad->inf.expirare.zi, rad->inf.expirare.luna, rad->inf.expirare.an);
        inordine(rad->dreapta);
    }
}

//SDR
void postordine(nodArb *rad) {
    if (rad != NULL) {
        postordine(rad->stanga);
        postordine(rad->dreapta);
        printf("\nID = %d, Denumire = %s, Producator = %s, Pret = %5.2f, Data expirare = %d/%d/%d",
               rad->inf.id, rad->inf.denumire, rad->inf.producator, rad->inf.pret,
               rad->inf.expirare.zi, rad->inf.expirare.luna, rad->inf.expirare.an);
    }
}

//DEZALOCARE
void dezalocare(nodArb *rad) {
    //preordine
    /*if (rad!=NULL) {
        nodArb* st = rad->stanga;
        nodArb* dr = rad->dreapta;
        free(rad->inf.denumire);
        free(rad->inf.producator);
        free(rad);
        dezalocare(st);
        dezalocare(dr);
    }*/

    //postordine
    if (rad != NULL) {
        dezalocare(rad->stanga);
        dezalocare(rad->dreapta);
        free(rad->inf.denumire);
        free(rad->inf.producator);
        free(rad);
    }
}

//SALVARE SOFTWARE-URI IN VECTOR
void salvareSoftwareVector(nodArb *rad, software *vect, int *nr, int anPrag) {
    //parcurge arborele in adancime
    if (rad != NULL) {
        //verifica daca e frunza
        if (rad->stanga == NULL && rad->dreapta == NULL && rad->inf.expirare.an == anPrag) {
            vect[*nr].id = rad->inf.id;
            vect[*nr].denumire = (char *) malloc((strlen(rad->inf.denumire) + 1) * sizeof(char));
            strcpy(vect[*nr].denumire, rad->inf.denumire);
            vect[*nr].producator = (char *) malloc((strlen(rad->inf.producator) + 1) * sizeof(char));
            strcpy(vect[*nr].producator, rad->inf.producator);
            vect[*nr].pret = rad->inf.pret;
            vect[*nr].expirare.zi = rad->inf.expirare.zi;
            vect[*nr].expirare.luna = rad->inf.expirare.luna;
            vect[*nr].expirare.an = rad->inf.expirare.an;
            (*nr)++;
        }
        salvareSoftwareVector(rad->stanga, vect, nr, anPrag);
        salvareSoftwareVector(rad->dreapta, vect, nr, anPrag);
    }
}

void sumaPreturi(nodArb *rad, float *suma) {
    if (rad != NULL) {
        *suma += rad->inf.pret;
        sumaPreturi(rad->stanga, suma);
        sumaPreturi(rad->dreapta, suma);
    }
}

void main() {
    nodArb *rad = NULL;
    software s;
    char buffer[50];
    int nrSoftware;
    FILE *f = fopen("../fisier.txt", "r");
    fscanf(f, "%d", &nrSoftware);
    for (int i = 0; i < nrSoftware; ++i) {
        fscanf(f, "%d", &s.id);
        fscanf(f, "%s", buffer);
        s.denumire = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(s.denumire, buffer);
        fscanf(f, "%s", buffer);
        s.producator = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(s.producator, buffer);
        fscanf(f, "%f", &s.pret);
        fscanf(f, "%d", &s.expirare.zi);
        fscanf(f, "%d", &s.expirare.luna);
        fscanf(f, "%d", &s.expirare.an);
        rad = inserareNod(rad, s);
        free(s.denumire);
        free(s.producator);
    }
    fclose(f);

    printf("\n---PREORDINE------------------------------");
    preordine(rad);
    printf("\n---INORDINE------------------------------");
    inordine(rad);
    printf("\n---POSTORDINE------------------------------");
    postordine(rad);
    printf("\n---------------------------------");

    software *vect = (software *) malloc(nrSoftware * sizeof(software));
    int nr = 0;
    salvareSoftwareVector(rad, vect, &nr, 2023);
    for (int i = 0; i < nr; ++i) {
        printf("\nID = %d, Denumire = %s, Producator = %s, Pret = %5.2f, Data expirare = %d/%d/%d",
               vect[i].id, vect[i].denumire, vect[i].producator, vect[i].pret,
               vect[i].expirare.zi, vect[i].expirare.luna, vect[i].expirare.an);
    }
    for (int i = 0; i < nr; ++i) {
        free(vect[i].denumire);
        free(vect[i].producator);
    }
    free(vect);

    printf("\n---------------------------------");

    float suma = 0;
    sumaPreturi(rad, &suma);
    printf("\nSuma preturilor = %5.2f", suma);

    dezalocare(rad);
}
