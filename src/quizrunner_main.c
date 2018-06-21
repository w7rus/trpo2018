#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "quizrunner_changedir.h"
#include "quizrunner_closefile.h"
#include "quizrunner_createbuffer.h"
#include "quizrunner_openfile.h"
#include "quizrunner_writetobuffer.h"
#include "quizrunner_printlist.h"
#include "quizrunner_addlistelement.h"
#include "quizrunner_dataextract.h"
#include "quizrunner_dataexchange.h"
#include "quizrunner_datacompare.h"

#define MAX_PATH (260)

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
    printf("Quiz Runner (version %d.%d.%d)", version[0], version[1], version[2]);
    if (debug) {
        printf(" [DEBUG]");
    }

    printf("\n\n[->]: Please input path to quiz tests directory (for default type \".\\bin\\..\\data\\tests\"): ");
    char workpath[MAX_PATH];
    scanf("%s", workpath);

    if (quizrunner_changedir(workpath, debug)) {
        printf("\033[0;31m[Error]\033[0m: Failed to change dir to (%s)\n", workpath);
        return 1;
    } else {
        if (getcwd(workpath, sizeof(workpath)) != NULL) {
            printf("\033[0;32m[Success]\033[0m: Current working directory is: \033[1;32m%s\033[0m\n", workpath);
        }
    }

    printf("\n[->]: Please specify Quiz test filename: ");
    char ptrFileName[255];
    scanf("%s", ptrFileName);

    /////////////////STARTOFPTRFILEBUFFERMANIPULATIONS//////////////////

    printf("\033[0;36m[Stage 1/11]\033[0m: Opening... ");

    FILE * ptrFile = NULL;

    if (quizrunner_openfile(&ptrFile, ptrFileName, debug, "rb")) {
        printf("\n\033[0;31m[Error]\033[0m: Failed to open file \033[7;31m%s\033[0m", ptrFileName);
        return 1;
    } else {
        printf("\033[0;32m[Success]\033[0m");
    }

    printf("\n\033[0;36m[Stage 2/11]\033[0m: Allocating buffer for opened file... ");

    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;

    int quizrunner_createbuffer_result = quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug);
    if (quizrunner_createbuffer_result) {
        if (quizrunner_createbuffer_result == 1) {
            printf("\n\033[0;31m[Error]\033[0m: Missing required data");
        }
        if (quizrunner_createbuffer_result == 2) {
            printf("\n\033[0;31m[Error]\033[0m: Limit of file size is \033[7;31m1 MB\033[0m");
        }
        if (quizrunner_createbuffer_result == 3) {
            printf("\n\033[0;31m[Error]\033[0m: Failed to allocate buffer");
        }
        return 1;
    } else {
        printf("\033[0;32m[Success]\033[0m");
    }

    printf("\n\033[0;36m[Stage 3/11]\033[0m: Writing opened file to buffer... ");

    unsigned long int ptrFileSizeRead = 0;

    int quizrunner_writetobuffer_result = quizrunner_writetobuffer(&ptrFile, &ptrFileSize, &ptrFileSizeRead, &ptrFileBuffer, debug);
    if (quizrunner_writetobuffer_result) {
        if (quizrunner_writetobuffer_result == 1) {
            printf("\n\033[0;31m[Error]\033[0m: Missing required data");
        }
        if (quizrunner_writetobuffer_result == 2) {
            printf("\n\033[0;31m[Error]\033[0m: Failed to write file to buffer");
        }
        return 1;
    } else {
        printf("\033[0;32m[Success]\033[0m");
    }

    printf("\n\033[0;36m[Stage 4/11]\033[0m: Closing opened file... ");

    if(quizrunner_closefile(&ptrFile, debug)) {
        printf("\n\033[0;31m[Error]\033[0m: Failed to close file");
        return 1;
    } else {
        printf("\033[0;32m[Success]\033[0m");
    }

    /////////////////ENDOFPTRFILEBUFFERMANIPULATIONS//////////////////

    if (debug) {
        printf("\n\n[DEBUG]: Print what is saved in ptrFileBuffer");
        printf("\n%s\n", ptrFileBuffer);
    }

    printf("\n\033[0;36m[Stage 5/11]\033[0m: Extracting data of Quiz test from buffer... ");

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

    int quizrunner_dataextract_result = quizrunner_dataextract(ptrFileSize, &ptrFileBuffer, debug, &quiz_detailsBuffer, &tail_listQuestion, &tail_listAnswer, &quiz_propAmount_Questions, &quiz_propAmount_Answers);
    if(quizrunner_dataextract_result) {
        if (quizrunner_dataextract_result == 1) {
            printf("\n\033[0;31m[Error]\033[0m: Missing required data");
        }
        if (quizrunner_dataextract_result == 2) {
            printf("\n\033[0;31m[Error]\033[0m: Quiz test structure is wrong");
        }
        return 1;
    } else {
        printf("\033[0;32m[Success]\033[0m");
    }

    if (quiz_detailsBuffer[0] != NULL || quiz_detailsBuffer[1] != NULL || quiz_detailsBuffer[2] != NULL || quiz_detailsBuffer[3] != NULL) {
        printf("\n\n\033[0;33m[INFO]\033[0m: ");
    }

    if (quiz_detailsBuffer[0] != NULL) {
        printf("\033[0;35m[Alias]\033[0m\n\t%s", quiz_detailsBuffer[0]);
    }

    if (quiz_detailsBuffer[1] != NULL) {
        printf("\n\t\033[0;35m[Description]\033[0m\n\t%s", quiz_detailsBuffer[1]);
    }

    if (quiz_detailsBuffer[2] != NULL) {
        printf("\n\t\033[0;35m[Author]\033[0m\n\t%s", quiz_detailsBuffer[2]);
    }

    if (quiz_detailsBuffer[3] != NULL) {
        printf("\n\t\033[0;35m[Completion time]\033[0m\n\t%s s.", quiz_detailsBuffer[3]);
    }

    if (debug) {
        printf("\n\n[DEBUG]: Print what is saved in head_listQuestion");
        quizrunner_printlist(head_listQuestion, debug);
        printf("\n\n[DEBUG]: Print what is saved in head_listAnswer");
        quizrunner_printlist(head_listAnswer, debug);
    }

    if (head_listQuestion -> next == 0 || head_listAnswer -> next == 0) {
        printf("\n\033[0;31m[Error]\033[0m: Missing required data. Quiz test has no questions or answers");
        return 1;
    }

    printf("\n\n\033[0;36m[Stage 6/11]\033[0m: Running Quiz test... ");
    printf("\n\033[0;33m[INFO]\033[0m: Please remeber, input strings MUST NOT contain whitespaces! Use underscores _ instead\n");

    unsigned long int timelogpoint01 = clock();

    int quizrunner_dataexchange_result = quizrunner_dataexchange(head_listQuestion, &tail_listInput, debug);
    if (quizrunner_dataexchange_result) {
        printf("\n\033[0;31m[Error]\033[0m: Missing required data");
        return 1;
    } else {
        printf("\n\033[0;32m[Success]\033[0m");
    }

    unsigned long int timelogpoint02 = clock();

    if (debug) {
        printf("\n\n[DEBUG]: Print what is saved in head_listInput");
        quizrunner_printlist(head_listInput, debug);
        printf("\n");
    }

    printf("\n\033[0;36m[Stage 7/11]\033[0m: Comparing user input data to answers... ");

    char * quiz_InputCheckArray = 0;
    quiz_InputCheckArray = malloc(sizeof(char) * quiz_propAmount_Answers);

    if (quizrunner_datacompare(head_listAnswer, head_listInput, quiz_propAmount_Answers, &quiz_InputCheckArray, debug)) {
        printf("\n\033[0;31m[Error]\033[0m: Missing required data");
        return 1;
    } else {
        printf("\n\033[0;32m[Success]\033[0m");
    }

    if (debug) {
        printf("\n\n[DEBUG: Print what is saved in quiz_InputCheckArray\n");
        printf("[");
        for (unsigned long int quiz_InputCheckArrayOffset = 0; quiz_InputCheckArrayOffset < quiz_propAmount_Answers; quiz_InputCheckArrayOffset++) {
            printf(" %d ", quiz_InputCheckArray[quiz_InputCheckArrayOffset]);
        }
        printf("]");
        printf("\n");
    }

    printf("\n\033[0;36m[Stage 7/11]\033[0m: Printing Quiz test pass data...");

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

    printf("\n\033[0;33m[INFO]\033[0m: Quiz test completed with %lu out of %lu correct answers", quiz_propAmount_correctInputs, quiz_propAmount_Answers);
    printf("\n\033[0;33m[INFO]\033[0m: Quiz test pass percentage is: %.2f", ((float) quiz_propAmount_correctInputs / quiz_propAmount_Answers) * 100);
    if (quiz_detailsBuffer[3] != NULL) {
        printf("\n\033[0;33m[INFO]\033[0m: Quiz test passing took %lu s. out of %s s.", (timelogpoint02 - timelogpoint01)/1000, quiz_detailsBuffer[3]);
    }

    printf("\n\n[->]: Do you want to save results to file? (y/n): ");
    char saveresult[3];
    scanf("%s", saveresult);

    if(saveresult[0] == 'y') {

        printf("\n\n[->]: Please input path to quiz tests results directory (for default type \".\\..\\results\"): ");
        scanf("%s", workpath);

        if (quizrunner_changedir(workpath, debug)) {
            printf("\033[0;31m[Error]\033[0m: Failed to change dir to (%s)\n", workpath);
            return 1;
        } else {
            if (getcwd(workpath, sizeof(workpath)) != NULL) {
                printf("\033[0;32m[Success]\033[0m: Current working directory is: \033[1;32m%s\033[0m\n", workpath);
            }
        }

        printf("\n[->]: Please specify Quiz test result filename: ");
        char ptrFileNameResult[255];
        scanf("%s", ptrFileNameResult);

        printf("\033[0;36m[Stage 9/11]\033[0m: Opening... ");

        FILE * ptrFileResult = NULL;

        if (quizrunner_openfile(&ptrFileResult, ptrFileNameResult, debug, "w")) {
            printf("\n\033[0;31m[Error]\033[0m: Failed to open file \033[7;31m%s\033[0m", ptrFileName);
            return 1;
        } else {
            printf("\033[0;32m[Success]\033[0m");
        }

        printf("\n\n\033[0;36m[Stage 10/11]\033[0m: Writing Quiz test pass data to file... ");

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

        printf("\033[0;32m[Success]\033[0m");

        printf("\n\033[0;36m[Stage 11/11]\033[0m: Closing opened file... ");

        if(quizrunner_closefile(&ptrFileResult, debug)) {
            printf("\n\033[0;31m[Error]\033[0m: Failed to close file");
            return 1;
        } else {
            printf("\033[0;32m[Success]\033[0m");
        }

    }

    printf("\n\033[0;33m[INFO]\033[0m: Exiting Quiz tests sequence... Hit any key to close...");

    system("cls");

    return 0;
}