#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

int quizrunner_dataexchange(node_t * struct_01, node_t ** struct_02, int int_01) {
    if (struct_01 == NULL || *struct_02 == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }
        return 1;
    }

    unsigned long int counter = 1;
    for (struct_01 = struct_01 -> next; struct_01; struct_01 = struct_01 -> next) {
        char * quiz_propInput_Buffer = 0;
        quiz_propInput_Buffer = (char*) malloc((sizeof(char) * 255 + sizeof(char)));
        printf("\n#%lu. ", counter);
        printf("%s", struct_01 -> data);
        printf("\nPlease provide an answer (max 255 symbols): ");
        scanf("%s", quiz_propInput_Buffer);
        quizrunner_addlistelement(*(&struct_02), quiz_propInput_Buffer, int_01);
        counter++;
    }

    if (int_01) {
        printf("\n[DEBUG]: Function returned %d", 0);
    }
    return 0;
}