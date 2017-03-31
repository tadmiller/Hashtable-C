/**
*
* @author Theodore Miller
* @description This .h file contains all the functions to run commands from the prompt
*              and get input from the user.
*
*/

#ifndef cmdutil_h
#define cmdutil_h
#include "hashtable.h"
#include <string.h>

// FUNCTION DEFINITIONS
void get_args(int argc, char *argv[], char **FILEPATH, char **FILENUMBER, char **BUCKETS);
void help();
void close();

/**
* Print help options for a user,
* then exit the program.
*
* @arg NULL
* @return NULL
*/
void help()
{
    printf("\n[USAGE]\n");

    printf("\n[-p FILEPATH]\n");
    printf("\n[-n FILE NUMBER], [USE \"*\" FOR ARBITRARY]\n");
    printf("\n[-b BUCKETS]\n");

    printf("\n[EXAMPLE]\t./engine -p 'C:\\myfiles\\*.txt'\n");
    printf("\n\t\tOPEN IN C:\\myfiles all txt files\n");
    printf("\n[EXAMPLE]\t./engine -p 'C:\\myfiles\\' -n 3 -b 17\n");
    printf("\n\t\tOPEN IN C:\\myfiles D1, D2, D3");

    close();
}

void get_args(int argc, char *argv[], char **FILEPATH, char **FILENUMBER, char **BUCKETS)
{
    if (argc <= 2)
        help();

    // Set i = 1. We
    int i = 1;

    for (i; i < argc; i++)
    {
        if (strcmp(*(argv + i), "-h") == 0)
            help();
        else if (strcmp(*(argv + i), "-p") == 0)
            *FILEPATH = *(argv + i + 1);
        else if (strcmp(*(argv + i), "-n") == 0)
            *FILENUMBER = *(argv + i + 1);
        else if (strcmp(*(argv + i), "-b") == 0)
            *BUCKETS = *(argv + i + 1);
            // wildcard character input thing using substring to check for .exe or .o
            //if (memcpy)
    }

    return;
}

// Flush stdin since we don't want things trailing from one scanf to another.
void flushIn()
{
    while(getchar() != '\n');
    fflush(stdin);
}

char *get_query()
{
    char *buffer = malloc(sizeof(char) * 1024);
    char option = 'A';

    while (1)
    {
        printf("\nEnter S for search, or X to exit: ");
        scanf("%c", &option);

        if (option == 'S' || option == 's')
            break;
        else if (option == 'X' || option == 'x')
            close();
        else
            printf("\nInvalid input");
        flushIn();
    }

    flushIn();
    printf("\nEnter query: ");
    scanf("%1024[^\n]", buffer);
    flushIn();

    return buffer;
}

void print_wordnode(wordnode *w)
{
    if (w == NULL)
        return;

    printf("\n\nWORD:\t%s", w -> word);
    printf("\nDF:\t%d", w -> occurences -> size);
    printf("\nREL:\t%lf", w -> relevance);

    node *n = w -> occurences -> head;
    int i = 0;
    while (n != NULL)
    {
        printf("\n\nDOC:\t%d", i++);
        printf("\nPATH:\t%s", ((occurencenode*)n->data)->doc);
        printf("\nFREQ:\t%d", ((occurencenode*)n->data)->tf);

        n = n -> next;
    }
}

void read_query(char *query, hashtable *table)
{
    printf("\nQuery is: %s\n", query);
    int i = 0;
    int start = 0;
    int nodeItr = -1;
    wordnode **nodes = 0;
    // clear buffer
    char *buffer = malloc(sizeof(char));
    free(buffer);

    while (*(query + i) != '\0')
    {
        start = i;

        while (*(query + i) != ' ' && *(query + i) != '\0')
            i++;

        buffer = malloc(sizeof(char) * (i - start + 1));
        strncpy(buffer, query + start, i - start);
        *(buffer + i - start) = '\0';
        printf("\n%s", buffer);

        wordnode *n = get_occurences(table, buffer);

        if (n != NULL)
        {
            //printf("\nrelloc");
            nodes = realloc(nodes, (++nodeItr) * sizeof(nodes));
            *(nodes + nodeItr) = n;
            //printf("\n\t\t\t\tfound and done\n");
        }

        free(buffer);
        while (*(query + i) == ' ' && *(query + i) != '\0')
            i++;
    }

    if (nodeItr > -1)
    {
        while (nodeItr >= 0)
        {
            print_wordnode(*(nodes + nodeItr));
            nodeItr--;
        }
    }
    else
        printf("\nNo results...\n");

    read_query(get_query(), table);
}

void close()
{
    printf("\n\n\n\n");
    exit(0);
}

#endif
