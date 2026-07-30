#include<stdio.h>

void my_strcpy(char *x, char *y){
    for(;*x;){
        *y++ = *x++;
    }
    *y = '\0';
}

int main(){
    char x[] = "Tanvir";
    char y[10];
    my_strcpy(x, y);
    printf("%s",y);
    return 0;
}