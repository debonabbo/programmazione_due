#include <stdlib.h>
#include <stdio.h>
#include "tree_rec.h"

Response put(IntTree *treePtr, char *path, int e){
    if(!treePtr || !path)
        return ERROR;
    IntTree posizione = *treePtr;

    while((*path) != '\0' && posizione != 0){
        if((*path) == 'L'){
            posizione = posizione->left;
        } else if ((*path) == 'R'){
            posizione = posizione->right;
        } else {
            return ERROR;
        }
        path++;
    }

    if(posizione){
        posizione->data = e;
        return OVERWRITTEN;
    }

    posizione = malloc(sizeof(struct intTreeNode));

    if(!posizione)
        return OUT_OF_MEMORY;
    
    posizione->data = e;
    posizione->left = 0;
    posizione->right = 0;

    return ADDED;    
}

_Bool isPruning(IntTree tree, IntTree pruned){
    if(tree){
        if(!pruned){
            return 1;
        } else {
            if(tree->data == pruned->data){
                return isPruning(tree->left, pruned->left) &&
                        isPruning(tree->right, pruned->right);
            } else {
                return 0;
            }
        }
    } else if(!pruned)
        return 1;
    return 0;
}

void arbToArray_rec(IntTree tree, int** array){
    if(tree){
        *((*array)++) = tree->data;

        arbToArray_rec(tree->left, array);
        arbToArray_rec(tree->right, array);
    }
}

int* arbToArray(IntTree tree){
    int* array = malloc(sizeof(int) * 50);
    arbToArray_rec(tree, &array);

    return array;
}

ReportPtr minMaxLevel_rec(CharTree tree){
    return 0;
}