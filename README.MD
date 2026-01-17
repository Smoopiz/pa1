# PA-1 Words and list ADT
# Yuval Szwarcbord, yszwarcb@ucsc.edu, CSE 101

## Files Submitted: 
    *List.h: Header file for the Integer List ADT type, defines the "List" type and all of the exported operations.
    *List.c: The implementation of the list ADT using a doubly linked list with a movable cursor that supports, insertion, deletion, traversal, copying, joining two Lists, seperating two Lists, and printing them
    *ListTest.c: This file is a custom test client for the List ADT, it runs and executes all major operations and prints internal state to verify correctness.
    *Words.c: This is the main file for PA-1,it reads an input text file, from that file it extracts unique words, and outputs them in alphabetical order using an indirect sort via the List ADT
    *Makefile: This file is what builds the executable `Words` along with required object files. Includes targets for building, testing, cleaning, and memory checking with Valgrind.