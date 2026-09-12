#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
    FILE *file = fopen(argv[1],"w");
    char str[80];
    if(!file){
        printf("Failed to open file\n");
        return 1;
    }
    
    printf("Enter a blank line to stop\n");
    for(;;){
        printf(": ");
        fgets(str,sizeof(str),stdin);
        if(!strcmp(str,"\n")) break;
        fputs(str,file);
    }
    fclose(file);
    
    file = fopen(argv[1],"r");
    if(!file){
        printf("Failed to open file\n");
        return 1;
    }
    for(;;){
        fgets(str,79,file);
        if(feof(file)) break;
        printf(str);
    }
    fclose(file);

    return 0;
}