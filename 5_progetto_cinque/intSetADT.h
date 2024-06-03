#ifndef GUARD_IntSetADT
#define GUARD_IntSetADT

/** Un tipo di dato per gli insiemi di int
*/
typedef struct intSet *IntSetADT;

/*
 NOTA:
 le seguenti funzioni, in base al loro tipo, devono restituire 
 NULL, -1 oppure false (0) se ricevono uno o più puntatori NULL come 
 parametri di tipo IntSetADT
*/

/**
 * @brief Costruisce un insieme vuoto
 * @return Un insieme vuoto
*/
IntSetADT mkSet();

/**
 * @brief Distrugge l'insieme (e tutti i suoi elementi) recuperando la memoria
 * @param sp* il puntatore al set da distruggere
 * @return 1 se l'operazione e' stata completata, 0 altrimenti
*/
_Bool dsSet(IntSetADT*);

/**
 * @brief Aggiunge un elemento all'insieme
 * @param set il set a cui aggiungere l'elemento
 * @param elem l'elemento da aggiungere
 * @return 0 se l'elemento era gia' presente, 1 altrimenti
*/
_Bool set_add(IntSetADT, const int);

/**
 * @brief Toglie un elemento dall'insieme
 * @param set il set da cui rimuovere l'elemento
 * @param int l'elemento da rimuovere
 * @return 1 se l'elemento era presente ed e' stato rimosso, 0 altrimenti
*/
_Bool set_remove(IntSetADT, const int);

/**
 * @brief Controlla se un elemento appartiene all'insieme
 * @param set il set in cui cercare l'elemento
 * @param int l'elemento da cercare
 * @return 1 se l'elemento appartiene all'insieme, 0 altrimenti
*/
_Bool set_member(const IntSetADT, const int);

/**
 * @brief Controlla se l'insieme e' vuoto
 * @param set il set da controllare 
 * @return 1 se l'insieme e' vuoto, 0 altrimenti
*/
_Bool isEmptySet(const IntSetADT);

/**
 * @brief Restituisce il numeri di elementi presenti nell'insieme
 * @param set il set in cui contare gli elementi
 * @return Il numero di elementi presenti nell'insieme, -1 se il set e' NULL
*/
int set_size(const IntSetADT);

/**
 * @brief Toglie e restituisce un elemento a caso dall'insieme
 * @param set il set da cui togliere l'elemento
 * @param datap* il puntatore che conterra' l'elemento tolto
 * @return 1 se l'operazione e' stata completata, 0 altrimenti
*/
_Bool set_extract(IntSetADT, int *);

/**
 * @brief Controlla se due insiemi sono uguali
 * @param set1 il primo insieme da controllare
 * @param set2 il secondo insieme da controllare
 * @return 1 se gli insiemi sono uguali, 0 altrimenti
*/
_Bool set_equals(const IntSetADT, const IntSetADT);

/**
 * @brief Controlla se il primo insieme e' incluso o coincide col secondo
 * @param set1 il primo insieme
 * @param set2 il secondo insieme
 * @return 1 se il primo insieme e' incluso o coincide col secondo, 0 altrimenti
*/
_Bool subseteq(const IntSetADT, const IntSetADT);

/**
 * @brief Controlla se il primo insieme e' incluso strettamente nel secondo
 * @param set1 il primo insieme
 * @param set2 il secondo insieme
 * @return 1 se il primo insieme e' incluso strettamente nel secondo,
 * 0 altrimenti
*/
_Bool subset(const IntSetADT, const IntSetADT);

/**
 * @brief Restituisce l'unione di due insiemi
 * @param set1 il primo insieme
 * @param set2 il secondo insieme
 * @return Un nuovo insieme contenente l'unione dei due insiemi
*/
IntSetADT set_union(const IntSetADT, const IntSetADT);

/**
 * @brief Restituisce l'intersezione di due insiemi
 * @param set1 il primo insieme
 * @param set2 il secondo insieme
 * @return Un nuovo insieme contenente l'intersezione dei due insiemi
*/
IntSetADT set_intersection(const IntSetADT, const IntSetADT);

/**
 * @brief Restituisce la sottrazione di due insiemi
 * @param set1 il primo insieme
 * @param set2 il secondo insieme
 * @return Un nuovo insieme contenente la sottrazione dei due insiemi
*/
IntSetADT set_subtraction(const IntSetADT, const IntSetADT);

#endif