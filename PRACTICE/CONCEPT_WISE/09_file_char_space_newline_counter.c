#include<stdio.h>
#include<stdlib.h>

int main(){
    FILE *fp = fopen("text.txt", "r");
    if(fp == NULL) exit(1);
    int char_counter = 0;
    int space_counter = 0;
    int newline_counter = 0;
    char ch;
    
    for(int i = 0;(ch = fgetc(fp))!= EOF;i++){
        int ascii = ch;
        if(ascii >= 0 && ascii <= 255) char_counter++;
        if(ch == ' ') space_counter++;
        if(ch == '\n') newline_counter++;
        printf("%d",i);

    }
    printf("%d %d %d",char_counter,space_counter,newline_counter );
}