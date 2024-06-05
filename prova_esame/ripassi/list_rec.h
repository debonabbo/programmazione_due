#ifndef LIST_REC_H
#define LIST_REC_H
#include <stdlib.h>

typedef struct listNode ListNode, *ListNodePtr;

struct listNode {
   int data;
   ListNodePtr next;
};

/**
 * @brief Restituisce una lista contenente tutti i numeri compresi tra m ed n
 * @param m numero m
 * @param n numero n
 * @return Il puntatore al primo elemento della lista
*/
ListNodePtr fromTo(int m, int n);

/**
 * @brief Controlla se tutti gli elementi della prima lista compaiono nello
 * stesso ordine nella seconda lista
 * @param ls1 prima lista
 * @param ls2 seconda lista
 * @return 1 se tutti gli elementi della prima lista compaiono nello stesso
 * ordine nella seconda lista, 0 altrimenti
*/
_Bool included_rec(ListNodePtr ls1, ListNodePtr ls2);

/**
 * @brief Restituisce una nuova lista con gli elementi di ls in ordine inverso
 * @param ls la lista da invertire
 * @return Il puntatore al primo elemento della nuova lista invertita
*/
ListNodePtr reverse_rec(ListNodePtr ls);

/**
 * @brief Restituisce una nuova lista i cui elementi sono le somme a coppie
 * degli elementi in posizioni corrispondenti delle due liste ls1 e ls2 di
 * uguale lunghezza
 * @param ls1 la lista uno
 * @param ls2 la lista due
 * @return Il puntatore al primo elemento della nuova lista
*/
ListNodePtr zipSum(ListNodePtr ls1, ListNodePtr ls2);

/**
 * @brief Conta il numero di occorrenze di x nella lista ls
 * @param ls la lista in cui contare 
 * @param x l'elemento da contare
 * @return Il numero di occorrenze di x nella lista
*/
int occurrences(ListNodePtr ls, int x);

/**
 * @brief Toglie tutte le occorrenze di x dalla lista ls
 * @param p_ls* il puntatore alla lista in cui rimuovere gli elementi
 * @param x l'elemento da rimuovere
 * @return void
*/
void remove_all_rec(ListNodePtr *p_ls, int x);

/**
 * @brief Duplica tutti i nodi della lista ls che contengono un numero pari
 * @param ls la lista da modificare
 * @return void
*/
void duplicate_even_rec(ListNodePtr ls);

#endif
