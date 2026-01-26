// Yuval Szwarcbord
// yszwarcb
// PA1
// Chat GPT helped me debgud append and printList, those two functions were causing me to fail Test 1&3
// Because it was returning in an incorrect, and it caught it by giving it the message that comes when running pa1.sh

// Link to the chat: https://chatgpt.com/share/696b417d-782c-8011-8623-33e44d1aad3f

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"

// Private Types

typedef struct Node
{
    ListElement data;

    struct Node* prev;
    struct Node* next;

} Node;
typedef struct ListObj
{
    Node* front;
    Node* back;
    Node* cursor;

    int length;
    int index;

} ListObj;

// Private Constructors and Helpers

static Node* newNode(ListElement data) {
    Node* N = malloc(sizeof(Node));

    assert(N != NULL);

    N->data = data;
    N->prev = NULL;
    N->next = NULL;

    return N;
}

static void freeNode(Node** pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}
static void requireList(List L, const char* fn) {
    if (L == NULL) {
        fprintf(stderr, "List Error: %s: NULL List Refrence\n", fn);
        exit(EXIT_FAILURE);
    }
}
static void requireNotEmpty(List L, const char* fn) {
    requireList(L, fn);

    if (L->length == 0) {
        fprintf(stderr, "List Error %s: Empty List\n", fn);
        exit(EXIT_FAILURE);
    }
}
static void requireCursor(List L, const char* fn) {
    requireList(L, fn);

    if (L->cursor == NULL || L->index < 0) {
        fprintf(stderr, "List Error: %s: Undefined Cursor\n", fn);
        exit(EXIT_FAILURE);
    }
}

// Constructors and Destructors

List newList() {
    List L = malloc(sizeof(ListObj));

    assert(L != NULL);

    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->length = 0;
    L->index = -1;

    return L;
}

void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Access Functions

int length(List L) {
    requireList(L, "length()");
    return L->length;
}
int position(List L) {
    requireList(L, "position()");
    return L->index;
}

ListElement front(List L) {
    requireList(L, "front()");
    return L->front->data;
}
ListElement back(List L) {
    requireList(L, "back()");
    return L->back->data;
}
ListElement get(List L) {
    requireList(L, "get()");
    return L->cursor->data;
}

bool equals(List A, List B) {
    requireList(A, "equals()");
    requireList(B, "equals()");

    if (A->length != B->length) {
        return false;
    }

    Node* N = A->front;
    Node* M = B->front;

    while (N != NULL && M != NULL) {
        if (N->data != M->data){
            return false;
        }

        N = N->next;
        M = M->next;
    }

    return true;
}

// Manipulation Procedures

void clear(List L) {
    requireList(L, "clear()");

    Node* N = L->front;

    while (N != NULL) {
        Node* next = N->next;
        freeNode(&N);
        N = next;
    }

    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
}
void set(List L, ListElement x){
    requireCursor(L, "set()");

    L->cursor->data = x;
}
void moveFront(List L){
    requireList(L, "moveFront()");

    if (L->length == 0) {
        L->cursor = NULL;
        L->index = -1;
        
        return;
    }

    L->cursor = L->front;
    L->index = 0;
}
void moveBack(List L) {
    requireList(L, "moveBack()");

    if (L->length == 0) {
        L->cursor = NULL;
        L->index = -1;
        
        return;
    }

    L->cursor = L->back;
    L->index = L->length -1;
}
void movePrev(List L) {
    requireList(L, "movePrev()");
    
    if (L->cursor == NULL) {
        return;
    }
    if (L->cursor->prev == NULL) {
        L->cursor = NULL;
        L->index = -1;
    }
    else {
        L->cursor = L->cursor->prev;
        L->index--;
    }
}
void moveNext(List L) {
    requireList(L, "moveNext()");
    
    if (L->cursor == NULL) {
        return;
    }
    if (L->cursor->next == NULL) {
        L->cursor = NULL;
        L->index = -1;
    }
    else {
        L->cursor = L->cursor->next;
        L->index++;
    }
}
void prepend(List L, ListElement data) {
    requireList(L, "prepend()");

    Node* N = newNode(data);

    if (L->length == 0) {
        L->front = L->back = N;
    }
    else {
        N->next = L->front;

        L->front->prev = N;
        L->front = N;

        if (L->index >= 0) {
            L->index++;
        }
    }

    L-> length++;
}
void append(List L, ListElement data) {
    requireList(L, "append()");

    Node* N = newNode(data);

    if (L->length == 0) {
        L->front = L->back = N;
    }
    else {
        N->prev = L->back;

        L->back->next = N;
        L->back = N;
    }

    L-> length++;
}
void insertBefore(List L, ListElement data) {
    requireCursor (L, "insertBefore()");

    Node* N = newNode(data);

    if (L->cursor == L->front) {
        N->next = L->front;

        L->front->prev = N;
        L->front = N;
    } else {
        Node* C = L->cursor;

        N->prev = C->prev;
        N->next = C;

        C->prev->next = N;
        C->prev = N;
    }

    L->length++;
    L->index++;
}
void insertAfter(List L, ListElement data) {
    requireCursor(L, "insertAfter()");

    Node* N = newNode(data);

    if (L->cursor == L->back) {
        N->prev = L->back;

        L->back->next = N;
        L->back = N;
    } else {
        Node* C = L->cursor;

        N->next = C->next;
        N->prev = C;

        C->next->prev = N;
        C->next = N;
    }

    L->length++;
}
void deleteFront(List L) {
    requireNotEmpty(L, "deleteFront()");

    Node* N = L->front;

    if (L->cursor == N) {
        L->cursor = NULL;
        L->index = -1;
    } else if (L->index >= 0) {
        L->index--;

        if (L->index < 0) {
            L->index = -1;
        }
    }

    if (L->length == 1) {
        L->front = L->back = NULL;
    } else {
        L->front = N->next;
        L->front->prev = NULL;
    }

    L->length--;

    freeNode(&N);
}
void deleteBack(List L) {
    requireNotEmpty(L, "deleteBack()");

    Node* N = L->back;

    if (L->cursor == N) {
        L->cursor = NULL;
        L->index = -1;
    }

    if (L->length == 1) {
        L->front = L->back = NULL;
    } else {
        L->back = N->prev;
        L->back->next = NULL;
    }

    L->length--;

    freeNode(&N);
}
void delete(List L) {
    requireCursor(L, "delete()");

    Node* C = L->cursor;

    if (C == L->front) {
        deleteFront(L);

        return;
    }

    if (C == L->back) {
        deleteBack(L);

        return;
    }

    C->prev->next = C->next;
    C->next->prev = C->prev;

    freeNode(&C);

    L->length--;
    L->cursor = NULL;
    L->index = -1;
}

// Other Operations

void printList(FILE* out, List L) {
    requireList (L, "printList()");

    if (out == NULL) {
        fprintf(stderr, "List Error: printList(): NULL FILE Reference\n"); 
        exit(EXIT_FAILURE);
    }

    fprintf(out, "(");
    for (Node* N = L->front; N != NULL; N = N->next) {

        fprintf(out, "%d", N->data);

        if (N->next != NULL) {
            fprintf(out, ", ");
        }
    }

    fprintf(out, ")");
}

List copyList(List L) {
    requireList (L, "copyList()");

    List C = newList();
    
    for (Node* N = L->front; N != NULL; N = N->next) {
        append(C, N->data);
    }

    return C;
}
List join(List A, List B) {
    requireList(A, "join()");
    requireList(B, "join()");

    List J = newList();

    for (Node* N = A->front; N != NULL; N = N->next) {
        append(J, N->data);
    }
    for (Node* N = B->front; N != NULL; N = N->next) {
        append(J, N->data);
    }
    
    return J;
}
List split(List L) {
    requireList(L, "split()");

    List S = newList();

    if (L->cursor == NULL || L->index < 0) {
        return S;
    }

    for (Node* N = L->cursor->next; N != NULL; N = N->next) {
        append(S, N->data);
    }

    return S;
}
