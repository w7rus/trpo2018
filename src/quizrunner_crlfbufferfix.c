#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int quizrunner_crlfbufferfix(unsigned long int file_01_size, char * string_01, unsigned long int * file_02_size, char ** string_02, int int_01) {
    if (string_01 == NULL || file_02_size == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }
        return 1;
    }

    for (unsigned long int file_01_size_offset = 0; file_01_size_offset < file_01_size; file_01_size_offset++) {
        if (string_01[file_01_size_offset] == '\r') {
            continue;
        }

        (*file_02_size)++;
    }

    *string_02 = (char*) malloc((sizeof(char) * (*file_02_size)) + sizeof(char));

    if (*string_02 == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }
        return 2;
    }

    unsigned long int file_02_size_offset = 0;

    for (unsigned long int file_01_size_offset = 0; file_01_size_offset < file_01_size; file_01_size_offset++) {
        if (string_01[file_01_size_offset] == '\r') {
            continue;
        }

        (*string_02)[file_02_size_offset] = string_01[file_01_size_offset];
        file_02_size_offset++;
    }

    if (int_01) {
        printf("\n[DEBUG]: string_02 returned (0x%p)", string_01);
    }

    if (int_01) {
        printf("\n[DEBUG]: Function returned %d", 0);
    }

    return 0;
}