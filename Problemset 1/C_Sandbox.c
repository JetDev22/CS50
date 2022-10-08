#include <stdio.h>

int main(void) 
{
    char name[20];                  // delcare max length of string
    printf("What is your name? ");
    scanf("%s", name);              // scan for string input
    printf("Hello, %s\n", name);    // print input in placeholder &s

}