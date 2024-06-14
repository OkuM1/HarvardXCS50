// Implements a dictionary's functionality

#include <cs50.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 7533;

// Hash table
node *table[N];

//size of dictionary loaded

int dictionary_size = 0;

//check if word is in dictionary
bool check(const char *word)
{


    int index = hash(word);

    node *n = table[index];

    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }

    return false;
}

//Hashes word to a number
unsigned int hash(const char *word)
{

    int sum = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        sum += (toupper(word[i]));
    }



    return sum % N;


}

//put file into memory
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }

    char load_word[LENGTH + 1];


    //read file
    while (fscanf(file, "%s", load_word) != EOF)
    {

        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }
        
        strcpy(n->word, load_word);
        n->next = NULL;

        int index = hash(load_word);

        n->next = table[index];
        table[index] = n;

        dictionary_size++;

    }

    fclose(file);

    return true;
}


unsigned int size(void)
{
    // TODO
    return dictionary_size;
}

// unload from memory
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {

        while (table[i] != NULL)
        {
            //swap and free last node to null
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }

    return true;
}
