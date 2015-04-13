#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dbg.h" 
#include "list_sort.h" 

// create a new list (simply allocates space)
List *List_create()
{
    return calloc(1, sizeof(List));
}

void List_populate(List *list)
{
    int i;
    int values[] = {1, 7, 3 ,8, 1, 5};
    // create a new node
    ListNode *node = calloc(1, sizeof(ListNode));
    node->value = 1;
    // setup the first node that begins the list
    list->first = node;
    for(i = 1; i < (sizeof(values) / sizeof(int)); i++) {
        // create a new node to hold the next value
        node->next = calloc(1, sizeof(ListNode));
        node = node->next;
        node->value = values[i];
    } 
    // add the final node that ends the list
    list->last = node;
    list->last->next = NULL;
}

void List_print(List *list)
{
   // create a node to step through the list
   ListNode *node = calloc(1, sizeof(ListNode));
   // walk through the list
   node = list->first;
   while(node != NULL) {
       printf("%d\n", node->value);
       node = node->next;
   }
}

void List_sort(List *list)
{
    bool sorted = false;
    // create a node to step through the list
    ListNode *node = calloc(1, sizeof(ListNode));
    // walk through the list
    while(!sorted) {
        sorted = true;
        node = list->first;
        while(node->next != NULL) {
            if(node->value > node->next->value) {
                void *temp = node->next->value; 
                node->next->value = node->value;
                node->value = temp;
                sorted = false;
                // for troubleshooting purposes
                printf("Switched %d with %d\n", node->next->value, node->value);
            } else {
                // for troubleshooting purposes
                printf("Didn't switch %d with %d\n", node->value, node->next->value);
            }
            node = node->next;
        }
    }
}
int main(int argc, char *argv[])
{
    List *list = List_create();
    List_populate(list);
    List_print(list);
    List_sort(list);
    List_print(list);

    return 0;
}
