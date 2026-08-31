#include<stdio.h>


int main(){
    FILE *file = fopen("data/name_cg.txt", "r");
    if (file == NULL) {
        printf("Unable to open the file \n");
        return 0;
    }
    int roll[50];
    float cgpa[50];
    char name[50][100];
    char ch;
    for(int i = 0 ; i < 50 ; i++){
        fscanf(file, " %d %s %f" ,&roll[i] , name[i],&cgpa[i]);
    }
    for(int i = 0 ; i < 50 ; i++){
        printf("%d %s %.2f\n" ,roll[i] , name[i],cgpa[i]);
    }
    fclose(file);

}