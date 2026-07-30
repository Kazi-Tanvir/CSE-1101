#include<stdio.h>

int my_strlen(char *str){
    int i;
    for(i = 0; *(str++);i++);
    return i;
}

int main(){
    char str[10] = "Kazi";
    printf("%d",my_strlen(str));
    return 0;
}