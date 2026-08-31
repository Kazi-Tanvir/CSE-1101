#include<stdio.h>

int main(){
    FILE *file = fopen("data/char_input.txt", "r");
    char ch;
    char string[100];
    int count = 0;
    if (file == NULL) {
        printf("Unable to open the file \n");
    }
    for(; (ch = fgetc(file))!= EOF ;){
        if(ch == ' '|| ch == '\n') count++;
    }
    fseek(file,count/2,SEEK_SET);
    for(; (ch = fgetc(file))!= EOF && ch != ' ' && ch != '\n' ;){
        fseek(file,-2,SEEK_CUR);
    }
    ch = fgetc(file);
    for(int i = 0 ; ch != EOF && ch != ' ' && ch != '\n'; i++){
        string[i] = ch;
        ch = fgetc(file);
    }
    printf("%s\n",string);
    fclose(file);
}