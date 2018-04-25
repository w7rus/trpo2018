#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

int quizrunner_closefile(FILE ** ptrFile, int debug) {
    putch('\n');

    if (*ptrFile == NULL) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
        }
        return 1;
    }

    fclose(*ptrFile);

    if (debug) {
        printf("[DEBUG]: Function returned %d\n", 0);
    }
    return 0;
}