#include <stdio.h>
#include <stdlib.h>

#include "contactBook.h"

void stampa_menu(){
    printf("\n--------------------------------\n");
    printf("Azioni disponibili:\n");
    printf("0. Chiudi il programma.\n");
    printf("1. Crea una nuova rubrica.\n");
    printf("2. Inserisci un nuovo contatto.\n");
    printf("3. Ricerca un contatto.\n");
    printf("4. Rimuovi un contatto.\n");
    printf("5. Salva la rubrica.\n");
    printf("6. Carica una rubrica.\n");
    printf("7. Visualizza la rubrica.\n");
    printf("--------------------------------\n");
    return;
}

ContactBookADTptr nuova_rubrica();
void nuovo_contatto(ContactBookADTptr);
void cerca_contatto(ContactBookADTptr);
void cancella_contatto(ContactBookADTptr);
void salva_rubrica(ContactBookADTptr);
ContactBookADTptr carica_rubrica(ContactBookADTptr);
void visualizza_rubrica(ContactBookADTptr);

int main(){
    ContactBookADTptr rubrica = NULL;

    char c = 'b';

    while(c != '0'){
        printf("\033[2J");      //Pulisci lo schermo
        printf("\033[0;0H");    //Setta il cursore alla posizione 0
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
                cerca_contatto(rubrica);
                break;
            case '4':
                cancella_contatto(rubrica);
                break;
            case '5':
                salva_rubrica(rubrica);
                break;
            case '6':
                rubrica = carica_rubrica(rubrica);
                break;
            case '7':
                visualizza_rubrica(rubrica);
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

    // variabili temporanee nello stack
    char surname_temp[25];
    char name_temp[25];
    char mobile_temp[25];
    char url_temp[25];

    printf("Completa i campi seguenti:\n");
    printf("Nome: ");
    scanf(" %24[0-9a-zA-Z ]", name_temp);
    printf("Cognome: ");
    scanf(" %24[0-9a-zA-Z ]", surname_temp);
    printf("Mobile: ");
    scanf(" %24[0-9a-zA-Z+ ]", mobile_temp);
    printf("Url: ");
    scanf(" %24[0-9a-zA-Z.@ ]", url_temp);
    
    // variabili effettive nell'heap (alloco solo il necessario)
    char* surname = malloc(sizeof(char)*(str_len(surname_temp)+1));
    char* name = malloc(sizeof(char)*(str_len(name_temp)+1));
    char* mobile = malloc(sizeof(char)*(str_len(mobile_temp)+1));
    char* url = malloc(sizeof(char)*(str_len(url_temp)+1));

    if(!check_mem(name, surname, mobile, url)){
        printf("ERRORE: Hai finito la memoria.\n");
        return;
    }

    str_copy(surname_temp, surname);
    str_copy(name_temp, name);
    str_copy(mobile_temp, mobile);
    str_copy(url_temp, url);

    ContactPtr contatto = mkContact(name, surname, mobile, url);
    if(contatto){
        if(cbook_add(rubrica, contatto)){
            printf("Contatto aggiunto correttamente!\n");
            return;
        }
    }

    printf("Operazione fallita, qualcosa e' andato storto :(\n");
    return;
}

void stampa_contatto(ContactPtr contatto){
    printf("+");
    for (size_t i = 0; i < 80; i++) printf("-");
    printf("+\n");
    
    printf("| %15s | %15s | %15s | %24s |\n",   
            getName(contatto), getSurname(contatto), 
            getMobile(contatto), getUrl(contatto));

    printf("+");
    for (size_t i = 0; i < 80; i++) printf("-");
    printf("+\n");
    return;
}

void cerca_contatto(ContactBookADTptr rubrica){
    if(!rubrica){
        printf("ERRORE: Non hai una rubrica.\n");
        return;
    }

    char nome[30], cognome[30];
    printf("RICERCA\nNome: ");
    scanf(" %29[0-9a-zA-Z ]", &nome);
    printf("Cognome: ");
    scanf(" %29[0-9a-zA-Z ]", &cognome);

    ContactPtr risultato = cbook_search(rubrica, nome, cognome);

    if(risultato){
        printf("Contatto trovato:\n");
        stampa_contatto(risultato);
        printf("\n");
    } else {
        printf("Nessun risultato :(\n");
    }

    return;
}

void cancella_contatto(ContactBookADTptr rubrica){
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

ContactBookADTptr carica_rubrica(ContactBookADTptr oldrubrica){
    char nome[30] = "";
    printf("Inserisci il nome della rubrica: ");
    scanf("%s", nome);
    str_append(nome, ".csv");
    FILE* file = fopen(nome, "r");
    ContactBookADTptr newrubrica = cbook_load(file);

    if(newrubrica)
        printf("Operazione eseguita correttamente!\n");
    else
        printf("Operazione fallita :(\n");

    fclose(file);

    if(oldrubrica)
        dsCBook(&oldrubrica);

    return newrubrica;
}

void visualizza_rubrica(ContactBookADTptr rubrica){
    if(!rubrica){
        printf("ERRORE: Non hai una rubrica.\n");
        return;
    }

    Contact** elenco_contatti = cbook_toArray(rubrica);
    if(!elenco_contatti)
        return;

    int size = cbook_size(rubrica);

    printf("\n");
    // printf("╔═════════════════════════════════════╗\n");
    // printf("║              RUBRICA                ║\n");
    printf("+");
    for (size_t i = 0; i < 80; i++) printf("-");
    printf("+\n");
    printf("|");
    for (size_t i = 0; i < 36; i++) printf(" ");
    printf("RUBRICA ");
    for (size_t i = 0; i < 36; i++) printf(" ");
    printf("|\n");
    printf("|");
    for (size_t i = 0; i < 80; i++) printf(" ");
    printf("|\n");
    for (int i = 0; i < size; i++){
        stampa_contatto(elenco_contatti[i]);
    }
    printf("|");
    for (size_t i = 0; i < 80; i++) printf(" ");
    printf("|\n");
    printf("+");
    for (size_t i = 0; i < 80; i++) printf("-");
    printf("+\n");
    // printf("╚═════════════════════════════════════╝\n");
    
    free(elenco_contatti);
}
