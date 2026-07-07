#include<stdio.h>
#include<string.h>

int main(){
    char str1[] = "Kazi";
    char str2[] = "Kazi1";
    int i;
// Manual Process
    int isEqual = 1; 
    for(i = 0; str1[i] != '\0' || str2[i] != '\0'; i++){
        if(str1[i] != str2[i]){
            isEqual = 0;
            break;
        }
    }

    if(isEqual){
        printf("Equal\n");
    }
    else{
        printf("Not Equal\n");
    }
    
    // using built in function
    if(strcmp(str1, str2) == 0){
        printf("Equal\n");
    }
    else{
        printf("Not Equal\n");
    }
}