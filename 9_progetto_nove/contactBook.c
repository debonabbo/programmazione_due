#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
    printf("%s %s: %s (%s)", getName(contact), getSurname(contact), 
                            getMobile(contact), getUrl(contact));
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
                if(getSurname(contatto))
                    free(getSurname(contatto));
                if(getName(contatto))
                    free(getName(contatto));
                if(getMobile(contatto))
                    free(getMobile(contatto));
                if(getUrl(contatto))
                    free(getUrl(contatto));
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
ContactBookADTptr cbook_load(FILE* fin){
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
                str_extract(&buf_temp, url_temp, ',');
                
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
        ContactPtr* rubrica = (ContactPtr*)sset_toArray(book->contacts, false);
        int size = sset_size(book->contacts);
        
        for (size_t i = 0; i < size; i++){
            fprintf(fout, "%s", getSurname(rubrica[i]));
            fprintf(fout, ",%s", getName(rubrica[i]));
            if(str_len(getMobile(rubrica[i])) > 0)
                fprintf(fout, ",%s", getMobile(rubrica[i]));
            if(str_len(getUrl(rubrica[i])) > 0)
                fprintf(fout, ",%s", getUrl(rubrica[i]));
            //printf("\n");
        }

        free(rubrica);
        return true;
    }
    return false;
}

Contact** cbook_toArray(const ContactBookADT* book){
    if(book){
        return (Contact**)sset_toArray(book->contacts, true);
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