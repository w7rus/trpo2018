#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

int quizrunner_openfile(FILE ** ptrFile, char ptrFileName[255], int debug) {
    putch('\n');

    *ptrFile = fopen(ptrFileName, "rb");

    if (*ptrFile == NULL) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
            printf("[DEBUG]: Pointer points to NULL\n");
        }
        return 1;
    }

    if (debug) {
        printf("[DEBUG]: ptrFile returned (0x%p)\n", ptrFile);
    }

    if (debug) {
        printf("[DEBUG]: Function returned %d\n", 0);
    }
    return 0;
}