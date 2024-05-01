#include <stdio.h>

struct test
{
    int id;
    int numero;
};

void printTest(struct test pluto){
    int idPluto = pluto.id;
    int numeroPluto = pluto.numero;

    printf("Id: %d, numero: %d\n", idPluto, numeroPluto);
}

void printTestPointer(const struct test *pluto){
    int idPluto = pluto->id;
    int numeroPluto = pluto->numero;

    printf("Id: %d, numero: %d\n", idPluto, numeroPluto);
}


int main(){
    struct test prova;
    prova.id = 1;
    prova.numero = 111;

    struct test prova2;
    prova2.id = 2;
    prova2.numero = 222;

    struct test prova3;
    prova3.id = 3;
    prova3.numero = 333;

    printTest(prova);
    printTest(prova2);
    printTestPointer(&prova3);

    return 0;
}