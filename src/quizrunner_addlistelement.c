#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef _QUIZRUNNER_NODESTRUCT_DEFINE
#define _QUIZRUNNER_NODESTRUCT_DEFINE

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

#endif

int quizrunner_addlistelement(node_t ** struct_01, char * string_01, int int_01) {
    if (*struct_01 == NULL || string_01 == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }

        return 1;
    }

    node_t * new_struct_01 = malloc(sizeof(node_t));
    new_struct_01 -> next = 0;
    new_struct_01 -> prev = *struct_01;
    (*struct_01) -> next = new_struct_01;
    *struct_01 = new_struct_01;
    new_struct_01 -> data = string_01;

    if (int_01) {
        printf("\n[DEBUG]: Function returned %d", 0);
    }

    return 0;
}