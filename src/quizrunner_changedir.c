#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_PATH (260)

int quizrunner_changedir(char string_01[MAX_PATH], int int_01) {
    int int_02 = chdir(string_01);

    if (int_02) {
        if (int_01) {
            printf("\n[DEBUG]: Function returned %d", int_02);
        }
        return 1;
    }

    if (int_01) {
        printf("\n[DEBUG]: Function returned %d", 0);
    }
    return 0;
}