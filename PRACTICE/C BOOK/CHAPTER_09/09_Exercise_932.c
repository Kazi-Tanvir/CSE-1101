#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[]){
    FILE *source = fopen(argv[1],"r");
    FILE *destination = fopen("data/temp","w");

    if(!source||!destination){
        printf("Failed to open file !");
        return 1;
    }

    for(;!feof(source);){
        char ch = fgetc(source);
        fputc(ch,destination);
    }
    fclose(source);
    fclose(destination);

    source = fopen(argv[2],"r");
    destination = fopen(argv[1],"w");

    if(!source||!destination){
        printf("Failed to open file !");
        return 1;
    }

    for(;!feof(source);){
        char ch = fgetc(source);
        fputc(ch,destination);
    }
    fclose(source);
    fclose(destination);

    source = fopen("data/temp","r");
    destination = fopen(argv[2],"w");

    if(!source||!destination){
        printf("Failed to open file !");
        return 1;
    }

    for(;!feof(source);){
        char ch = fgetc(source);
        fputc(ch,destination);
    }
    fclose(source);
    fclose(destination);
}
