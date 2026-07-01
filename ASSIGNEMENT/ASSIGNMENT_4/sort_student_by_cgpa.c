#include <stdio.h>

float checkCGPA(int marks)
{
    if (marks >= 80 && marks <= 100)  return 4.0;
    if (marks >= 75)  return 3.75;
    if (marks >= 70)  return 3.5;
    if (marks >= 65)  return 3.25;
    if (marks >= 60)  return 3.0;
    if (marks >= 55)  return 2.75;
    if (marks >= 50)  return 2.5;
    if (marks >= 45)  return 2.25;
    if (marks >= 40)  return 2.0;
    else return 0;
}

float countCGPA(int idx){
    int sub[7]; float sum = 0;
    printf("enter Your Marks : (Format is 110X) \n");
    for (int i = 0; i < 7; i++) scanf("%d", &sub[i]);
    for (int i = 0; i < 7; i++) {
        if (i < 6) sum += checkCGPA(sub[i]) * 3;
        else sum += checkCGPA(sub[i]) * 1.5;
    }
    float grade = sum / 19.5;
    printf("Grade of student %d is %.2f\n", idx + 1, grade);
    return grade;
}

int main(){
    float student[5];
    int roll[5];
    for(int i = 0; i < 5; i++){
        printf("Enter the marks of student %d: \n", i + 1);
        student[i] = countCGPA(i);
        roll[i] = i + 1;
    }
    for(int i = 0 ; i < 5 ; i++){
        for(int j = i + 1 ; j < 5 ; j++){
            if(student[i] < student[j]){
                float temp = student[i];
                student[i] = student[j];
                student[j] = temp;
                int t = roll[i];
                roll[i] = roll[j];
                roll[j] = t;
            }
        }
    }
    printf("Merit List: \n");
    for(int i = 0; i < 5; i++) printf("Merit %d: Roll %d (CGPA: %.2f)\n", i + 1, roll[i], student[i]);
    return 0;
}
