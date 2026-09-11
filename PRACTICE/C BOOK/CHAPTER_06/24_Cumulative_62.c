#include <stdio.h>

int main(void)
{
    char str[80],*ptr;
    ptr = str;
    int i, spaces;

    printf("Enter a string: ");
    scanf(" %[^\n]",str);
    spaces = 0;
    for(i=0; *(ptr++) ; i++)
        if(*ptr ==' ') spaces++;

    printf("Number of spaces: %d", spaces);

    return 0;
}