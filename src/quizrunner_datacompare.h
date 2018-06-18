#ifndef _QUIZRUNNER_DATACOMPARE
#define _QUIZRUNNER_DATACOMPARE

#ifndef _QUIZRUNNER_NODESTRUCT_DEFINE
#define _QUIZRUNNER_NODESTRUCT_DEFINE

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

#endif

int quizrunner_datacompare(node_t * struct_01, node_t * struct_02, unsigned long int int_amountAnswers, char ** array_int_validityInputs, int int_01);
#endif