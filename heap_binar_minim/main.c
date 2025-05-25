//HEAP BINAR MINIM - produs -> sortare produse crescator dupa pret

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float pret; //prioritatea
    char *denumire;
    int stoc;
} produs;

typedef struct {
    produs *vect;
    int nrElem;
} heap;

//FILTRARE (dupa pret)
void filtrare(heap h, int index) {
    int indexRad = index;
    int indexSt = 2 * index + 1;
    int indexDr = 2 * index + 2;

    if (indexSt < h.nrElem && h.vect[indexSt].pret < h.vect[indexRad].pret) {
        indexRad = indexSt;
    }

    if (indexDr < h.nrElem && h.vect[indexDr].pret < h.vect[indexRad].pret) {
        indexRad = indexDr;
    }

    if (index != indexRad) {
        produs aux = h.vect[index];
        h.vect[index] = h.vect[indexRad];
        h.vect[indexRad] = aux;

        filtrare(h, indexRad);
    }
}

//INSERARE - la final, apoi filtrare
heap inserare(heap h, produs produsNou) {
    produs *vectNou = (produs *) malloc((h.nrElem + 1) * sizeof(produs));
    for (int i = 0; i < h.nrElem; ++i) {
        vectNou[i] = h.vect[i];
    }
    h.nrElem++;
    vectNou[h.nrElem - 1] = produsNou;
    free(h.vect);
    h.vect = vectNou;
    for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
        filtrare(h, i);
    }
    return h;
}

//EXTRAGERE - se extrage elementul cu valoare minima
heap extragere(heap h, produs *produsExtras) {
    produs *vectNou = (produs *) malloc((h.nrElem - 1) * sizeof(produs));
    produs aux = h.vect[0];
    h.vect[0] = h.vect[h.nrElem - 1];
    h.vect[h.nrElem - 1] = aux;
    *produsExtras = h.vect[h.nrElem - 1];
    h.nrElem--;
    for (int i = 0; i < h.nrElem; ++i) {
        vectNou[i] = h.vect[i];
    }
    free(h.vect);
    h.vect = vectNou;
    for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
        filtrare(h, i);
    }
    return h;
}

//AFISARE
void afisare(heap h) {
    for (int i = 0; i < h.nrElem; ++i) {
        printf("\nPret = %5.2f, Denumire produs = %s, Stoc = %d",
               h.vect[i].pret, h.vect[i].denumire, h.vect[i].stoc);
    }
}

//DEZALOCARE
void dezalocare(heap h) {
    for (int i = 0; i < h.nrElem; ++i) {
        free(h.vect[i].denumire);
    }
    free(h.vect);
}

void main() {
    heap h;
    char buffer[50];
    FILE *f = fopen("fisier.txt", "r");
    fscanf(f, "%d", &h.nrElem);
    h.vect = (produs *) malloc(h.nrElem * sizeof(produs));
    for (int i = 0; i < h.nrElem; ++i) {
        fscanf(f, "%f", &h.vect[i].pret);
        fscanf(f, "%s", buffer);
        h.vect[i].denumire = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
        strcpy(h.vect[i].denumire, buffer);
        fscanf(f, "%d", &h.vect[i].stoc);
    }
    fclose(f);

    for (int i = (h.nrElem - 1) / 2; i >= 0; i--) {
        filtrare(h, i);
    }
    afisare(h);

    printf("\n-------------------------\n");

    produs produsNou;

    printf("Denumire = ");
    scanf("%s", buffer);
    produsNou.denumire = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(produsNou.denumire, buffer);
    printf("Pret = ");
    scanf("%f", &produsNou.pret);
    printf("Stoc = ");
    scanf("%d", &produsNou.stoc);

    h = inserare(h, produsNou);
    afisare(h);

    printf("\nNumar elemente dupa inserare: %d", h.nrElem);

    printf("\n-------------------------\n");

    produs produsExtras;
    h = extragere(h, &produsExtras);
    afisare(h);

    printf("\nEXTRAS -> Pret = %5.2f, Denumire produs = %s, Stoc = %d",
           produsExtras.pret, produsExtras.denumire, produsExtras.stoc);

    printf("\nNumar elemente dupa extragere: %d", h.nrElem);

    printf("\n-------------------------\n");

    //Extragerea elementelor din heap si adaugarea lor intr-un vector (sortat crescator)
    produs *vectSortat = (produs *) malloc(h.nrElem * sizeof(produs));
    int nr = h.nrElem;
    for (int i = 0; i < nr; ++i) {
        h = extragere(h, &produsExtras);
        vectSortat[i] = produsExtras;
    }

    for (int i = 0; i < nr; ++i) {
        printf("\nPret = %5.2f, Denumire produs = %s, Stoc = %d",
               vectSortat[i].pret, vectSortat[i].denumire, vectSortat[i].stoc);
    }
    for (int i = 0; i < nr; ++i) {
        free(vectSortat[i].denumire);
    }
    free(vectSortat);

    dezalocare(h);
}
