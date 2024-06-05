#ifndef TREE_ITER_H
#define TREE_ITER_H

enum report { ADDED, OVERWRITTEN, OUT_OF_MEMORY };

typedef enum response Response;

typedef struct intTreeNode IntTreeNode, *IntTree; 
struct intTreeNode {  
   IntTree left;
   int data;
   IntTree right;
}; 

/**
* @brief Mette nell'albero l'elemento `e` nella  posizione identificata da `path` (una stringa di caratteri ``L '' per left e ``R'' per right). Ovvero:
*  - se `path` porta a un nodo, assegna `e` al campo `data`di quel nodo
*  - se `path` porta fuori dall'abero, inserisce come figlio della foglia da cui è usciti dallalbero un nuovo nodo che contiene `e`.
* Restituisce:
* - ADDED se ha aggiunto un nuovo nodo, 
* - OVERWRITTEN se ha modificato nodo esistente, 
* - OUT_OF_MEMORY se la malloc fallisce,
* - ERROR se `path`contiene un carattere diverso da `L`o `R` prima di uscire dall'albero 
*/
Response putIter(IntTree *treePtr, char *path, int e);

/**
* @brief Controlla se il secondo albero è una potatura del primo
*/
_Bool isPruningIter(IntTree tree, IntTree pruned);

/**
* @brief Dato un ARB con restituisce un array che contiene tutti gli elementi dell'ARB in un ordine tale che, 
* se gli elementi sono tutti distinti, allora
* inserendoli in quell'ordine nell'ARB vuoto si ricostruisce l'ARB originale.
*/
int[] arbToArrayIter(IntTree tree);


typedef struct report Report, *ReportPtr;

struct report {  
    int min;
    int max;
}; 
 
typedef struct charTreeNode CharTreeNode, *CharTree; 

struct charTreeNode {  
    CharTree left;
    char data;
    CharTree right;
};

/**
* @brief Dato un albero binario restituisce le profondità minima e massima delle sue foglie
* (considerate entrambe -1 se l’albero è vuoto).
*/
ReportPtr minMaxLevel_iter(CharTree tree);

#endif
