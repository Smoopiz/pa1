// Yuval Szwarcbord
// yszwarcb@ucsc.ued
// PA1

#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include <stdio.h>
#include <stdbool.h>

typedef struct ListObj* List;
typedef int ListElement;

// Constructors and Destructors

List newList();
void freeList(List* pL);

// Access Functions

int length(List L);
int position(List L);
ListElement front(List L);
ListElement back (List L);
ListElement get(List L);
bool equals(List A, List B);

// Manipulation Procedures

void clear(List L);
void set (List L, ListElement x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, ListElement data);
void append(List L, ListElement data);
void insertBefore(List L, ListElement data);
void insertAfter(List L, ListElement data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

// Other Operations

void printList(FILE* out, List L);
List copyList(List L);
List join(List A, List B);
List split(List L);

#endif