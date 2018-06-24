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

int quizrunner_dataextract(unsigned long int file_01_size, char ** file_01_buffer, int int_01, char *** array_string_01, node_t ** struct_01, node_t ** struct_02, unsigned long int * int_amountQuestions, unsigned long int * int_amountAnswers) {
    if (*file_01_buffer == NULL || *array_string_01 == NULL || *struct_01 == NULL || *struct_02 == NULL || *array_string_01 == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }
        return 1;
    }

    char string_bufferPropertyName[16];
    int int_bufferPropertyName_offset = 0;
    int int_bufferPropertyName_switch = 0;
    unsigned long int int_bufferPropertyValue_offset = 0;

    for (unsigned long int file_01_buffer_offset = 0; file_01_buffer_offset < file_01_size; file_01_buffer_offset++) {
        if ((*file_01_buffer)[file_01_buffer_offset] == '\n') {
            if ((*file_01_buffer)[file_01_buffer_offset + 1] == '\n') {
                if (int_01) {
                    printf("\n[DEBUG]: Function returned %d", 2);
                    printf("\n[DEBUG]: File syntax is incorrect. Consider checking documentation...");
                }
                return 2;
            }
            int_bufferPropertyName_switch = 0;
            continue;
        }

        if ((*file_01_buffer)[file_01_buffer_offset] == '=') {
            if ((*file_01_buffer)[file_01_buffer_offset + 1] == '\n') {
                if (int_01) {
                    printf("\n[DEBUG]: Function returned %d", 2);
                    printf("\n[DEBUG]: File syntax is incorrect. Consider checking documentation...");
                }
                return 2;
            }
            int_bufferPropertyName_switch = 1;
            string_bufferPropertyName[int_bufferPropertyName_offset] = 0;
            if (int_01) {
                printf("\n\n[DEBUG]: Function printed (string_bufferPropertyName %s)", string_bufferPropertyName);
                printf("\n[DEBUG]: Function printed (int_bufferPropertyName_offset %d)", int_bufferPropertyName_offset);
            }
            int_bufferPropertyName_offset = 0;
            continue;
        }

        if (int_bufferPropertyName_switch == 0) {
            string_bufferPropertyName[int_bufferPropertyName_offset] = (*file_01_buffer)[file_01_buffer_offset];
            int_bufferPropertyName_offset++;
        }

        if (int_bufferPropertyName_switch == 1) {
            int_bufferPropertyValue_offset = file_01_buffer_offset;

            while ((*file_01_buffer)[int_bufferPropertyValue_offset] != '\n' && int_bufferPropertyValue_offset < file_01_size) {
                int_bufferPropertyValue_offset++;
            }

            if (int_01) {
                printf("\n[DEBUG]: Function printed (file_01_buffer_offset %lu)", file_01_buffer_offset);
                printf("\n[DEBUG]: Function printed (int_bufferPropertyValue_offset %lu)", int_bufferPropertyValue_offset);
                printf("\n[DEBUG]: Function printed (int_bufferPropertyValue_size %lu)", int_bufferPropertyValue_offset - file_01_buffer_offset);
            }

            char * string_bufferPropertyValue = 0;
            string_bufferPropertyValue = (char*) malloc((sizeof(char) * (int_bufferPropertyValue_offset - file_01_buffer_offset) + sizeof(char)));

            for (unsigned int int_bufferPropertyValue_offsetRelative = 0; file_01_buffer_offset < int_bufferPropertyValue_offset;) {
                string_bufferPropertyValue[int_bufferPropertyValue_offsetRelative] = (*file_01_buffer)[file_01_buffer_offset];
                string_bufferPropertyValue[int_bufferPropertyValue_offsetRelative + 1] = 0;
                file_01_buffer_offset++;
                int_bufferPropertyValue_offsetRelative++;
            }

            if (int_01) {
                printf("\n[DEBUG]: Function printed (string_bufferPropertyValue %s)", string_bufferPropertyValue);
            }

            int_bufferPropertyName_switch = 0;

            if (strcmp(string_bufferPropertyName, "NAME") == 0) {
               (*array_string_01)[0] = string_bufferPropertyValue;
            }

            if (strcmp(string_bufferPropertyName, "DESCRIPTION") == 0) {
                (*array_string_01)[1] = string_bufferPropertyValue;
            }

            if (strcmp(string_bufferPropertyName, "AUTHOR") == 0) {
                (*array_string_01)[2] = string_bufferPropertyValue;
            }

            if (strcmp(string_bufferPropertyName, "TIME") == 0) {
                (*array_string_01)[3] = string_bufferPropertyValue;
            }

            if (strcmp(string_bufferPropertyName, "QUESTION") == 0) {
                quizrunner_addlistelement(*(&struct_01), string_bufferPropertyValue, int_01);
                *int_amountQuestions = *int_amountQuestions + 1;
            }

            if (strcmp(string_bufferPropertyName, "ANSWER") == 0) {
                quizrunner_addlistelement(*(&struct_02), string_bufferPropertyValue, int_01);
                *int_amountAnswers = *int_amountAnswers + 1;
            }
        }
    }

    if (*int_amountQuestions != *int_amountAnswers) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 2);
            printf("\n[DEBUG]: File syntax is incorrect. Consider checking documentation...");
        }
        return 2;
    }

    if (int_01) {
        printf("\n[DEBUG]: Function returned %d", 0);
    }
    return 0;
}