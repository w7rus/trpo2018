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

int quizrunner_dataextract(unsigned long int ptrFileSize, char ** ptrFileBuffer, int debug, char *** quiz_detailsBuffer, node_t ** adressof_tail_struct_pointer1, node_t ** adressof_tail_struct_pointer2, unsigned long int * quiz_propAmount_Questions, unsigned long int * quiz_propAmount_Answers) {
    if (*ptrFileBuffer == NULL || *quiz_detailsBuffer == NULL || *adressof_tail_struct_pointer1 == NULL || *adressof_tail_struct_pointer2 == NULL) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
            printf("[DEBUG]: Pointer points to NULL\n");
        }
        return 1;
    }

    char quiz_propAlias_Buffer[16];
    int quiz_propAlias_BufferOffset = 0;
    int quiz_propMode = 0;
    unsigned long int quiz_propValue_BufferOffset = 0;

    for (unsigned long int ptrFileBufferOffset = 0; ptrFileBufferOffset < ptrFileSize; ptrFileBufferOffset++) {
        if ((*ptrFileBuffer)[ptrFileBufferOffset] == '\n') {
            if ((*ptrFileBuffer)[ptrFileBufferOffset + 1] == '\n') {
                if (debug) {
                    printf("[DEBUG]: Function returned %d\n", 1);
                    printf("[DEBUG]: File structure error\n");
                }
                return 1;
            }
            quiz_propMode = 0;
            continue;
        }

        if ((*ptrFileBuffer)[ptrFileBufferOffset] == '=') {
            if ((*ptrFileBuffer)[ptrFileBufferOffset + 1] == '\n') {
                if (debug) {
                    printf("[DEBUG]: Function returned %d\n", 1);
                    printf("[DEBUG]: File structure error\n");
                }
                return 1;
            }
            quiz_propMode = 1;
            quiz_propAlias_Buffer[quiz_propAlias_BufferOffset] = 0;
            if (debug) {
                printf("\n[DEBUG]: Function printed (quiz_propAlias_Buffer %s)\n", quiz_propAlias_Buffer);
                printf("[DEBUG]: Function printed (quiz_propAlias_BufferOffset %d)\n", quiz_propAlias_BufferOffset);
            }
            quiz_propAlias_BufferOffset = 0;
            continue;
        }

        if (quiz_propMode == 0) {
            quiz_propAlias_Buffer[quiz_propAlias_BufferOffset] = (*ptrFileBuffer)[ptrFileBufferOffset];
            quiz_propAlias_BufferOffset++;
        }

        if (quiz_propMode == 1) {
            quiz_propValue_BufferOffset = ptrFileBufferOffset;

            while ((*ptrFileBuffer)[quiz_propValue_BufferOffset] != '\n') {
                quiz_propValue_BufferOffset++;
            }

            if (debug) {
                printf("[DEBUG]: Function printed (ptrFileBufferOffset %lu)\n", ptrFileBufferOffset);
                printf("[DEBUG]: Function printed (quiz_propValue_BufferOffset %lu)\n", quiz_propValue_BufferOffset);
                printf("[DEBUG]: Function printed (quizPropValueSize %lu)\n", quiz_propValue_BufferOffset - ptrFileBufferOffset);
            }

            char * quiz_propValue_Buffer = 0;
            quiz_propValue_Buffer = (char*) malloc((sizeof(char) * (quiz_propValue_BufferOffset - ptrFileBufferOffset) + sizeof(char)));

            for (unsigned int quiz_propValue_BufferOffsetRelative = 0; ptrFileBufferOffset < quiz_propValue_BufferOffset;) {
                quiz_propValue_Buffer[quiz_propValue_BufferOffsetRelative] = (*ptrFileBuffer)[ptrFileBufferOffset];
                quiz_propValue_Buffer[quiz_propValue_BufferOffsetRelative + 1] = 0;
                ptrFileBufferOffset++;
                quiz_propValue_BufferOffsetRelative++;
            }

            if (debug) {
                printf("[DEBUG]: Function printed (quiz_propValue_Buffer %s)\n\n", quiz_propValue_Buffer);
            }

            quiz_propMode = 0;

            if (strcmp(quiz_propAlias_Buffer, "NAME") == 0) {
               (*quiz_detailsBuffer)[0] = quiz_propValue_Buffer;
            }

            if (strcmp(quiz_propAlias_Buffer, "DESCRIPTION") == 0) {
                (*quiz_detailsBuffer)[1] = quiz_propValue_Buffer;
            }

            if (strcmp(quiz_propAlias_Buffer, "AUTHOR") == 0) {
                (*quiz_detailsBuffer)[2] = quiz_propValue_Buffer;
            }

            if (strcmp(quiz_propAlias_Buffer, "TIME") == 0) {
                (*quiz_detailsBuffer)[3] = quiz_propValue_Buffer;
            }

            if (strcmp(quiz_propAlias_Buffer, "QUESTION") == 0) {
                quizrunner_addlistelement(*(&adressof_tail_struct_pointer1), quiz_propValue_Buffer, debug);
                *quiz_propAmount_Questions = *quiz_propAmount_Questions + 1;
            }

            if (strcmp(quiz_propAlias_Buffer, "ANSWER") == 0) {
                quizrunner_addlistelement(*(&adressof_tail_struct_pointer2), quiz_propValue_Buffer, debug);
                *quiz_propAmount_Answers = *quiz_propAmount_Answers + 1;
            }
        }
    }

    if (*quiz_propAmount_Questions != *quiz_propAmount_Answers || *quiz_propAmount_Questions == 0 || *quiz_propAmount_Answers == 0) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
            printf("[DEBUG]: File structure error\n");
        }
        return 1;
    }

    if (debug) {
        printf("[DEBUG]: Function returned %d\n", 0);
    }
    return 0;
}