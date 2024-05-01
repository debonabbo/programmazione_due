#include "charQueueADT.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct listNode ListNode, *ListNodePtr;
struct listNode {
   char data;
   ListNodePtr next;
};

struct charQueue {
    ListNodePtr front; /* Punta al primo nodo della lista, che contiene l'elemento in testa alla coda, se la coda è vuota vale NULL */
    ListNodePtr rear; /* Punta all'ultimo nodo della lista, che contiene l'elemento in fondo alla coda, se la coda è vuota vale NULL */
    
    /* aggiungere eventuali altre variabili per ottenere una implementazione più efficiente */
    int length;
};

/* @brief Restituisce una coda vuota, se non trova memoria restituisce NULL */
CharQueueADT mkQueue() {
    CharQueueADT queuePointer = malloc(sizeof(struct charQueue));

    if(queuePointer){
        queuePointer->front = NULL;
        queuePointer->rear = NULL;
        queuePointer->length = 0;

        return queuePointer;
    }

    return NULL;
}

/* @brief Distrugge la coda, recuperando la memoria */
void dsQueue(CharQueueADT *pq) {
    free(*pq);
    *pq = NULL;

    return; 
}

/* @brief Aggiunge un elemento in fondo alla coda */
_Bool enqueue(CharQueueADT q, const char e) {
    ListNodePtr nodePtr = malloc(sizeof(struct listNode));

    if(nodePtr){
        nodePtr->data = e;
        nodePtr->next = NULL;

        if(isEmpty(q)){
            //La lista e' vuota
            q->front = nodePtr;         //Imposto l'elemento come primo
            q->front->next = nodePtr;   //E come ultimo
            q->rear = nodePtr;
        } else {
            //Aggiungo semplicemente l'elemento al fondo
            q->rear->next = nodePtr;
            q->rear = nodePtr;
        }

        q->length++;

        return 1;
    }

    return 0;
}

/* @brief Toglie e restituisce l'elemento in testa alla coda */
_Bool dequeue(CharQueueADT q, char* res) {
    if(!isEmpty(q)){
        *res = q->front->data;
        
        if(size(q) == 1){
            //Rimuovo l'ultimo elemento rimasto
            free(q->front);
            q->front = NULL;
            q->rear = NULL;
        } else {
            ListNodePtr frontNext = q->front->next;
            free(q->front);
            q->front = frontNext;
        }
        q->length--;

        return 1;
    }

    return 0;
}

/* @brief Controlla se la coda è vuota */
_Bool isEmpty(CharQueueADT q) {
    if(q->front == NULL || q->rear == NULL)
        return 1; 

    return 0;
}

/* @brief Restituisce il numero degli elementi presenti nella coda */
int size(CharQueueADT q) {
    if(q){
        return q->length;
    }

    return 0;
}

/* @brief Restituisce l'elemento nella posizione data (senza toglierlo) */
_Bool peek(CharQueueADT q, int position, char *res) {
    if(q){
        ListNodePtr elementPt = q->front;

        for (int i = 0; i < q->length; i++){
            if(i == position){
                *res = elementPt->data;
                return 1;
            }

            elementPt = elementPt->next;
        }
    }
    return 0;
}


