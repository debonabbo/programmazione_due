ac = array;
n = lunghezza di AC;

string = malloc(newsize);
temp = string;

for(n; n > 0; n--){
    if(((*ac) == NUM)){
        *(temp++) = *ac;
    }
    *(temp++) = *(ac++);
}

return string;

newlen(a, n){
    size = 0;
    for(; n > 0; n--){
        if(((*ac++) == NUM)){
            size++;
        }
        size++;
    }
}

"23"

newlen(s) {
    int i;
    for(i=0;*s++!='\0';i++) {
        if(*s is num) i++;
    }
    return i+1;
}