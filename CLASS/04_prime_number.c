#include<stdio.h>

int main()
{
    int num  , isPrime = 1;

    for (int i  = 0 ; i < 5; i++)
    {
        printf("Enter a number: ");
        scanf("%d", &num);

        if (num <= 1)
        {
            isPrime = 0;
        }
        else
        {
            for (int j = 2; j <= num / 2; j++)
            {
                if (num % j == 0)
                {
                    isPrime = 0;
                    break;
                }
            }
        }

        if (isPrime)
        {
            printf("%d is a prime number.\n", num);
        }
        else
        {
            printf("%d is not a prime number.\n", num);
        }
    }

    return 0;
}