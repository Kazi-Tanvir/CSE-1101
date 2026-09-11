#include <stdio.h>

int main(void)
{
    char *p, **mp, str[80];

    p = str;
    mp = &p;

    printf("Enter your name: ");
    scanf(" %[^\n]" , *mp);
    printf("Hi %s", *mp);

    return 0;
}