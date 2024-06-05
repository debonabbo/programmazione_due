#include <stdlib.h>
#include "list_iter.h"

ListNodePtr fromTo_iter(int m, int n){
    ListNodePtr first = malloc(sizeof(struct listNode));
    first->data = m;
    ListNodePtr prev = first;
    first->next = NULL;

    int a = m;
    while(a < n){
        ListNodePtr nodo = malloc(sizeof(struct listNode));
        nodo->data = ++a;
        prev->next = nodo;
        nodo->next = NULL;
        prev = nodo;
    }

    return first;
}

_Bool included_iter(ListNodePtr ls1, ListNodePtr ls2){
    if(ls1 && ls2){
        while(ls2 && ls2->data != ls1->data)
            ls2 = ls2->next;
        if(ls2){
            while(ls1 && ls1->data == ls2->data){
                ls1 = ls1->next;
                ls2 = ls2->next;
            }
            if(!ls1)
                return 1;
        }
    }
    return 0;
}

ListNodePtr reverse_iter(ListNodePtr ls){
    ListNodePtr prev = NULL, next = ls->next;
    ListNodePtr new = ls;

    while(next && new){
        new = malloc(sizeof(struct listNode));
        if(new){
            new->data = ls->data;
            new->next = prev;
            prev = ls;
            ls = next;
            next = ls->next;
        }
    }
    return new;
}

ListNodePtr zipSum_iter(ListNodePtr ls1, ListNodePtr ls2){
    if(!ls1 || !ls2)
        return NULL;
    ListNodePtr nodo = malloc(sizeof(struct listNode));
    if(!nodo)
        return NULL;
    ListNodePtr first = nodo;
    while(nodo && ls1 && ls2){
        nodo->data = ls1->data + ls2->data;
        nodo->next = malloc(sizeof(struct listNode));
        nodo = nodo->next;
        ls1 = ls1->next;
        ls2 = ls2->next;
    }
    return first;
}

int occurrences_iter(ListNodePtr ls, int x){
    if(!ls)
        return -1;
    int occorrenze = 0;
    while(ls){
        if(ls->data == x)
            occorrenze++;
        ls = ls->next;
    }

    return occorrenze;
}

void remove_all_iter(ListNodePtr *p_ls, int x){
    if(!p_ls || !(*p_ls))
        return;

    // Elimino le occorrenze di testa
    while(*p_ls && (*p_ls)->data == x){
        ListNodePtr next = (*p_ls)->next;
        free((*p_ls));
        (*p_ls) = next;
    }

    ListNodePtr first = *p_ls;
    // Elimino le occorrenze lungo la lista
    if(*p_ls){
        while((*p_ls)->next){
            if((*p_ls)->next->data == x){
                ListNodePtr temp = (*p_ls)->next;
                (*p_ls)->next = (*p_ls)->next->next;
                free(temp);
            } else {
                *p_ls = (*p_ls)->next;
            }
        }
    }

    *p_ls = first;

    return;
}

void duplicate_even_iter(ListNodePtr ls){
    if(!ls)
        return;

    while(ls){
        if(ls->data % 2 == 0){
            ListNodePtr newnode = malloc(sizeof(struct listNode));
            if(!newnode)
                return;
            newnode->data = ls->data;
            newnode->next = ls->next;
            ls->next = newnode;
            ls = ls->next;
        }
        ls = ls->next;
    }
    return;
}