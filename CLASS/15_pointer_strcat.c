#include<stdio.h>

void my_strcat(char *x, char *y){
    int i;
    for(i = 0; i <= (strlen(x) + strlen(y)) ; i++){
        *(x+i) = *y++;
    }
}

int main(){
    char x[] = "Tanvir";
    char y[] = "Kazi";
    my_strcat(x, y);
    printf("%s",x);
    return 0;
}