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

int converti(char carattere, unsigned short b){
    int convertito = -1;

    if(carattere>='A' && carattere<='Z'){
        convertito = carattere-'A'+10;
    } else if(carattere>='0' && carattere<='9'){
        convertito = carattere-'0';
    }

    if(convertito >= b)
        convertito = -1;

    return convertito;
}

int stoub(char *s, unsigned short b, int*r) {
    int num = 0;
    int num_conv= 0;

    if(b>=2 && b<=36){
        while(*s== ' ' || *s== '\n' || *s== '\t')
            s++;

        int segno= 1;

        if(*s== '-'){
            segno= -1;
            s++;
        }else if(*s=='+')
            s++;
        
        _Bool almeno_una = 0;

        while(*s!='\0' && num_conv >= 0){
            num_conv= converti(*s, b);
            if(num_conv>=0){
                almeno_una = 1;
                num= num*b;
                num += num_conv;
            }
            s++;
        }

        *r = num * segno;

        if(almeno_una)
            return 1;
    }

    return 0;
}