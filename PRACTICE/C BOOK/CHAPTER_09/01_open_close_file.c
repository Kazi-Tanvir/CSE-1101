#include<stdio.h>

int main(){
    // FILE *fopen(char *fname, char *mode);
    FILE *fp;
    fp = fopen("myfile", "r");
    if(fp == NULL) {
        printf("Error opening file.\n");
        exit(1); /* or substitute your own error handler */
    }
}