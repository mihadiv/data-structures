//ARBORE AVL

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
    int BF;
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
        return creareNod(s,NULL,NULL);
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
    if (rad != NULL) {
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

//SUMA PRETURI
void sumaPreturi(nodArb *rad, float *suma) {
    if (rad != NULL) {
        *suma += rad->inf.pret;
        sumaPreturi(rad->stanga, suma);
        sumaPreturi(rad->dreapta, suma);
    }
}

//STERGERE RADACINA
nodArb *stergereRad(nodArb *rad) {
    nodArb *aux = rad;
    if (aux->dreapta != NULL) {
        rad = aux->dreapta;
        if (aux->stanga != NULL) {
            nodArb *temp = aux->dreapta;
            while (temp->stanga != NULL) {
                temp = temp->stanga;
            }
            temp->stanga = aux->stanga;
        }
    } else {
        if (aux->stanga != NULL) {
            rad = aux->stanga;
        } else {
            rad = NULL;
        }
    }
    free(aux->inf.denumire);
    free(aux->inf.producator);
    free(aux);
    return rad;
}

//STERGERE NOD
nodArb *stergereNod(nodArb *rad, int cheieDeSters) {
    if (rad != NULL) {
        if (rad->inf.id == cheieDeSters) {
            rad = stergereRad(rad);
            return rad;
        } else {
            if (cheieDeSters < rad->inf.id) {
                rad->stanga = stergereNod(rad->stanga, cheieDeSters);
                return rad;
            } else {
                rad->dreapta = stergereNod(rad->dreapta, cheieDeSters);
                return rad;
            }
        }
    } else {
        return NULL;
    }
}

//MAXIM
int maxim(int a, int b) {
    int max = a;
    if (max < b) {
        max = b;
    }
    return max;
}

//INALTIME ARBORE
int inaltimeArbore(nodArb *rad) {
    if (rad != NULL) {
        return 1 + maxim(inaltimeArbore(rad->stanga), inaltimeArbore(rad->dreapta));
    } else {
        return 0;
    }
}

//CALCUL BF - balance factor
void calculBF(nodArb *rad) {
    if (rad != NULL) {
        rad->BF = inaltimeArbore(rad->dreapta) - inaltimeArbore(rad->stanga);
        calculBF(rad->stanga);
        calculBF(rad->dreapta);
    }
}

//ROTATIE DREAPTA
nodArb *rotatie_dreapta(nodArb *rad) {
    printf("\nRotatie dreapta\n");
    nodArb *nod1 = rad->stanga;
    rad->stanga = nod1->dreapta;
    nod1->dreapta = rad;
    rad = nod1;
    return rad;
}

//ROTATIE STANGA
nodArb *rotatie_stanga(nodArb *rad) {
    printf("\nRotatie stanga\n");
    nodArb *nod1 = rad->dreapta;
    rad->dreapta = nod1->stanga;
    nod1->stanga = rad;
    rad = nod1;
    return rad;
}

//ROTATIE STANGA DREAPTA
nodArb *rotatie_stanga_dreapta(nodArb *rad) {
    printf("\nRotatie stanga-dreapta\n");
    nodArb *nod1 = rad->stanga;
    nodArb *nod2 = nod1->dreapta;
    nod1->dreapta = nod2->stanga;
    nod2->stanga = nod1;
    rad->stanga = nod2->dreapta;
    nod2->dreapta = rad;
    rad = nod2;
    return rad;
}

//ROTATIE DREAPTA STANGA
nodArb *rotatie_dreapta_stanga(nodArb *rad) {
    printf("\nRotatie dreapta-stanga\n");
    nodArb *nod1 = rad->dreapta;
    nodArb *nod2 = nod1->stanga;
    nod1->stanga = nod2->dreapta;
    nod2->dreapta = nod1;
    rad->dreapta = nod2->stanga;
    nod2->stanga = rad;
    rad = nod2;
    return rad;
}

//REECHILIBRARE
nodArb *reechilibrare(nodArb *rad) {
    calculBF(rad);
    nodArb *fiuSt = rad->stanga;
    nodArb *fiuDr = rad->dreapta;
    if (rad->BF <= -2 && fiuSt->BF <= -1) {
        rad = rotatie_dreapta(rad);
        calculBF(rad);
    } else {
        if (rad->BF >= 2 && fiuDr->BF >= 1) {
            rad = rotatie_stanga(rad);
            calculBF(rad);
        } else {
            if (rad->BF <= -2 && fiuSt->BF >= 1) {
                rad = rotatie_stanga_dreapta(rad);
                calculBF(rad);
            } else {
                if (rad->BF >= 2 && fiuDr->BF <= -1) {
                    rad = rotatie_dreapta_stanga(rad);
                    calculBF(rad);
                }
            }
        }
    }
    return rad;
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

        rad = reechilibrare(rad);
    }
    fclose(f);

    printf("\n---PREORDINE------------------------------");
    preordine(rad);

    /*printf("\n---INORDINE------------------------------");
    inordine(rad);
    printf("\n---POSTORDINE------------------------------");
    postordine(rad);*/

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

    printf("\n---------------------------------");

    printf("\nInaltime arbore: %d", inaltimeArbore(rad));
    printf("\nInaltime subarbore stang: %d", inaltimeArbore(rad->stanga));
    printf("\nInaltime subarbore drept: %d", inaltimeArbore(rad->dreapta));

    printf("\n---DUPA STERGERE------------------------------");

    // rad = stergereRad(rad);
    rad = stergereNod(rad, 110);
    rad = reechilibrare(rad);

    printf("\n---------------------------------");
    preordine(rad);
    printf("\n---------------------------------");
    preordine(rad->stanga);
    printf("\n---------------------------------");
    preordine(rad->dreapta);

    dezalocare(rad);
}
