// Yuval Szwarcbord
// yszwarcb@ucsc.ued
// PA1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// Helper Function

static void printState(const char* tag, List L) {
    printf("\n --- %s --- \n", tag);
    printf("length=%d --- postion=%d\n", length(L), position(L));
    printf("List: ");
    
    printList(stdout, L);

    printf("\n");

    if (length(L) > 0) {
        printf("front=%d --- back=%d\n", front(L), back(L));
    }
    if (position(L) >= 0) {
        printf("get(cursor)=%d\n", get(L));
    }
}

int main (void) {
    printf("List ADT Test:\n");

    // Create lists
    List A = newList();
    List B = newList();

    // Test State of New List
    printf("Empty State of A", A);
    printf("Empty State of B", B);

    // Append and Prepend
    for (int i = 1; i <= 5; i++) {
        append(A, i);
    }
    for (int i = 10; i <= 30; i += 10) {
        prepend(B, i);
    }

    printState("After Append to A", A);
    printState("After Prepend to B", B);

    // Test Equals and Copy List
    printf("\nA Equals B? %s\n", equals(A,B) ? "true":"false");
    List A2 = copyList(A);
    printf("A Equals copy(A)? %s\n", equals(A,A2) ? "true":"false");

    // Test Cursor Movments
    moveFront(A);
    moveNext(A);
    moveNext(A);
    movePrev(A);
    moveBack(A);
    moveNext(A);

    // Test Set, InsertAfter, and InsertBefore
    moveFront(A);
    set(A, 111);
    insertBefore(A, 222);
    insertAfter(A, 333);

    // Test Deletes
    deleteFront(A);
    deleteBack(A);

    moveFront(A);
    moveNext(A);
    delete(A);

    // Test Join
    List J = join(A,B);
    printState("J = join(A,B)", J);

    // Test Split
    moveFront(J);
    moveNext(J);
    moveNext(J);
    List S = split(J);

    // Test Clear
    clear(B);
    printState("B After clear()", B);

    // Test Empty List
    List Empty = newList();
    printf("\n B Equals New Empty List? %s\n", equals(B, Empty) ? "true":"false");

    // Test Cleanup
    freeList(&A);
    freeList(&B);
    freeList(&A2);
    freeList(&J);
    freeList(&S);
    freeList(&Empty);
}