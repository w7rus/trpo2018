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