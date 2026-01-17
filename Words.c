// Yuval Szwarcbord
// yszwarcb@ucsc.ued
// PA1
// ChatGPT helped me debug this file, I had an issue that I did not know was breaking 
// everything and it recommended me to get rid of a function to fix it.

// Link to the chat: https://chatgpt.com/share/696b417d-782c-8011-8623-33e44d1aad3f

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "List.h"

// Delimiters are whitspaces, common punctuation items, and digits
static const char delimiters[] = " \t\n\r\"\'\\,.;:!?()[]{}<>|`~@#$%^&*-_=+/0123456789";

// Returns the index of a word in words[0...n], or -1 if not found
static int findWord(const char* word, char** words, int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(word, words[i]) == 0) return i;
    }
    return -1;
}

// Inserts newIndex into L so that whenever words[get(L)] gets called the order is alphabetical
static void insertIndexSorted(List L, char** words, int newIndex) {
    if (length(L) == 0) {
        append(L, newIndex);

        return;
    }

    moveFront(L);
    while (position(L) >= 0) {
        int curIndex = get(L);
        int cmp = strcmp(words[newIndex], words[curIndex]);

        if (cmp < 0) {
            insertBefore(L, newIndex);

            return;
        }

        moveNext(L);
    }

    append(L, newIndex);
}

int main(int argc, char* argv[]) {
    FILE* in = NULL;
    FILE* out = NULL;

    // In Charge of Validating command-line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);

        return EXIT_FAILURE;
    }

    // In Charge of Opening files
    in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);

        return EXIT_FAILURE;
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        fclose(in);
        return EXIT_FAILURE;
    }

    // In Charge of Creating Dynamic array of unique words
    int wordCount = 0;
    int capacity = 16;
    char** words = malloc((size_t)capacity * sizeof(char*));
    if (words == NULL) {
        fprintf(stderr, "Words Error: malloc failed\n");

        fclose(in);
        fclose(out);

        return EXIT_FAILURE;
    }

    // List of indices that keeps words[] sorted indirectly
    List idx = newList();

    // Read and tokenize input
    const size_t lineBufSize = 5000;
    char lineBuf[5000];

    while (fgets(lineBuf, (int)lineBufSize, in) != NULL) {
        char* tok = strtok(lineBuf, delimiters);

        while (tok != NULL) {

            // Skip Anything That Matches to Delimiters
            if (tok[0] == '\0') {
                tok = strtok(NULL, delimiters);

                continue;
            }

            // If unique, add to words[]
            if (findWord(tok, words, wordCount) == -1) {
                if (wordCount == capacity) {
                    capacity *= 2;

                    char** bigger = realloc(words, (size_t)capacity * sizeof(char*));

                    if (bigger == NULL) {
                        fprintf(stderr, "Words Error: realloc failed\n");

                        for (int i = 0; i < wordCount; i++) free(words[i]);

                        free(words);

                        freeList(&idx);

                        fclose(in);
                        fclose(out);

                        return EXIT_FAILURE;
                    }

                    words = bigger;
                }

                // In Charge of Copying the Token to the Heap
                char* copy = malloc(strlen(tok) + 1);

                if (copy == NULL) {
                    fprintf(stderr, "Words Error: malloc failed\n");

                    for (int i = 0; i < wordCount; i++) free(words[i]);

                    free(words);

                    freeList(&idx);

                    fclose(in);
                    fclose(out);

                    return EXIT_FAILURE;
                }

                strcpy(copy, tok);

                words[wordCount] = copy;

                insertIndexSorted(idx, words, wordCount);

                wordCount++;
            }

            tok = strtok(NULL, delimiters);
        }
    }

    // Start of Creating Output
    printList(out, idx);

    fprintf(out, "\n\n");

    moveFront(idx);

    while (position(idx) >= 0) {
        int i = get(idx);

        fprintf(out, "%s\n", words[i]);

        moveNext(idx);
    }

    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }

    free(words);

    freeList(&idx);

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}