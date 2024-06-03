/* Un tipo di dato astratto per le code di char */
typedef struct charQueue *CharQueueADT;

/**
 * @brief Crea una coda vuota
 * @return La coda creata, 0 se non c'e' memoria sufficiente 
*/
CharQueueADT mkQueue();

/**
 * @brief Distrugge la coda, recuperando la memoria
 * @param 
*/
void dsQueue(CharQueueADT *pq);

/**
 * @brief Aggiunge un elemento in fondo alla coda
 * @return 1 se l'operazione e' andata a buon fine, 0 altrimenti 
*/
_Bool enqueue(CharQueueADT q, const char e);

/**
 * @brief Toglie e restituisce l'elemento in testa alla coda
 * @param q la coda da cui togliere l'elemento
 * @param res* il puntatore che conterra' l'elemento rimosso
 * @return 1 se l'operazione e' andata a buon fine, 0 altrimenti
*/
_Bool dequeue(CharQueueADT q, char*res);

/** 
 * @brief Controlla se la coda è vuota 
 * @param q la coda da controllare
 * @return 1 se la coda e' vuota, 0 altrimenti
*/
_Bool isEmpty(CharQueueADT q);

/**
 * @brief Restituisce il numero degli elementi presenti nella coda
 * @param q la coda
 * @return Il numero di elementi nella coda
*/
int size(CharQueueADT q);

/**
 * @brief Restituisce l'elemento nella posizione data senza toglierlo.
 * La testa della coda ha indice 0.
 * @param q la coda in cui prendere l'elemento
 * @param position la posizione in cui prendere l'elemento
 * @param res* il puntatore che conterra' l'elemento richiesto
 * @return 1 se l'operazione e' andata a buon fine, 0 altrimenti
*/
_Bool peek(CharQueueADT q, int position, char* res);
