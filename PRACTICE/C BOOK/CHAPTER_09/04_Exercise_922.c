#include<stdio.h>

int main(int argc, char *argv[]){
    char str[26] = "abcdefghijklmnopqrstuvwxyz";
    int counter[26] = {0};
    FILE *file = fopen(argv[1],"r");
        if(file == NULL){
        printf("unable to open File");
        return 1;
    }

    char ch;
    for (;((ch = fgetc(file)) != EOF);){
        for(int i = 0; i < 26 ;i++){
            if(ch == str[i] || ch == (str[i]+32)) counter[i]++;
        }
    }
    for(int i = 0; i < 26; i++){
        printf("%c : %d\n",str[i],counter[i]);
    }
    fclose(file);

    return 0;
}
