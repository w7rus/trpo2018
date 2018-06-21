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

int quizrunner_addlistelement(node_t ** struct_01, char * string_01, int int_01);
#endif