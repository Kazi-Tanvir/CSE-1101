#include <stdio.h>

int main()
{
    int height;
    printf("Enter Your Pyramid Height : ");
    scanf("%d", &height);
    // normal pyramid
    for (int i = 0; i < height; i++)
    {
        // for spaces
        for (int j = height - i; j > 0; j--)
        {
            printf(" ");
        }
        // for #
        for (int j = 0; j < (2 * i + 1); j++)
        {
            printf("#");
        }
        printf("\n");
    }
    // inverted pyramid
    for (int i = height - 1; i > 0; i--)
    {
        // for spaces
        for (int j = height - i + 1; j > 0; j--)
        {
            printf(" ");
        }
        // for #
        for (int j = 0; j < (2 * i - 1); j++)
        {
            printf("#");
        }
        printf("\n");
    }
    //
    return 0;
}