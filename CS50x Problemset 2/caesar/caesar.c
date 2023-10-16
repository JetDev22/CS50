#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Check if user gives only one argument
    if (argc != 2)
    {
        printf("wrong arguments given. quitting program!\n");
        return 1;
    }
    // Check if given argument consists only of digits
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert key into int to be used for encryption
    int key = atoi(argv[1]);

    // Get user plaintext
    string plaintext = get_string("plaintext:  ");

    // Reduce key
    if (key > 26)
    {
        key = key % 26;
    }

    // print cyphertext
    printf("ciphertext: ");

    // Cypher text, differentiation by lowercase and uppercase
    for (int i = 0; i <= strlen(plaintext) -  1; i++)
    {
        if (isupper(plaintext[i]))
        {
            // Get distance to upper Z from current character
            int remainderToUpperZ = 90 - plaintext[i];
            // Key wraps over upper Z so loop it back over upper A
            if (key > remainderToUpperZ)
            {
                int tempoKey = key - remainderToUpperZ;
                char cryptedChar = 64 + tempoKey;
                printf("%c", cryptedChar);
            }
            else
            {
                // Key will not go over upper z
                char cryptedChar = plaintext[i] + key;
                printf("%c", cryptedChar);
            }
        }
        else if (islower(plaintext[i]))
        {
            // Get distance to lower z from current character
            int remainderToUpperZ = 122 - plaintext[i];
            // Key wraps over lower z so loop it back over lower A
            if (key > remainderToUpperZ)
            {
                int tempoKey = key - remainderToUpperZ;
                char cryptedChar = 96 + tempoKey;
                printf("%c", cryptedChar);
            }
            else
            {
                // Key will not go over lower z
                char cryptedChar = plaintext[i] + key;
                printf("%c", cryptedChar);
            }
        }
        else
        {
            // No alphabetical char so we just print it without ciphering
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
}