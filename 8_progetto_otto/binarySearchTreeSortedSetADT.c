#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "sortedSetADT.h"

typedef struct treeNode TreeNode, *TreeNodePtr;

struct treeNode {
    void* elem;
    TreeNodePtr left, right;
};

struct sortedSetADT {
    TreeNodePtr root; /* Punta alla radice dell'albero, se l'insieme e' vuoto vale NULL */
    int (*compare)(void*, void*); /* confronto tra due elementi: -1,0,1 se primo precede, uguale o segue il secondo */
    int size; /* Numero di elementi presenti nell'insieme */
};

// for debug: stampa un insieme
void stampaSet_rec(TreeNodePtr cur, void (*stampaelem)(void*)) {
    #ifdef DEBUG
    printf("( ");
    #endif
    if (cur) {
        stampaSet_rec(cur->left, stampaelem);
        (*stampaelem)(cur->elem);
        stampaSet_rec(cur->right, stampaelem);
    }
    #ifdef DEBUG
    printf(") ");
    #endif
}

void stampaSet(SortedSetADTptr ss, void (*stampaelem)(void*)) {
    if(!ss) printf("Insieme non esiste\n");
    else if(sset_size(ss) == 0) printf("Insieme vuoto\n");
    else {
        printf("Insieme: (size %d) ",ss->size);
        stampaSet_rec(ss->root, stampaelem);
        printf("\n");
    }
}

int compareInt(void *a, void *b){
    if(*((int*)a) > *((int*)b))
        return 1;
    else if(*((int*)a) < *((int*)b))
        return -1;
    
    return 0;
}

//Trova il nodo ottimale per l'elemento ELEM all'interno del set
//Se il nodo non esiste SI FERMA al nodo padre
TreeNodePtr FindNodeFor_rec(void* elem, TreeNodePtr nodo, 
                            int (*compare)(void*, void*))
{
    if(nodo){
        int confronto = compare(nodo->elem, elem);
        if (confronto == 1){
            if(nodo->left)
                return FindNodeFor_rec(elem, nodo->left, compare);
        } else if(confronto == -1){
            if(nodo->right)
                return FindNodeFor_rec(elem, nodo->right, compare);
        }
    }
    //Restituisce il nodo con ELEM se nodo->elem == elem
    //Altrimenti 'nodo' e' rimasto il nodo padre
    return nodo;
}

//Trova il nodo ottimale per l'elemento ELEM all'interno del set.
//Se il nodo non esiste si ferma al nodo padre
//Restituisce NULL se il set non ha nodi
TreeNodePtr FindNodeFor(const SortedSetADT* ss, void* elem){
    if(isEmptySSet(ss) == 0){
        return FindNodeFor_rec(elem, ss->root, ss->compare);
    }

    return NULL;
}

// restituisce un insieme vuoto impostando funzione di confronto, NULL se errore
SortedSetADTptr mkSSet(int (*compare)(void*, void*)) {
    if(compare){
        SortedSetADTptr newset = malloc(sizeof(struct sortedSetADT));

        if(newset){
            newset->root = NULL;
            newset->compare = compare;
            newset->size = 0;

            return newset;
        }
    } 
    return NULL;
}

void dsSSet_rec(TreeNodePtr nodo){
    if(nodo){
        if(nodo->left)
            dsSSet_rec(nodo->left);
        if(nodo->right)
            dsSSet_rec(nodo->right);

        free(nodo);
    }
    return;
}

// distrugge l'insieme, recuperando la memoria
_Bool dsSSet(SortedSetADTptr* ssptr) {
    if(*ssptr){
        dsSSet_rec((*ssptr)->root);
        *ssptr = NULL;
        return true;
    }
    return false;
}

// aggiunge un elemento all'insieme 
_Bool sset_add(SortedSetADTptr ss, void* elem) { 
    if(ss){
        TreeNodePtr nodo_ottimale = FindNodeFor(ss, elem);

        if(nodo_ottimale){
            if(ss->compare(nodo_ottimale->elem, elem) == 0){
                //Il valore e' gia' all'interno del set
                return false;
            } else {
                //Il valore non e' presente nel set, il suo nodo e' ancora vuoto
                //e nodo_ottimale e' il nodo padre; decido in che ramo metterlo
                TreeNodePtr newnode = malloc(sizeof(struct treeNode));

                newnode->elem = elem;
                newnode->left = NULL;
                newnode->right = NULL;

                if(newnode){
                    if(ss->compare(nodo_ottimale->elem, elem) == 1){
                        //Ramo sinistro
                        nodo_ottimale->left = newnode;
                    } else if(ss->compare(nodo_ottimale->elem, elem) == -1){
                        //Ramo destro
                        nodo_ottimale->right = newnode;
                    }
                }
                ss->size++;
                return true;
            }
        } else {
            //Il set non ha nodi
            TreeNodePtr newnode = malloc(sizeof(struct treeNode));

            newnode->elem = elem;
            newnode->left = NULL;
            newnode->right = NULL;

            ss->root = newnode;
            ss->size++;
            return true;
        }
    }
    return false;
}  

//Funzioni usate all'interno di sset_remove_rec
void sset_extractMin_rec(TreeNodePtr* cur, void**ptr, int (*compare)(void*, void*));
void sset_extractMax_rec(TreeNodePtr* cur, void**ptr, int (*compare)(void*, void*));

// funzione ausiliaria che toglie un elemento da un sottoalbero
_Bool sset_remove_rec(TreeNodePtr* cur, void* elem, int (*compare)(void*, void*)) {
    if (*cur == NULL) return false;
    int r = compare(elem, (*cur)->elem);
    if (r < 0) return sset_remove_rec(&((*cur)->left), elem, compare);
    if (r > 0) return sset_remove_rec(&((*cur)->right), elem, compare);
    void* ptr;
    if ((*cur)->left == NULL) {
        sset_extractMin_rec(cur, &ptr, compare);
    } else if ((*cur)->right == NULL) {
        sset_extractMax_rec(cur, &ptr, compare);
    } else {
        sset_extractMax_rec(&((*cur)->left), &ptr, compare);
        (*cur)->elem = ptr;
    }
    return true;
}
// toglie un elemento all'insieme
_Bool sset_remove(SortedSetADTptr ss, void* elem) {
    if (ss && sset_remove_rec(&(ss->root), elem, ss->compare)) {
        ss->size--;
        return true;
    }
    return false;
}

// controlla se un elemento appartiene all'insieme
int sset_member(const SortedSetADT* ss, void* elem) {
    if(isEmptySSet(ss) == 0){
        TreeNodePtr nodo_ottimale = FindNodeFor(ss, elem);

        if(nodo_ottimale && ss->compare(nodo_ottimale->elem, elem) == 0){
            return 1;   //Il nodo trovato coincide con quello dell'elemento
        }
        
        return 0; //Il nodo non e' quello dell'elemento o non esiste
    }
    return -1;
}
    
// controlla se l'insieme e' vuoto    
int isEmptySSet(const SortedSetADT* ss) {
    if(ss){
        if(ss->size > 0)
            return 0;
        return 1;
    }
    return -1;
} 

// restituisce il numero di elementi presenti nell'insieme
int sset_size(const SortedSetADT* ss) {
    if(ss){
        return ss->size;
    }
    return -1;
}

// toglie e restituisce un elemento a caso dall'insieme
_Bool sset_extract(SortedSetADTptr ss, void**ptr) { 
    if(ss){
        //Estraggo il min perche' ho gia' scritto la funzione ed e' comodo
        return sset_extractMin(ss, ptr);
    }
    return false;
}

_Bool sset_equals_rec2(TreeNodePtr nodo, const SortedSetADT* s2){
    if(nodo){
        if(sset_member(s2, nodo->elem) == 1){    
            //Se l'elemento attuale c'e' nel s2 procedo 
            return  sset_equals_rec2(nodo->left, s2) && 
                    sset_equals_rec2(nodo->right, s2);
        }

        //Restituisco false SOLO se l'elemento attuale non c'e' in s2
        return false;
    }

    return true;
}

_Bool sset_equals_rec1(const SortedSetADT* s1, const SortedSetADT* s2, TreeNodePtr nodo){
    if(nodo){
        //Controllo se il il nodo attuale c'e' nel set 2
        if(sset_equals_rec2(nodo, s2)){
            //Procedo sui due rami left e right
            return  sset_equals_rec1(s1, s2, nodo->left) && 
                    sset_equals_rec1(s1, s2, nodo->right);
        }

        // Restituisco false SOLO se il nodo attuale non c'e' in s2
        return false;
    }

    return true;
}

// controlla se due insiemi sono uguali
int sset_equals(const SortedSetADT* s1, const SortedSetADT* s2) { 
    if(s1 && s2){
        return sset_equals_rec1(s1, s2, s1->root);
    }
    return -1;
}

_Bool sset_subseteq_rec(const TreeNodePtr nodo, const SortedSetADT* s2){
    bool ret = true;
    if(nodo->left)
        ret &= sset_subseteq_rec(nodo->left, s2);
    if(nodo->right)
        ret &= sset_subseteq_rec(nodo->right, s2);
    return ret && (sset_member(s2, nodo->elem) == 1);
}

// controlla se il primo insieme e' incluso nel secondo
int sset_subseteq(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 && s2){
        if(s1->size == 0)
            return 1;
        if(s2->size > 0){
            if(sset_subseteq_rec(s1->root, s2))
                return 1;
        }
        return 0;
    }
    return -1;
}

// controlla se il primo insieme e' incluso strettamente nel secondo
int sset_subset(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 && s2){
        if(s1->size < s2->size && sset_subseteq(s1, s2))
            return 1;
        return 0;
    }
    return -1;
} 

// restituisce la sottrazione primo insieme meno il secondo, NULL se errore
SortedSetADTptr sset_subtraction(const SortedSetADT* s1, const SortedSetADT* s2) {
    return NULL;   
} 

// restituisce l'unione di due insiemi, NULL se errore
SortedSetADTptr sset_union(const SortedSetADT* s1, const SortedSetADT* s2) {
    return NULL; 
} 

// restituisce l'intersezione di due insiemi, NULL se errore
SortedSetADTptr sset_intersection(const SortedSetADT* s1, const SortedSetADT* s2) {
    return NULL;
}

// restituisce il primo elemento
_Bool sset_min(const SortedSetADT* ss, void**ptr) {
    if(isEmptySSet(ss) == 0){
        TreeNodePtr nodo = ss->root;

        while(nodo->left){
            nodo = nodo->left;
        }

        *ptr = nodo->elem;
        return true;
    }

    return false;
}

// restituisce l'ultimo elemento 
_Bool sset_max(const SortedSetADT* ss, void**ptr) {
    if(isEmptySSet(ss) == 0){
        TreeNodePtr nodo = ss->root;

        while(nodo->right){
            nodo = nodo->right;
        }

        *ptr = nodo->elem;
        return true;
    }
    return false;
}

void sset_extractMin_rec(TreeNodePtr* cur, void**ptr, int (*compare)(void*, void*)){
    if(!(*cur)->left){      //Caso base
        //Leggo il valore del min
        *ptr = (*cur)->elem;
        if((*cur)->right){      //Se ha un ramo destro
            //Copio il suo nodo di destra all'interno del nodo attuale
            TreeNodePtr old = (*cur)->right;
            (*cur)->left = old->left;
            (*cur)->elem = old->elem;
            (*cur)->right = old->right;
            //Cancello il vecchio nodo di destra
            free(old);
        } else {
            //Devo rimuovere l'intero nodo
            free(*cur);
            *cur = NULL;
        }
    } else {
        return sset_extractMin_rec(&((*cur)->left), ptr, compare);
    }
    return;
}

// toglie e restituisce il primo elemento 
_Bool sset_extractMin(SortedSetADTptr ss, void**ptr) {
    if(isEmptySSet(ss) == 0){
        sset_extractMin_rec(&(ss->root), ptr, ss->compare);
        ss->size--;
        return true;
    }
    printf("ss vuoto.\n");
    return false;    
}

void sset_extractMax_rec(TreeNodePtr* cur, void**ptr, int (*compare)(void*, void*)){
    if(!(*cur)->right){     //Caso base
        //Leggo il valore del max
        *ptr = (*cur)->elem;
        if((*cur)->left){      //Se ha un ramo sinistro
            //Copio il suo nodo di sinistra all'interno del nodo attuale
            TreeNodePtr old = (*cur)->left;
            (*cur)->right = old->right;
            (*cur)->elem = old->elem;
            (*cur)->left = old->left;
            //Cancello il vecchio nodo di sinistra
            free(old);
        } else {
            //Devo rimuovere l'intero nodo
            free(*cur);
            *cur = NULL;
        }
    } else {
        return sset_extractMax_rec(&((*cur)->right), ptr, compare);
    }
    return;
}
// toglie e restituisce l'ultimo elemento (0 se lista vuota, -1 se errore, 1 se restituisce elemento)
_Bool sset_extractMax(SortedSetADTptr ss, void**ptr) {
    if(isEmptySSet(ss) == 0){
        sset_extractMax_rec(&(ss->root), ptr, ss->compare);
        ss->size--;
        return true;
    }
    return false;       
}
