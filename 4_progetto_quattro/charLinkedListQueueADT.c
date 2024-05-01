#include "charQueueADT.h"
#include <stddef.h>
#include <stdlib.h>

/* il valore 8 può essere cambiato */
#define INITIAL_CAPACITY 8

struct charQueue {
    int capacity; /* capacity == INITIAL CAPACITY^n, per qualche numero naturale n >= 1 */
    char* a; /* array, di dimensione capacity, che memorizza gli elementi presenti nella coda */
    int size; /* numero di elementi presenti nella coda (0 <= size <= capacity) */
    int rear; /* prima posizione libera in a (dove sarà memorizzato il prossimo elemento della coda (0 <= rear <= capacity-1) */
    int front; /* posizione in a dove (se size > 0) è memorizzato il primo elemento della coda (0 <= front <= capacity-1) */
    /* (front==rear) se e solo se ((size == 0) || (size == capacity)) */
    /* Gli elementi della coda sono in: a[front..rear-1] se rear > front, e in a[front..capacity-1],a[0..rear-1], se rear <= front */
    /* L'array si espande di un fattore due quando si riempie, e si dimezza (se capacity > INITIAL_CAPACITY) */
    /* quando size scende a capacity/4 (parametri personalizzabili) */      
    /* Se capacity > INITIAL_CAPACITY, allora il numero di elementi in coda è >= capacity/4 */
};


/* @brief Restituisce una coda vuota, se non trova memoria restituisce NULL */
CharQueueADT mkQueue() {
    CharQueueADT coda = malloc(sizeof(struct charQueue));

    if(coda){
        coda->a = malloc(sizeof(char)*INITIAL_CAPACITY);

        if(coda->a){
            coda->capacity = INITIAL_CAPACITY;
            coda->size = 0;
            coda->rear = 0;
            coda->front = 0;

            return coda;
        }

        //Allocazione dell'array fallita, libero la memoria
        free(coda);
    }

    return NULL;
}

/* @brief Distrugge la coda, recuperando la memoria */
void dsQueue(CharQueueADT *pq) {
    if(*pq){
        if((*pq)->a){
            free((*pq)->a);
        }
        free(*pq);
    }
    *pq = NULL;
}

/* @brief 
   Controlla che le dimensioni della coda siano adeguate e agisce se non lo sono
*/
_Bool check_size(CharQueueADT q){
    if(q->size == q->capacity){
        //L'array e' completamente pieno, ho bisogno di altro spazio
        //Alloco un nuovo array di dimensioni doppie
        char* newA = malloc(sizeof(char)*(q->capacity*2));

        if(newA){
            //Copio il vecchio array nel nuovo array
            int p;
            for (size_t i = 0; i < q->size; i++){
                p = (q->front + i) % q->capacity; //Calcolo l'indice equivalente
                newA[i] = q->a[p];
            }

            //Sostituisco il vecchio array con il nuovo array
            free(q->a);     //Libero la memoria occupata dal vecchio array
            q->a = newA;
            q->front = 0;
            q->rear = q->size;
            q->capacity *= 2;

            //Tutto e' andato bene
            return 1;
        }

        //Non sono riuscito ad allocare il nuovo array, operazione fallita
        return 0;
    } else if (q->size > INITIAL_CAPACITY && q->size <= (q->capacity/4)){
        //Solo un quarto dell'array e' occupato, posso recuperare dello spazio
        //Alloco un nuovo array con dimensione la meta'
        char* newA = malloc(sizeof(char)*(q->capacity/2));

        if(newA){
            //Copio il vecchio array nel nuovo array
            int p;
            for (size_t i = 0; i < q->size; i++){
                p = (q->front + i) % q->capacity; //Calcolo l'indice equivalente
                newA[i] = q->a[p];
            }
            
            //Sostituisco il vecchio array con il nuovo array
            free(q->a);     //Libero la memoria occupata dal vecchio array
            q->a = newA;
            q->front = 0;
            q->rear = q->size;
            q->capacity /= 2;

            //Tutto e' andato bene
            return 1;
        }

        //Non sono riuscito ad allocare il nuovo array, operazione fallita
        return 0;
    }

    //Le dimensioni dell'array sono gia' adeguate
    return 1;
}

/* @brief Aggiunge un elemento in fondo alla coda */
_Bool enqueue(CharQueueADT q, const char e) {
    if(q){
        if(q->size < q->capacity){
            q->a[q->rear++] = e;
            q->size++;

            q->rear %= q->capacity;

            //Controllo che l'array abbia ancora spazio a sufficienza
            //e lo raddopio se non basta
            if(check_size(q))
                return 1;
        }
    }

    return 0;
}

/* @brief Toglie e restituisce l'elemento in testa alla coda */
_Bool dequeue(CharQueueADT q, char* res) {
    if(!isEmpty(q)){
        *res = q->a[q->front++];
        q->size--;

        q->front %= q->capacity;

        //Controllo che l'array non abbia dimensioni esagerate
        //e lo dimezzo se e' troppo grande per recuperare memoria
        if(check_size(q))
            return 1;
    }

    return 0;
}

/* @brief Controlla se la coda è vuota */
_Bool isEmpty(CharQueueADT q) {
    if(q){
        if(q->size == 0)    
            return 1;
    }

    return 0; 
}

/* @brief Restituisce il numero degli elementi presenti nella coda */
int size(CharQueueADT q) {
    if(q)
        return q->size;
    return 0;
}

/* @brief Restituisce l'elemento nella posizione data (senza toglierlo) */
_Bool peek(CharQueueADT q, int position, char *res) {
    if(!isEmpty(q)){
        if(position < q->size){
            position = (q->front + position)%q->capacity;
            *res = q->a[position];
            return 1;
        }
    }
    return 0;
}

