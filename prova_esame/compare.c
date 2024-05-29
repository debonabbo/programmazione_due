#include <stdlib.h>
#include <stdio.h>

_Bool str_equal(char* s1, char* s2){
    while(*s1 == *s2 && *s1 != '\0' && *s2 != '\0') { s1++; s2++; }
    return (*s1 == *s2);
}

int compare(char* fname1, char* fname2, long* line, long* charpos){
    FILE *f1, *f2;
    _Bool eq = 1;

    f1 = fopen(fname1, "r");
    if(!f1)
        return -1;
    f2 = fopen(fname2, "r");
    if(!f2){
        fclose(f1);
        return -1;
    }

    char* buffer1 = malloc(sizeof(char) * 256);
    char* buffer2 = malloc(sizeof(char) * 256);

    _Bool stop = 0;
    while(eq && !stop){
        char* res1 = fgets(buffer1, 256, f1);
        char* res2 = fgets(buffer2, 256, f2);

        if(res1 == NULL && res2 == NULL)
            stop = 1;
        else if(res1 != NULL && res2 != NULL)
            eq = str_equal(buffer1, buffer2);
        else
            eq = 0;
    }

    free(buffer1);
    free(buffer2);

    fclose(f1);
    fclose(f2);

    return eq;
}

int main(){
    long line, charpos;
    int res = compare("a.txt", "b.txt", &line, &charpos);

    if(res == -1)
        printf("Errore nell'aprire i file.\n");
    else if(res == 0)
        printf("I file sono diversi :(\n");
    else
        printf("I file sono uguali :)\n");

    return 0;
}