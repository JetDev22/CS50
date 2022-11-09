#include <stdio.h>

int collatz(int n);

int main(void)
{
    int result = collatz(3);
    printf("%i\n", result);
}

int collatz(int n)
{
	
    // base case
	if (n == 1)
	{
		return 1;
	}

	// recursive case for even number
	else if ((n % 2) == 0)
	{
        return 1 + collatz(n / 2);
	}

    // recursive case for odd number
	else
	{
        return 1 + collatz(3*n + 1);
	}
}