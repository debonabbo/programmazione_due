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
    struct Test tests[17];

    tests[0].s = "0";
    tests[0].b = 10;
    tests[0].res = 1;
    tests[0].num = 0;

    tests[1].s = "";
    tests[1].b = 10;
    tests[1].res = 0;
    tests[1].num = 0;

    tests[2].s = " ";
    tests[2].b = 16;
    tests[2].res = 0;
    tests[2].num = 0;

    tests[3].s = " 0";
    tests[3].b = 10;
    tests[3].res = 1;
    tests[3].num = 0;

    tests[4].s = " -3";
    tests[4].b = 10;
    tests[4].res = 1;
    tests[4].num = -3;

    tests[5].s = "B";
    tests[5].b = 16;
    tests[5].res = 1;
    tests[5].num = 11;

    tests[6].s = "-C";
    tests[6].b = 16;
    tests[6].res = 1;
    tests[6].num = -12;

    tests[7].s = "Z";
    tests[7].b = 36;
    tests[7].res = 1;
    tests[7].num = 35;

    tests[8].s = "Z";  //Fuori range, lettera massima X
    tests[8].b = 34;
    tests[8].res = 0;
    tests[8].num = 0;

    tests[9].s = ":-)";
    tests[9].b = 33;
    tests[9].res = 0;
    tests[9].num = 0;

    tests[10].s = "f";
    tests[10].b = 10;
    tests[10].res = 0;
    tests[10].num = 0;

    tests[11].s = "9r";
    tests[11].b = 10;
    tests[11].res = 1;
    tests[11].num = 9;

    tests[12].s = "+C";
    tests[12].b = 16;
    tests[12].res = 1;
    tests[12].num = 12;

    tests[13].s = "\nC";
    tests[13].b = 16;
    tests[13].res = 1;
    tests[13].num = 12;

    tests[14].s = "34";
    tests[14].b = -2;
    tests[14].res = 0;
    tests[14].num = 0;

    tests[15].s = "10";
    tests[15].b = 16;
    tests[15].res = 1;
    tests[15].num = 16;

    tests[16].s = "129";
    tests[16].b = 9;
    tests[16].res = 1;
    tests[16].num = 11;

    int num = 0;

    for (size_t i = 0; i < 17; i++)
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