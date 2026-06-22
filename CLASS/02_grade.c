#include<stdio.h>

int main()
{
    int marks;
    char grade;

    printf("Enter your marks: ");
    scanf("%d", &marks);

    if (marks >= 80)
    {
        grade = 'A+';
    }
    else if (marks >= 70)
    {
        grade = 'A';
    }
    else if (marks >= 60)
    {
        grade = 'A-';
    }
    else if (marks >= 50)
    {
        grade = 'B';
    }
    else if (marks >= 40)
    {
        grade = 'C';
    }
    else if (marks >= 30)
    {
        grade = 'D';
    }
    else
    {
        grade = 'F';
    }

    printf("Your grade is: %c\n", grade);

    return 0;
}