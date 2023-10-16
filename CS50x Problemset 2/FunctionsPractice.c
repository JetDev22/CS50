# include <stdio.h>

float trianglecheck (float a, float b, float c);

int main(void)
{
   int z = trianglecheck(5, 6, 9);
   if (z == 0)
   {
        printf("Triangle possible");
   }
   else
   {
        printf("Not a triangle");
   }
}

 float trianglecheck (float a, float b, float c)
{
    if ((a + b) > c && (b + c) > a && (c + a) > b)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}