#include <stdio.h>
#include "contactOpq.c"

int main(){
    Contact gabriele;
    Contact giacomo;
    Contact gAbrIele;

    gabriele.name = "Gabriele";
    gabriele.surname = "De Bona";
    gabriele.mobile = "14";
    gabriele.url = "1";

    giacomo.name = "Giacomo";
    giacomo.surname = "De Bona";
    giacomo.mobile = "5";
    giacomo.url = "2";

    gAbrIele.name = "gaBrieLe";
    gAbrIele.surname = "de bOna";
    gAbrIele.mobile = "14";
    gAbrIele.url = "1";

    if(contactEq(gabriele, giacomo)){
        printf("I contatti %s %s e %s %s sono uguali.\n", 
                gabriele.surname, gabriele.name,
                giacomo.surname, giacomo.name);
    } else {
        printf("I contatti %s %s e %s %s sono diversi.\n", 
                gabriele.surname, gabriele.name,
                giacomo.surname, giacomo.name);
    }

    if(contactEq(gabriele, gabriele)){
        printf("I contatti %s %s e %s %s sono uguali.\n", 
                gabriele.surname, gabriele.name,
                gabriele.surname, gabriele.name);
    } else {
        printf("I contatti %s %s e %s %s sono diversi.\n",
                gabriele.surname, gabriele.name,
                gabriele.surname, gabriele.name);
    }

    if(contactEqEff(&gabriele, &giacomo)){
        printf("I contatti %s %s e %s %s sono uguali.\n", 
                gabriele.surname, gabriele.name,
                giacomo.surname, giacomo.name);
    } else {
        printf("I contatti %s %s e %s %s sono diversi.\n", 
                gabriele.surname, gabriele.name,
                giacomo.surname, giacomo.name);
    }

    if(contactEqEff(&gabriele, &gabriele)){
        printf("I contatti %s %s e %s %s sono uguali.\n", 
                gabriele.surname, gabriele.name,
                gabriele.surname, gabriele.name);
    } else {
        printf("I contatti %s %s e %s %s sono diversi.\n",
                gabriele.surname, gabriele.name,
                gabriele.surname, gabriele.name);
    }

    int confronto = contactCmp(gabriele, giacomo);
    if(confronto == -1){
        printf("%s %s viene prima di %s %s.\n", 
                gabriele.surname, gabriele.name,
                giacomo.surname, giacomo.name);
    } else if(confronto == 1) {
        printf("%s %s viene dopo di %s %s.\n", 
                gabriele.surname, gabriele.name,
                giacomo.surname, giacomo.name);
    } else if(confronto == 0){
        printf("%s %s e' uguale a %s %s.\n", 
                gabriele.surname, gabriele.name,
                giacomo.surname, giacomo.name);
    }

    confronto = contactCmp(giacomo, gabriele);
    if(confronto == -1){
        printf("%s %s viene prima di %s %s.\n", 
                giacomo.surname, giacomo.name,
                gabriele.surname, gabriele.name);
    } else if(confronto == 1) {
        printf("%s %s viene dopo di %s %s.\n", 
                giacomo.surname, giacomo.name,
                gabriele.surname, gabriele.name);
    } else if(confronto == 0){
        printf("%s %s e' uguale a %s %s.\n", 
                giacomo.surname, giacomo.name,
                gabriele.surname, gabriele.name);
    }

    confronto = contactCmp(gabriele, gabriele);
    if(confronto == -1){
        printf("%s %s viene prima di %s %s.\n", 
                gabriele.surname, gabriele.name,
                gabriele.surname, gabriele.name);
    } else if(confronto == 1){
        printf("%s %s viene dopo di %s %s.\n",
                gabriele.surname, gabriele.name,
                gabriele.surname, gabriele.name);
    } else if(confronto == 0){
        printf("%s %s e' uguale a %s %s.\n", 
                gabriele.surname, gabriele.name,
                gabriele.surname, gabriele.name);
    }

    confronto = contactCmp(gabriele, giacomo);
    if(confronto == -1){
        printf("%s %s viene prima di %s %s.\n", 
                gabriele.surname, gabriele.name,
                giacomo.surname, giacomo.name);
    } else if(confronto == 1) {
        printf("%s %s viene dopo di %s %s.\n", 
                gabriele.surname, gabriele.name,
                giacomo.surname, giacomo.name);
    } else if(confronto == 0){
        printf("%s %s e' uguale a %s %s.\n", 
                gabriele.surname, gabriele.name,
                giacomo.surname, giacomo.name);
    }

    confronto = contactCmpEff(&giacomo, &gabriele);
    if(confronto == -1){
        printf("%s %s viene prima di %s %s.\n", 
                giacomo.surname, giacomo.name,
                gabriele.surname, gabriele.name);
    } else if(confronto == 1) {
        printf("%s %s viene dopo di %s %s.\n", 
                giacomo.surname, giacomo.name,
                gabriele.surname, gabriele.name);
    } else if(confronto == 0){
        printf("%s %s e' uguale a %s %s.\n", 
                giacomo.surname, giacomo.name,
                gabriele.surname, gabriele.name);
    }

    confronto = contactCmpEff(&gabriele, &gabriele);
    if(confronto == -1){
        printf("%s %s viene prima di %s %s.\n", 
                gabriele.surname, gabriele.name,
                gabriele.surname, gabriele.name);
    } else if(confronto == 1){
        printf("%s %s viene dopo di %s %s.\n",
                gabriele.surname, gabriele.name,
                gabriele.surname, gabriele.name);
    } else if(confronto == 0){
        printf("%s %s e' uguale a %s %s.\n", 
                gabriele.surname, gabriele.name,
                gabriele.surname, gabriele.name);
    }

    confronto = contactCmpEff(&gabriele, &gAbrIele);
    if(confronto == -1){
        printf("%s %s viene prima di %s %s.\n", 
                gabriele.surname, gabriele.name,
                gAbrIele.surname, gAbrIele.name);
    } else if(confronto == 1){
        printf("%s %s viene dopo di %s %s.\n",
                gabriele.surname, gabriele.name,
                gAbrIele.surname, gAbrIele.name);
    } else if(confronto == 0){
        printf("%s %s e' uguale a %s %s.\n", 
                gabriele.surname, gabriele.name,
                gAbrIele.surname, gAbrIele.name);
    }

    // char *c = gAbrIele.surname;
    // while(*c != '\0'){
    //     printf("%c", toLow(c));
    //     c++;
    // }
}