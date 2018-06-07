#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
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

int quizrunner_datacompare(node_t * head_struct_pointer1, node_t * head_struct_pointer2, unsigned long int quiz_propAmount_Answers, char ** quiz_InputCheckArray, int debug) {
    if (head_struct_pointer1 == NULL || head_struct_pointer2 == NULL || *quiz_InputCheckArray == NULL) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
            printf("[DEBUG]: Pointer points to NULL\n");
        }
        return 1;
    }


    unsigned long int counter = 0;
    for (head_struct_pointer1 = head_struct_pointer1 -> next, head_struct_pointer2 = head_struct_pointer2 -> next; head_struct_pointer1; head_struct_pointer1 = head_struct_pointer1 -> next, head_struct_pointer2 = head_struct_pointer2 -> next) {
        unsigned long int data1_elementAmount = 0;

        for (unsigned long int data1_strlen = 0; data1_strlen < strlen(head_struct_pointer1 -> data); data1_strlen++) {
            if ((head_struct_pointer1 -> data)[data1_strlen] == ',') {
                data1_elementAmount++;
            }
        }

        if (data1_elementAmount) {
            char ** quiz_InputBuffer = 0;
            quiz_InputBuffer = malloc(sizeof(char *) * (data1_elementAmount + 1));

            for (unsigned long int quiz_InputBufferElementOffset = 0; quiz_InputBufferElementOffset < (data1_elementAmount + 1); quiz_InputBufferElementOffset++) {
                quiz_InputBuffer[quiz_InputBufferElementOffset] = malloc(sizeof(char) * 32 + sizeof(char));
            }

            unsigned long int quiz_InputBufferElementOffset = 0;
            unsigned long int quiz_InputBufferOffset = 0;
            unsigned long int quiz_InputBufferOffsetRelative = 0;
            char quiz_InputBufferOffsetRelativeReset = 0;

            for(;quiz_InputBufferOffset <= strlen(head_struct_pointer1 -> data); quiz_InputBufferOffsetRelative++) {
                if ((head_struct_pointer1 -> data)[quiz_InputBufferOffsetRelative + quiz_InputBufferOffset] != ',' || (head_struct_pointer1 -> data)[quiz_InputBufferOffsetRelative] != 0) {
                    if (quiz_InputBufferOffsetRelativeReset) {
                        quiz_InputBufferOffsetRelative = 0;
                        quiz_InputBufferOffsetRelativeReset = 0;
                    }
                    quiz_InputBuffer[quiz_InputBufferElementOffset][quiz_InputBufferOffsetRelative] = (head_struct_pointer1 -> data)[quiz_InputBufferOffsetRelative + quiz_InputBufferOffset];
                    quiz_InputBuffer[quiz_InputBufferElementOffset][quiz_InputBufferOffsetRelative + 1] = 0;
                }
                if ((head_struct_pointer1 -> data)[quiz_InputBufferOffsetRelative + quiz_InputBufferOffset] == 0) {
                    break;
                }
                if ((head_struct_pointer1 -> data)[quiz_InputBufferOffsetRelative + quiz_InputBufferOffset] == ',') {
                    quiz_InputBuffer[quiz_InputBufferElementOffset][quiz_InputBufferOffsetRelative] = 0;
                    quiz_InputBufferOffset = quiz_InputBufferOffset + quiz_InputBufferOffsetRelative + 1;
                    quiz_InputBufferOffsetRelativeReset = 1;
                    quiz_InputBufferElementOffset++;
                }
            }

            char quiz_InputIsCorrect = 0;

            for (unsigned long int quiz_InputSplitBufferOffset = 0; quiz_InputSplitBufferOffset <= quiz_InputBufferElementOffset && quiz_InputIsCorrect == 0; quiz_InputSplitBufferOffset++) {
                if (strcmp(quiz_InputBuffer[quiz_InputSplitBufferOffset], head_struct_pointer2 -> data) == 0 ) {
                    (*quiz_InputCheckArray)[counter] = 1;
                    quiz_InputIsCorrect = 1;
                    break;
                } else {
                    (*quiz_InputCheckArray)[counter] = 0;
                }
            }
            counter++;
        } else {
            if (strcmp(head_struct_pointer1 -> data, head_struct_pointer2 -> data) == 0) {
                (*quiz_InputCheckArray)[counter] = 1;
            } else {
                (*quiz_InputCheckArray)[counter] = 0;
            }
            counter++;
        }
    }

    if (debug) {
        printf("[DEBUG]: Function returned %d\n", 0);
    }
    return 0;
}