#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE MAX_PATH

int quizrunner_changedir(char dirpath[MAX_PATH], int debug) {
    int result = chdir(dirpath);
    if (result) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", result);
        }
        return 1;
    }

    if (debug) {
        printf("[DEBUG]: Function returned %d\n", result);
    }
    return 0;
}

int quizrunner_openfile(FILE ** ptrFile, char ptrFileName[255], int debug) {
    putch('\n');

    *ptrFile = fopen(ptrFileName, "rb");

    if (debug) {
        printf("[DEBUG]: ptrFile returned (0x%p)\n", ptrFile);
    }

    if (ptrFile == NULL) {
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

int quizrunner_writetobuffer(FILE ** ptrFile, unsigned long int * ptrFileSize, unsigned long int * ptrFileSizeRead, char ** ptrFileBuffer, int debug) {
    putch('\n');

    *ptrFileSizeRead = fread(*ptrFileBuffer, sizeof(char), *ptrFileSize, *ptrFile);

    if (debug) {
        printf("[DEBUG]: ptrFileSizeRead returned (%lu)\n", *ptrFileSizeRead);
    }

    if (*ptrFileSize != *ptrFileSizeRead) {
        if (debug) {
            printf("[DEBUG]: Function returned %d\n", 1);
        }
        return 1;
    }

    *ptrFileBuffer[*ptrFileSize] = 0;

    if (debug) {
        printf("[DEBUG]: Function returned %d\n", 0);
    }
    return 0;
}

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
        printf("[DEBUG]: Function returned %d\n", 1);
    }
    return 0;
}

void run_quiz() {
    return;
}

int main(int argc, char *argv[]) {
    int version[3] = {0, 0, 1};
    int debug = 0;

    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-debug") == 0) {
            debug = 1;
        }
    }

    system("cls");

    putch('\n');
    printf("Quiz Runner (version %d.%d.%d)", version[0], version[1], version[2]);
    if (debug) {
        printf(" [DEBUG]");
    }
    putch('\n');
    putch('\n');

    printf("Please specity tests directory path (for default type .\\build\\..\\data\\tests): ");
    char dirpath[MAX_PATH];
    scanf("%s", dirpath);

    if (quizrunner_changedir(dirpath, debug)) {
        printf("[Error]: Failed to change dir to (%s)\n", dirpath);
        printf("Exiting...");
        return 1;
    }

    printf("Please specity test filename: ");
    char ptrFileName[255];
    scanf("%s", ptrFileName);
    printf("Selected file: %s\n", ptrFileName);

    /////////////////STARTOFPTRFILEBUFFERMANIPULATIONS//////////////////

    printf("[Stage 1/5]: Opening... ");

    FILE * ptrFile = NULL;

    if (quizrunner_openfile(&ptrFile, ptrFileName, debug)) {
        printf("[Error]: Failed to open file (%s)", ptrFileName);
        putch('\n');
        printf("Exiting...");
        return 1;
    }

    printf("[Stage 2/5]: Allocating buffer for opened file... ");

    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;

    if (quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug)) {
        printf("[Error]: Failed to allocate buffer\n");
        printf("Exiting...");
        return 1;
    }

    printf("[Stage 3/5]: Writing opened file to buffer... ");

    unsigned long int ptrFileSizeRead = 0;

    if (quizrunner_writetobuffer(&ptrFile, &ptrFileSize, &ptrFileSizeRead, &ptrFileBuffer, debug)) {
        printf("[Error]: Failed to write file in buffer\n");
        printf("Exiting...");
        return 1;
    }

    printf("[Stage 4/5]: Closing opened file... ");
    quizrunner_closefile(&ptrFile, debug);

    /////////////////ENDOFPTRFILEBUFFERMANIPULATIONS//////////////////

    if (debug) {
        putch('\n');
        printf("[Debug]: Print what is saved in ptrFileBuffer");
        putch('\n');
        printf("%s", ptrFileBuffer);
        putch('\n');
        putch('\n');
    }

    printf("[Stage 5/5]: Running Quiz tests sequence... ");
    putch('\n');

    //run_quiz();

    getch();

    system("cls");

    return 0;
}