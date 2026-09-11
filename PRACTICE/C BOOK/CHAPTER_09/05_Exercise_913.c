#include<stdio.h>

int main(int argc,char *argv[]){

    char in[80];
    char out[] = "Writing was done successfully";
    FILE *output = fopen("data/output","w");
    FILE *input = fopen("data/output.txt","r");
        if(output == NULL || input== NULL){
        printf("unable to open File");
        return 1;
    }
    for (int i = 0; out[i]; i++){
        fputc(out[i],output);
    }
    fclose(output);
    char ch;
    for (int i = 0;((ch = fgetc(input)) != EOF); i++){
        in[i] = ch;
    }
    fclose(input);

    printf("%s\n",in);
    

    
    
}
