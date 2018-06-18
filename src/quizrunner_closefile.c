#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

int quizrunner_closefile(FILE ** file_01, int int_01) {
    if (*file_01 == NULL) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", 1);
            printf("\n[DEBUG]: Pointer points to NULL");
        }
        return 1;
    }

    fclose(*file_01);

    if (int_01) {
        printf("\n[DEBUG]: Function returned %d", 0);
    }
    return 0;
}