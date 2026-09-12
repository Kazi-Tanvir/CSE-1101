#include<stdio.h>
#include<string.h>

int main(int argc,char *argv[]){
    FILE *file = fopen(argv[1],"w");
    float f;
    int i;
    char str[80];
    if(!file) return 1;

    fprintf(file ,"%f %d %s", 12345.342, 1908, "hello");

    fclose(file);
    file = fopen(argv[1],"r");

    fscanf(file,"%f %d %s", &f, &i, str);
    printf("%f %d %s",f,i,str);

    fclose(file);

    return 0;
}