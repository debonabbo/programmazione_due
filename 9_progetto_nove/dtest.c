#include <stdio.h>
#include <stdlib.h>

#include "contactBook.h"

void stampa_menu(){
    printf("\n--------------------------------\n");
    printf("Azioni disponibili:\n");
    printf("0. Chiudi il programma.\n");
    printf("1. Crea una nuova rubrica.\n");
    printf("2. Inserisci un nuovo contatto.\n");
    printf("3. Salva la rubrica.\n");
    printf("--------------------------------\n");
    return;
}

ContactBookADTptr nuova_rubrica();
void nuovo_contatto(ContactBookADTptr);
void salva_rubrica(ContactBookADTptr);

int main(){
    ContactBookADTptr rubrica;

    char c = 'b';

    while(c != '0'){
        switch (c)
        {
            case 'b':
                printf("Benvenuto nella tua rubrica!");
                break;
            case '1':
                rubrica = nuova_rubrica();
                break;
            case '2':
                nuovo_contatto(rubrica);
                break;
            case '3':
                salva_rubrica(rubrica);
                break;
            default:
                break;
        }

        stampa_menu();
        printf("Seleziona un'azione: ");
        scanf(" %c", &c);
    }

    return 0;
}

ContactBookADTptr nuova_rubrica(){
    return mkCBook();
}

_Bool check_mem(char* n, char* c, char* m, char* u){
    if(n && c && m && u)
        return 1;

    free(n);
    free(c);
    free(m);
    free(u);
    return 0;
}

void nuovo_contatto(ContactBookADTptr rubrica){
    if(!rubrica){
        printf("ERRORE: Non hai una rubrica.\n");
        return;
    }

    char* nome    = malloc(sizeof(char) * 30);
    char* cognome = malloc(sizeof(char) * 30);
    char* mobile  = malloc(sizeof(char) * 30);
    char* url     = malloc(sizeof(char) * 30);

    if(!check_mem(nome, cognome, mobile, url)){
        printf("ERRORE: Hai finito la memoria.\n");
        return;
    }

    printf("Completa i campi seguenti:\n");
    printf("Nome: ");
    scanf("%s", nome);
    printf("Cognome: ");
    scanf("%s", cognome);
    printf("Mobile: ");
    scanf("%s", mobile);
    printf("Url: ");
    scanf("%s", url);

    ContactPtr contatto = mkContact(nome, cognome, mobile, url);
    if(contatto){
        if(cbook_add(rubrica, contatto)){
            printf("Contatto aggiunto correttamente!\n");
            return;
        }
    }

    printf("Operazione fallita, qualcosa e' andato storto :(\n");
    return;
}

void str_append(char* s, char* a){
    while(*s != '\0')
        s++;
    while(*a != '\0')
        *(s++) = *(a++);
    *s = '\0';
}

void salva_rubrica(ContactBookADTptr rubrica){
    if(!rubrica){
        printf("ERRORE: Non hai una rubrica.\n");
        return;
    }

    char nome[30] = "";
    printf("Inserisci il nome della rubrica: ");
    scanf("%s", nome);
    str_append(nome, ".csv");
    FILE* file = fopen(nome, "w");

    if(cbook_dump(rubrica, file))
        printf("Operazione eseguita correttamente!\n");
    else
        printf("Operazione fallita :(\n");

    fclose(file);
    return;
}