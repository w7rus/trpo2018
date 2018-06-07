#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "quizrunner_changedir.h"
#include "quizrunner_closefile.h"
#include "quizrunner_createbuffer.h"
#include "quizrunner_openfile.h"
#include "quizrunner_openfile_write.h"
#include "quizrunner_writetobuffer.h"
#include "quizrunner_printlist.h"
#include "quizrunner_addlistelement.h"
#include "quizrunner_dataextract.h"
#include "quizrunner_dataexchange.h"
#include "quizrunner_datacompare.h"

#define BUFSIZE MAX_PATH

#ifndef _QUIZRUNNER_NODESTRUCT_DEFINE
#define _QUIZRUNNER_NODESTRUCT_DEFINE

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

#endif

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

    printf("[Stage 1/11]: Opening... ");

    FILE * ptrFile = NULL;

    if (quizrunner_openfile(&ptrFile, ptrFileName, debug)) {
        printf("[Error]: Failed to open file (%s)", ptrFileName);
        putch('\n');
        printf("Exiting...");
        return 1;
    }

    printf("[Stage 2/11]: Allocating buffer for opened file... ");

    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;

    if (quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug)) {
        printf("[Error]: Failed to allocate buffer\n");
        printf("Exiting...");
        return 1;
    }

    printf("[Stage 3/11]: Writing opened file to buffer... ");

    unsigned long int ptrFileSizeRead = 0;

    if (quizrunner_writetobuffer(&ptrFile, &ptrFileSize, &ptrFileSizeRead, &ptrFileBuffer, debug)) {
        printf("[Error]: Failed to write file in buffer\n");
        printf("Exiting...");
        return 1;
    }

    printf("[Stage 4/11]: Closing opened file... ");
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

    printf("[Stage 5/11]: Running Quiz tests data extraction sequence...\n");

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

    unsigned long int quiz_propAmount_Questions = 0;
    unsigned long int quiz_propAmount_Answers = 0;

    if(quizrunner_dataextract(ptrFileSize, &ptrFileBuffer, debug, &quiz_detailsBuffer, &tail_listQuestion, &tail_listAnswer, &quiz_propAmount_Questions, &quiz_propAmount_Answers)) {
        printf("[Error]: Please use -debug launch parameter to trace error...\n");
        printf("Exiting...");
        return 1;
    }

    if (quiz_detailsBuffer[0] != NULL || quiz_detailsBuffer[1] != NULL || quiz_detailsBuffer[2] != NULL || quiz_detailsBuffer[3] != NULL) {
        printf("[INFO]: Quiz details\n");
    }

    if (quiz_detailsBuffer[0] != NULL) {
        printf("\tName: %s\n", quiz_detailsBuffer[0]);
    }

    if (quiz_detailsBuffer[1] != NULL) {
        printf("\tDescription: %s\n", quiz_detailsBuffer[1]);
    }

    if (quiz_detailsBuffer[2] != NULL) {
        printf("\tAuthor: %s\n", quiz_detailsBuffer[2]);
    }

    if (quiz_detailsBuffer[3] != NULL) {
        printf("\tTime: %s s.\n", quiz_detailsBuffer[3]);
    }

    if (quiz_detailsBuffer[0] != NULL || quiz_detailsBuffer[1] != NULL || quiz_detailsBuffer[2] != NULL || quiz_detailsBuffer[3] != NULL) {
        putch('\n');
    }

    if (debug) {
        printf("[Debug]: Print what is saved in head_listQuestion\n");
        quizrunner_printlist(head_listQuestion, debug);
        printf("\n[Debug]: Print what is saved in head_listAnswer\n");
        quizrunner_printlist(head_listAnswer, debug);
        putch('\n');
    }

    if (head_listQuestion -> next == 0 || head_listAnswer -> next == 0) {
        printf("[Error]: No required data found\n");
        printf("[INFO]: Quiz must have at least single question and answer to proceed\n");
        printf("Exiting...");
        return 1;
    }

    printf("[Stage 6/11]: Running Quiz...");
    putch('\n');
    printf("Please remeber, input strings MUST NOT contain whitespaces!");
    putch('\n');

    unsigned long int timelogpoint01 = clock();

    quizrunner_dataexchange(head_listQuestion, &tail_listInput, debug);

    unsigned long int timelogpoint02 = clock();

    if (debug) {
        printf("\n[Debug]: Print what is saved in head_listInput\n");
        quizrunner_printlist(head_listInput, debug);
        putch('\n');
    }

    if (debug == 0) {
        putch('\n');
    }

    printf("[Stage 7/11]: Running Quiz test data comparizon sequence...");
    putch('\n');

    char * quiz_InputCheckArray = 0;
    quiz_InputCheckArray = malloc(sizeof(char) * quiz_propAmount_Answers);

    quizrunner_datacompare(head_listAnswer, head_listInput, quiz_propAmount_Answers, &quiz_InputCheckArray, debug);

    if (debug) {
        printf("\n[Debug]: Print what is saved in quiz_InputCheckArray\n");
        putch('[');
        for (unsigned long int quiz_InputCheckArrayOffset = 0; quiz_InputCheckArrayOffset < quiz_propAmount_Answers; quiz_InputCheckArrayOffset++) {
            printf(" %d ", quiz_InputCheckArray[quiz_InputCheckArrayOffset]);
        }
        putch(']');
        putch('\n');
    }

    printf("[Stage 8/11]: Printing Quiz test pass data...");
    putch('\n');

    unsigned long int quiz_propAmount_correctInputs = 0;
    unsigned long int quiz_propAmount_wrongInputs = 0;

    for (unsigned long int quiz_InputCheckArrayOffset = 0; quiz_InputCheckArrayOffset < quiz_propAmount_Answers; quiz_InputCheckArrayOffset++) {
        if (quiz_InputCheckArray[quiz_InputCheckArrayOffset] == 1) {
            quiz_propAmount_correctInputs++;
        }
        if (quiz_InputCheckArray[quiz_InputCheckArrayOffset] == 0) {
            quiz_propAmount_wrongInputs++;
        }
    }

    printf("\n[INFO]: Test completed with %lu out of %lu correct answers\n", quiz_propAmount_correctInputs, quiz_propAmount_Answers);
    printf("[INFO]: Test pass percentage is: %.2f\n", ((float) quiz_propAmount_correctInputs / quiz_propAmount_Answers) * 100);
    if (quiz_detailsBuffer[3] != NULL) {
        printf("[INFO]: Test pass took %lu s. out of %s s.\n\n", (timelogpoint02 - timelogpoint01)/1000, quiz_detailsBuffer[3]);
    }

    printf("[Stage 9/11]: Writing Quiz test pass data to file...");
    putch('\n');

    printf("Please specity results directory path (for default type \".\\..\\results\"): ");
    scanf("%s", dirpath);

    if (quizrunner_changedir(dirpath, debug)) {
        printf("[Error]: Failed to change dir to (%s)\n", dirpath);
        printf("Exiting...");
        return 1;
    }

    printf("Please specity test results filename: ");
    char ptrFileNameResult[255];
    scanf("%s", ptrFileNameResult);
    printf("Selected file: %s\n", ptrFileNameResult);

    printf("[Stage 10/11]: Opening...");
    putch('\n');

    FILE * ptrFileResult = NULL;

    if (quizrunner_openfile_write(&ptrFileResult, ptrFileNameResult, debug)) {
        printf("[Error]: Failed to open file (%s)", ptrFileNameResult);
        putch('\n');
        printf("Exiting...");
        return 1;
    }

    fputs("Filename: ", ptrFileResult);
    fputs(ptrFileName, ptrFileResult);
    fputc('\n', ptrFileResult);

    if (quiz_detailsBuffer[0] != NULL) {
        fputs("Name: ", ptrFileResult);
        fputs(quiz_detailsBuffer[0], ptrFileResult);
        fputc('\n', ptrFileResult);
    }

    if (quiz_detailsBuffer[1] != NULL) {
        fputs("Description: ", ptrFileResult);
        fputs(quiz_detailsBuffer[1], ptrFileResult);
        fputc('\n', ptrFileResult);
    }

    if (quiz_detailsBuffer[2] != NULL) {
        fputs("Author: ", ptrFileResult);
        fputs(quiz_detailsBuffer[2], ptrFileResult);
        fputc('\n', ptrFileResult);
    }

    if (quiz_detailsBuffer[3] != NULL) {
        fputs("Time: ", ptrFileResult);
        fputs(quiz_detailsBuffer[3], ptrFileResult);
        fputs(" s.", ptrFileResult);
        fputc('\n', ptrFileResult);
    }

    unsigned long int quiz_InputCheckArrayOffset = 0;

    for (node_t * head_listQuestion_offset = head_listQuestion -> next, * head_listAnswer_offset = head_listAnswer -> next, * head_listInput_offset = head_listInput -> next; head_listAnswer_offset; head_listQuestion_offset = head_listQuestion_offset -> next, head_listAnswer_offset = head_listAnswer_offset -> next, head_listInput_offset = head_listInput_offset -> next) {
        fputc('\n', ptrFileResult);
        fputs("Question: ", ptrFileResult);
        fputs(head_listQuestion_offset -> data, ptrFileResult);
        fputc('\n', ptrFileResult);

        fputs("Answer: ", ptrFileResult);
        fputs(head_listAnswer_offset -> data, ptrFileResult);
        fputc('\n', ptrFileResult);

        fputs("Input: ", ptrFileResult);
        fputs(head_listInput_offset -> data, ptrFileResult);
        fputc('\n', ptrFileResult);

        fputs("Valid: ", ptrFileResult);
        if (quiz_InputCheckArray[quiz_InputCheckArrayOffset]) {
            fputs("Yes", ptrFileResult);
        } else {
            fputs("False", ptrFileResult);
        }
        quiz_InputCheckArrayOffset++;
        fputc('\n', ptrFileResult);
    }

    fputc('\n', ptrFileResult);

    fprintf(ptrFileResult, "[INFO]: Test completed with %lu out of %lu correct answers\n", quiz_propAmount_correctInputs, quiz_propAmount_Answers);
    fprintf(ptrFileResult, "[INFO]: Test pass percentage is: %.2f\n", ((float) quiz_propAmount_correctInputs / quiz_propAmount_Answers) * 100);
    if (quiz_detailsBuffer[3] != NULL) {
        fprintf(ptrFileResult, "[INFO]: Test pass took %lu s. out of %s s.", (timelogpoint02 - timelogpoint01)/1000, quiz_detailsBuffer[3]);
    }

    fflush(ptrFileResult);

    printf("[Stage 11/11]: Closing opened file... ");
    quizrunner_closefile(&ptrFileResult, debug);

    printf("[INFO]: Exiting Quiz tests sequence...");
    putch('\n');

    getch();

    system("cls");

    return 0;
}