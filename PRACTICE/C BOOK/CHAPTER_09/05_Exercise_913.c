#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
    FILE *source = fopen(argv[1],"r");
    FILE *destination = fopen(argv[2],"w");

    if(!source||!destination){
        printf("Failed to open file !");
        return 1;
    }

    for(;!feof(source);){
        char ch = fgetc(source);
        fputc(ch,destination);
        if(!strcmp("watch",argv[3])) printf("%c",ch); 
    }

    fclose(source);
    fclose(destination);
}