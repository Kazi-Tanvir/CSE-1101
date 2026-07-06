#include<stdio.h>
#include<string.h>

int main(){
    char str1[10] = "Kazi ";
    char str2[10] = "Tanvir";
    char str3[20];

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    // manual process
    for(int i = 0; i < len1; i++){
        str3[i] = str1[i];
    }
    for(int i = 0; i < len2; i++){
        str3[len1 + i] = str2[i];
    }
    str3[len1 + len2] = '\0';
    printf(str3);
    printf("\n");


    // using built in function
    printf(strcat(str1, str2));
    printf("\n");
    

    return 0;
}