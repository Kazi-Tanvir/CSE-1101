#include<stdio.h>
#include<stdlib.h>

char encryption(char ch,int SHIFT){
    ch += SHIFT;
    return ch;
}

char decryption(char ch,int SHIFT){
    encryption(ch,-SHIFT);
}

int main(int argC,char *argV[]){
    char ch;
    FILE *input = fopen("data/name_cg.txt","r");
    FILE *output = fopen("data/name_cg_encrytion.txt","w");
    if(input == NULL || output == NULL){
        printf("Unable to open file\n");
        return 1;
    }
    for(int i = 0; (ch=fgetc(input)) != EOF; i++){
        if(i > argC) i-=argC;
        int SHIFT = atoi(argV[i]);
        fprintf(output,"%c",encryption(ch,SHIFT));
    }
    fclose(input);
    fclose(output);
}