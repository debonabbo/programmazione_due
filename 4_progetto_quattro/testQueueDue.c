#include "charQueueADT.c"
#include <stdio.h>

int main(){
    CharQueueADT cqPt = mkQueue();

    if(!cqPt)
        return 0;

    printf("Lista creata correttamente.\n");

    if(enqueue(cqPt, 'c'))
        printf("Lettera 'c' inserita correttamente.\n");

    printf("La lista e' lunga: %d.\n", size(cqPt));
    

    char e;

    if(peek(cqPt, 0, &e))
        printf("L'elemento in posizione 0 e': %c.\n", e);


    if(!isEmpty(cqPt)){
        printf("Primo elemento della lista: %c\n", cqPt->front->data);
        printf("Ultimo elemento della lista: %c\n", cqPt->rear->data);
    }
    printf("----------------------------\n");
    if(dequeue(cqPt, &e))
        printf("Il primo elemento era: %c.\n", e);
    printf("La lista e' lunga: %d.\n", size(cqPt));
    
    if(!isEmpty(cqPt)){
        printf("Primo elemento della lista: %c\n", cqPt->front->data);
        printf("Ultimo elemento della lista: %c\n", cqPt->rear->data);
    }
    printf("----------------------------\n");


    dsQueue(&cqPt);
    printf("Coda distrutta correttamente.\n");

    return 0;
}