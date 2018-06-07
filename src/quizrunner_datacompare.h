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

int quizrunner_datacompare(node_t * head_struct_pointer1, node_t * head_struct_pointer2, unsigned long int quiz_propAmount_Answers, char ** quiz_InputCheckArray, int debug);
#endif