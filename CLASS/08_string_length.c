#include<stdio.h>
#include <string.h>

int main(){
    char str[100];
    scanf("%s", str);
    // using for loop
    int count = 0;
    for(int i = 0; str[i] != '\0'; i++){
        count++;
    }
    printf("%d\n", count);

    // directly using strlen from string library
    printf("%d\n", strlen(str));

    return 0;
}