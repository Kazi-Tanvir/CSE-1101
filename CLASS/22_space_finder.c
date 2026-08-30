#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    FILE *file = fopen("data/char_input.txt", "r");
    if(file == NULL){
        printf("Error opening file.\n");
        return 1;
    }
    char ch;
    char string[100];
    fseek(file, 200, SEEK_SET);
    while((ch = fgetc(file)) != ' ');
    while((ch = fgetc(file)) == ' ');

    for (int i = 0; ch != EOF && ch != ' '&& ch != '\n'; i++)
        {
            string[i] = ch;
            ch = fgetc(file);
        }
    string[strlen(string)] = '\0';
    printf("%s", string);  
    fclose(file);
    }