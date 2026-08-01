#include <stdio.h>

int main()
{
    int height;
    printf("Enter Your Pyramid Height : ");
    scanf("%d", &height);

    for (int i = 1; i <= height; i++)
    {
        //for spaces
        for (int j = height - i; j > 0; j--)
        {
            printf(" ");
        }
        // for #
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}