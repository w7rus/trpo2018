#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

int quizrunner_writetobuffer(FILE ** ptrFile, unsigned long int * ptrFileSize, unsigned long int * ptrFileSizeRead, char ** ptrFileBuffer, int debug) {
    putch('\n');

    *ptrFileSizeRead = fread(*ptrFileBuffer, sizeof(char), *ptrFileSize, *ptrFile);

    if (debug) {
        printf("[DEBUG]: ptrFileSizeRead returned (%lu)\n", *ptrFileSizeRead);
    }

    if (*ptrFileSize != *ptrFileSizeRead) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
            printf("[DEBUG]: Buffer sizes are not equal\n");
        }
        return 1;
    }

    (*ptrFileBuffer)[*ptrFileSize] = 0;

    if (debug) {
        printf("[DEBUG]: Function returned %d\n", 0);
    }
    return 0;
}