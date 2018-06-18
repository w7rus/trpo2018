#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

int quizrunner_createbuffer(FILE ** file_01, unsigned long int * file_01_size, char ** string_01, int int_01) {
    if (*file_01 == NULL || file_01_size == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }
        return 1;
    }

    fseek(*file_01, 0, SEEK_END);
    *file_01_size = ftell(*file_01);
    rewind(*file_01);

    if (int_01) {
        printf("\n[DEBUG]: file_01_size returned (%lu)", *file_01_size);
    }

    if (*file_01_size > 1048576) {//1MB limit
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 2);
            printf("\n[DEBUG]: Size of file exceeds limit of 1048576 Bytes");
        }
        return 2;
    }

    *string_01 = (char*) malloc((sizeof(char) * (*file_01_size)) + sizeof(char));

    if (*string_01 == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }
        return 3;
    }

    if (int_01) {
        printf("\n[DEBUG]: string_01 returned (0x%p)", string_01);
    }

    if (int_01) {
        printf("\n[DEBUG]: Function returned %d", 0);
    }

    return 0;
}