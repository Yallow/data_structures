#ifndef dslib_list_sort_h
#define dslib_list_sort_h

#include <stdlib.h>

struct ListNode;

typedef struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    int *value;
} ListNode;

typedef struct List {
    ListNode *first;
    ListNode *last;
    int count;
} List;

// create the basic functions
List *List_create();
void List_sort(List *list);
void List_print(List *list);
void List_destoy(List *list);

// define a couple macros for the first and last nodes in the list
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)
#define List_last(A) ((A)->first != NULL ? (A)->first->value : NULL)

// define a macro to move through the whole list
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
    ListNode *V = NULL;\
    for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
