#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

int quizrunner_createbuffer(FILE ** ptrFile, unsigned long int * ptrFileSize, char ** ptrFileBuffer, int debug) {
    putch('\n');

    fseek(*ptrFile, 0, SEEK_END);
    *ptrFileSize = ftell(*ptrFile);
    rewind(*ptrFile);

    if (debug) {
        printf("[DEBUG]: ptrFileSize returned (%lu)\n", *ptrFileSize);
    }

    *ptrFileBuffer = (char*) malloc((sizeof(char) * (*ptrFileSize)) + sizeof(char));

    if (debug) {
        printf("[DEBUG]: ptrFileBuffer returned (0x%p)\n", ptrFileBuffer);
    }

    if (ptrFileBuffer == NULL) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
        }
        return 1;
    }

    if (debug) {
        printf("[DEBUG]: Function returned %d\n", 0);
    }
    return 0;
}