#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

#include "quizrunner_changedir.h"
#include "quizrunner_closefile.h"
#include "quizrunner_createbuffer.h"
#include "quizrunner_openfile.h"
#include "quizrunner_writetobuffer.h"

#define BUFSIZE MAX_PATH

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

void quizrunner_addListElement(node_t ** tail, char * input) {
    node_t * p = malloc(sizeof(node_t));
    p -> next = 0;
    p -> prev = *tail;
    (*tail) -> next = p;
    *tail = p;
    p -> data = input;
}

void quizrunner_printList(node_t * p) {
    for (p = p -> next; p; p = p -> next) {
        printf("[%p] %s\n", p, p -> data);
    }
}

int run_quizDataExtraction(unsigned long int ptrFileSize, char ** ptrFileBuffer, int debug, char *** quiz_detailsBuffer, node_t ** tail_listQuestion, node_t ** tail_listAnswer) {
    char quiz_propAlias_Buffer[16];
    int quiz_propAlias_BufferOffset = 0;
    int quiz_propMode = 0;
    unsigned long int quiz_propValue_BufferOffset = 0;

    putch('\n');

    for (unsigned long int ptrFileBufferOffset = 0; ptrFileBufferOffset < ptrFileSize; ptrFileBufferOffset++) {
        if ((*ptrFileBuffer)[ptrFileBufferOffset] == '\n') {
            quiz_propMode = 0;
            continue;
        }

        if ((*ptrFileBuffer)[ptrFileBufferOffset] == '=') {
            if ((*ptrFileBuffer)[ptrFileBufferOffset + 1] == '\n') {
                return 1;
            }
            quiz_propMode = 1;
            quiz_propAlias_Buffer[quiz_propAlias_BufferOffset] = 0;
            if (debug) {
                printf("[DEBUG]: Function printed (quiz_propAlias_Buffer %s)\n", quiz_propAlias_Buffer);
                printf("[DEBUG]: Function printed (quiz_propAlias_BufferOffset %d)\n", quiz_propAlias_BufferOffset);
            }
            quiz_propAlias_BufferOffset = 0;
            continue;
        }

        if (quiz_propMode == 0) {
            quiz_propAlias_Buffer[quiz_propAlias_BufferOffset] = (*ptrFileBuffer)[ptrFileBufferOffset];
            quiz_propAlias_BufferOffset++;
        }

        if (quiz_propMode == 1) {
            quiz_propValue_BufferOffset = ptrFileBufferOffset;

            while ((*ptrFileBuffer)[quiz_propValue_BufferOffset] != '\n') {
                quiz_propValue_BufferOffset++;
            }

            if (debug) {
                printf("[DEBUG]: Function printed (ptrFileBufferOffset %lu)\n", ptrFileBufferOffset);
                printf("[DEBUG]: Function printed (quiz_propValue_BufferOffset %lu)\n", quiz_propValue_BufferOffset);
                printf("[DEBUG]: Function printed (quizPropValueSize %lu)\n", quiz_propValue_BufferOffset - ptrFileBufferOffset);
            }

            char * quiz_propValue_Buffer = 0;
            quiz_propValue_Buffer = (char*) malloc((sizeof(char) * (quiz_propValue_BufferOffset - ptrFileBufferOffset) + sizeof(char)));

            for (unsigned int quiz_propValue_BufferOffsetRelative = 0; ptrFileBufferOffset < quiz_propValue_BufferOffset;) {
                quiz_propValue_Buffer[quiz_propValue_BufferOffsetRelative] = (*ptrFileBuffer)[ptrFileBufferOffset];
                quiz_propValue_Buffer[quiz_propValue_BufferOffsetRelative + 1] = 0;
                ptrFileBufferOffset++;
                quiz_propValue_BufferOffsetRelative++;
            }

            if (debug) {
                printf("[DEBUG]: Function printed (quiz_propValue_Buffer %s)\n\n", quiz_propValue_Buffer);
            }

            quiz_propMode = 0;

            if (strcmp(quiz_propAlias_Buffer, "NAME") == 0) {
               (*quiz_detailsBuffer)[0] = quiz_propValue_Buffer;
            }

            if (strcmp(quiz_propAlias_Buffer, "DESCRIPTION") == 0) {
                (*quiz_detailsBuffer)[1] = quiz_propValue_Buffer;
            }

            if (strcmp(quiz_propAlias_Buffer, "AUTHOR") == 0) {
                (*quiz_detailsBuffer)[2] = quiz_propValue_Buffer;
            }

            if (strcmp(quiz_propAlias_Buffer, "TIME") == 0) {
                (*quiz_detailsBuffer)[3] = quiz_propValue_Buffer;
            }

            if (strcmp(quiz_propAlias_Buffer, "QUESTION") == 0) {
                quizrunner_addListElement(*(&tail_listQuestion), quiz_propValue_Buffer);
            }

            if (strcmp(quiz_propAlias_Buffer, "ANSWER") == 0) {
                quizrunner_addListElement(*(&tail_listAnswer), quiz_propValue_Buffer);
            }
        }
    }

    return 0;
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

    printf("Please specity tests directory path (for default type \".\\bin\\..\\data\\tests\"): ");
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

    printf("[Stage 1/6]: Opening... ");

    FILE * ptrFile = NULL;

    if (quizrunner_openfile(&ptrFile, ptrFileName, debug)) {
        printf("[Error]: Failed to open file (%s)", ptrFileName);
        putch('\n');
        printf("Exiting...");
        return 1;
    }

    printf("[Stage 2/6]: Allocating buffer for opened file... ");

    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;

    if (quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug)) {
        printf("[Error]: Failed to allocate buffer\n");
        printf("Exiting...");
        return 1;
    }

    printf("[Stage 3/6]: Writing opened file to buffer... ");

    unsigned long int ptrFileSizeRead = 0;

    if (quizrunner_writetobuffer(&ptrFile, &ptrFileSize, &ptrFileSizeRead, &ptrFileBuffer, debug)) {
        printf("[Error]: Failed to write file in buffer\n");
        printf("Exiting...");
        return 1;
    }

    printf("[Stage 4/6]: Closing opened file... ");
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

    printf("[Stage 5/6]: Running Quiz tests data extraction sequence... ");
    putch('\n');

    //TODO: Make structure list of pointers to questions strings

    char ** quiz_detailsBuffer = 0;
    quiz_detailsBuffer = malloc(sizeof(char *) * 4);
    quiz_detailsBuffer[0] = NULL;
    quiz_detailsBuffer[1] = NULL;
    quiz_detailsBuffer[2] = NULL;
    quiz_detailsBuffer[3] = NULL;

    node_t * head_listQuestion;
    node_t * tail_listQuestion;
    head_listQuestion = tail_listQuestion = malloc(sizeof(node_t));
    head_listQuestion -> next = 0;
    head_listQuestion -> prev = 0;
    head_listQuestion -> data = 0;

    node_t * head_listAnswer;
    node_t * tail_listAnswer;
    head_listAnswer = tail_listAnswer = malloc(sizeof(node_t));
    head_listAnswer -> next = 0;
    head_listAnswer -> prev = 0;
    head_listAnswer -> data = 0;

    node_t * head_listInput;
    node_t * tail_listInput;
    head_listInput = tail_listInput = malloc(sizeof(node_t));
    head_listInput -> next = 0;
    head_listInput -> prev = 0;
    head_listInput -> data = 0;

    if(run_quizDataExtraction(ptrFileSize, &ptrFileBuffer, debug, &quiz_detailsBuffer, &tail_listQuestion, &tail_listAnswer)) {
        printf("[Error]: Syntax error\n");
        printf("Exiting...");
        return 0;
    }

    if (quiz_detailsBuffer[0] != NULL) {
        printf("Quiz Name: %s\n", quiz_detailsBuffer[0]);
    }

    if (quiz_detailsBuffer[1] != NULL) {
        printf("Quiz Description: %s\n", quiz_detailsBuffer[1]);
    }

    if (quiz_detailsBuffer[2] != NULL) {
        printf("Quiz Author: %s\n", quiz_detailsBuffer[2]);
    }

    if (quiz_detailsBuffer[3] != NULL) {
        printf("Quiz Completion time: %s\n", quiz_detailsBuffer[3]);
    }

    if (debug) {
        putch('\n');
        printf("[Debug]: Print what is saved in head_listQuestion\n");
        quizrunner_printList(head_listQuestion);
        putch('\n');
        printf("[Debug]: Print what is saved in head_listAnswer\n");
        quizrunner_printList(head_listAnswer);
    }

    putch('\n');

    printf("[Stage 6/6]: Running Quiz... ");
    putch('\n');

    printf("[INFO]: Exiting Quiz tests sequence... ");
    putch('\n');

    getch();

    system("cls");

    return 0;
}