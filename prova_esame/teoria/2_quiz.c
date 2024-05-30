#include <stdio.h>
#include <stdlib.h>

typedef struct intNode IntNode, *IntList;
struct intNode {
    int data;
    IntList next;
};

// void reverse_old (IntList* lsPtr) {
//     if(!lsPtr || !*lsPtr)
//         return;

//     IntList a, b;
//     int temp;
    
//     size_t size = 0;
    
//     for(a = *lsPtr; a != NULL; a = a->next) { size++; }

//     //printf("SIZE: %zu\n", size);
    
//     a = *lsPtr;
//     for(size_t i = 0; i < (size-i); i++){
//         b = *lsPtr;
//         for(size_t j = 0; j < (size-1-i); j++){
//             b = b->next;
//         }
//         printf("Inverto %d e %d\n", a->data, b->data);
//         temp = a->data;
//         a->data = b->data;
//         b->data = temp;
//         a = a->next;
//     }
    
//     return;
// }

void reverse(IntList* plst){
    if(!plst || !*plst)
        return;

    IntList prev = NULL, next = NULL, curr = *plst;

    while(curr != NULL){
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    *plst = prev;
    return;
}

IntList swap_rec(IntList prev, IntList curr){
    if(!curr){
        return prev;
    } else {
        IntList next = curr->next;
        curr->next = prev;

        return swap_rec(curr, next);
    }
}

void reverse_rec(IntList* plst){
    *plst = swap_rec(NULL, *plst);
    return;
}

int main(){
    printf("Inizio\n");

    reverse(NULL);

    IntList primo, secondo, terzo, quarto, quinto;
    primo = malloc(sizeof(struct intNode));
    secondo = malloc(sizeof(struct intNode));
    terzo = malloc(sizeof(struct intNode));
    quarto = malloc(sizeof(struct intNode));
    quinto = malloc(sizeof(struct intNode));
    primo->data = 1;
    primo->next = NULL;

    reverse(&primo);

    primo->next = secondo;
    secondo->data = 2;
    secondo->next = terzo;
    terzo->data = 3;
    terzo->next = quarto;
    quarto->data = 4;
    quarto->next = quinto;
    quinto->data = 5;
    quinto->next = NULL;

    printf("Prima: ");
    for (IntList a = primo; a != NULL; a = a->next){
        printf("%d ", a->data);
    }
    printf("\n");

    reverse(&primo);
    
    printf("Dopo: ");
    for (IntList a = primo; a != NULL; a = a->next){
        printf("%d ", a->data);
    }
    printf("\n");

    reverse_rec(&primo);

    printf("Dopo ricorsiva: ");
    for (IntList a = primo; a != NULL; a = a->next){
        printf("%d ", a->data);
    }
    printf("\n");

    free(primo);
    free(secondo);
    free(terzo);
    free(quarto);
    free(quinto);
    return 0;
}