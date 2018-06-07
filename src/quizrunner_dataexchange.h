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

int quizrunner_dataexchange(node_t * head_struct_pointer, node_t ** adressof_tail_struct_pointer, int debug);
#endif