#include <stdio.h>

int main()
{
    int a = 45;
    int b = 55;
    int guess;
    int sum = a + b;

    for(int i = 0; i < 5; i++)
    {
        printf("Guess the sum : ");
        scanf("%d", &guess);

        if (guess == sum)
        {
            printf("Congratulations! You guessed it right.\n");
            break;
        }
        else if (i == 4)
        {
            printf("Sorry, you've used all your attempts. The correct answer is %d.\n", sum);
        }
        else if (guess < sum)
        {
            printf("Too low! `Try again.\n");
        }
        else
        {
            printf("Too high! Try again.\n");
        }
    }

    return 0;
}