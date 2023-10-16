#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Get text from user
    string text = get_string("Text: ");

    // Initialize required variables
    float wordCount = 1;          //To get word at the beginning of the string
    float sentenceCount = 0;
    float letterCount = 0;
    float averageSentences = 0;
    float averageLetters = 0;

    // Count Words, Sentences and Letters
    for (int i = 0; i < strlen(text); i++)
    {
        // Check for letters
        if (isupper(text[i]) || islower(text[i]))
        {
            letterCount++;
        }
        // Check for . ! ? depicting end of sentence
        else if (text[i] == 21 || text[i] == 46 || text[i] == 63 || text[i] == 33)
        {
            sentenceCount++;
        }
        // Check seperators like white space or comma or parenthesis to get words
        else if (text[i] == 32)
        {
            wordCount++;
        }
    }

    // Get Grade
    averageSentences = (sentenceCount / wordCount) * 100;
    averageLetters = (letterCount / wordCount) * 100;
    double grade = 0.0588 * averageLetters - 0.296 * averageSentences - 15.8;

    // Sort grade output
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(grade));
    }

    // Exit Main
    return 0;
}