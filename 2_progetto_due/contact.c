#include "contact.h"

/**  Un tipo di dato per i contatti telefonici e cyberspaziali
*/

char toLow(char *c){
    if(*c >= 'A' && *c <= 'Z')
        return (*c) + 32;
    return *c;
}

_Bool strEqual(char *c1, char *c2){
    while(toLow(c1) == toLow(c2) && *c1 != '\0'){
        c1++;
        c2++;
    }

    if(*c1 == '\0' && *c2 == '\0'){
        return 1;
    }

    return 0;
}

int strEqualLexic(char *c1, char *c2){
    while(toLow(c1) == toLow(c2) && *c1 != '\0'){
        c1++;
        c2++;
    }

    if(*c1 == '\0' && *c2 == '\0')
        return 0;
    if(toLow(c1) < toLow(c2))
        return -1;
    return 1;
}

/**  @brief Controlla se due contatti hanno lo stesso nome e cognome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return 1 se i due contatti sono uguali, 0 altrimenti
*/
_Bool contactEq(Contact c1, Contact c2){
    if(strEqual(c1.surname, c2.surname)){
        if(strEqual(c1.name, c2.name)){
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
    if(strEqual(pc1->surname, pc2->surname)){
        if(strEqual(pc1->name, pc2->name)){
            return 1;
        }
    }

    return 0;
}


/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return -1 se c1 minore di c2, 0 se c1 uguale a c2, 1 se c1 maggiore di c2
*/
int contactCmp(Contact c1, Contact c2){
    int confronto = strEqualLexic(c1.surname, c2.surname);

    if(confronto == 0){
        confronto = strEqualLexic(c1.name, c2.name);
    }

    return confronto;
}


/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param pc1 il puntatore al primo  contatto (non può essere NULL)
      @param pc2 il puntatore al secondo  contatto (non può essere NULL)
      @return -1 se *pc1 minore di *pc2, 0 se *pc1 uguale a *pc2, 1 se *pc1 maggiore di *pc2
*/
int contactCmpEff(const Contact const *pc1, const Contact const *pc2){
    int confronto = strEqualLexic(pc1->surname, pc2->surname);

    if(confronto == 0){
        confronto = strEqualLexic(pc1->name, pc2->name);
    }

    return confronto;
}