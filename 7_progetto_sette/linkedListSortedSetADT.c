#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "sortedSetADT.h"

typedef struct listNode ListNode, *ListNodePtr;

struct listNode {
   void* elem;
   ListNodePtr next;
};

struct sortedSetADT {
    ListNodePtr first; /* Punta al primo nodo dell'insieme, se l'insieme e' vuoto vale NULL */
    ListNodePtr last; /* Punta all'ultimo nodo dell'insieme, se l'insieme e' vuoto vale NULL */
    int (*compare)(void*, void*); /* confronto tra due elementi: -1,0,1 se primo precede, uguale o segue il secondo */
    int size; /* Numero di elementi presenti nell'insieme */
};

// for debug: stampa un insieme
void stampaSet(SortedSetADTptr ss, void (*stampaelem)(void*)) {
    ListNodePtr cur;
    if(!ss) printf("Insieme non esiste\n");
    else if(sset_size(ss) == 0) printf("Insieme vuoto\n");
    else {
        printf("Insieme: (size %d) ",ss->size);
        for(cur = ss->first; cur; cur=cur->next) (*stampaelem)(cur->elem);
        printf("\n");
    }
}    

int compareElem(void* a, void* b){
    if(a > b)
        return 1;
    else if(a < b)
        return -1;
    return 0;
}

SortedSetADTptr mkSSet(int (*compare)(void*, void*)) {
    SortedSetADTptr set = malloc(sizeof(struct sortedSetADT));

    if(set){
        set->first = NULL;
        set->last = NULL;
        set->compare = compareElem;
        set->size = 0;
        return set;
    }

    return NULL;
}

_Bool dsSSet(SortedSetADTptr* ssptr) {
    if(ssptr){
        if(*ssptr){
            free(*ssptr);
            *ssptr = NULL;
            return true;
        }
    }
    return false;
}

_Bool sset_add(SortedSetADTptr ss, void* elem) { 
    if(ss){
        if(!isEmptySSet(ss)){
            ListNodePtr a;
            if(ss->compare(ss->last->elem, elem) != 1)
                a = ss->last;
            else
                a = ss->first;

            //Recupero la posizione ottimale per l'elemento
            while(a->next && ss->compare(a->next->elem, elem) != 1)
                a = a->next;

            if(ss->compare(a->elem, elem) == 0)     //L'elemento c'era gia'
                return false;

            //L'elemento non c'e ancora, lo aggiungo nella posizione ottimale
            ListNodePtr n = malloc(sizeof(struct listNode));
            if(n){
                n->elem = elem;

                if(ss->compare(a->elem, elem) == 1){
                    //L'elemento va inserito all'inizio della lista
                    n->next = a;
                    ss->first = n;
                } else {
                    //L'elemento va inserito in un'altra posizione
                    n->next = a->next;
                    a->next = n;
                    if(n->next == NULL)
                        ss->last = n;       //E' l'ultimo elemento del set
                }

                ss->size++;
                return true;
            }
        } else {
            //Il set era vuoto, aggiungo il primo elemento
            ListNodePtr n = malloc(sizeof(struct listNode));
            if(n){
                n->elem = elem;
                n->next = NULL;

                ss->first = n;
                ss->last = n;
                ss->size++;
                return true;
            }
        }
    }

    return false;
}  

_Bool sset_remove(SortedSetADTptr ss, void* elem) {
    if(ss){
        if(isEmptySSet(ss))
            return false;

        if(ss->compare(ss->first->elem, elem) == 1 || 
            ss->compare(ss->last->elem, elem) == -1) //L'elemento non c'e'
            return false;

        ListNodePtr a = ss->first;

        if(ss->compare(a->elem, elem) == 0){
            //L'elemento cercato coincide col primo della lista
            ss->first = a->next;
            free(a);
            ss->size--;

            return true;
        }

        while(a->next && ss->compare(a->next->elem, elem) != 1){
            //Se esiste un elemento successivo e il suo valore e' <= elem
            if(ss->compare(a->next->elem, elem) == 0){
                //Il successivo e' l'elemento da rimuovere
                ListNodePtr next = a->next->next;
                //Lo rimuovo
                free(a->next);
                a->next = next;
                ss->size--;

                return true;
            }

            //Non ho ancora trovato l'elemento, passo al successivo
            a = a->next;
        }
        
    }

    return false;
}

int sset_member(const SortedSetADT* ss, void* elem) {
    if(ss){
        ListNodePtr a = ss->first;

        while(a && ss->compare(a->elem, elem) != 1){
            if(ss->compare(a->elem, elem) == 0)
                return 1;
            a = a->next;
        }

        return 0;
    }

    return -1;
}
    
int isEmptySSet(const SortedSetADT* ss) {
    if(ss){
        if(ss->first == NULL)
            return 1;
        return 0;
    }

    return -1;
} 

int sset_size(const SortedSetADT* ss) {
    if(ss)
        return ss->size;
    return -1;
} 

_Bool sset_extract(SortedSetADTptr ss, void**ptr) {
    if(ss){
        if(ss->first){
            //Estraggo il primo elemento perche' mi e' comodo
            *ptr = ss->first->elem;
            ListNodePtr a = ss->first;
            ss->first = ss->first->next;
            free(a);
            ss->size--;
            return 1;
        }
    }

    return false;
} 

int sset_equals(const SortedSetADT* s1, const SortedSetADT* s2) { 
    if(s1 && s2){
        if(s1->size == s2->size){
            if(s1->size > 0){
                ListNodePtr a = s1->first;
                ListNodePtr b = s2->first;

                int i = 0;
                while(a && b && s1->compare(a->elem, b->elem) == 0 && i < s1->size){
                    i++;
                    a = a->next;
                    b = b->next;
                }

                if(i == s1->size)
                    return 1;
            } else {
                return 1;
            }
        }

        return 0;
    }
    
    return -1;
}

int sset_subseteq(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 && s2){
        if(isEmptySSet(s1) && isEmptySSet(s2)){
            return true;
        } else if (!isEmptySSet(s2)){
            if(s1->size == 0)
                return 1;
            else {
                if(s1->size <= s2->size){
                    ListNodePtr a = s1->first;
                    ListNodePtr b = s2->first;

                    int u = 0;
                    while(a && b && s1->compare(a->elem, b->elem) != 1 && u < s1->size){
                        if(s1->compare(a->elem, b->elem) == 0){
                            a = a->next;
                            u++;
                        }

                        b = b->next;
                    }

                    if(u == s1->size)
                        return 1;
                }
            }
        }

        return 0;
    }
    
    return -1;
}

int sset_subset(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 && s2){
        if(s1->size < s2->size){
            if(s1->size == 0)
                return true;
            else {
                ListNodePtr a = s1->first;
                ListNodePtr b = s2->first;

                int u = 0;
                while(a && b && s1->compare(a->elem, b->elem) != 1 && u < s1->size){
                    if(s1->compare(a->elem, b->elem) == 0){
                        a = a->next;
                        u++;
                    }

                    b = b->next;
                }

                if(u == s1->size)
                    return true;
            }
        }

        return 0;
    }

    return -1;
} 

SortedSetADTptr sset_union(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 && s2){
        SortedSetADTptr newset = mkSSet(compareElem);
        if(newset){
            ListNodePtr a = s1->first;
            ListNodePtr b = s2->first;

            while((a || b)){
                if(a && b){
                    if(newset->compare(a->elem, b->elem) == 0){
                        //Inserisco a e scarto b
                        sset_add(newset, a->elem);
                        a = a->next;
                        b = b->next;
                    } else if(newset->compare(a->elem, b->elem) == -1){
                        //Inserisco a
                        sset_add(newset, a->elem);
                        a = a->next;
                    } else {
                        //Inserisco b
                        sset_add(newset, b->elem);
                        b = b->next;
                    }
                } else if (a){
                    //Inserisco a
                    sset_add(newset, a->elem);
                    a = a->next;
                } else {
                    //Inserisco b
                    sset_add(newset, b->elem);
                    b = b->next;
                }
            }
            
            return newset;
        }
    }

    return NULL; 
} 

SortedSetADTptr sset_intersection(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 && s2){
        SortedSetADTptr newset = mkSSet(compareElem);

        if(newset){
            if(!isEmptySSet(s1) && !isEmptySSet(s2)){
                if(newset){
                    ListNodePtr a = s1->first;
                    ListNodePtr b = s2->first;

                    while(a && b){
                        if(newset->compare(a->elem, b->elem) == 0){
                            //Sono uguali, aggiungo e passo ai successivi
                            sset_add(newset, a->elem);
                            a = a->next;
                            b = b->next;
                        } else if (newset->compare(a->elem, b->elem) == 1){
                            b = b->next;
                        } else {
                            a = a->next;
                        }
                    }

                    return newset;
                }
            }

            return newset;
        }
    }
    return NULL;
}

SortedSetADTptr sset_subtraction(const SortedSetADT* s1, const SortedSetADT* s2) {
    if(s1 && s2){
        SortedSetADTptr newset = mkSSet(compareElem);

        if(newset){
            if(!isEmptySSet(s1) && !isEmptySSet(s2)){
                ListNodePtr a = s1->first;
                ListNodePtr b = s2->first;

                while(a){
                    if(b){
                        if(newset->compare(a->elem, b->elem) == 0){
                            //Ignoro l'elemento
                            a = a->next;
                            b = b->next;
                        } else if(newset->compare(a->elem, b->elem) == 1){
                            //Aumento b
                            b = b->next;
                        } else {
                            // L'elemento non c'era, lo aggiungo
                            sset_add(newset, a->elem);
                            //Passo al successivo
                            a = a->next;
                        }
                    } else {
                        //Gli elementi in b son finiti, copio quelli in a
                        sset_add(newset, a->elem);
                        a = a->next;
                    }
                }
            } else if (!isEmptySSet(s1) && isEmptySSet(s2)){
                //Se il secondo set e' vuoto, copio semplicemente tutti gli
                //elementi del primo
                ListNodePtr a = s1->first;

                while(a){
                    sset_add(newset, a->elem);
                    a = a->next;
                }
            }

            return newset;
        }
    }
    return NULL;   
} 

_Bool sset_min(const SortedSetADT* ss, void**ptr) {
    if(ss){
        if(ss->first){
            *ptr = ss->first->elem;
            return true;
        }
    }
    return false;
}

_Bool sset_max(const SortedSetADT* ss, void**ptr) {
    if(ss){
        if(ss->last){
            *ptr = ss->last->elem;
            return true;
        }
    }
    return false;
}

_Bool sset_extractMin(SortedSetADTptr ss, void**ptr) {
    if(ss){
        if(ss->first){
            *ptr = ss->first->elem;

            //Rimuovo il primo elemento
            ListNodePtr a = ss->first;
            ss->first = a->next;
            free(a);
            ss->size--;
            return true;
        }
    }
    return false;    
}

// toglie e restituisce l'ultimo elemento (0 se lista vuota, -1 se errore, 1 se restituisce elemento)
_Bool sset_extractMax(SortedSetADTptr ss, void**ptr) {
    if(ss){
        if(ss->last){
            *ptr = ss->last->elem;

            //Rimuovo l'ultimo elemento
            ListNodePtr a = ss->first;
            while(a->next != ss->last)
                a = a->next;
            free(ss->last);
            a->next = NULL;
            ss->last = a;
            ss->size--;
            return true;
        }
    }
    return false;       
}

