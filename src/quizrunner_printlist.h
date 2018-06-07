#ifndef _QUIZRUNNER_PRINTLIST
#define _QUIZRUNNER_PRINTLIST

#ifndef _QUIZRUNNER_NODESTRUCT_DEFINE
#define _QUIZRUNNER_NODESTRUCT_DEFINE

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

#endif

int quizrunner_printlist(node_t * head_struct_pointer, int debug);
#endif