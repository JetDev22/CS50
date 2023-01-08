// Implements a dictionary's functionality

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

// Global Variables
int wordCount = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5490;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get hash value for checkString
    int hashCode = hash(word);

    // Create traversal pointer
    node *trav = table[hashCode];

    // Check if word exists in dictionary
    while (trav != NULL)
    {
        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }
        trav = trav->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashCode = 0;
    // Get sum of ASCII values of characters
    for (int i = 0; i < strlen(word); i++)
    {
        hashCode += tolower(word[i]);
    }
    //if (hashCode > 365)
    //{
    //    hashCode = 0;
    //}
    return hashCode;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary from file
    FILE *storedDict = fopen(dictionary, "r");

    // Check if file opened and stored in dictionary
    if (storedDict == NULL)
    {
        return false;
    }

    // Initialise all table positons with NULL pointer
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Create buffer to store words from dict for entering into hash table
    char buffer[46];

    // Loop through dictionary and add words to hash table
    while (fscanf(storedDict, "%s", buffer) != EOF)
    {
        // Update Word Counter
        wordCount += 1;

        // Create node to store word
        node *n = malloc(sizeof(node));

        // Check if memory was allocated
        if (n == NULL)
        {
            return false;
        }

        // Reduce buffer size to word length
        char newWord[strlen(buffer)];
        for (int i = 0; i < strlen(buffer) + 1; i++)
        {
            newWord[i] = buffer[i];
        }

        // Copy word from buffer to new node
        strcpy(n->word, buffer);

        // Get hash code for word
        int hashCode = hash(buffer);

        // Set pointer of new node to old node
        n->next = table[hashCode];

        // Set hash table pointer to new node
        table[hashCode] = n;
    }

    // Close dictionary file
    fclose(storedDict);

    // Return true
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // return global variable wordCount
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through every hashtable cell
    for (int i = 0; i < N; i++)
    {
        // Create pointers
        node *current = table[i];
        while (current != NULL)
        {
            // Create pointer to node to be deleted
            node *delete = current;

            // Point current to next node
            current = current->next;

            // Delete current node
            free(delete);
        }
        // Check if end of list reached and last node is NULL
        if (current == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}