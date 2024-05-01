#include "contactOpq.h"

typedef struct contact {
    char *name;
    char *surname;
    char *mobile;
    char *url;
}*ContactPtr;

ContactPtr mkContact(char* name, char* surname, char* mobile, char* url){
    if(name == 0 || surname == 0)
        return 0;

    ContactPtr contatto;
    
    contatto = malloc(sizeof(struct contact));

    contatto->name = name;
    contatto->surname = surname;
    contatto->mobile = mobile;
    contatto->url = url;

    return contatto;
}

void dsContact(ContactPtr* cntptr){
    free(*cntptr);
    *cntptr = 0;

    return;
}

void updateMobile(ContactPtr cnt, char* newMobile){
    cnt->mobile = newMobile;

    return;
}

void updateUrl(ContactPtr cnt, char* newUrl){
    cnt->url = newUrl;

    return;
}

char* getName(const ContactPtr cnt){
    return cnt->name;
}

char* getSurname(const ContactPtr cnt){
    return cnt->surname;
}

char* getMobile(const ContactPtr cnt){
    return cnt->mobile;
}

char* getUrl(const ContactPtr cnt){
    return cnt->url;
}

char toLow(char *c){
    if(*c >= 'A' && *c <= 'Z')
        return (*c) + 32;
    return *c;
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

_Bool equalsContact(const ContactPtr cnt1, const ContactPtr cnt2){
    if(strEqualLexic(cnt1->surname, cnt2->surname) == 0){
        if(strEqualLexic(cnt1->name, cnt2->name) == 0){
            return 1;
        }
    }

    return 0;
}

int cmpContact(const ContactPtr cnt1, const ContactPtr cnt2){
    int confronto = strEqualLexic(cnt1->surname, cnt2->surname);

    if(confronto == 0){
        confronto = strEqualLexic(cnt1->name, cnt2->name);
    }

    return confronto;
}