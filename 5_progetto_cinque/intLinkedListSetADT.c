#include <stdlib.h>
#include <stdbool.h>

#include "intSetADT.h"
#include "intLinkedListSet.h"

// struct listNode {
//    int data;
//    ListNodePtr next;
// };

// struct intSet {
//     ListNodePtr front; /* Punta al primo nodo dell'insieme, se l'insieme e' vuoto vale NULL */
//     int size; /* Numero di elementi presenti nell'insieme */
// };

IntSetADT mkSet() {
    IntSetADT set = malloc(sizeof(struct intSet));

    if(set){
        set->front = NULL;
        set->size = 0;

        return set;
    }

    return NULL;
}

_Bool dsSet(IntSetADT *sp) {
    if(sp){
        if(*sp){
            if(!isEmptySet(*sp)){
                ListNodePtr a = (*sp)->front;
                ListNodePtr next;

                while(a){
                    next = a->next;
                    free(a);
                    a = next;
                }
            }
            free(*sp);
            *sp = NULL;
            return true;
        }
    }
    return false;
}

_Bool set_add(IntSetADT set, const int elem) { 
    if(set){
        if(!set_member(set, elem)){
            //L'elemento non c'e ancora, lo aggiungo
            ListNodePtr n = malloc(sizeof(struct listNode));
            if(n){
                n->data = elem;
                n->next = set->front;
                // printf("Aggiungo %d.\n", elem);

                set->front = n;
                set->size++;
                return true;
            }
        }
    }
    return false;
}

_Bool set_remove(IntSetADT set, const int elem) {
    if(set){
        ListNodePtr a = set->front;

        if(a){
            if(a->data == elem){
                //L'elemento cercato coincide col primo della lista
                set->front = a->next;
                free(a);
                set->size--;

                return true;
            }

            while(a->next){
                //Se esiste un elemento successivo
                if(a->next->data == elem){
                    //Il successivo e' l'elemento da rimuovere
                    ListNodePtr next = a->next->next;
                    //Lo rimuovo
                    free(a->next);
                    a->next = next;
                    set->size--;

                    return true;
                }

                //Non ho ancora trovato l'elemento, passo al successivo
                a = a->next;
            }
        }
        
    }
    return false;
}

_Bool set_member(const IntSetADT set, const int elem) {
    if(set){
        ListNodePtr a = set->front;

        while(a){
            if(a->data == elem)
                return true;
            a = a->next;
        }
    }

    return false;
}

_Bool isEmptySet(const IntSetADT set) {
    if(set){
        if(set->front == NULL)
            return true;
    }
    return false;
}

int set_size(const IntSetADT set) {
    if(set)
        return set->size;
    return -1;
}

_Bool set_extract(IntSetADT set, int *datap) {
    if(set){
        if(!isEmptySet(set)){
            //Restituisco il primo elemento e lo rimuovo
            *datap = set->front->data;
            ListNodePtr a = set->front;
            set->front = a->next;
            free(a);
            set->size--;

            return true;
        }
    }
    return false;
}

_Bool set_equals(const IntSetADT set1, const IntSetADT set2) {
    if(set1 && set2){
        if(set1->size == set2->size){
            if(set1->size > 0){
                ListNodePtr a = set1->front;
                ListNodePtr b;

                int i = 0;
                _Bool trovato;
                while(a){
                    b = set2->front;
                    trovato = false;
                    while(b && !trovato && i < set1->size){ 
                        if(a->data == b->data){
                            trovato = true;
                            i++;
                        }
                        b = b->next;
                    }

                    a = a->next;
                }

                if(i == set1->size)
                    return true;
            } else {
                return true;
            }
        }
    }
    return false;
}

_Bool subseteq(const IntSetADT set1, const IntSetADT set2) {
    if(set1 && set2){
        if(isEmptySet(set1) && isEmptySet(set2)){
            return true;
        } else if (!isEmptySet(set2)){
            if(set1->size == 0)
                return true;
            else {
                if(set1->size <= set2->size){
                    ListNodePtr a = set1->front;
                    ListNodePtr b = set2->front;

                    int u = 0;
                    _Bool trovato;
                    while(a){
                        trovato = false;
                        while(b && !trovato && u < set1->size){ 
                            if(a->data == b->data){
                                trovato = true;
                                u++;
                            }
                            b = b->next;
                        }

                        a = a->next;
                    }

                    if(u == set1->size)
                        return true;
                }
            }
        }
    }
    return false;
}

_Bool subset(const IntSetADT set1, const IntSetADT set2) {
    if(set1 && set2){
        if(set1->size < set2->size){
            if(set1->size == 0)
                return true;
            else {
                ListNodePtr a = set1->front;
                ListNodePtr b = set2->front;

                int u = 0;
                _Bool trovato;
                while(a){
                    trovato = false;
                    while(b && !trovato && u < set1->size){ 
                        if(a->data == b->data){
                            trovato = true;
                            u++;
                        }
                        b = b->next;
                    }

                    a = a->next;
                }

                if(u == set1->size)
                    return true;
            }
        }
    }
    return false;    
}

IntSetADT set_union(const IntSetADT set1, const IntSetADT set2) {
    if(set1 && set2){
        IntSetADT newset = mkSet();
        if(newset){
            ListNodePtr a = set1->front;
            ListNodePtr b = set2->front;

            while(a){
                set_add(newset, a->data);
                a = a->next;
            }

            while(b){
                set_add(newset, b->data);
                b = b->next;
            }
            
            return newset;
        }
    }
    return NULL;
}

IntSetADT set_intersection(const IntSetADT set1, const IntSetADT set2) {
    if(set1 && set2){
        if(!isEmptySet(set1) && !isEmptySet(set2)){
            IntSetADT newset = mkSet();
            if(newset){
                ListNodePtr a = set1->front;
                ListNodePtr b = set2->front;

                _Bool trovato;
                while(a){
                    trovato = false;
                    while(b && !trovato){
                        if(a->data == b->data){
                            ListNodePtr n = malloc(sizeof(struct listNode));

                            if(n){
                                n->data = a->data;
                                n->next = newset->front;

                                newset->front = n;
                                newset->size++;
                            }

                            trovato = true;
                        }

                        b = b->next;
                    }
                    b = set2->front;
                    a = a->next;
                }

                return newset;
            }
        } else {
            //L'intersezione e' l'insieme vuoto
            IntSetADT newset = mkSet();

            if(newset){
                return newset;
            }
        }
    }
    return NULL;
}

IntSetADT set_subtraction(const IntSetADT set1, const IntSetADT set2) {
    if(set1 && set2){
        IntSetADT newset = mkSet();

        if(newset){
            ListNodePtr a = set1->front;

            while(a){
                if(!set_member(set2, a->data)){
                    set_add(newset, a->data);
                }
                a = a->next;
            }

            return newset;
        }
    }
    return NULL;
}