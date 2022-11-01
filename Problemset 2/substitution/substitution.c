#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check if enough arguments are given
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) < 26)
    {
        printf("%lu\n", strlen(argv[1]));
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check if non alphanumeric chars given
    for (int i = 0; i < strlen(argv[1] + 1); i++)
    {
        char testChar = argv[1][i];
        if (isdigit(testChar) || isalpha(testChar) == 0)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    // Check for multiples of same char in key
    for (int i = 0; i < 27; i++)
    {
        int compareChar = argv[1][i];
        for (int n = i + 1; n < 27; n++)
        {
            int nextChar = argv[1][n];
            if (compareChar == nextChar)
            {
                printf("Duplicates found in arguments, quitting program\n");
                return 1;
            }
        }
    }
    // Get user plaintext
    string plaintext = get_string("plaintext:  ");

    // print cyphertext
    printf("ciphertext: ");

    // Cypher text, differentiation by lowercase and uppercase
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // If char is uppercase, check against key and make key output uppercase
        if (isupper(plaintext[i]))
        {
            int ASCIIvalueChar = plaintext[i];
            int indexCypherArray = ASCIIvalueChar - 65;
            printf("%c", toupper(argv[1][indexCypherArray]));
        }
        // If char is lowercase, check against key and make key output lowercase
        else if (islower(plaintext[i]))
        {
            int ASCIIvalueChar = plaintext[i];
            int indexCypherArray = ASCIIvalueChar - 97;
            printf("%c", tolower(argv[1][indexCypherArray]));
        }
        // Char is no alphabetic char, so will just be printed unaltered
        else
        {
            // No alphabetical char so we just print it without ciphering
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}