#include<stdio.h>
#include<stdlib.h>

struct Student {
    char name[100];
    int roll;
    float cgpa;
} Student[50];

int main (){
    FILE *file = fopen("data/name_cg.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for(int i = 0 ; i < 50 ; i++){
        fscanf(file, "%d %s %f", &Student[i].roll, Student[i].name, &Student[i].cgpa);
        printf("%d %s %.2f\n", Student[i].roll, Student[i].name, Student[i].cgpa);
    }
    fclose(file);
    return 0;
}