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

int quizrunner_printlist(node_t * struct_01, int int_01) {
    if (struct_01 == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }
        return 1;
    }

    for (struct_01 = struct_01 -> next; struct_01; struct_01 = struct_01 -> next) {
        printf("\n[%p] %s", struct_01, struct_01 -> data);
    }

    if (int_01) {
        printf("\n[DEBUG]: Function returned %d", 0);
    }
    return 0;
}