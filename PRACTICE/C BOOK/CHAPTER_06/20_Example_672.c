#include <stdio.h>

void mystrcpy(char *to, char *from);

int main(void)
{
    char str[80];

    mystrcpy(str, "this is a test");
    printf(str);

    return 0;
}

void mystrcpy(char *to, char *from)
{
    while(*from) *to++ = *from++;
    *to = '\0'; 
}