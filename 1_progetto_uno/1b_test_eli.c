#include <stdio.h>
#include "1b_eli.c"

struct Test
{
    char *s;
    unsigned short b;
    int res;
    int num;
};


int main(){
    struct Test tests[18];

    tests[0].s = "0";   //Deve diventare 0
    tests[0].b = 10;
    tests[0].res = 1;
    tests[0].num = 0;

    tests[1].s = "";    //Non e' valido
    tests[1].b = 10;
    tests[1].res = 0;
    tests[1].num = 0;

    tests[2].s = " ";   //Non e' valido
    tests[2].b = 10;
    tests[2].res = 0;
    tests[2].num = 0;

    tests[3].s = " 0";  //Deve diventare 0
    tests[3].b = 10;
    tests[3].res = 1;
    tests[3].num = 0;

    tests[4].s = " 1";  //Deve diventare 1 
    tests[4].b = 10;
    tests[4].res = 1;
    tests[4].num = 1;

    tests[5].s = "A";  //Deve diventare 10
    tests[5].b = 16;  // in base 16
    tests[5].res = 1;
    tests[5].num = 10;

    tests[6].s = "-A";  //Deve diventare -10
    tests[6].b = 16;
    tests[6].res = 1;
    tests[6].num = -10;

    tests[7].s = "-1";  //Deve diventare -1
    tests[7].b = 33;
    tests[7].res = 1;
    tests[7].num = -1;

    tests[8].s = "Z";  //Deve diventare 35
    tests[8].b = 36;
    tests[8].res = 1;
    tests[8].num = 35;

    tests[9].s = "Z";  //Fuori range (lettera massima W)
    tests[9].b = 33;
    tests[9].res = 0;  //restituisce 0
    tests[9].num = 0;

    tests[10].s = "*()";  //Non valido
    tests[10].b = 33;
    tests[10].res = 0;
    tests[10].num = 0;

    tests[11].s = "a";  //Non valido
    tests[11].b = 10;
    tests[11].res = 0;
    tests[11].num = 0;

    tests[12].s = "12c";  //Deve valere 12
    tests[12].b = 10;
    tests[12].res = 1;
    tests[12].num = 12;

    tests[13].s = "+B";  //Deve diventare 11
    tests[13].b = 16;
    tests[13].res = 1;
    tests[13].num = 11;


    tests[14].s = "\n+B";  //Deve diventare 11
    tests[14].b = 16;
    tests[14].res = 1;
    tests[14].num = 11;

    tests[15].s = "36";  //Non valido
    tests[15].b = 37;
    tests[15].res = 0;
    tests[15].num = 0;

    tests[16].s = "127";  //Non valido
    tests[16].b = 7;
    tests[16].res = 1;
    tests[16].num = 9;

    tests[17].s = "10";  //Non valido
    tests[17].b = 12;
    tests[17].res = 1;
    tests[17].num = 12;

    int num = 0;

    for (size_t i = 0; i < 18; i++)
    {
        if(stoub(tests[i].s, tests[i].b, &num) == tests[i].res &&
            tests[i].num == num){
            printf("Test %zu passato.\n", i);
        } else {
            printf("Test %zu NON PASSATO.\n", i);
        }
    }

    // int test = 0;
    // char *prova = "10";
    // stoub(prova, 12, &test);

    // printf("%d", test);

    return 0;
}