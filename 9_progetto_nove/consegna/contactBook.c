#include "contactBook.h"
#include "sortedSetADT.h"

/**
 Un tipo di dato per una rubrica di contatti
*/
struct contactBookADT {
    SortedSetADTptr contacts; // Tutto quello che serve è già in questa struttura
};

void stampaContact(void* elem) {
    ContactPtr contact = (ContactPtr)elem;
    printf("%s %s: %s (%s)", getName(contact), getSurname(contact), getMobile(contact), getUrl(contact));
}

int contact_cmp(void* c1, void* c2) {
    return cmpContact((ContactPtr)c1, (ContactPtr)c2);
}

// restituisce una rubrica vuota, NULL se errore
ContactBookADTptr mkCBook() {
    ContactBookADTptr newcbook = malloc(sizeof(struct contactBookADT));

    if(newcbook){
        newcbook->contacts = mkSSet(contact_cmp);

        if(newcbook->contacts){
            return newcbook;
        }
    }

    return NULL;
}

// distrugge la rubrica, recuperando la memoria, false se errore
_Bool dsCBook(ContactBookADTptr* book) {
    if(book && *book){
        dsSSet(&(*book)->contacts);
        free(*book);
        *book = NULL;
        return true;
    }
    return false;
}

// controlla se la rubrica e' vuota, -1 se NULL
int isEmptyCBook(const ContactBookADT* book) {
    if(book){
        if(sset_size(book->contacts) > 0){
            return 0;
        }

        return 1;
    }
    return -1;
}

// restituisce il numero di contatti presenti nella rubrica, -1 se NULL
int cbook_size(const ContactBookADT* book) {
    if(book){
       return sset_size(book->contacts);
    }
    return -1;
}

// aggiunge un contatto alla rubrica (restituisce false se l'elemento era gia' presente, true altrimenti)
_Bool cbook_add(ContactBookADTptr book, ContactPtr cnt) {
    if(book && cnt){
        return sset_add(book->contacts, cnt);
    }
    return false;
}

// toglie un elemento all'insieme (restituisce false se l'elemento non era presente, true altrimenti)
_Bool cbook_remove(ContactBookADTptr book, char* name, char* surname) {
    if(book && name && surname){
        // contatto utilizzato per la ricerca
        ContactPtr contatto_temp = mkContact(name, surname, "", "");
        
        if(contatto_temp){
            // leggo il contatto originale per liberare la memoria allocata
            ContactPtr contatto = sset_search(book->contacts, contatto_temp);
            if(contatto){
                _Bool ret = sset_remove(book->contacts, contatto_temp);
                // libero la memoria allocata
                // if(getSurname(contatto))
                //     free(getSurname(contatto));
                // if(getName(contatto))
                //     free(getName(contatto));
                // if(getMobile(contatto))
                //     free(getMobile(contatto));
                // if(getUrl(contatto))
                //     free(getUrl(contatto));
                return ret;
            }
            dsContact(&contatto_temp);
        }
    }
    return false;
}

// restituisce un puntatore al contatto con dato nome e cognome (può essere usata per accedere o modificare il numero e url del contatto), NULL se non presente
ContactPtr cbook_search(const ContactBookADT* book, char* name, char* surname) {
    if(book && name && surname){
        ContactPtr contatto_temp = mkContact(name, surname, "", "");
        ContactPtr contatto = sset_search(book->contacts, contatto_temp);
        dsContact(&contatto_temp);
        if(contatto)
            return contatto;
    }
    return NULL;
}

// estrae la parte iniziale della stringa fino al carattere SEP
void str_extract(char** str_in, char* str_out, char sep){
    if(str_in && *str_in && str_out){
        while((**str_in) != '\0' && (**str_in) != sep){
            *(str_out++) = *((*str_in)++);
        }
        *(str_out) = '\0';
        (*str_in)++;
    }
}

size_t str_len(char* str){
    size_t len = 0;
    while((*str) != '\0'){
        str++;
        len++;
    }
    return len;
}
void str_copy(char* source, char* dest){
    while((*source) != '\0')
        *(dest++) = *(source++);
    *dest = '\0';
}

// carica una rubrica da file, NULL se errore
ContactBookADTptr cbook_load(FILE* fin) {
    if(fin){
        // alloco buffer per la lettura temporanea
        char* buffer = malloc(sizeof(char) * 101);
        ContactBookADTptr cbook = mkCBook();
        if(cbook && buffer){
            while(fgets(buffer, 101, fin) != NULL){
                char* buf_temp = buffer;

                // variabili temporanee nello stack
                char surname_temp[25];
                char name_temp[25];
                char mobile_temp[25];
                char url_temp[25];
                
                str_extract(&buf_temp, surname_temp, ',');
                str_extract(&buf_temp, name_temp, ',');
                str_extract(&buf_temp, mobile_temp, ',');
                str_extract(&buf_temp, url_temp, '\n');
                
                // variabili effettive nell'heap (alloco solo il necessario)
                char* surname = malloc(sizeof(char)*(str_len(surname_temp)+1));
                char* name = malloc(sizeof(char)*(str_len(name_temp)+1));
                char* mobile = malloc(sizeof(char)*(str_len(mobile_temp)+1));
                char* url = malloc(sizeof(char)*(str_len(url_temp)+1));

                if(!surname || !name || !mobile || !url)
                    return NULL;

                str_copy(surname_temp, surname);
                str_copy(name_temp, name);
                str_copy(mobile_temp, mobile);
                str_copy(url_temp, url);

                ContactPtr newcontact = mkContact(name, surname, mobile, url);
                if(newcontact){
                    cbook_add(cbook, newcontact);
                }
            }
            free(buffer);

            return cbook;
        }
    }
    return NULL;
}

// salva una rubrica su file, false se errore
_Bool cbook_dump(const ContactBookADT* book, FILE* fout) {
    if(book && fout){
        ContactPtr* rubrica = (ContactPtr*)sset_toArray(book->contacts);
        int size = sset_size(book->contacts);
        
        for (size_t i = 0; i < size; i++){
            fprintf(fout, "%s", getSurname(rubrica[i]));
            fprintf(fout, ",%s", getName(rubrica[i]));
            fprintf(fout, ",%s", getMobile(rubrica[i]));
            fprintf(fout, ",%s", getUrl(rubrica[i]));
            printf("\n");
        }

        free(rubrica);
        return true;
    }
    return false;
}

Contact** cbook_toArray(const ContactBookADT* book){
    if(book){
        return (Contact**)sset_toArray(book->contacts);
    }

    return NULL;
}

void cbook_optimize_rec(ContactBookADT* book, Contact** array, 
size_t left, size_t right){
    if(right - left == 0){
        cbook_add(book, array[left]);
    } else if(right - left == 1){
        cbook_add(book, array[left]);
        cbook_add(book, array[right]);
    } else {
        size_t center = ((right-left)/2)+left;

        cbook_add(book, array[center]);

        cbook_optimize_rec(book, array, left, center-1);
        cbook_optimize_rec(book, array, center+1, right);
    }
}


void cbook_optimize(ContactBookADT* book){
    if(book){
        Contact** elenco_contatti = cbook_toArray(book);
        if(!elenco_contatti)
            return;

        int size = cbook_size(book);

        free(book->contacts);
        book->contacts = mkSSet(contact_cmp);

        cbook_optimize_rec(book, elenco_contatti, 0, size-1);
    }
}

void stampa_menu(){
    printf("\n");
    printf("\t+--------------------------------+\n");
    printf("\t|       Azioni disponibili:      |\n");
    printf("\t| 0. Chiudi il programma.        |\n");
    printf("\t| 1. Crea una nuova rubrica.     |\n");
    printf("\t| 2. Inserisci un nuovo contatto.|\n");
    printf("\t| 3. Cerca un contatto.          |\n");
    printf("\t| 4. Salva la rubrica.           |\n");
    printf("\t| 5. Carica una rubrica.         |\n");
    printf("\t| 6. Visualizza la rubrica.      |\n");
    printf("\t+--------------------------------+\n");
    printf("\n");
    return;
}

// variabili utilizzate per la stampa della rubrica
_Bool UpdatePrintParams = 1;
int MaxLenName = 0;
int MaxLenSurname = 0;
int MaxLenMobile = 0;
int MaxLenUrl = 0;

ContactBookADTptr nuova_rubrica();
void nuovo_contatto(ContactBookADTptr);
void visualizza_contatto(ContactBookADTptr);
void cancella_contatto(ContactBookADTptr, char*, char*);
void modifica_contatto(ContactBookADTptr, ContactPtr);
void ottimizza_rubrica(ContactBookADTptr);
void salva_rubrica(ContactBookADTptr);
ContactBookADTptr carica_rubrica(ContactBookADTptr);
void visualizza_rubrica(ContactBookADTptr);

int main(){
    ContactBookADTptr rubrica = NULL;

    char c = 'b';

    while(c != '0'){
        printf("\033[2J");      //Pulisce lo schermo
        printf("\033[0;0H");    //Setta il cursore alla posizione 0
        switch (c)
        {
            case 'b':
                printf("Benvenuto nella tua rubrica!\n");
                break;
            case '1':
                rubrica = nuova_rubrica();
                break;
            case '2':
                nuovo_contatto(rubrica);
                break;
            case '3':
                visualizza_contatto(rubrica);
                break;
            case '4':
                salva_rubrica(rubrica);
                break;
            case '5':
                rubrica = carica_rubrica(rubrica);
                break;
            case '6':
                visualizza_rubrica(rubrica);
                break;
            default:
                printf("Azione non valida. :(.\n");
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

            // aggiorno le variabili usate per mostrare la rubrica
            if(str_len(name) > MaxLenName)  
                MaxLenName = str_len(name);
            if(str_len(surname) > MaxLenSurname) 
                MaxLenSurname = str_len(surname);
            if(str_len(mobile) > MaxLenMobile)  
                MaxLenMobile = str_len(mobile);
            if(str_len(url) > MaxLenUrl)  
                MaxLenUrl = str_len(url);
            return;
        }
    }

    printf("Operazione fallita, qualcosa e' andato storto :(\n");
    return;
}

void stampa_contatto(ContactPtr contatto, _Bool inTabella){
    size_t larghezza_rubrica = 13 + MaxLenName + MaxLenSurname + MaxLenMobile +
                                MaxLenUrl;
    printf("+");
    for (size_t i = 0; i < (larghezza_rubrica-2); i++) printf("-");
    printf("+\n");
    
    printf("| %-*s | %-*s | %-*s | %-*s |\n",   
            MaxLenName, getName(contatto), 
            MaxLenSurname, getSurname(contatto), 
            MaxLenMobile, getMobile(contatto), 
            MaxLenUrl, getUrl(contatto));

    if(!inTabella){
        printf("+");
        for (size_t i = 0; i < (larghezza_rubrica-2); i++) printf("-");
        printf("+\n");
    }
    return;
}

void visualizza_contatto(ContactBookADTptr rubrica){
    if(!rubrica){
        printf("ERRORE: Non hai una rubrica.\n");
        return;
    }

    char nome[30], cognome[30];
    printf("RICERCA\nNome: ");
    scanf(" %29[0-9a-zA-Z ]", nome);
    printf("Cognome: ");
    scanf(" %29[0-9a-zA-Z ]", cognome);

    ContactPtr risultato = cbook_search(rubrica, nome, cognome);

    if(risultato){
        stampa_contatto(risultato, 0);
        char c;
        printf("\n0. MENU' PRINCIPALE\t1. MODIFICA\t2.ELIMINA");
        printf("\nSeleziona un'azione: ");
        scanf(" %c", &c);

        if(c == '1')
            modifica_contatto(rubrica, risultato);
        else if(c == '2')
            cancella_contatto(rubrica, nome, cognome);
    } else {
        printf("Nessun risultato :(\n");
    }

    return;
}

void cancella_contatto(ContactBookADTptr rubrica, char* nome, char* cognome){
    if(!rubrica){
        printf("ERRORE: Non hai una rubrica.\n");
        return;
    }

    _Bool risultato = cbook_remove(rubrica, nome, cognome);

    if(risultato){
        printf("Contatto rimosso correttamente.\n");
    } else {
        printf("Operazione fallita :(.\n");
    }

    return;
}

void modifica_contatto(ContactBookADTptr rubrica, ContactPtr contatto){
    if(!rubrica){
        printf("ERRORE: Non hai una rubrica.\n");
        return;
    }

    if(contatto){
        char mobile_temp[30];
        char url_temp[30];
        char* old_mobile = getMobile(contatto);
        char* old_url = getUrl(contatto);
        
        printf("NUOVI DATI\nMobile: ");
        scanf(" %29[0-9a-zA-Z+ ]", mobile_temp);
        printf("Url: ");
        scanf(" %29[0-9a-zA-Z.@ ]", url_temp);

        // variabili effettive nell'heap (alloco solo il necessario)
        char* mobile = malloc(sizeof(char)*(str_len(mobile_temp)+1));
        char* url = malloc(sizeof(char)*(str_len(url_temp)+1));

        if(!mobile || !url){
            printf("ERRORE: Hai finito la memoria.\n");
            return;
        }

        if(old_mobile)
            free(old_mobile);
        if(old_url)
            free(old_url);

        str_copy(mobile_temp, mobile);
        str_copy(url_temp, url);

        updateMobile(contatto, mobile);
        updateUrl(contatto, url);

        printf("Contatto aggiornato correttamente.\n");
    } else {
        printf("Operazione fallita :(.\n");
    }

    return;
}

void str_append(char* s, char* a){
    while(*s != '\0')
        s++;
    while(*a != '\0')
        *(s++) = *(a++);
    *s = '\0';
}

void ottimizza_rubrica(ContactBookADTptr rubrica){
    if(!rubrica){
        printf("ERRORE: Non hai una rubrica.\n");
        return;
    }

    cbook_optimize(rubrica);
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

    if(newrubrica){
        printf("Operazione eseguita correttamente!\n");
        UpdatePrintParams = 1;
    }
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

    int size = cbook_size(rubrica);

    if(size <= 0){
        printf("\t\tRUBRICA VUOTA :(\n");
        return;
    }

    Contact** elenco_contatti = cbook_toArray(rubrica);
    if(!elenco_contatti)
        return;

    if(UpdatePrintParams){
        // aggiorno le variabili usate per mostrare la rubrica
        for (size_t i = 0; i < size; i++)
        {
            if(str_len(getName(elenco_contatti[i])) > MaxLenName)  
                MaxLenName = str_len(getName(elenco_contatti[i]));
            if(str_len(getSurname(elenco_contatti[i])) > MaxLenSurname) 
                MaxLenSurname = str_len(getSurname(elenco_contatti[i]));
            if(str_len(getMobile(elenco_contatti[i])) > MaxLenMobile)  
                MaxLenMobile = str_len(getMobile(elenco_contatti[i]));
            if(str_len(getUrl(elenco_contatti[i])) > MaxLenUrl)  
                MaxLenUrl = str_len(getUrl(elenco_contatti[i]));
        }
        UpdatePrintParams = 0;
    }

    size_t larghezza_rubrica = 13 + MaxLenName + MaxLenSurname + MaxLenMobile +
                                MaxLenUrl;

    printf("\n");
    printf("+");
    for (size_t i = 0; i < (larghezza_rubrica-2); i++) printf("-");
    printf("+\n");
    printf("|");
    for (size_t i = 0; i < (larghezza_rubrica/2)-5; i++) printf(" ");
    printf("RUBRICA ");
    for (size_t i = 0; i < (larghezza_rubrica/2)-5; i++) printf(" ");
    printf("|\n");
    printf("|");
    for (size_t i = 0; i < (larghezza_rubrica-2); i++) printf(" ");
    printf("|\n");
    for (int i = 0; i < size; i++){
        stampa_contatto(elenco_contatti[i], 1);
    }
    printf("+");
    for (size_t i = 0; i < (larghezza_rubrica-2); i++) printf("-");
    printf("+\n");

    free(elenco_contatti);
}

