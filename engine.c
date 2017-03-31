/**
*
* @author Theodore Miller
* @description This is the core of the Search Engine. It implements all of the
*              .h helper files to use for each functionality.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include "cmdutil.h"
#include "hashtable.h"

void stop_word(hashtable *table, wordnode *w)
{
    if (w -> idf == 0)
    {
        node *n = w -> occurences -> head;
        node *tmp;

        while (n != NULL)
        {
            tmp = n;
            free(((occurencenode *)(tmp -> data)) -> doc);
            free(tmp);
            n = n -> next;
        }

       /** linkedlist *ll = *(table -> buckets + (hash_code(w -> word) % table -> size));

        n = ll -> head;
        tmp = n;

        while (n != NULL)
        {
            if (strcmp(((wordnode *)(n->data)) -> word, w -> word) == 0)
            {
                tmp -> next = n -> next;
                free(n);
                break;
            }
            tmp = n;
        }*/
    }
}

void calculate_relevance(wordnode *w, int totalDocs)
{
    //w -> df = w -> occurences -> size;
    w -> idf = log10(((double)totalDocs / (double)w -> occurences -> size));

    node *n = w -> occurences -> head;
    node *tmp;

    while (n != NULL)
    {
        ((occurencenode *)(n -> data)) -> idfi = (((occurencenode *)(n -> data)) -> tf) * (w -> idf);
        w -> relevance += ((occurencenode *)(n -> data)) -> idfi;

        n = n -> next;
    }
}

void compute_ranks(hashtable *table, int totalDocs)
{
    int i;

    for (i = 0; i < table -> size; i++)
    {
        linkedlist *l = *(table -> buckets + i);

        node *n = l -> head;

        while (n != NULL)
        {
            calculate_relevance((wordnode *)n -> data, totalDocs);
            //stop_word(table, (wordnode *)n -> data);
            n = n -> next;
        }
    }
}

int get_files(char *path)
{
    DIR *files;
    struct dirent *dir;
    files = opendir(".");
    char temp[32];

    if (files)
    {
        while ((dir = readdir(files)) != NULL)
        {
            if ((dir -> d_name)[strlen(dir -> d_name)] == 't' && (dir -> d_name)[strlen(dir -> d_name) - 1] == 'x' && (dir -> d_name)[strlen(dir -> d_name) - 2] == 't' && (dir -> d_name)[strlen(dir -> d_name) - 3] == '.')
                printf("%s\n", dir->d_name);
        }

        closedir(files);
    }
    exit(0);
}

void training(char *FILEPATH, char *FILENUMBER, char *BUCKETS, hashtable **table)
{
    int totalDocs = 0;
    if (FILEPATH == NULL)
    {
        printf("\nNO FILEPATH SPECIFIED... EXITING.\n");
        help();
    }

    // Determine HashTable size.
    if (BUCKETS != NULL)
        *table = init_table(atoi(BUCKETS));
    else if (BUCKETS == NULL && FILENUMBER != NULL)
        *table = init_table(next_prime(atoi(FILENUMBER) * 5));
    else
        *table = init_table(17);

    if (FILENUMBER == NULL)
    {
        printf("\nNO FILENUMBER SPECIFIED. READING *\n");
        get_files(FILENUMBER);
    }
    else
    {
        totalDocs = atoi(FILENUMBER);
        printf("\nREADING FROM %s D1 to D%s\n", FILEPATH, FILENUMBER);

        int i;
        char buffer[20];// = malloc(sizeof(char) * 32);
        char *doc = malloc(sizeof(char) * (strlen(FILEPATH) + strlen(FILENUMBER) + 5));
        FILE *fptr;

        for (i = 1; i <= atoi(FILENUMBER); i++)
        {
            sprintf(doc, "%s%c%d%s", FILEPATH, 'D', i, ".txt");
            fptr = fopen(doc, "r");

            while (fscanf(fptr, " %511s", buffer) == 1)
            //{                free(buffer);
                //buffer = malloc(sizeof(char) * 20);
                //printf("\n%s", buffer);
                hash_table_insert(*table, buffer, doc);
            //}
            fclose(fptr);
        }
    }

    compute_ranks(*table, totalDocs);
}

void main(int argc, char *argv[])
{
    char *FILEPATH = NULL;
    char *FILENUMBER = NULL;
    char *BUCKETS = NULL;
    hashtable *table = NULL;

    //printf("TABLE IS %sNULL", table == NULL ? "" : "NOT ");

    get_args(argc, argv, &FILEPATH, &FILENUMBER, &BUCKETS);
    training(FILEPATH, FILENUMBER, BUCKETS, &table);

    read_query(get_query(), table);
    close();
}


