#include<stdio.h>
#include<string.h>

int main(){
    char *ptr = "stop";
    char str[80] = {0};

    while(strcmp(ptr,str)){
        printf("Enter your string : ");
        fgets(str,sizeof(str),stdin);
    }
    return 0;
}
