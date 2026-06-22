#include <stdio.h>

int operation(int a, int b, char op)
{
    if (op == '+')
    {
        return a + b;
    }
    else if (op == '-')
    {
        return a - b;
    }
    else if (op == '*')
    {
        return a * b;
    }
    else if (op == '/')
    {
        return a / b;
    }
    else if (op == '%')
    {
        return a % b;
    }
    else
    {
        printf("Invalid operator\n");
        return 0;
    }
}

int main()
{
    int num1, num2;
    char op;

    for (int i = 0; i < 5; i++)
    {

        printf("Enter Your Expression (e.g., 5 + 3): ");

        scanf("%d", &num1);
        scanf(" %c", &op);
        scanf("%d", &num2);

        int result = operation(num1, num2, op);
        printf("Result: %d\n", result);
    }

    return 0;
}