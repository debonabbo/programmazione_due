#include <stdlib.h>
#include "list_rec.h"

// Ricorsione di fromTo
ListNodePtr fromTo_rec(int m, int n){
    if(m > n){
        return NULL;
    } else {
        ListNodePtr nodo = malloc(sizeof(struct listNode));

        if(!nodo)
            return NULL;

        nodo->data = m;
        nodo->next = fromTo_rec(m+1,n);

        return nodo;
    }
}

ListNodePtr fromTo(int m, int n){
    return fromTo_rec(m,n);
}

_Bool included_rec(ListNodePtr ls1, ListNodePtr ls2){

}

ListNodePtr reverse_rec(ListNodePtr ls){

}

// Ricorsione di zipSum
ListNodePtr zipSum_rec(ListNodePtr ls1, ListNodePtr ls2){

}

ListNodePtr zipSum(ListNodePtr ls1, ListNodePtr ls2){

}

// Ricorsione di occurrences
int occurrences_rec(ListNodePtr ls, int x){

}

int occurrences(ListNodePtr ls, int x){

}

void remove_all_rec(ListNodePtr *p_ls, int x){

}

void duplicate_even_rec(ListNodePtr ls){
    
}