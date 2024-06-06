#include <stdlib.h>
#include "list_rec.h"

// Ricorsione di fromTo()
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
    if(!ls1)
        return 1;
    if(!ls2)
        return 0;

    if(ls1->data == ls2->data)
        return 1 && included_rec(ls1->next, ls2->next);
    return included_rec(ls1, ls2->next);
}

// Ricorsione di reverse()
ListNodePtr reverse_rec(ListNodePtr ls, ListNodePtr mia){
    if(!ls){ 
        return mia;
    } else {
        ListNodePtr new = malloc(sizeof(struct listNode));
        new->data = ls->data;
        new->next = mia;
        return reverse_rec(ls->next, new);
    }
}

// ListNodePtr reverse_rec(ListNodePtr ls){
//     if(!ls) return NULL;
//     if(!ls->next) return ls;
//     ListNodePtr restante = reverse_rec(ls->next);
//     ls->next->next = ls;
//     ls->next = NULL;
//     return restante;
// }

ListNodePtr reverse(ListNodePtr ls){
    return reverse_rec(ls, NULL);
}

// Ricorsione di zipSum()
ListNodePtr zipSum_rec(ListNodePtr ls1, ListNodePtr ls2){
    if(!ls1 || !ls2){
        return NULL;
    } else {
        ListNodePtr a = malloc(sizeof(struct listNode));
        a->data = ls1->data;
    }
}

ListNodePtr zipSum(ListNodePtr ls1, ListNodePtr ls2){

}

// Ricorsione di occurrences()
int occurrences_rec(ListNodePtr ls, int x){

}

int occurrences(ListNodePtr ls, int x){

}

void remove_all_rec(ListNodePtr *p_ls, int x){

}

void duplicate_even_rec(ListNodePtr ls){
    
}