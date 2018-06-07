#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

#ifndef _QUIZRUNNER_NODESTRUCT_DEFINE
#define _QUIZRUNNER_NODESTRUCT_DEFINE

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

#endif

int quizrunner_printlist(node_t * head_struct_pointer, int debug) {
    if (head_struct_pointer == NULL) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
            printf("[DEBUG]: Pointer points to NULL\n");
        }
        return 1;
    }

    for (head_struct_pointer = head_struct_pointer -> next; head_struct_pointer; head_struct_pointer = head_struct_pointer -> next) {
        printf("[%p] %s\n", head_struct_pointer, head_struct_pointer -> data);
    }

    if (debug) {
        printf("[DEBUG]: Function returned %d\n", 0);
    }
    return 0;
}