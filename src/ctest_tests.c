#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

#include "ctest.h"

#define	MAX_PATH (260)

#ifndef _QUIZRUNNER_NODESTRUCT_DEFINE
#define _QUIZRUNNER_NODESTRUCT_DEFINE

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

#endif

int debug = 0;

CTEST(file_operations, changedir_1) {
    char dirpath[MAX_PATH] = "ctest_env";
    const int result = quizrunner_changedir(dirpath, debug);
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(file_operations, changedir_2) {
    char dirpath[MAX_PATH] = "\\/?*()<>|";
    const int result = quizrunner_changedir(dirpath, debug);
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(file_operations, changedir_3) {
    char dirpath[MAX_PATH] = "";
    const int result = quizrunner_changedir(dirpath, debug);
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(file_operations, openfile_1) {
    FILE * ptrFile = NULL;
    const int result = quizrunner_openfile(&ptrFile, "test.txt", debug, "rb");
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(file_operations, openfile_2) {
    FILE * ptrFile = NULL;
    const int result = quizrunner_openfile(&ptrFile, "\\/?*()<>|", debug, "rb");
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(file_operations, openfile_3) {
    FILE * ptrFile = NULL;
    const int result = quizrunner_openfile(&ptrFile, "", debug, "rb");
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(file_operations, closefile_1) {
    FILE * ptrFile = NULL;
    const int result = quizrunner_closefile(&ptrFile, debug);;
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(file_operations, closefile_2) {
    FILE * ptrFile = NULL;
    quizrunner_openfile(&ptrFile, "test.txt", debug, "rb");
    const int result = quizrunner_closefile(&ptrFile, debug);;
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(code_operations, createbuffer_1) {
    FILE * ptrFile = NULL;
    quizrunner_openfile(&ptrFile, "test.txt", debug, "rb");
    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;
    const int result = quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug);
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(code_operations, createbuffer_2) {
    FILE * ptrFile = NULL;
    quizrunner_openfile(&ptrFile, "410346.jpg", debug, "rb");
    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;
    const int result = quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug);
    const int expected = 2;
    ASSERT_EQUAL(expected, result);
}

CTEST(code_operations, createbuffer_3) {
    FILE * ptrFile = NULL;
    quizrunner_openfile(&ptrFile, "", debug, "rb");
    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;
    const int result = quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug);
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(code_operations, writetobuffer_1) {
    FILE * ptrFile = NULL;
    quizrunner_openfile(&ptrFile, "test.txt", debug, "rb");
    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;
    quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug);
    unsigned long int ptrFileSizeRead = 0;
    const int result = quizrunner_writetobuffer(&ptrFile, &ptrFileSize, &ptrFileSizeRead, &ptrFileBuffer, debug);
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(code_operations, writetobuffer_2) {
    FILE * ptrFile = NULL;
    quizrunner_openfile(&ptrFile, "", debug, "rb");
    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;
    quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug);
    unsigned long int ptrFileSizeRead = 0;
    const int result = quizrunner_writetobuffer(&ptrFile, &ptrFileSize, &ptrFileSizeRead, &ptrFileBuffer, debug);
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(code_operations, writetobuffer_3) {
    FILE * ptrFile = NULL;
    quizrunner_openfile(&ptrFile, "410346.jpg", debug, "rb");
    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;
    quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug);
    unsigned long int ptrFileSizeRead = 0;
    const int result = quizrunner_writetobuffer(&ptrFile, &ptrFileSize, &ptrFileSizeRead, &ptrFileBuffer, debug);
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(code_operations, printlist_1) {
    node_t * head_listQuestion;
    node_t * tail_listQuestion;
    head_listQuestion = tail_listQuestion = malloc(sizeof(node_t));
    head_listQuestion -> next = 0;
    head_listQuestion -> prev = 0;
    head_listQuestion -> data = 0;
    const int result = quizrunner_printlist(head_listQuestion, debug);
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(code_operations, printlist_2) {
    node_t * head_listQuestion;
    node_t * tail_listQuestion;
    head_listQuestion = tail_listQuestion = NULL;
    const int result = quizrunner_printlist(head_listQuestion, debug);
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}

CTEST(code_operations, dataextract_1) {
    FILE * ptrFile = NULL;
    quizrunner_openfile(&ptrFile, "test.txt", debug, "rb");
    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;
    quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug);
    unsigned long int ptrFileSizeRead = 0;
    quizrunner_writetobuffer(&ptrFile, &ptrFileSize, &ptrFileSizeRead, &ptrFileBuffer, debug);
    quizrunner_closefile(&ptrFile, debug);
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
    const int result = quizrunner_dataextract(ptrFileSize, &ptrFileBuffer, debug, &quiz_detailsBuffer, &tail_listQuestion, &tail_listAnswer, &quiz_propAmount_Questions, &quiz_propAmount_Answers);
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}

CTEST(code_operations, dataextract_2) {
    FILE * ptrFile = NULL;
    quizrunner_openfile(&ptrFile, "failtest01.txt", debug, "rb");
    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;
    quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug);
    unsigned long int ptrFileSizeRead = 0;
    quizrunner_writetobuffer(&ptrFile, &ptrFileSize, &ptrFileSizeRead, &ptrFileBuffer, debug);
    quizrunner_closefile(&ptrFile, debug);
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
    const int result = quizrunner_dataextract(ptrFileSize, &ptrFileBuffer, debug, &quiz_detailsBuffer, &tail_listQuestion, &tail_listAnswer, &quiz_propAmount_Questions, &quiz_propAmount_Answers);
    const int expected = 2;
    ASSERT_EQUAL(expected, result);
}

CTEST(code_operations, dataextract_3) {
    FILE * ptrFile = NULL;
    quizrunner_openfile(&ptrFile, "failtest01.txt", debug, "rb");
    unsigned long int ptrFileSize = 0;
    char * ptrFileBuffer = NULL;
    quizrunner_createbuffer(&ptrFile, &ptrFileSize, &ptrFileBuffer, debug);
    unsigned long int ptrFileSizeRead = 0;
    quizrunner_writetobuffer(&ptrFile, &ptrFileSize, &ptrFileSizeRead, &ptrFileBuffer, debug);
    quizrunner_closefile(&ptrFile, debug);
    char ** quiz_detailsBuffer = 0;
    quiz_detailsBuffer = NULL;

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
    const int result = quizrunner_dataextract(ptrFileSize, &ptrFileBuffer, debug, &quiz_detailsBuffer, &tail_listQuestion, &tail_listAnswer, &quiz_propAmount_Questions, &quiz_propAmount_Answers);
    const int expected = 1;
    ASSERT_EQUAL(expected, result);
}