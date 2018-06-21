#include <stdlib.h>
#include <stdio.h>
#include "conio.h"
#include <string.h>
#include <unistd.h>
#include <time.h>

#ifndef _QUIZRUNNER_NODESTRUCT_DEFINE
#define _QUIZRUNNER_NODESTRUCT_DEFINE

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

#endif

int quizrunner_datacompare(node_t * struct_01, node_t * struct_02, unsigned long int int_amountAnswers, char ** array_int_validInputs, int int_01) {
    if (struct_01 == NULL || struct_02 == NULL || *array_int_validInputs == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }
        return 1;
    }

    unsigned long int counter = 0;
    for (struct_01 = struct_01 -> next, struct_02 = struct_02 -> next; struct_01; struct_01 = struct_01 -> next, struct_02 = struct_02 -> next) {
        unsigned long int data1_elementAmount = 0;

        for (unsigned long int data1_strlen = 0; data1_strlen < strlen(struct_01 -> data); data1_strlen++) {
            if ((struct_01 -> data)[data1_strlen] == ',') {
                data1_elementAmount++;
            }
        }

        if (data1_elementAmount) {
            char ** array_string_buffer_Inputs = 0;
            array_string_buffer_Inputs = malloc(sizeof(char *) * (data1_elementAmount + 1));

            for (unsigned long int int_buffer_InputsElements_offset = 0; int_buffer_InputsElements_offset < (data1_elementAmount + 1); int_buffer_InputsElements_offset++) {
                array_string_buffer_Inputs[int_buffer_InputsElements_offset] = malloc(sizeof(char) * 255 + sizeof(char));
            }

            unsigned long int int_buffer_InputsElements_offset = 0;
            unsigned long int int_buffer_Inputs_offset = 0;
            unsigned long int int_buffer_Inputs_offsetRelative = 0;
            char int_buffer_Inputs_offsetRelative_statereset = 0;

            for(;int_buffer_Inputs_offset <= strlen(struct_01 -> data); int_buffer_Inputs_offsetRelative++) {
                if ((struct_01 -> data)[int_buffer_Inputs_offsetRelative + int_buffer_Inputs_offset] != ',' || (struct_01 -> data)[int_buffer_Inputs_offsetRelative] != 0) {
                    if (int_buffer_Inputs_offsetRelative_statereset) {
                        int_buffer_Inputs_offsetRelative = 0;
                        int_buffer_Inputs_offsetRelative_statereset = 0;
                    }
                    array_string_buffer_Inputs[int_buffer_InputsElements_offset][int_buffer_Inputs_offsetRelative] = (struct_01 -> data)[int_buffer_Inputs_offsetRelative + int_buffer_Inputs_offset];
                    array_string_buffer_Inputs[int_buffer_InputsElements_offset][int_buffer_Inputs_offsetRelative + 1] = 0;
                }
                if ((struct_01 -> data)[int_buffer_Inputs_offsetRelative + int_buffer_Inputs_offset] == 0) {
                    break;
                }
                if ((struct_01 -> data)[int_buffer_Inputs_offsetRelative + int_buffer_Inputs_offset] == ',') {
                    array_string_buffer_Inputs[int_buffer_InputsElements_offset][int_buffer_Inputs_offsetRelative] = 0;
                    int_buffer_Inputs_offset = int_buffer_Inputs_offset + int_buffer_Inputs_offsetRelative + 1;
                    int_buffer_Inputs_offsetRelative_statereset = 1;
                    int_buffer_InputsElements_offset++;
                }
            }

            char int_isvalidInput = 0;

            for (unsigned long int int_buffer_InputsSplitted_offset = 0; int_buffer_InputsSplitted_offset <= int_buffer_InputsElements_offset && int_isvalidInput == 0; int_buffer_InputsSplitted_offset++) {
                if (strcmp(array_string_buffer_Inputs[int_buffer_InputsSplitted_offset], struct_02 -> data) == 0 ) {
                    (*array_int_validInputs)[counter] = 1;
                    int_isvalidInput = 1;
                    break;
                } else {
                    (*array_int_validInputs)[counter] = 0;
                }
            }
            counter++;
        } else {
            if (strcmp(struct_01 -> data, struct_02 -> data) == 0) {
                (*array_int_validInputs)[counter] = 1;
            } else {
                (*array_int_validInputs)[counter] = 0;
            }
            counter++;
        }
    }

    if (int_01) {
        printf("\n[DEBUG]: Function returned %d", 0);
    }
    return 0;
}