#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "hashtable.h"

void main2()
{
    //linkedlist *l = init_list();

    //printf("Hello world!\n");


    //int *data = malloc(sizeof(char) * 32);

    //*data = "swag";

    char *doc = malloc(sizeof(char) * 10);
    strcpy(doc, "document1");

    char *doc2 = malloc(sizeof(char) * 10);
    strcpy(doc2, "document2");

    char *doc3 = "doc3";

        char *doc4 = "doc4";

    char *a = malloc(sizeof(char) * 10);
    strcpy(a, "architecture");
    char *b = malloc(sizeof(char) * 10);
    strcpy(b, "test");
    char *c = malloc(sizeof(char) * 10);
    strcpy(c, "test1");

    printf("\nInit\n");
    hashtable *h = init_table(3);

    hash_table_insert(h, a, doc);
    hash_table_insert(h, a, doc);
    hash_table_insert(h, a, doc);
    hash_table_insert(h, a, doc);

    hash_table_insert(h, a, doc2);
    hash_table_insert(h, a, doc2);

    hash_table_insert(h, a, doc3);
    hash_table_insert(h, a, doc3);
    hash_table_insert(h, a, doc3);

        hash_table_insert(h, a, doc4);
    hash_table_insert(h, a, doc4);

    print_bucket(h, a);

    //printf(table_contains(h, "test") != NULL ? "\nYes\n" : "\nNo\n");
/**
    char *str = malloc(sizeof(char) * 8);
    strcpy(str, "swag");
    printf("%s\n", str);
    void *ptr;
    ptr = &str;

    printf("%s", *(char **)ptr);

    linkedlist *l = init_list();

    char *a = "applel";
    char *b = "sauce";
    char *c = "noob";
    char *d = malloc(sizeof(char) * 8);
    strcpy(d, "swaggg");
    add_node(l, a);
    add_node(l, b);
    add_node(l, c);
    add_node(l, d);

    //print_list(l);
    printf("%s\n", contains_str(l, "noobb") == 1 ? "YES" : "NO");*/
    /**printf("%s", *data);
    hashtable *h = init_table(17);
    hash_table_insert(h, data, data);

    //add_node(l, data);

    //print_list(l -> head, 0);

    //    exit(0);

    //char *ss = "fsssff";
    //add_node(l, &ss);

    //printList(l -> head, 0);

    //printf("%d", hash_code(ss));


    //printf("%d %d", *(l -> size), *(l -> head -> data));    */

}
