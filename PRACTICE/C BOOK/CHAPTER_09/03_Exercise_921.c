#include<stdio.h>

int main(int argc, char *argv[]){

    char in[80];
    FILE *file = fopen(argv[1],"r");
        if(file == NULL){
        printf("unable to open File");
        return 1;
    }

    char ch;
    for (int i = 0;((ch = fgetc(file)) != EOF); i++){
        in[i] = ch;
    }
    fclose(file);

    printf("%s\n",in);

    return 0;
}

