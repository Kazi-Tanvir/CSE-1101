#include<stdio.h>

int main(int argc,char *argv[]){
    FILE *file;
    int count = 0;
    char ch;
    if(argc < 2){
        printf("Not enough argument\n");
        return 1;
    }
    if((file = fopen(argv[1],"r")) == NULL){
        printf("Failed to open file\n");
        return 1;
    }

    for(;(ch=fgetc(file))!=EOF;){
        count++;
    }
    printf("%d\n",count);
    fclose(file);

}