#include<stdio.h>
#include<string.h>

int main(){
    char str[] = "This Aint a Reverse String";
    char rStr[80],*p1,*p2;

    p1 = str + strlen(str) - 1;
    p2 = rStr;

    while (p1>= str) *p2++ = *p1--;
    *p2 = '\0';

    printf(str);
    printf("\n");
    printf(rStr);

    return 0;
}