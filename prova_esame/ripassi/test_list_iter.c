#include "list_iter.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
// Crea lista, con i valori passati come argomento
ListNodePtr mkList(int n, ...){
    va_list ap;
    va_start(ap, n);
    ListNodePtr head = malloc(sizeof(ListNode));

    head->data = va_arg(ap, int);
    head->next = NULL;
    ListNodePtr current = head;
    for(int i = 1; i < n; i++){
        ListNodePtr newNode = malloc(sizeof(ListNode));
        newNode->data = va_arg(ap, int);
        newNode->next = NULL;
        current->next = newNode;
        current = newNode;
    }
    va_end(ap);
    return head;
}
void printList(ListNodePtr ls){
    while(ls!=NULL){
        printf("%d ",ls->data);
        ls=ls->next;
    }
    printf("\n");
}
int main(){
    // Test case 1: m = 1, n = 5
    ListNodePtr list1 = fromTo_iter(1, 5);
    printf("Test Case 1: ");
    printList(list1); // Expected output: 1 2 3 4 5

    // Test case 2: m = 0, n = 10
    ListNodePtr list2 = fromTo_iter(0, 10);
    printf("Test Case 2: ");
    printList(list2); // Expected output: 0 1 2 3 4 5 6 7 8 9 10

    // Test case 3: m = 5, n = 5
    ListNodePtr list3 = fromTo_iter(5, 5);
    printf("Test Case 3: ");
    printList(list3); // Expected output: 5

    // Test case 4: m = 10, n = 5 (invalid range)
    ListNodePtr list4 = fromTo_iter(10, 5);
    printf("Test Case 4: ");
    printList(list4); // Expected output: NULL

    // Test case 5: m = 1, n = 1
    ListNodePtr list5 = fromTo_iter(1, 1);
    printf("Test Case 5: ");
    printList(list5); // Expected output: 1

    // Test case 6: m = 0, n = 0
    ListNodePtr list6 = fromTo_iter(0, 0);
    printf("Test Case 6: ");
    printList(list6); // Expected output: 0

    // Test case 7: included_iter with equal lists
    ListNodePtr list7_1 = fromTo_iter(1, 5);
    ListNodePtr list7_2 = fromTo_iter(1, 5);
    printf("Test Case 7: included_iter with equal lists: ");
    printf("%d\n", included_iter(list7_1, list7_2)); // Expected output: 1 (true)

    // Test case 8: included_iter with different lists
    ListNodePtr list8_1 = fromTo_iter(1, 5);
    ListNodePtr list8_2 = fromTo_iter(2, 6);
    printf("Test Case 8: included_iter with different lists: ");
    printf("%d\n", included_iter(list8_1, list8_2)); // Expected output: 0 (false)

    // Test case 9: included_iter with one empty list
    ListNodePtr list9_1 = fromTo_iter(1, 5);
    ListNodePtr list9_2 = NULL;
    printf("Test Case 9: included_iter with one empty list: ");
    printf("%d\n", included_iter(list9_1, list9_2)); // Expected output: 0 (false)

    // Test case 10: included_iter with both empty lists
    ListNodePtr list10_1 = NULL;
    ListNodePtr list10_2 = NULL;
    printf("Test Case 10: included_iter with both empty lists: ");
    printf("%d\n", included_iter(list10_1, list10_2)); // Expected output: 0 (false)

    ListNodePtr list11 = fromTo_iter(1, 5);
    printf("Test Case 11: Reverse a list with multiple elements: ");
    ListNodePtr reversedList11 = reverse_iter(list11);
    printList(reversedList11); // Expected output: 5 4 3 2 1

    ListNodePtr list12 = fromTo_iter(1, 1);
    printf("Test Case 12: Reverse a list with a single element: ");
    ListNodePtr reversedList12 = reverse_iter(list12);
    printList(reversedList12); // Expected output: 1 

    // Test case 17: zipSum_iter with different lists
    ListNodePtr list17_1 = fromTo_iter(1, 5);
    ListNodePtr list17_2 = fromTo_iter(1, 5);
    printf("Test Case 18: zipSum_iter with equals lists: ");
    ListNodePtr zipSumList17 = zipSum_iter(list17_1, list17_2);
    printList(zipSumList17); // Expected output: 


    // Test case 18: zipSum_iter with different lists
    ListNodePtr list18_1 = fromTo_iter(1, 5);
    ListNodePtr list18_2 = fromTo_iter(2, 6);
    printf("Test Case 18: zipSum_iter with different lists: ");
    ListNodePtr zipSumList18 = zipSum_iter(list18_1, list18_2);
    printList(zipSumList18); // Expected output: 3 5 7 9 11

    // Test case 19: zipSum_iter with one empty list
    ListNodePtr list19_1 = fromTo_iter(1, 5);
    ListNodePtr list19_2 = NULL;
    printf("Test Case 19: zipSum_iter with one empty list: ");
    ListNodePtr zipSumList19 = zipSum_iter(list19_1, list19_2);
    printList(zipSumList19); // Expected output: NULL

    // Test case 20: zipSum_iter with both empty lists
    ListNodePtr list20_1 = NULL;
    ListNodePtr list20_2 = NULL;
    printf("Test Case 20: zipSum_iter with both empty lists: ");
    ListNodePtr zipSumList20 = zipSum_iter(list20_1, list20_2);
    printList(zipSumList20); // Expected output: NULL

    ListNodePtr list21 = fromTo_iter(1, 5);
    int count21 = occurrences_iter(list21, 3);
    printf("Test Case 21: Count occurrences in a list with multiple elements: %d\n", count21); // Expected output: 1

    // Test case 22: Count occurrences of x in an empty list
    ListNodePtr list22 = NULL;
    int count22 = occurrences_iter(list22, 5);
    printf("Test Case 22: Count occurrences in an empty list: %d\n", count22); // Expected output: 0

    // Test case 23: Count occurrences of x in a list with duplicate elements
    ListNodePtr list23 = fromTo_iter(1, 5);
    int count23 = occurrences_iter(list23, 2);
    printf("Test Case 23: Count occurrences in a list with duplicate elements: %d\n", count23); // Expected output: 1

    // Test case 24: Count occurrences of x in a list with no occurrences
    ListNodePtr list24 = fromTo_iter(1, 5);
    int count24 = occurrences_iter(list24, 6);
    printf("Test Case 24: Count occurrences in a list with no occurrences: %d\n", count24); // Expected output: 0

    // Test case 26: Remove all occurrences of x from an empty list
    ListNodePtr list26 = NULL;
    printf("Test Case 26: Remove all occurrences from an empty list: ");
    remove_all_iter(&list26, 5);
    printList(list26); // Expected output: NULL

    // Test case 27: Remove all occurrences of x from a list with duplicate elements
    ListNodePtr list27 = fromTo_iter(1, 5);
    printf("Test Case 27: Remove all occurrences from a list with duplicate elements: ");
    remove_all_iter(&list27, 2);
    printList(list27); // Expected output: 1 3 4 5

    // Test case 28: Remove all occurrences of x from a list with no occurrences
    ListNodePtr list28 = fromTo_iter(1, 5);
    printf("Test Case 28: Remove all occurrences from a list with no occurrences: ");
    remove_all_iter(&list28, 6);
    printList(list28); // Expected output: 1 2 3 4 5

    ListNodePtr list29 = mkList(5, 1, 1, 1, 1, 1);
    printf("Test Case 29: Remove all occurrences from a list with same occurrences: ");
    remove_all_iter(&list29, 1);
    printList(list29); // Expected output: 

    ListNodePtr list34 = mkList(7, 2, 1, 1, 1, 1, 1, 3);
    printf("Test Case 34: Remove all occurrences from a list with some duplicate: ");
    remove_all_iter(&list34, 1);
    printList(list34); // Expected output: 2 3

    ListNodePtr list30 = fromTo_iter(1, 5);
    printf("Test Case 30: Duplicate even nodes in a list with multiple elements: ");
    duplicate_even_iter(list30);
    printList(list30); // Expected output: 1 2 2 3 4 4 5

    // Test case 31: Duplicate even nodes in an empty list
    ListNodePtr list31 = NULL;
    printf("Test Case 31: Duplicate even nodes in an empty list: ");
    duplicate_even_iter(list31);
    printList(list31); // Expected output: NULL

    // Test case 32: Duplicate even nodes in a list with no even nodes
    ListNodePtr list32 = mkList(4, 1, 3, 5, 7);
    printf("Test Case 32: Duplicate even nodes in a list with no even nodes: ");
    duplicate_even_iter(list32);
    printList(list32); // Expected output: 1 2 3 4 5

    // Test case 33: Duplicate even nodes in a list with only even nodes
    ListNodePtr list33 = mkList(4, 2, 4, 6, 8);
    printf("Test Case 33: Duplicate even nodes in a list with only even nodes: ");
    duplicate_even_iter(list33);
    printList(list33); // Expected output: 2 2 4 4 6 6 8 8 10 10

    return 0;
}