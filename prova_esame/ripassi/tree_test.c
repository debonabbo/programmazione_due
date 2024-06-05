#include <stdio.h>
#include <stdlib.h>
#include "tree_rec.h"
// #include "tree_iter.h"

void osserva(Response res){
    if(res == ADDED){
        printf("ho aggiunto l'elemento\n");
    } else if (res == OVERWRITTEN){
        printf("ho sovrascritto un elemento\n");
    } else if(res == OUT_OF_MEMORY){
        printf("la memoria era piena\n");
    } else {
        printf("hai inserito un carattere sbagliato\n");
    }
}

void stampa_albero(IntTree node, int level) {
  if (node == NULL) {
    return;
  }

  level++;

  stampa_albero(node->right, level);

  for (int i = 0; i < level - 1; i++) {
    printf("  ");
  }

  printf("%d\n", node->data);

  stampa_albero(node->left, level);
}

int main(){
    // printf("Test iterativo:\n");

    printf("Test ricorsivo:\n");
    IntTree a = malloc(sizeof(struct intTreeNode));
    IntTree b = malloc(sizeof(struct intTreeNode));
    IntTree c = malloc(sizeof(struct intTreeNode));
    IntTree d = malloc(sizeof(struct intTreeNode));
    IntTree e = malloc(sizeof(struct intTreeNode));
    IntTree f = malloc(sizeof(struct intTreeNode));
    IntTree g = malloc(sizeof(struct intTreeNode));
    IntTree h = malloc(sizeof(struct intTreeNode));

    a->data = 1;
    b->data = 2;
    c->data = 3;
    d->data = 4;

    a->left = 0;
    a->right = 0;
    b->left = a;
    b->right = d;
    c->left = 0;
    c->right = 0;
    d->left = c;
    d->right = 0;

    printf("Inizio l'inserimento:\n");
    Response resa = put(&b, "LL", 0);
    Response resb = put(&b, "LR", 7);
    Response resc = put(&b, "RL", 12);

    printf("Osservo resa: ");
    osserva(resa);
    printf("Osservo resb: ");
    osserva(resb);
    printf("Osservo resc: ");
    osserva(resc);

    a->left = 0;
    a->right = b;
    b->left = c;
    b->right = 0;
    c->left = 0;
    c->right = 0;

    d->left = 0;
    d->right = e;
    e->left = f;
    e->right = 0;
    f->left = 0;
    f->right = g;
    g->left = h;
    g->right = 0;
    h->left = 0;
    h->right = 0;

    a->data = 1;
    b->data = 2;
    c->data = 3;
    d->data = 1;
    e->data = 2;
    f->data = 3;
    g->data = 4;
    h->data = 5;

    if(isPruning(d, a)){
        printf("L'albero a e' una potatura dell'albero d.\n");
    } else {
        printf("L'albero a NON e' una potatura dell'albero d.\n");
    }

    printf("\nAlbero a:\n");
    stampa_albero(a, 0);
    printf("\nAlbero d:\n");
    stampa_albero(d, 0);

    free(a);
    free(b);
    free(c);
    free(d);
    free(e);

    return 0;
}