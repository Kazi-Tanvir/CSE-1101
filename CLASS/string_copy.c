#include<stdio.h>
#include <string.h>

int main(){
    char str1[] = "Kazi";
    char str2[10];
    char str3[10];

    // using for loop
    int i;
    for(i = 0; str1[i] != '\0'; i++){
        str2[i] = str1[i];
    }
    str2[i] = '\0';


    // directly using strcpy from string library
    strcpy(str3, str1);
    printf(str2);
    printf("\n");
    printf(str3);
    return 0;
}