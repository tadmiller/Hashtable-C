/**
*
* @author Theodore Miller
* @description This is a LinkedList. There's not much I can say about it other than it's
*              incredibly simple.
*
*/


#ifndef linkedlist_h
#define linkedlist_h

#include <stdbool.h>

typedef struct node
{
    struct node *next;
    void *data;
} node;

typedef struct linkedlist
{
    node *head;
    int size;
} linkedlist;

linkedlist *init_lists(int num)
{
    linkedlist *l = malloc(sizeof(linkedlist) * num);

    int i = 0;
    for (i; i < num; i++)
    {
        (l + i) -> size = 0;
        (l + i) -> head = NULL;
    }

    return l;
}

linkedlist *init_list()
{
    linkedlist *l = malloc(sizeof(linkedlist));

    l -> size = 0;
    l -> head = NULL;

    return l;
}

void add_node(linkedlist *list, void *data)
{
    node *n = malloc(sizeof(node));
    n -> data = data;

    node *tmp = list -> head;

    list -> head = n;

    n -> next = tmp;

    list -> size += 1;
}

bool contains_str(linkedlist *list, void *str)
{
    node *n = list -> head;

    while (n != NULL)
    {
        char *s = (char *)(n -> data);

        printf("\n\"%s\"", s);

        if (strcmp(str, s) == 0)
            return true;

        n = n -> next;
    }

    return false;
}

// debug
void print_list(linkedlist *list)
{
    node *n = list -> head;

    int i = 0;
    while (n != NULL)
    {
         printf("\nnode:\t%d \ndata:\t%s\n", i++, (char *)(n -> data));
         n = n -> next;
    }
}

#endif
