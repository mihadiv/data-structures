// LISTA SIMPLA INLANTUITA

typedef struct nodLS {
    produs info;
    struct nodLS* next;
} nodLS;

nodLS* initializareNodLS(produs p) {
    nodLS* nou = (nodLS*)malloc(sizeof(nodLS));
    nou->info.pret = p.pret;
    nou->info.stoc = p.stoc;
    nou->info.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
    strcpy(nou->info.denumire, p.denumire);
    nou->next = NULL;
    return nou;
}

nodLS* inserareSfarsitLS(nodLS* cap, produs p) {
    nodLS* nou = initializareNodLS(p);
    if (cap == NULL) return nou;
    nodLS* temp = cap;
    while (temp->next) temp = temp->next;
    temp->next = nou;
    return cap;
}

// LISTA DUBLA

typedef struct nodLD {
    produs info;
    struct nodLD* next, *prev;
} nodLD;

nodLD* initializareNodLD(produs p) {
    nodLD* nou = (nodLD*)malloc(sizeof(nodLD));
    nou->info.pret = p.pret;
    nou->info.stoc = p.stoc;
    nou->info.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
    strcpy(nou->info.denumire, p.denumire);
    nou->next = nou->prev = NULL;
    return nou;
}

nodLD* inserareSfarsitLD(nodLD* cap, nodLD** coada, produs p) {
    nodLD* nou = initializareNodLD(p);
    if (cap == NULL) {
        *coada = nou;
        return nou;
    } else {
        (*coada)->next = nou;
        nou->prev = *coada;
        *coada = nou;
        return cap;
    }
}

// LISTA DUBLA CIRCULARA

typedef struct nodLDC {
    produs info;
    struct nodLDC* next, *prev;
} nodLDC;

nodLDC* initializareNodLDC(produs p) {
    nodLDC* nou = (nodLDC*)malloc(sizeof(nodLDC));
    nou->info.pret = p.pret;
    nou->info.stoc = p.stoc;
    nou->info.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
    strcpy(nou->info.denumire, p.denumire);
    nou->next = nou;
    nou->prev = nou;
    return nou;
}

nodLDC* inserareSfarsitLDC(nodLDC* cap, nodLDC** coada, produs p) {
    nodLDC* nou = initializareNodLDC(p);
    if (cap == NULL) {
        *coada = nou;
        return nou;
    } else {
        nou->next = cap;
        nou->prev = *coada;
        (*coada)->next = nou;
        cap->prev = nou;
        *coada = nou;
        return cap;
    }
}

// STIVA

typedef struct nodStiva {
    produs info;
    struct nodStiva* next;
} nodStiva;

void push(nodStiva** varf, produs p) {
    nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
    nou->info.pret = p.pret;
    nou->info.stoc = p.stoc;
    nou->info.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
    strcpy(nou->info.denumire, p.denumire);
    nou->next = *varf;
    *varf = nou;
}

int pop(nodStiva** varf, produs* p) {
    if (*varf == NULL) return -1;
    *p = (*varf)->info;
    nodStiva* temp = *varf;
    *varf = (*varf)->next;
    free(temp);
    return 0;
}

// COADA

typedef struct nodCoada {
    produs info;
    struct nodCoada* next;
} nodCoada;

void put(nodCoada** prim, nodCoada** ultim, produs p) {
    nodCoada* nou = (nodCoada*)malloc(sizeof(nodCoada));
    nou->info.pret = p.pret;
    nou->info.stoc = p.stoc;
    nou->info.denumire = (char*)malloc((strlen(p.denumire) + 1) * sizeof(char));
    strcpy(nou->info.denumire, p.denumire);
    nou->next = NULL;
    if (*prim == NULL) {
        *prim = *ultim = nou;
    } else {
        (*ultim)->next = nou;
        *ultim = nou;
    }
}

int get(nodCoada** prim, nodCoada** ultim, produs* p) {
    if (*prim == NULL) return -1;
    *p = (*prim)->info;
    nodCoada* temp = *prim;
    *prim = (*prim)->next;
    if (*prim == NULL) *ultim = NULL;
    free(temp);
    return 0;
}