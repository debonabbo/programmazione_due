#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "intSortedSetADT.h"
#include "intLinkedListSortedSetADT.h"

IntSortedSetADT mkSSetv(int count, ...) {
    IntSortedSetADT set = mkSSet();

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        int num = va_arg(args, int);
        sset_add(set,num);        
    }
    va_end(args);
    return set;
}

char *toString(IntSortedSetADT set) {
    char *sout = malloc(100*sizeof(char));

    ListNodePtr nptr = set->first;
    sprintf(sout, "{");
    while (nptr) {
        if (nptr == set->first)
            sprintf(sout+strlen(sout), "%d", nptr->elem);
        else
            sprintf(sout+strlen(sout), ",%d", nptr->elem);
        nptr = nptr->next;
    }

    sprintf(sout+strlen(sout), "}");

    return sout;
}

int check_mkSSet() {
    int passed = 1;
    IntSortedSetADT sptr = mkSSet();
    if (!sptr) {
        printf("mkSSet()\n");    
        printf("FAILED");
        printf("EXPECTED: not %d\n", 0);   
        printf("RESULT:%ld\n\n", sptr);  
    } else
        // printf("OK\n");
    return passed;
}

int check_dsSSet() {
    int passed = 1;

    if (passed) {
        _Bool rv;
        IntSortedSetADT sptr = mkSSet();
        rv = dsSSet(&sptr);
        if (!rv || sptr) {
            printf("dsSSet({})\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d AND PTR %ld\n", 0, NULL); 
            printf("RESULT:%d AND PTR %ld\n\n", rv, sptr);
            passed=0;  
        } else {
            // printf("OK\n");
        }
    }  

    if (passed) {
        _Bool rv;
        rv = dsSSet(NULL);
        if (rv) {
            printf("dsSSet(NULL)\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT:%d\n\n", rv);
            passed=0;   
        } else {
            // printf("OK\n");
        }
    }

    return passed;
}

int check_sset_add() {
    int passed=1;

    if(passed){
        _Bool rv;   
        rv = sset_add(NULL,5);
        if (rv) {
            printf("set_add(NULL,5)\n"); 
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT: %d\n", rv); 
            passed=0;
        } else {
            // printf("OK\n");
        } 
    }

    if(passed){
        _Bool rv;
        IntSortedSetADT sptr = mkSSet();
        rv = sset_add(sptr,5);
        if (!rv || sptr->size!=1) {
            printf("set_add({},5)\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d WITH SIZE %d\n", 0, 1);
            printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    if(passed){
        _Bool rv;
        IntSortedSetADT sptr = mkSSet();
        rv = sset_add(sptr,5); 
        rv = sset_add(sptr,7);
        if (!rv || sptr->size!=2) {
            printf("set_add({5},7)\n");   
            printf("FAILED\n");
            printf("EXPECTED: NOT %d WITH SIZE %d\n", 0, 2);
            printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);     
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    if(passed){
        _Bool rv;
        IntSortedSetADT sptr = mkSSet();  
        rv = sset_add(sptr,5);
        rv = sset_add(sptr,7);   
        rv = sset_add(sptr,5);
        if (rv || sptr->size!=2) {
            printf("set_add({5,7},5)\n"); 
            printf("FAILED\n");
            printf("EXPECTED: %d WITH SIZE %d\n", 0, 2);
            printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    if(passed){
        _Bool rv;
        IntSortedSetADT sptr = mkSSet();  
        rv = sset_add(sptr,5);
        rv = sset_add(sptr,6);
        rv = sset_add(sptr,7);   
        rv = sset_add(sptr,6);
        if (rv || sptr->size!=3) {
            printf("set_add({5,6,7},6)\n"); 
            printf("FAILED\n");
            printf("EXPECTED: %d WITH SIZE %d\n", 0, 3);
            printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    return passed;
}

int check_sset_remove(){
    int passed=1;
    _Bool rv;

    if(passed){
        rv = sset_remove(NULL, 3);
        if (rv) {
            printf("sset_remove(NULL,3)\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT: %d\n", rv); 
            passed=0;
        } else {
            // printf("OK\n");
        }
    }

    if(passed){
        IntSortedSetADT sptr = mkSSet();
        rv = sset_remove(sptr, 3);
        if (rv || sptr->size!=0) {
            printf("sset_remove({},3)\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d WITH SIZE %d\n", 0, 0);
            printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size); 
            passed=0;
        } else {
            // printf("OK\n");
        } 
        dsSSet(&sptr);
    }

    if(passed){
        IntSortedSetADT sptr = mkSSetv(2,5,7);
        rv = sset_remove(sptr, 3);
        if (rv || sptr->size!=2) {
            printf("FAILED\n");
            printf("EXPECTED: %d WITH SIZE %d\n", 0, 2);
            printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    if(passed){
        IntSortedSetADT sptr = mkSSetv(2,5,7);
        rv = sset_remove(sptr, 5);
        if (!rv || sptr->size!=1) {
            printf("sset_remove({5,7},5)\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d AND WITH SIZE %d\n", 0, 1);
            printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);     
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    if(passed){
        IntSortedSetADT sptr = mkSSetv(1,7);
        rv = sset_remove(sptr, 7);
        if (!rv || sptr->size!=0) {
            printf("sset_remove({7},7)\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d WITH SIZE %d\n", 0, 0);
            printf("RESULT:%d WITH SIZE %d\n", rv, sptr->size);  
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    return passed;
}

int check_sset_member(){
    int passed=1;
    _Bool rv;

    if(passed){
        rv = sset_member(NULL, 3);
        if (rv) {
            printf("sset_member(NULL,3)\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
    }

    if(passed){
        IntSortedSetADT sptr = mkSSetv(2,5,7);
        rv = sset_member(sptr, 3);
        if (rv) {
            printf("sset_member({5,7},3)\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);   
            printf("RESULT:%d\n", rv);  
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    if(passed){
        IntSortedSetADT sptr = mkSSetv(2,5,7);
        rv = sset_member(sptr, 5);
        if (!rv) {
            printf("sset_member({5,7},5)\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);   
            printf("RESULT:%d\n", rv);  
            passed=false;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    if(passed){
        IntSortedSetADT sptr = mkSSetv(2,5,7);
        rv = sset_member(sptr, 7);
        if (!rv) {
            printf("sset_member({5,7},7)\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);   
            printf("RESULT:%d\n", rv);  
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    return passed;  
}

int check_isEmptySSet(){
    int passed=1;
    _Bool rv;

    if(passed){
        rv = isEmptySSet(NULL);
        if (rv) {
            printf("isEmptySSet(NULL)\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);   
            printf("RESULT:%d\n", rv); 
            passed=0;
        } else {
            // printf("OK\n");
        }
    }

    if(passed){
        IntSortedSetADT sptr = mkSSet();
        rv = isEmptySSet(sptr);
        if (!rv) {
            printf("isEmptySSet({})\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);   
            printf("RESULT:%d\n", rv);  
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    if(passed){
        IntSortedSetADT sptr = mkSSetv(1,5);
        rv = isEmptySSet(sptr);
        if (rv) {
            printf("isEmpty({5})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT:%d\n", rv); 
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    return passed;
}

int check_sset_size(){
    int passed=1;
    int rv;

    if(passed){
        rv = sset_size(NULL);
        if (rv!=-1) {
            printf("sset_size(NULL)\n");
            printf("FAILED\n");
            printf("EXPECTED: %d\n", -1);
            printf("RESULT:%d\n", rv);
            passed=0;   
        } else {
            // printf("OK\n");
        }
    }

    if(passed){
        IntSortedSetADT sptr = mkSSet();
        rv = sset_size(sptr);
        if (rv!=0) {
            printf("sset_size({})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT:%d\n", rv);  
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    if(passed){
        IntSortedSetADT sptr = mkSSetv(1,5);
        rv = sset_size(sptr);
        if (rv!=1) {
            printf("sset_size({5})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 1);
            printf("RESULT:%d\n", rv);  
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    if(passed){
        IntSortedSetADT sptr = mkSSetv(2,5,7);
        rv = sset_size(sptr);
        if (rv!=2) {
            printf("sset_size({5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 2);   
            printf("RESULT:%d\n", rv);  
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    return passed;
}


int check_sset_extract(){
    int passed=1;
    _Bool rv;
    int dat;

    if(passed){
        rv = sset_extract(NULL, &dat);
        if (rv) {
            printf("sset_extract(NULL)\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT: %d\n", rv);
            passed=0;   
        } else {
            // printf("OK\n");
        }
    }

    if(passed){
        IntSortedSetADT sptr = mkSSet();
        rv = sset_extract(sptr, &dat);
        if (rv) {
            printf("sset_extract({})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT: %d\n", rv);  
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr);
    }

    if(passed){
        int dat1,dat2,dat3;

        IntSortedSetADT sptr = mkSSetv(3,3,5,7);
        rv = sset_extract(sptr,&dat1);
        if (!rv || (dat1!=3 && dat1!=5 && dat1!=7)) {
            printf("sset_extract(%s)\n", toString(sptr));    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d AND VALUE IN %s\n", 0, toString(sptr));
            printf("RESULT:%d AND VALUE %d\n", rv, dat1);  
            passed=0;   
        } else {
            // printf("OK\n");
        }

        if (passed) {
            rv = sset_extract(sptr,&dat2);
            if (!rv || dat2==dat1 || (dat2!=3 && dat2!=5 && dat2!=7)) {
                printf("sset_extract(%s))\n", toString(sptr));    
                printf("FAILED\n");
                printf("EXPECTED: NOT %d AND VALUE IN %s\n", 0, toString(sptr));
                printf("RESULT:%d AND VALUE %d\n", rv, dat2);  
                passed=0;   
            } else {
                // printf("OK\n");
            }
        }

        if (passed) {
            rv = sset_extract(sptr,&dat3);
            if (!rv || dat3==dat1 || dat3==dat2 || (dat3!=3 && dat3!=5 && dat3!=7)) {
                printf("sset_extract(%s)\n", toString(sptr));    
                printf("FAILED\n");
                printf("EXPECTED: NOT %d  AND VALUE IN %s\n", 0, toString(sptr));
                printf("RESULT:%d AND VALUE %d\n", rv, dat3);  
                passed=0;   
            } else {
                // printf("OK\n");
            }
        }
        dsSSet(&sptr);
    }

    return passed;
}

int check_sset_equals(){
    int passed=1;
    _Bool rv;

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        rv = sset_equals(NULL,sptr1);
        if (rv) {
            printf("sset_equals(NULL, {})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT: %d\n", rv);
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        rv = sset_equals(sptr1,NULL);
        if (rv) {
            printf("sset_equals({}, NULL)\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);   
            printf("RESULT: %d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        IntSortedSetADT sptr2 = mkSSet();
        rv = sset_equals(sptr2,sptr1);
        if (!rv) {
            printf("sset_equals({}, {})\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        IntSortedSetADT sptr2 = mkSSetv(3,3,5,7);
        rv = sset_equals(sptr2,sptr1);
        if (rv) {
            printf("sset_equals({}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSetv(3,3,5,7);
        rv = sset_equals(sptr2,sptr1);
        if (!rv) {
            printf("sset_equals({3,5,7}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSetv(2,3,5);
        rv = sset_equals(sptr2,sptr1);
        if (rv) {
            printf("sset_equals({3,5,7}, {3,5})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    return passed;
}

int check_sset_subseteq(){
    int passed=1;
    _Bool rv;

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        rv = sset_subseteq(NULL,sptr1);
        if (rv) {
            printf("sset_subseteq(NULL, {})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT: %d\n", rv);
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        rv = sset_subseteq(sptr1,NULL);
        if (rv) {
            printf("sset_subseteq({}, NULL)\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);   
            printf("RESULT: %d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSet();
        rv = sset_subseteq(sptr2,sptr1);
        if (!rv) {
            printf("sset_subseteq({}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSetv(1,3);
        rv = sset_subseteq(sptr2,sptr1);
        if (!rv) {
            printf("sset_subseteq({3}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSetv(2,3,5);
        rv = sset_subseteq(sptr2,sptr1);
        if (!rv) {
            printf("sset_subseteq({3,5}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);  
            printf("RESULT:%d\n", rv);
            passed=0; 
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSetv(3,3,5,7);
        rv = sset_subseteq(sptr2,sptr1);
        if (!rv) {
            printf("sset_subseteq({3,5,7}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSetv(4,3,5,7,9);
        rv = sset_subseteq(sptr2,sptr1);
        if (rv) {
            printf("sset_subseteq({3,5,7,9}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        IntSortedSetADT sptr2 = mkSSetv(1,5);
        rv = sset_subseteq(sptr2,sptr1);
        if (rv) {
            printf("sset_subseteq({5}, {})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT:%d\n", rv);
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    return passed;
}

int check_sset_subset() {
    int passed=1;
    _Bool rv;

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        rv = sset_subset(NULL,sptr1);
        if (rv) {
            printf("sset_subset(NULL, {})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT: %d\n", rv);
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        rv = sset_subset(sptr1,NULL);
        if (rv) {
            printf("sset_subset({}, NULL)\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);   
            printf("RESULT: %d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSet();
        rv = sset_subset(sptr2,sptr1);
        if (!rv) {
            printf("sset_subset({}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSetv(1,3);
        rv = sset_subset(sptr2,sptr1);
        if (!rv) {
            printf("sset_subset({3}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSetv(2,3,5);
        rv = sset_subset(sptr2,sptr1);
        if (!rv) {
            printf("sset_subset({3,5}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: NOT %d\n", 0);  
            printf("RESULT:%d\n", rv);
            passed=0; 
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSetv(3,3,5,7);
        rv = sset_subset(sptr2,sptr1);
        if (rv) {
            printf("sset_subset({3,5,7}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSetv(3,3,5,7);
        IntSortedSetADT sptr2 = mkSSetv(4,3,5,7,9);
        rv = sset_subset(sptr2,sptr1);
        if (rv) {
            printf("sset_subset({3,5,7,9}, {3,5,7})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);   
            printf("RESULT:%d\n", rv);
            passed=0;
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        IntSortedSetADT sptr2 = mkSSetv(1,5);
        rv = sset_subset(sptr2,sptr1);
        if (rv) {
            printf("sset_subset({5}, {})\n");    
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            printf("RESULT:%d\n", rv);
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    return passed;
}


int check_sset_union() {
    int passed=1;

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        IntSortedSetADT uset;
        uset = sset_union(sptr1,NULL);
        if (uset) {
            printf("sset_union({},NULL)\n");
            printf("FAILED\n");
            printf("EXPECTED: NOT %ld\n", uset);
            passed=0;   
        } else {
            // printf("OK\n");
        }
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        IntSortedSetADT uset;
        uset = sset_union(NULL,sptr1);
        if (uset) {
            printf("sset_union(NULL,{})\n");
            printf("FAILED\n");
            printf("EXPECTED: NOT %ld\n", uset);
            passed=0;   
        } else {
            // printf("OK\n");
        }
    }

    if(passed){
        IntSortedSetADT sptr1,sptr2;
        IntSortedSetADT uset,expset;

        sptr1 = mkSSetv(3,3,5,7);  
        sptr2 = mkSSet();
        uset = sset_union(sptr1,sptr2);
        expset = mkSSetv(3,7,5,3);
        if (!sset_equals(uset, expset)) {
            printf("sset_union({3,5,7},{})\n");
            printf("FAILED\n");
            printf("EXPECTED: %s\n", "{3,5,7}");
            printf("RESULT: %s\n", toString(uset));
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&expset);
        dsSSet(&uset);
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1,sptr2;
        IntSortedSetADT uset,expset;

        sptr1 = mkSSetv(3,3,5,7);  
        sptr2 = mkSSetv(1,5);
        uset = sset_union(sptr1,sptr2);
        expset = mkSSetv(3,7,5,3);
        if (!sset_equals(uset, expset)) {
            printf("sset_union({3,5,7},{5})\n");
            printf("FAILED\n");
            printf("EXPECTED: %s\n", "{7,5,3}");
            printf("RESULT: %s\n", toString(uset));
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&expset);
        dsSSet(&uset);
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1,sptr2;
        IntSortedSetADT uset,expset;

        sptr1 = mkSSetv(3,3,5,7);  
        sptr2 = mkSSetv(1,9);
        uset = sset_union(sptr1,sptr2);
        expset = mkSSetv(4,9,7,5,3);
        if (!sset_equals(uset, expset)) {
            printf("sset_union({3,5,7},{9})\n");
            printf("FAILED\n");
            printf("EXPECTED: %s\n", "{9,7,5,3}");
            printf("RESULT: %s\n", toString(uset));
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&expset);
        dsSSet(&uset);
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    return passed;
}

int check_sset_intersection() {
    int passed=1;

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        IntSortedSetADT uset;
        uset = sset_intersection(sptr1,NULL);
        if (uset) {
            printf("sset_intersection({},NULL)\n");
            printf("FAILED\n");
            printf("EXPECTED: NOT %ld\n", uset);
            passed=0;   
        } else {
            // printf("OK\n");
        }
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        IntSortedSetADT uset;
        uset = sset_intersection(NULL,sptr1);
        if (uset) {
            printf("sset_intersection(NULL,{})\n");
            printf("FAILED\n");
            printf("EXPECTED: NOT %ld\n", uset);
            passed=0;   
        } else {
            // printf("OK\n");
        }
    }

    if(passed){
        IntSortedSetADT sptr1,sptr2;
        IntSortedSetADT iset,expset;

        sptr1 = mkSSetv(3,3,5,7);  
        sptr2 = mkSSet();
        iset = sset_intersection(sptr1,sptr2);
        expset = mkSSet();
        if (!sset_equals(iset, expset)) {
            printf("sset_intersection({3,5,7},{})\n");
            printf("FAILED\n");
            printf("EXPECTED: %s\n", toString(expset));
            printf("RESULT: %s\n", toString(iset));
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&expset);
        dsSSet(&iset);
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1,sptr2;
        IntSortedSetADT iset,expset;

        sptr1 = mkSSetv(3,3,5,7);  
        sptr2 = mkSSetv(1,5);
        iset = sset_intersection(sptr1,sptr2);
        expset = mkSSetv(1,5);
        if (!sset_equals(iset, expset)) {
            printf("sset_intersection({3,5,7},{5})\n");
            printf("FAILED\n");
            printf("EXPECTED: %s\n", toString(expset));
            printf("RESULT: %s\n", toString(iset));
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&expset);
        dsSSet(&iset);
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1,sptr2;
        IntSortedSetADT iset,expset;

        sptr1 = mkSSetv(3,3,5,7);  
        sptr2 = mkSSetv(3,5,7,9);
        iset = sset_intersection(sptr1,sptr2);
        expset = mkSSetv(2,5,7);
        if (!sset_equals(iset, expset)) {
            printf("sset_intersection({3,5,7},{5,7,9})\n");
            printf("FAILED\n");
            printf("EXPECTED: %s\n", toString(expset));
            printf("RESULT: %s\n", toString(iset));
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&expset);
        dsSSet(&iset);
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    return passed;
}

int check_sset_subtraction() {
    int passed=1;

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        IntSortedSetADT uset;
        uset = sset_subtraction(sptr1,NULL);
        if (uset) {
            printf("sset_subtraction({},NULL)\n");
            printf("FAILED\n");
            printf("EXPECTED: NOT %ld\n", uset);
            passed=0;   
        } else {
            // printf("OK\n");
        }
    }

    if(passed){
        IntSortedSetADT sptr1 = mkSSet();
        IntSortedSetADT uset;
        uset = sset_subtraction(NULL,sptr1);
        if (uset) {
            printf("sset_subtraction(NULL,{})\n");
            printf("FAILED\n");
            printf("EXPECTED: NOT %ld\n", uset);
            passed=0;   
        } else {
            // printf("OK\n");
        }
    }

    if(passed){
        IntSortedSetADT sptr1,sptr2;
        IntSortedSetADT sset,expset;

        sptr1 = mkSSetv(3,3,5,7);  
        sptr2 = mkSSet();
        sset = sset_subtraction(sptr1,sptr2);
        expset = mkSSetv(3,3,5,7);
        if (!sset_equals(sset, expset)) {
            printf("sset_subtraction({3,5,7},{})\n");
            printf("FAILED\n");
            printf("EXPECTED: %s\n", toString(expset));
            printf("RESULT: %s\n", toString(sset));
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&expset);
        dsSSet(&sset);
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1,sptr2;
        IntSortedSetADT sset,expset;

        sptr1 = mkSSetv(3,3,5,7);  
        sptr2 = mkSSetv(1,5);
        sset = sset_subtraction(sptr1,sptr2);
        expset = mkSSetv(2,3,7);
        if (!sset_equals(sset, expset)) {
            printf("sset_subtraction({3,5,7},{5})\n");
            printf("FAILED\n");
            printf("EXPECTED: %s\n", toString(expset));
            printf("RESULT: %s\n", toString(sset));
            passed=0;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&expset);
        dsSSet(&sset);
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    if(passed){
        IntSortedSetADT sptr1,sptr2;
        IntSortedSetADT sset,expset;

        sptr1 = mkSSetv(3,3,5,7);  
        sptr2 = mkSSetv(3,5,7,9);
        sset = sset_subtraction(sptr1,sptr2);
        expset = mkSSetv(1,3);
        if (!sset_equals(sset, expset)) {
            printf("sset_subtraction({3,5,7},{5,7,9})\n");
            printf("FAILED\n");
            printf("EXPECTED: %s\n", toString(expset));
            printf("RESULT: %s\n", toString(sset));
            passed=false;   
        } else {
            // printf("OK\n");
        }
        dsSSet(&expset);
        dsSSet(&sset);
        dsSSet(&sptr2);
        dsSSet(&sptr1);
    }

    return passed;
}

int check_sset_min(){
    int passed=1;
    int min;

    if(passed){
        IntSortedSetADT sptr;
        sptr = mkSSetv(3, 4, 2, 5);
        if(sset_min(sptr, &min)){
            if(min == 2){
                // printf("OK\n");
            } else {
                printf("sset_min({2,4,5})\n");
                printf("FAILED\n");
                printf("EXPECTED: 2\n");
                printf("RESULT: %d\n", min);
                passed = false;
            }
        } else {
            printf("sset_min({2,4,5})\n");
            printf("FAILED\n");
            printf("EXPECTED: 2\n");
            printf("RESULT: false", min);
            passed = false;
        }
        dsSSet(&sptr);
    }

    return passed;
}

int check_sset_max(){
    int passed=1;
    int max;

    if(passed){
        IntSortedSetADT sptr;
        sptr = mkSSetv(3, 4, 2, 5);
        if(sset_max(sptr, &max)){
            if(max == 5){
                // printf("OK\n");
            } else {
                printf("sset_max({2,4,5})\n");
                printf("FAILED\n");
                printf("EXPECTED: 5\n");
                printf("RESULT: %d\n", max);
                passed = false;
            }
        } else {
            printf("sset_max({2,4,5})\n");
            printf("FAILED\n");
            printf("EXPECTED: 5\n");
            printf("RESULT: false", max);
            passed = false;
        }
        dsSSet(&sptr);
    }

    return passed;
}

int check_sset_extractMin(){
    int passed=1;
    int min;

    if(passed){
        IntSortedSetADT sptr;
        IntSortedSetADT exp;
        sptr = mkSSetv(3, 4, 2, 5);
        exp = mkSSetv(2, 4, 5);
        if(sset_extractMin(sptr, &min)){
            if(min == 2 && sset_equals(sptr, exp)){
                // printf("OK\n");
            } else {
                printf("sset_extractMin({2,4,5})\n");
                printf("FAILED\n");
                printf("EXPECTED: 2 and %s\n", toString(exp));
                printf("RESULT: %d and %s\n", min, toString(sptr));
                passed = false;
            }
        } else {
            printf("sset_extractMin({2,4,5})\n");
            printf("FAILED\n");
            printf("EXPECTED: 2 and %s\n", toString(exp));
            printf("RESULT: false");
            passed = false;
        }
        dsSSet(&sptr);
        dsSSet(&exp);
    }

    return passed;
}

int check_sset_extractMax(){
    int passed=1;
    int max;

    if(passed){
        IntSortedSetADT sptr;
        IntSortedSetADT exp;
        sptr = mkSSetv(3, 4, 2, 5);
        exp = mkSSetv(2, 4, 2);
        if(sset_extractMax(sptr, &max)){
            if(max == 5 && sset_equals(sptr, exp)){
                // printf("OK\n");
            } else {
                printf("sset_extractMax({2,4,5})\n");
                printf("FAILED\n");
                printf("EXPECTED: 5 and %s\n", toString(exp));
                printf("RESULT: %d and %s\n", max, toString(sptr));
                passed = false;
            }
        } else {
            printf("sset_extractMax({2,4,5})\n");
            printf("FAILED\n");
            printf("EXPECTED: 5 and %s\n", toString(exp));
            printf("RESULT: false");
            passed = false;
        }
        dsSSet(&sptr);
        dsSSet(&exp);
    }

    return passed;
}

int main(int argc, char *argv[]) {
  puts("BEGIN TEST intLinkedListSortedSetADT"); 

  {
    // printf("TEST mkSSet\n");
    check_mkSSet();
    printf("\n");
  }

  {
    // printf("TEST dsSSet\n");
    check_dsSSet();
    printf("\n");
  }

  {
    // printf("TEST sset_add\n");
    check_sset_add();
    printf("\n");
  }

  {
    // printf("TEST sset_remove\n");    
    check_sset_remove();
    printf("\n");
  }

  {
    // printf("TEST sset_member\n");    
    check_sset_member();
    printf("\n");
  }

  {
    // printf("TEST isEmptySSet\n");    
    check_isEmptySSet();
    printf("\n");
  }

  {
    // printf("TEST sset_size\n");    
    check_sset_size();
    printf("\n");
  }

  {
    // printf("TEST sset_extract\n");    
    check_sset_extract();
    printf("\n");
  }

  {
    // printf("TEST sset_equals\n");    
    check_sset_equals();
    printf("\n");
  }

  {
    // printf("TEST sset_sset_subseteq\n");    
    check_sset_subseteq();
    printf("\n");
  }

  {
    // printf("TEST sset_subset\n");    
    check_sset_subset();
    printf("\n");
  }

  {
    // printf("TEST sset_union\n");    
    check_sset_union();
    printf("\n");
  }

  {
    // printf("TEST sset_intersection\n");    
    check_sset_intersection();
    printf("\n");
  }

  {
    // printf("TEST sset_subtraction\n");    
    check_sset_subtraction();
    printf("\n");
  }

  {
    // printf("TEST sset_min\n");    
    check_sset_min();
    printf("\n");
  }

  {
    // printf("TEST sset_max\n");    
    check_sset_max();
    printf("\n");
  }

  {
    // printf("TEST sset_extractMin\n");    
    check_sset_extractMin();
    printf("\n");
  }

  {
    // printf("TEST sset_extractMax\n");    
    check_sset_extractMax();
    printf("\n");
  }

  puts("END TEST intLinkedListSortedSetADT"); 
}
