#ifndef _QUIZRUNNER_DATAEXTRACT
#define _QUIZRUNNER_DATAEXTRACT

#ifndef _QUIZRUNNER_NODESTRUCT_DEFINE
#define _QUIZRUNNER_NODESTRUCT_DEFINE

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

#endif

int quizrunner_dataextract(unsigned long int file_01_size, char ** file_01_buffer, int int_01, char *** array_string_01, node_t ** struct_01, node_t ** struct_02, unsigned long int * int_amountQuestions, unsigned long int * int_amountAnswers);
#endif