#include <stdio.h>

int addition(int a, int b)
{
    return a + b;
}

int subtraction(int a, int b)
{
    return a - b;
}

int multiplication(int a, int b)
{
    return a * b;
}

int division(int a, int b)
{
    return a / b;
}

int main()
{
    int num1, num2;

    printf("Enter first number: ");
    scanf("%d", &num1);

    printf("Enter second number: ");
    scanf("%d", &num2);

    printf("%d + %d = %d\n", num1, num2, addition(num1, num2));
    printf("%d - %d = %d\n", num1, num2, subtraction(num1, num2));
    printf("%d * %d = %d\n", num1, num2, multiplication(num1, num2));
    printf("%d / %d = %d\n", num1, num2, division(num1, num2));

    return 0;
}


// use user defined functions for making a simple calculator that performs addition, subtraction, multiplication, and division. The program should take two numbers as input and display the results of all four operations.
// Lesson : Teaches you how to use user user defined function