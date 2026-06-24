#include<stdio.h> 

int main(){
    char n[10];
    for (int i = 0; i < 10; i++){
        scanf(" %c", &n[i]);
    }
    char min = n[0];
    for (int i = 1; i < 10; i++){
        if (n[i] < min){
            min = n[i];
        }
    }
    printf("%c", min);
    return 0;
}