#include "contact.h"
// #include <string.h>
#include <ctype.h>

/**  Un tipo di dato per i contatti telefonici e cyberspaziali
*/
// typedef struct contact {
//    char* name;   
//    char* surname;
//    char* mobile;
//    char* url;
// } Contact, *ContactPtr;

/**  @brief Controlla se due contatti hanno lo stesso nome e cognome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return 1 se i due contatti sono uguali, 0 altrimenti
*/
_Bool contactEq(Contact c1, Contact c2){
    while(*c1.name== *c2.name && *c1.name!='\0'){
      c1.name++;
      c2.name++;
    }
    if(*c1.name=='\0' && *c2.name=='\0'){
      while(*c1.surname== *c2.surname && *c1.surname!='\0'){
            c1.surname++;
            c2.surname++;
      }
      if(*c1.surname=='\0' && *c2.surname=='\0')
            return 1;
      
    }
    return 0;
}

/**  @brief Controlla se due contatti hanno lo stesso nome e cognome∗ 
      @param pc1 il puntatore al primo  contatto (non può essere NULL)
      @param pc2 il puntatore al secondo  contatto (non può essere NULL)
      @return 1 se i due contatti sono uguali, 0 altrimenti
*/
_Bool coneq(char *pc1, char *pc2){
      while(*pc1== *pc2 && *pc1!='\0'){
            pc1++;
            pc2++;
      }

      if(*pc1=='\0' && *pc2=='\0')
            return 1;

      return 0;
}

_Bool contactEqEff(const Contact const *pc1, const Contact const *pc2){
      //Confronta i cognomi
      if(coneq(pc1->surname, pc2->surname) == 1){
            if(coneq(pc1->name, pc2->name) == 1)
                  return 1;
      }
      return 0;
}

/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param c1 il primo  contatto 
      @param c2 il secondo contatto
      @return -1 se c1 minore di c2, 0 se c1 uguale a c2, 1 se c1 maggiore di c2
*/
int contactCmp(Contact c1, Contact c2){
      while((tolower(*c1.surname) == tolower(*c2.surname)) && *c1.surname!='\0'){
            c1.surname++;
            c2.surname++;
      }

      if(*c1.surname=='\0' && *c2.surname=='\0'){
            //I cognomi sono uguali
            while((toupper(*c1.name)== toupper(*c2.name)) && *c1.name!='\0'){
                  c1.name++;
                  c2.name++;
            }
            if(*c1.name==*c2.name && *c1.name=='\0')   //Anche i nomi sono uguali
                  return 0;
            if(tolower(*c1.name)<tolower(*c2.name))   //Il primo nome e' piu' piccolo del secondo
                  return -1;
            
            //Il primo nome e' PIU' GRANDE del secondo
            return -1;
      }

      //I cognomi sono diversi
      if(tolower(*c1.surname)>tolower(*c2.surname)) //Il primo congnome e' piu' grande del secondo
            return 1;

      //il primo cognome e' piu' piccolo del secondo
      return -1;
}



/**  @brief Confronta due contatti per cognome rispetto all'ordine lessicografico e, se il cognome e' lo stesso, per nome
      @param pc1 il puntatore al primo  contatto (non può essere NULL)
      @param pc2 il puntatore al secondo  contatto (non può essere NULL)
      @return -1 se *pc1 minore di *pc2, 0 se *pc1 uguale a *pc2, 1 se *pc1 maggiore di *pc2
*/
int conew(char *pc1, char *pc2){
     while(tolower(*pc1) == tolower(*pc2) && *pc1 != '\0'){
            pc1++;
            pc2++;
      }

      if(*pc1 < *pc2)
           return -1;
      if (*pc1 > *pc2)
           return 1;

      return 0;
}

// conew restituisce -1, 0 oppure 1
// -1 se str1 < str2
// 0 se str1 == str2
// 1 se str1 > str2

int contactCmpEff(const Contact const *pc1, const Contact const *pc2){
      if(conew(pc1->surname, pc2->surname) == 0){     //Cognomi uguali
            if(conew(pc1->name, pc2->name) == 0)      //Nomi uguali
                  return 0;
            //I cognomi sono uguali MA i nomi sono diversi
            if (conew(pc1->name, pc2->name) == 1)     //Il primo nome e' piu' grande del secondo
                  return 1;
            
            //I cognomi sono uguali ma il primo nome e' piu' piccolo del secondo
            return -1;
      }
      //I cognomi sono diversi
      if(conew(pc1->surname, pc2->surname) == -1)     //Il primo cognome e' minore del secondo
            return -1;
            
      return 1;
}
