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

int quizrunner_dataextract(unsigned long int ptrFileSize, char ** ptrFileBuffer, int debug, char *** quiz_detailsBuffer, node_t ** adressof_tail_struct_pointer1, node_t ** adressof_tail_struct_pointer2, unsigned long int * quiz_propAmount_Questions, unsigned long int * quiz_propAmount_Answers);
#endif