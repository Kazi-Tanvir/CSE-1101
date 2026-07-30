#include<stdio.h>

int my_strcmp(char *x, char *y){
    int i;
    if(strlen(*x)!= strlen(*y)) return 0;
    for(i = 0; *x++ == *y++ ; i++){
    }
    if(i == strlen(*x)) return 1;
    return 0;
}

int main(){
    char x[] = "Tanvir";
    char y[] = "Tanvir";
    printf("%d",my_strcmp(x, y));
    return 0;
}