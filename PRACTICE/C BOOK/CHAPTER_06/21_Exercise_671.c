#include<stdio.h>
#include<string.h>

void my_strcat(char *x, char *y){
    int i;
    for(i = strlen(x); i <= (strlen(x) + strlen(y)) ; i++){
        *(x+i) = *y++;
    }
    *(x+i) = '\0';
}

int main(){
    char x[] = "Kazi";
    char y[] = "Tanvir";
    my_strcat(x, y);
    printf("%s",x);
    return 0;
}