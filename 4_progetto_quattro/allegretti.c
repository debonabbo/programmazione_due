#include "charQueueADT.h"

#include <stdlib.h>
#include <stdbool.h>

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



void arrayIncrease(CharQueueADT q){
    char *b=(char *)malloc(sizeof(char)*(q->capacity)*2);
    if(b != NULL){
        for(int i=0; i<q->size; i++){
            b[i%(q->capacity*2)]=q->a[i%q->capacity];
        }
        //char *c=q->a;
        q->a=b;
        q->capacity=q->capacity*2;
        //c=NULL;
        //free(b);
        //b=NULL;
        }
        return;
}

void arrayDecrease(CharQueueADT q){
    char *b=(char *)malloc(sizeof(char)*(q->capacity)/2);
    if(b!=NULL){
            for(int i=0; i<q->size; i++){
                b[i%(q->capacity/2)]=q->a[i%q->capacity];
            }
                //char *c=q->a;
            q->a=b;
            q->capacity=q->capacity*2;
            //free(b);
            //b=NULL;
            }
    return;
}

/* @brief Restituisce una coda vuota, se non trova memoria restituisce NULL */
CharQueueADT mkQueue() {
    CharQueueADT q=(CharQueueADT)malloc(sizeof(struct charQueue));
    if(q!=NULL){
        q->capacity=INITIAL_CAPACITY;
        q->a=(char *)malloc(sizeof(char)*INITIAL_CAPACITY);
        if(q->a!=NULL){
            q->size=0;
            q->rear=0;
            q->front=0;
            return q;
        }
        free(q);
    }
    return NULL;
    
}

/* @brief Distrugge la coda, recuperando la memoria */
void dsQueue(CharQueueADT *pq) {
    if(*pq!=NULL){
        free((*pq)->a);
        free(*pq);
        *pq=NULL;
        return;
    }
}

/* @brief Aggiunge un elemento in fondo alla coda */
_Bool enqueue(CharQueueADT q, const char e) {
    int ret=0;
    if(q!=NULL){
        if(q->size >= q->capacity){
            arrayIncrease(q);
            
        }
        q->a[(q->rear)%q->capacity]=e;
        q->rear=(q->rear+1)%q->capacity;
        q->size++;
        ret=1;
    }
    return ret;
}

/* @brief Toglie e restituisce l'elemento in testa alla coda */
_Bool dequeue(CharQueueADT q, char* res) {
    int ret=0;
    if(q!=NULL){
        if(q->size > 0){
            *res=q->a[q->front];
            q->front=(q->front+1)%q->capacity;
            q->size--;
            if(q->size==(q->capacity/4)){
                arrayDecrease(q);
            }
            ret=1;
        }
    }
    return ret;
}

/* @brief Controlla se la coda è vuota */
_Bool isEmpty(CharQueueADT q) {
    if(q->size==0)
        return 1;
    return 0;
}

/* @brief Restituisce il numero degli elementi presenti nella coda */
int size(CharQueueADT q) {
    return q->size;
}

/* @brief Restituisce l'elemento nella posizione data (senza toglierlo) */
_Bool peek(CharQueueADT q, int position, char *res) {
    int ret=0;
    if(q!=NULL && (position>=0 && position<q->size)){
        *res=q->a[(q->front+position)%q->capacity];
        ret=1;   
    }
    return ret;
}