#include <stdio.h>

void print(int n, char c){
    for (int i = 0; i <= 2 * (n - 2) ; i++)
    {
        i == n - 2 ? printf("\\ /") : printf("%c", c);
    }
}

int main()  
{
    int n;

    printf("Enter Your number: ");
    scanf("%d", &n);
    
    int height = 2 * (n - 2) + 1;

    for (int i = 0; i < height; i++)
    {
        if (i == (height - 1) / 2)
        {
            for (int j = 0; j < n - 1; j++)
            {
                printf(" ");
            }
            printf("@");
        }
        else
        {
            print(n, (i % 2 == 0) ? '*' : '=');
        }
        printf("\n");
    }

    return 0;
}