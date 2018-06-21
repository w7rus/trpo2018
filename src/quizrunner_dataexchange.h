#ifndef _QUIZRUNNER_DATAEXCHANGE
#define _QUIZRUNNER_DATAEXCHANGE

#ifndef _QUIZRUNNER_NODESTRUCT_DEFINE
#define _QUIZRUNNER_NODESTRUCT_DEFINE

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

#endif

int quizrunner_dataexchange(node_t * struct_01, node_t ** struct_02, int int_01);
#endif