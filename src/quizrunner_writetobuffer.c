#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

int quizrunner_writetobuffer(FILE ** file_01, unsigned long int * file_01_size, unsigned long int * file_01_sizeread, char ** file_01_buffer, int int_01) {
    if (*file_01 == NULL || file_01_size == NULL || *file_01_buffer == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }
        return 1;
    }
    
    *file_01_sizeread = fread(*file_01_buffer, sizeof(char), *file_01_size, *file_01);

    if (int_01) {
        printf("\n[DEBUG]: file_01_sizeread returned (%lu)", *file_01_sizeread);
    }

    if (*file_01_size != *file_01_sizeread) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Buffer sizes are not equal");
        }
        return 2;
    }

    (*file_01_buffer)[*file_01_size] = 0;

    if (int_01) {
        printf("\n[DEBUG]: Function returned %d", 0);
    }
    return 0;
}