/**
*
* @author Theodore Miller
* @description This is the HashTable. It has an occurencenode and a wordnode.
*              The wordnode is what is stored in the buckets (LinkedLists) in the
*              HashTable. It has its own LinkedList, much like implementation 2 from the
*              project 5 definition, and stores a word with various properties.
*              Each LinkedList contains occurencenodes, which keep track of the individual documents that contain a word
*
*/

#ifndef hashtable_h
#define hashtable_h
#include <stdbool.h>
#include "linkedlist.h"
#include "etc.h"

// HASHTABLE -> WORDNODE -> OCCURENCENODE
typedef struct wordnode
{
    linkedlist *occurences;
    char *word;
    // 2 log10(totaldocs/occurences->size)
    double idf;
    // 4 sum of idfi
    double relevance;
} wordnode;

typedef struct occurencenode
{
    char *doc;
    // 1
    int tf;
    // 3 tf * idf
    double idfi;
} occurencenode;

typedef struct hashtable
{
    linkedlist **buckets;
    int size;
    int docs;
} hashtable;

/**
* This hash function takes a string s,
* and for each character, takes that number
*/
int hash_code(char *str)
{
    int i = 0;
    int hash = 0;

    while (*(str + i) != '\0')
        hash += (*(str + i)) * (int)power(10, i++);

    return hash < 0 ? -hash : hash;
}

// Returns a pointer to an wordnode if TRUE. Else returns NULL.
wordnode *contains_wordnode(linkedlist *list, void *str)
{
    node *n = list -> head;

    while (n != NULL)
    {
        char *s = (((wordnode *)(n -> data)) -> word);

        //printf("\n\"%s\"", s);

        if (strcmp(str, s) == 0)
            return n -> data;

        n = n -> next;
    }

    return NULL;
}

// Returns a pointer to an occurencenode if TRUE. Else returns NULL.
occurencenode *contains_occurencenode(linkedlist *list, void *str)
{
    //printf("\nstart contains_occurencenode\n");
    node *n = list -> head;

    //printf("\nSIZE: %d", list->size);

    while (n != NULL)
    {
        //printf("\n data: \"");
        //void *p = ((occurencenode *)(n -> data)) -> doc;

        //printf(p == NULL ? "\nSwag" : "\nNope");

        char *s = ((occurencenode *)(n -> data)) -> doc;
        //printf("%s\"\n", s);
        occurencenode *o = n -> data;

        if (strcmp(str, s) == 0)
            return n -> data;

        n = n -> next;
    }

    //printf("\nreturning NULL");
    return NULL;
}

// For debugging.
void print_bucket(hashtable *table, char *str)
{
    int bucket = hash_code(str) % table -> size;

    linkedlist *l = *(table -> buckets);
    node *n = l -> head;

    printf("\nSIZEOF LL TABLE: %d\n", l->size);

    linkedlist *ll = ((wordnode *)(l->head->data))->occurences;

    printf("\nSIZEOF LL OCCUR: %d\n", ll->size);
    printf("\nWORD: %s\n", ((wordnode *)(l->head->data))->word);
    printf("\nNODE 1: %s\n", ((occurencenode *)(((wordnode *)(l->head->data))->occurences->head->data))->doc);
    printf("\nNODE 1: %d\n", ((occurencenode *)(((wordnode *)(l->head->data))->occurences->head->data))->tf);
    printf("\nNODE 2: %s\n", ((occurencenode *)(((wordnode *)(l->head->data))->occurences->head->next->data))->doc);
    printf("\nNODE 2: %d\n", ((occurencenode *)(((wordnode *)(l->head->data))->occurences->head->next->data))->tf);
}

// Inserts into the hashtable specified, the string as a wordnode, and the document as an occurencenode.
void hash_table_insert(hashtable *table, char *str, char *document)
{
    if (str == NULL)
    {
        printf("\nSOMETHING WENT WRONG");
        return;
    }
    int bucket = hash_code(str) % (table -> size);

    // malloc the proper size for the string we'll be storing.
    char *insertWord = malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(insertWord, str);

    // Get the LinkedList for the bucket we'll be using.
    linkedlist *l = (table -> buckets)[bucket];

    wordnode *w = contains_wordnode(l, insertWord);

    if (w == NULL)
    {
        //printf("\nNo wordnode found.\n");
        // case for if wordnode is there but occurencenode is not
        wordnode *n = malloc(sizeof(wordnode));
        n -> word = insertWord;
        n -> occurences = init_list();

        add_node(l, n);

        occurencenode *occ = malloc(sizeof(occurencenode));
        occ -> doc = malloc(sizeof(char) * strlen(document));
        occ -> tf = 1;

        strcpy(occ -> doc, document);

        add_node(n -> occurences, occ);
    }
    else
    {
        //printf("\nWordnode found!\n");
        occurencenode *o = contains_occurencenode(w -> occurences, document);

        if (o == NULL)
        {
            //printf("\nNo occurencenode found!\n");
            occurencenode *occ = malloc(sizeof(occurencenode));

            char *d = malloc(sizeof(char) * strlen(document));
            strcpy(d, document);

            occ -> doc = d;
            occ -> tf = 1;

            add_node(w -> occurences, occ);
            //printf("\nDone insert\n");

            return;
        }
        else
        {
            //printf("\noccurencenode found!\n");
            o -> tf = (o -> tf) + 1;
        }
    }
}

wordnode *get_occurences(hashtable *table, char *str)
{
    int bucket = hash_code(str) % (table -> size);

    //printf("\nTable Size: %d", table->size);
    //printf("\nDoc: %s", str);
    linkedlist *ll = (table->buckets)[bucket];
    //return contains_wordnode(*(table -> buckets + bucket), str);
    return contains_wordnode(ll, str);
}

// balance a hashtable to a new one. Not yet implemented.
hashtable *balance(hashtable *input)
{
    return input;
}

// Initialize a table of size b.
hashtable *init_table(int b)
{
    hashtable *table = malloc(sizeof(hashtable));
    int i;

        //table -> buckets = init_lists(size);
    linkedlist **ll = malloc(sizeof(linkedlist *) * b);

    for (i = 0; i < b; i++)
        *(ll + i) = init_list();

    table -> buckets = ll;
    //table -> docs = fn;
    table -> size = b;
    //int f = (*table)->size;//(**table).size;

    return table;
}

#endif
