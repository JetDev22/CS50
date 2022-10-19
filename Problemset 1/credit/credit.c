#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // initiate empty card as long
    long card = 0;

    // get credit card number from user
    do
    {
        card = get_long("Number: ");
    }
    while (card == 0);

    // get length of number
    int card_length = 0;
    long rest = card;
    while (rest > 0)
    {
        rest = rest / 10;
        card_length++;
    }

    // first loop to loop through every other digit, multiply by 2, add digits together
    int loop_counter = 0;
    int loop_digit = 0;
    int single_digit = 0;
    int sum_digit_first = 0;
    long card_remainder = card / 10;
    while (loop_counter != card_length)
    {
        single_digit = card_remainder % 10;
        card_remainder = card_remainder / 100;
        single_digit = single_digit * 2;
        if (single_digit >= 10)
        {
            loop_digit = single_digit % 10;
            sum_digit_first = sum_digit_first + loop_digit;
            single_digit = single_digit / 10;
            sum_digit_first = sum_digit_first + single_digit;
        }
        else
        {
            sum_digit_first = sum_digit_first + single_digit;
        }
        loop_counter++;
        // Result of this first loop is stored in sum_digit_first
    }

    // Second Loop to loop through the rest and add digits together
    int sum_digit_second = 0;
    long temp_card = card;
    while (temp_card != 0)
    {
        int x = temp_card % 10;
        sum_digit_second = sum_digit_second + x;
        temp_card = temp_card / 100;
    }

    // Get Checksum
    int checksum = sum_digit_first + sum_digit_second;
    int last_digit = checksum % 10;
    if (last_digit != 0 || card_length < 13)
    {
        printf("INVALID\n");
    }
    else
    {
        // get first two digits of card for identification
        int first_two_digits = 0;
        long tempo_card = card;
        while (tempo_card > 100)
        {
            tempo_card = tempo_card / 10;
        }
        first_two_digits = tempo_card;

        // get first digit for visa
        int first_digit = first_two_digits / 10;

        // Check if card is American Express
        if (card_length == 15)
        {
            if (first_two_digits == 34 || first_two_digits == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        // Check if card is MasterCard or VISA
        else if (card_length == 16)
        {
            if (first_two_digits == 51 || first_two_digits == 52 || first_two_digits == 53 || first_two_digits == 54 || first_two_digits == 55)
            {
                printf("MASTERCARD\n");
            }
            else if (first_digit == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (card_length == 13 && first_digit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }

}