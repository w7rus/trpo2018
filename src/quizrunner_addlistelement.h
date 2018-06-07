#ifndef _QUIZRUNNER_ADDLISTELEMENT
#define _QUIZRUNNER_ADDLISTELEMENT

#ifndef _QUIZRUNNER_NODESTRUCT_DEFINE
#define _QUIZRUNNER_NODESTRUCT_DEFINE

typedef struct node {
    struct node * next;
    struct node * prev;
    char * data;
} node_t;

#endif

int quizrunner_addlistelement(node_t ** adressof_tail_struct_pointer, char * string_pointer, int debug);
#endif