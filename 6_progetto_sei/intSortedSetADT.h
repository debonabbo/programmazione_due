#ifndef GUARD_IntSortedSetADT
#define GUARD_IntSortedSetADT

/** Un tipo di dato per gli insiemi ordinati di int
*/
typedef struct intSortedSet *IntSortedSetADT;

/*
 NOTA:
 le seguenti funzioni, in base al loro tipo, devono restituire 
 NULL, -1 oppure false (0) se ricevono uno o più puntatori NULL come parametri 
 di tipo IntSortedSetADT
*/

/**
 * @brief Restituisce un nuovo insieme vuoto
 * @return Un nuovo insieme
*/
IntSortedSetADT mkSSet(); // restituisce un insieme vuoto

/**
 * @brief Distrugge l'insieme, recuperando la memoria
 * @param ssptr* il puntatore all'insieme da distruggere
 * @return 1 se l'operazione e' andata a buon fine, 0 altrimenti
*/
_Bool dsSSet(IntSortedSetADT*);

/**
 * @brief Aggiunge un elemento all'insieme
 * @param ss l'insieme in cui aggiungere l'elemento
 * @param elem l'elemento da aggiungere
 * @return 0 se l'elemento era gia' presente, 1 altrimenti
*/
_Bool sset_add(IntSortedSetADT, const int);

/**
 * @brief Toglie un elemento dall'insieme
 * @param ss l'insieme dal quale rimuovere l'elemento
 * @param elem l'elemento da rimuovere
 * @return 0 se l'elemento non era presente, 1 altrimenti
*/
_Bool sset_remove(IntSortedSetADT, const int);

/**
 * @brief Controlla se un elemento appartiene all'insieme
 * @param ss l'insieme nel quale cercare l'elemento
 * @param elem l'elemento da cercare
 * @return 1 se l'elemento appartiene all'insieme, 0 altrimenti
*/
_Bool sset_member(const IntSortedSetADT, const int);

/**
 * @brief Controlla se l'insieme e' vuoto
 * @param ss l'insieme da controllare
 * @return 1 se l'insieme e' vuoto, 0 altrimenti
*/
_Bool isEmptySSet(const IntSortedSetADT);

/**
 * @brief Restituisce il numero di elementi presenti nell'insieme
 * @param ss il set in cui contare gli elementi
 * @return Il numero di elementi presenti nell'insieme, -1 se NULL
*/
int sset_size(const IntSortedSetADT);

/**
 * @brief Toglie e restituisce un elemento a caso dall'insieme
 * @param ss il set da cui estrarre l'elemento
 * @param ptr* il puntatore che conterra' l'elemento estratto
 * @return 1 se l'operazione e' andata a buon fine, 0 altrimenti
*/
_Bool sset_extract(IntSortedSetADT, int *);

/**
 * @brief Controlla se due insiemi sono uguali
 * @param s1 il primo set
 * @param s2 il secondo set
 * @return 1 se i set sono uguali, 0 altrimenti
*/
_Bool sset_equals(const IntSortedSetADT, const IntSortedSetADT);
_Bool sset_subseteq(const IntSortedSetADT, const IntSortedSetADT); // controlla se il primo insieme e' incluso nel secondo
_Bool sset_subset(const IntSortedSetADT, const IntSortedSetADT); // contr. se il primo ins. e' incluso strettamente nel secondo
IntSortedSetADT sset_union(const IntSortedSetADT, const IntSortedSetADT); // restituisce l'unione di due insiemi
IntSortedSetADT sset_intersection(const IntSortedSetADT, const IntSortedSetADT); // restituisce l'intersezione di due insiemi
IntSortedSetADT sset_subtraction(const IntSortedSetADT, const IntSortedSetADT); // restituisce l’insieme ottenuto dal primo togliendo gli elementi del secondo
_Bool sset_min(const IntSortedSetADT, int *); // restituisce l'elemento minimo
_Bool sset_max(const IntSortedSetADT, int *); // restituisce l'elemento massimo
_Bool sset_extractMin(IntSortedSetADT, int *); // toglie e restituisce l'elemento minimo
_Bool sset_extractMax(IntSortedSetADT, int *); // toglie e restituisce l'elemento massimo

#endif