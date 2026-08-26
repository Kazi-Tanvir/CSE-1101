#include<stdio.h>

void my_strcpy(char *dest, char *src){
    for(;*src;){
        *dest++ = *src++;
    }
    *dest = '\0';
}

int main(){
    char x[] = "Tanvir";
    char y[10];
    my_strcpy(x, y);
    printf("%s",y);
    return 0;
}