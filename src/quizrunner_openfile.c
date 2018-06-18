#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

int quizrunner_openfile(FILE ** file_01, char string_01[255], int int_01, char string_02[8]) {
    *file_01 = fopen(string_01, string_02);

    if (*file_01 == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }
        return 1;
    }

    if (int_01) {
        printf("\n[DEBUG]: file_01 returned (0x%p)", file_01);
    }

    if (int_01) {
        printf("\n[DEBUG]: Function returned %d", 0);
    }
    return 0;
}