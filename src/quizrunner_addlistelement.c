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

int quizrunner_addlistelement(node_t ** adressof_tail_struct_pointer, char * string_pointer, int debug) {
    if (*adressof_tail_struct_pointer == NULL || string_pointer == NULL) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
            printf("[DEBUG]: Pointer points to NULL\n");
        }
        return 1;
    }

    node_t * head_struct_pointer = malloc(sizeof(node_t));
    head_struct_pointer -> next = 0;
    head_struct_pointer -> prev = *adressof_tail_struct_pointer;
    (*adressof_tail_struct_pointer) -> next = head_struct_pointer;
    *adressof_tail_struct_pointer = head_struct_pointer;
    head_struct_pointer -> data = string_pointer;
    
    if (debug) {
        printf("[DEBUG]: Function returned %d\n", 0);
    }
    return 0;
}