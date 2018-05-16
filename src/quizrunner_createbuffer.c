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

    if (*ptrFileSize > 1048576) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 2);
            printf("[DEBUG]: Size of file exceeds limit of 1048576 Bytes\n");
        }
        return 2;
    }

    *ptrFileBuffer = (char*) malloc((sizeof(char) * (*ptrFileSize)) + sizeof(char));

    if (debug) {
        printf("[DEBUG]: ptrFileBuffer returned (0x%p)\n", ptrFileBuffer);
    }

    if (*ptrFileBuffer == NULL) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
            printf("[DEBUG]: Pointer points to NULL\n");
        }
        return 1;
    }

    if (debug) {
        printf("[DEBUG]: Function returned %d\n", 0);
    }
    return 0;
}