#include <stdio.h>

int main()
{
    char *ptr[3] = {"one", "two", "three"};
    
    printf("%s %s %s\n", *(ptr), *(ptr+1), *(ptr+2));
    printf("%s %s %s\n", *(ptr), *(ptr+2), *(ptr+1));
    printf("%s %s %s\n", *(ptr+1), *(ptr), *(ptr+2));
    printf("%s %s %s\n", *(ptr+1), *(ptr+2), *(ptr));
    printf("%s %s %s\n", *(ptr+2), *(ptr), *(ptr+1));
    printf("%s %s %s\n", *(ptr+2), *(ptr+1), *(ptr));

    return 0;
}