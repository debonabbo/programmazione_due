#include <stdio.h>

typedef struct charTreeNode CharTreeNode, *CharTree;

struct charTreeNode {
    CharTree left;
    char data;
    CharTree right;
};

/**
* @brief Dato un albero binario restituisce:
* il numero di foglie (se l’albero è vuoto restituisce 0).
*/
int nfoglie(CharTree tree){
    if(tree){
        if(!tree->left && !tree->right)
            return 1;

        return nfoglie(tree->left) + nfoglie(tree->right);
    }
    return 0;
}

int main(){

    return 0;
}