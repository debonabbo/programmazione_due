#include "contact.h"

char toLower(const char c){
    if(c <= 'Z')
        return c + 32;
    return c;
}

/**  @brief Controlla se due contatti hanno lo stesso nome e cognome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return 1 se i due contatti sono uguali, 0 altrimenti
*/
_Bool contactEq(Contact c1, Contact c2){
    while(toLower(*c1.surname) == toLower(*c2.surname) && *c1.surname != '\0'){
        c1.surname++;
        c2.surname++;
    }

    if(*c1.surname == *c2.surname && *c1.surname == '\0'){
        while(toLower(*c1.name) == toLower(*c2.name) && *c1.name != '\0'){
            c1.name++;
            c2.name++;
        }

        if(*c1.name == *c2.name && *c1.name == '\0'){
            return 1;
        }
    }

    return 0;
}


/**  @brief Controlla se due contatti hanno lo stesso nome e cognome∗ 
      @param pc1 il puntatore al primo  contatto (non può essere NULL)
      @param pc2 il puntatore al secondo  contatto (non può essere NULL)
      @return 1 se i due contatti sono uguali, 0 altrimenti
*/
_Bool contactEqEff(const Contact const *pc1, const Contact const *pc2){
    char *c1surname = pc1->surname;
    char *c2surname = pc2->surname;

    while(toLower(*c1surname) == toLower(*c2surname) && *c1surname != '\0'){
        c1surname++;
        c2surname++;
    }

    if(*c1surname == *c2surname && *c1surname == '\0'){
        char *c1name = pc1->name;
        char *c2name = pc2->name;

        while(toLower(*c1name) == toLower(*c2name) && *c1name != '\0'){
            c1name++;
            c2name++;
        }

        if(*c1name == *c2name && *c1name == '\0'){
            return 1;
        }
    }

    return 0;
}


/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico 
 *          e, se il cognome e' lo stesso, per nome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return -1 se c1 minore di c2, 0 se c1 uguale a c2, 1 se c1 maggiore di c2
*/
int contactCmp(Contact c1, Contact c2){
    while(toLower(*c1.surname) == toLower(*c2.surname) && *c1.surname != '\0'){
        c1.surname++;
        c2.surname++;
    }

    if(*c1.surname == *c2.surname && *c1.surname == '\0'){
        //I cognomi sono uguali, procedo coi nomi
        while(toLower(*c1.name) == toLower(*c2.name) && *c1.name != '\0'){
            c1.name++;
            c2.name++;
        }

        if(*c1.name == *c2.name && *c1.name == '\0'){
            //Anche i nomi sono uguali
            return 0;
        } else if(toLower(*c1.name) < toLower(*c2.name)){
            return -1;
        }
    } else if(toLower(*c1.surname) < toLower(*c2.surname)){
        return -1;
    }

    return 1;
}


/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, 
 *          se il cognome e' lo stesso, per nome
      @param pc1 il puntatore al primo  contatto (non può essere NULL)
      @param pc2 il puntatore al secondo  contatto (non può essere NULL)
      @return -1 se *pc1 minore di *pc2, 0 se *pc1 uguale a *pc2, 1 se *pc1 
            maggiore di *pc2
*/
int contactCmpEff(const Contact const *pc1, const Contact const *pc2){
    char *c1surname = pc1->surname;
    char *c2surname = pc2->surname;

    while(toLower(*c1surname) == toLower(*c2surname) && *c1surname != '\0'){
        c1surname++;
        c2surname++;
    }

    if(*c1surname == *c2surname && *c1surname == '\0'){
        //I cognomi sono uguali, procedo coi nomi
        char *c1name = pc1->name;
        char *c2name = pc2->name;

        while(toLower(*c1name) == toLower(*c2name) && *c1name != '\0'){
            c1name++;
            c2name++;
        }

        if(*c1name == *c2name && *c1name == '\0'){
            //Anche i nomi sono uguali
            return 0;
        } else if(toLower(*c1name) < toLower(*c2name)){
            return -1;
        }
    } else if (toLower(*c1surname) < toLower(*c2surname)){
        return -1;
    }

    return 1;
}