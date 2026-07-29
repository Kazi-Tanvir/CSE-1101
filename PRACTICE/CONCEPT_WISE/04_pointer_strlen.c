#include<stdio.h>

void my_strlen(const char *str){
    int i;
    for(i = 0 ; *(str++);i++);
    printf("%d",i);
}

int main(){
    char str[] = "KaziTanvir";
    my_strlen(str);
    return 0;
}