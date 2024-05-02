#include <stdlib.h>
#include <stdbool.h>

#include "intSortedSetADT.h"
#include "intLinkedListSortedSetADT.h"

IntSortedSetADT mkSSet() {
    IntSortedSetADT set = malloc(sizeof(struct intSortedSet));

    if(set){
        set->first = NULL;
        set->last = NULL;
        set->size = 0;
        return set;
    }

    return NULL;
}

_Bool dsSSet(IntSortedSetADT *ssptr) {
    if(ssptr){
        if(*ssptr){
            free(*ssptr);
            *ssptr = NULL;
            return true;
        }
    }

    return false;
}

_Bool sset_add(IntSortedSetADT ss, const int elem) {
    if(ss){
        if(!isEmptySSet(ss)){
            ListNodePtr a;
            if(ss->last->elem <= elem)
                a = ss->last;
            else
                a = ss->first;

            //Recupero la posizione ottimale per l'elemento
            while(a->next && a->next->elem <= elem)
                a = a->next;

            if(a->elem == elem)     //L'elemento c'era gia'
                return false;

            //L'elemento non c'e ancora, lo aggiungo nella posizione ottimale
            ListNodePtr n = malloc(sizeof(struct listNode));
            if(n){
                n->elem = elem;

                if(a->elem > elem){
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

_Bool sset_remove(const IntSortedSetADT ss, const int elem) {
    if(ss){
        if(isEmptySSet(ss))
            return false;

        if(ss->first->elem > elem || ss->last->elem < elem) //L'elemento non c'e'
            return false;

        ListNodePtr a = ss->first;

        if(a->elem == elem){
            //L'elemento cercato coincide col primo della lista
            ss->first = a->next;
            free(a);
            ss->size--;

            return true;
        }

        while(a->next && a->next->elem <= elem){
            //Se esiste un elemento successivo e il suo valore e' <= elem
            if(a->next->elem == elem){
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

_Bool sset_member(const IntSortedSetADT ss, const int elem) {
    if(ss){
        ListNodePtr a = ss->first;

        while(a && a->elem <= elem){
            if(a->elem == elem)
                return true;
            a = a->next;
        }
    }

    return false;
}

_Bool isEmptySSet(const IntSortedSetADT ss) {
    if(ss){
        if(ss->first == NULL)
            return true;
    }

    return false;
}

int sset_size(const IntSortedSetADT ss) {
    if(ss)
        return ss->size;
    return -1;
}

_Bool sset_extract(IntSortedSetADT ss, int *ptr) {
    if(ss){
        if(ss->first){
            //Estraggo il primo elemento perche' mi e' comodo
            *ptr = ss->first->elem;
            ListNodePtr a = ss->first;
            ss->first = ss->first->next;
            free(a);
            ss->size--;
            return true;
        }
    }
    return false;
}

_Bool sset_equals(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(s1 && s2){
        if(s1->size == s2->size){
            if(s1->size > 0){
                ListNodePtr a = s1->first;
                ListNodePtr b = s2->first;

                int i = 0;
                while(a && b && a->elem == b->elem && i < s1->size){
                    i++;
                    a = a->next;
                    b = b->next;
                }

                if(i == s1->size)
                    return true;
            } else {
                return true;
            }
        }
    }
    return false;
}

_Bool sset_subseteq(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(s1 && s2){
        if(isEmptySSet(s1) && isEmptySSet(s2)){
            return true;
        } else if (!isEmptySSet(s2)){
            if(s1->size == 0)
                return true;
            else {
                if(s1->size <= s2->size){
                    ListNodePtr a = s1->first;
                    ListNodePtr b = s2->first;

                    int u = 0;
                    while(a && b && a->elem <= b->elem && u < s1->size){
                        if(a->elem == b->elem){
                            a = a->next;
                            u++;
                        }

                        b = b->next;
                    }

                    if(u == s1->size)
                        return true;
                }
            }
        }
    }

    return false;
}

_Bool sset_subset(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(s1 && s2){
        if(s1->size < s2->size){
            if(s1->size == 0)
                return true;
            else {
                ListNodePtr a = s1->first;
                ListNodePtr b = s2->first;

                int u = 0;
                while(a && b && a->elem <= b->elem && u < s1->size){
                    if(a->elem == b->elem){
                        a = a->next;
                        u++;
                    }

                    b = b->next;
                }

                if(u == s1->size)
                    return true;
            }
        }
    }
    return false;
}

IntSortedSetADT sset_union(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(s1 && s2){
        IntSortedSetADT newset = mkSSet();
        if(newset){
            ListNodePtr a = s1->first;
            ListNodePtr b = s2->first;

            while((a || b)){
                if(a && b){
                    if(a->elem == b->elem){
                        //Inserisco a e scarto b
                        sset_add(newset, a->elem);
                        a = a->next;
                        b = b->next;
                    } else if(a->elem < b->elem){
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

IntSortedSetADT sset_intersection(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(s1 && s2){
        IntSortedSetADT newset = mkSSet();

        if(newset){
            if(!isEmptySSet(s1) && !isEmptySSet(s2)){
                if(newset){
                    ListNodePtr a = s1->first;
                    ListNodePtr b = s2->first;

                    while(a && b){
                        if(a->elem == b->elem){
                            //Sono uguali, aggiungo e passo ai successivi
                            sset_add(newset, a->elem);
                            a = a->next;
                            b = b->next;
                        } else if (a->elem > b->elem){
                            b = b->next;
                        } else {
                            a = a->next;
                        }
                    }
                }
            }

            return newset;
        }
    }
    return NULL;
}

IntSortedSetADT sset_subtraction(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if(s1 && s2){
        IntSortedSetADT newset = mkSSet();

        if(newset){
            if(!isEmptySSet(s1) && !isEmptySSet(s2)){
                ListNodePtr a = s1->first;
                ListNodePtr b = s2->first;

                while(a){
                    if(b){
                        if(a->elem == b->elem){
                            //Ignoro l'elemento
                            a = a->next;
                            b = b->next;
                        } else if(a->elem > b->elem){
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

_Bool sset_min(const IntSortedSetADT ss, int *ptr) {
    if(ss){
        if(ss->first){
            *ptr = ss->first->elem;
            return true;
        }
    }
    return false;
}

_Bool sset_max(const IntSortedSetADT ss, int *ptr) {
    if(ss){
        if(ss->last){
            *ptr = ss->last->elem;
            return true;
        }
    }
    return false;
}

_Bool sset_extractMin(IntSortedSetADT ss, int *ptr) {
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

_Bool sset_extractMax(IntSortedSetADT ss, int *ptr) {
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
