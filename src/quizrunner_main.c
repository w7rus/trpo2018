#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE MAX_PATH

int main(int argc, char *argv[]) {
    int version[3] = {0, 0, 1};
    unsigned char debug = 0;
    char directory[MAX_PATH] = ".\\build\\..\\data\\tests";

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

    if (chdir(directory)) {
        printf("Error: Failed to change dir to (%s)", directory);
        putch('\n');
        printf("Exiting...");
        exit(9);
    }

    printf("Please specity test filename: ");
    char inputFilename[255];
    scanf("%s", inputFilename);
    putch('\n');

    printf("Selected file: %s", inputFilename);
    putch('\n');
    printf("Stage: Opening... ");
    FILE * ptrFile = fopen(inputFilename, "r");

    if (ptrFile == NULL) {
        printf("Error: Failed to open file (%s)", inputFilename);
        putch('\n');
        printf("Exiting...");
        exit(9);
    }

    printf("Done!");
    putch('\n');

    printf("Stage: Allocating buffer for opened file... ");

    fseek(ptrFile, 0, SEEK_END);
	unsigned int ptrFileSize = ftell(ptrFile);
	rewind(ptrFile);

    char * ptrFileBuffer = (char*) malloc((sizeof(char) * ptrFileSize) + sizeof(char));

    if (ptrFileBuffer == NULL) {
        printf("Error: Failed to allocate buffer for (%d) bytes", ptrFileSize + sizeof(char));
        putch('\n');
        printf("Exiting...");
        exit(9);
    }

    printf("Done! (%d) Bytes", ptrFileSize + sizeof(char));
    putch('\n');

    printf("Stage: Writing opened file to buffer... ");

    unsigned int ptrFileSizeRead = fread(ptrFileBuffer, sizeof(char), ptrFileSize, ptrFile);

    if (ptrFileSizeRead != ptrFileSize) {
        printf("Error: Failed to write file in buffer");
        putch('\n');
        printf("Exiting...");
        exit(9);
    }

    ptrFileBuffer[ptrFileSize] = 0;

    printf("Done! Wrote (%d) out of (%d) Bytes", ptrFileSizeRead, ptrFileSize);
    putch('\n');

    printf("Stage: Closing opened file... ");
    fclose(ptrFile);
    printf("Done");
    putch('\n');
    putch('\n');

    if (debug) {
        printf("Debug: Print what is saved in ptrFileBuffer");
        putch('\n');
        printf("%s", ptrFileBuffer);
    }

    //run_quiz();

    getch();
    return 0;
}