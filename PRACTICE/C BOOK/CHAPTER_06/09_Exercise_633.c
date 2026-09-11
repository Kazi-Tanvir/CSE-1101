#include<stdio.h>
#include<string.h>

int main(){
    char str[] = "This Aint a Reverse String" ,*ptr;
    ptr = str;
    for(;*ptr++ != ' ';);
    printf(ptr);
    return 0;
}