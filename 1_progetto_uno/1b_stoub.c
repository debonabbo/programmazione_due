#include <stdbool.h>
/**
 * @brief Converte una stringa in intero (data la base).
 *
 * Calcola il numero intero rappresentato dalla stringa in argomento nella base
 * (la base deve essere un numero intero nel range 2..36) in argomento:
 * − saltando gli eventuali spazi bianchi iniziali,
 * − riconoscendo l'eventuale (singolo) carattere del segno,
 * − fermandosi al raggiungimento del primo carattere non cifra nella base data (le cifre per la base 36 sono: 0,..,9,A,..,Z).
 *
 * @param s: Una stringa da convertire.
 * @param b: La base.
 * @param r: L'indirizzo dell'intero dove memorizzare il risultato.
 * @return   Restituisce 0 se 'b' non è nell’intervallo ammesso, oppure se non trova nessuna cifra valida
 *           (e in tal caso il valore all'indirizzo r non è significativo).
 *           Altrimenti restituisce 1, e scrive all'indirizzo r il numero intero rappresentato nella stringa nella base data.
 *           Non si accorge dell'eventuale overflow (restituendo in questo caso un risultato scorretto).
 */


bool check_carattere(char *carattere, unsigned short base){
    if((*carattere) >= 48 && (*carattere) <= 57){  //Da 0 a 9
        if(((*carattere) - 48) < base){     //Se il carattere convertito e' minore della base
            return true;
        }
    } else if (*carattere >= 65 && *carattere <= 90){  //Da A a Z
        if(((*carattere) - 55) < base){     //Se il carattere convertito e' minore della base
            return true;
        }
    }

    return false;
}

int stoub(char *s, unsigned short b, int*r) {
    short segno = 1;

    //Controllo che la base sia da 0 a 36
    //Essendo unsigned, non può essere minore di 0
    if(b > 36){    
        *r = 0;
        return 0;
    }

    char *carattere = s;
    //Ignoro gli spazi iniziali
    while((*carattere) == ' ' || (*carattere) == '\n' || (*carattere) == '\t')
        carattere++;

    if((*carattere) == '-'){  //Leggo il segno negativo
        segno = -1;
        carattere++;
    }
    else if((*carattere) == '+')  //Ignoro il segno positivo
        carattere++;

    int risultato = 0;
    int ret = 0;
    while(check_carattere(carattere, b)){   //Se il carattere e' valido
        ret = 1;    //Ho trovato almeno un carattere valido
        if(*carattere <= 57){  //Da 0 a 9
            risultato = (risultato*b) + ((*carattere)-48);  //Converto il carattere e sommo
        } else {  //Da A a Z
            risultato = (risultato*b) + ((*carattere)-55);  //Converto il carattere e sommo
        }
        carattere++;    //Passo al carattere successivo
    }

    *r = risultato*segno;   //Moltiplico il numero per il segno e salvo il risultato

    return ret;
}
