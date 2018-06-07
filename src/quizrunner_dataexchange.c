#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "quizrunner_addlistelement.h"

#ifndef _QUIZRUNNER_NODESTRUCT_DEFINE
#define _QUIZRUNNER_NODESTRUCT_DEFINE

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

#endif

int quizrunner_dataexchange(node_t * head_struct_pointer, node_t ** adressof_tail_struct_pointer, int debug) {
    if (head_struct_pointer == NULL || *adressof_tail_struct_pointer == NULL) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
            printf("[DEBUG]: Pointer points to NULL\n");
        }
        return 1;
    }

    unsigned long int counter = 1;
    for (head_struct_pointer = head_struct_pointer -> next; head_struct_pointer; head_struct_pointer = head_struct_pointer -> next) {
        char * quiz_propInput_Buffer = 0;
        quiz_propInput_Buffer = (char*) malloc((sizeof(char) * (32) + sizeof(char)));
        printf("\n%lu. ", counter);
        printf("%s\n", head_struct_pointer -> data);
        printf("Please provide an answer (max 32 symbols): ");
        scanf("%s", quiz_propInput_Buffer);
        quizrunner_addlistelement(*(&adressof_tail_struct_pointer), quiz_propInput_Buffer, debug);
        counter++;
    }

    if (debug) {
        printf("[DEBUG]: Function returned %d\n", 0);
    }
    return 0;
}