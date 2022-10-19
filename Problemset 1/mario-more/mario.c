#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // initiate variable
    int height = 0;

    // get user input restricted to 1 - 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);


    // create bricks vertical
    for (int i = height; i > 0; i--)
    {
        // create spaces infront of bricks
        for (int n = i - 1; n > 0; n--)
        {
            printf(" ");
        }
        // create bricks after spaces
        for (int j = 0; j < height - i + 1; j++)
        {
            printf("#");
        }
        // modified mario-less to mario-more
        printf("  ");
        // print right side of brick
        for (int k = 0; k < height - i + 1; k++)
        {
            printf("#");
        }
        //break to new line
        printf("\n");
    }
}