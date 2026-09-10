//Example 2 from the book 

#include<stdio.h>

int main(int argC, char *argV[]){
    FILE *file = fopen(argV[1], "r");
    if(file == NULL) return 1;
    char ch;
    for(;(ch = fgetc(file))!=EOF;){
        if(ch == *argV[2]){
            printf("found %c\n",ch);
            break;
        }
    }
    fclose(file);
}