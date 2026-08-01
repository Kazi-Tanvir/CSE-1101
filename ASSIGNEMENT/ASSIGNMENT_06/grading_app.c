#include<stdio.h>
#include<string.h>

char studentName[50][100];
int subjectId[7];
int studentMarks[50][7][2];
char subjectGrade[50][7][10];
float studentCGPA[50];
char studentGrade[50][10];

int totalStudents = 0;

float checkCGPA(int marks)
{
    if(marks < 40 || marks > 100) return 0;
    if (marks >= 80)  return 4.0;
    if (marks >= 75)  return 3.75;
    if (marks >= 70)  return 3.5;
    if (marks >= 65)  return 3.25;
    if (marks >= 60)  return 3.0;
    if (marks >= 55)  return 2.75;
    if (marks >= 50)  return 2.5;
    if (marks >= 45)  return 2.25;
    if (marks >= 40)  return 2.0;
    return 0;
}

void checkGrade(float cgpa, char grade[]){
    if(cgpa >= 4.0)       strcpy(grade, "A+");
    else if(cgpa >= 3.75) strcpy(grade, "A");
    else if(cgpa >= 3.5)  strcpy(grade, "A-");
    else if(cgpa >= 3.25) strcpy(grade, "B+");
    else if(cgpa >= 3.0)  strcpy(grade, "B");
    else if(cgpa >= 2.75) strcpy(grade, "B-");
    else if(cgpa >= 2.5)  strcpy(grade, "C+");
    else if(cgpa >= 2.25) strcpy(grade, "C");
    else if(cgpa >= 2.0)  strcpy(grade, "D");
    else                  strcpy(grade, "F");
}

float countCGPA(int idx){
    float sum = 0;
    for (int i = 0; i < 7; i++) {
        int marks = (int)(0.6 * studentMarks[idx][i][0] + 0.4 * studentMarks[idx][i][1]);
        float gpa = checkCGPA(marks);
        checkGrade(gpa, subjectGrade[idx][i]);
        if (i < 6) sum += gpa * 3;
        else sum += gpa * 1.5;
    }
    float cgpa = sum / 19.5;
    studentCGPA[idx] = cgpa;
    checkGrade(cgpa, studentGrade[idx]);
    return cgpa;
}

void searchID(){
    int id;
    printf("Enter student index (1-%d): ", totalStudents);
    scanf("%d", &id);
    id--;
    if(id < 0 || id >= totalStudents){
        printf("Invalid student ID!\n");
        return;
    }
    printf("\n--- Student: %s ---\n", studentName[id]);
    printf("%-10s %-15s %-10s %-10s %-10s\n", "Subject", "Continuous", "Final", "Total", "Grade");
    for(int j = 0; j < 7; j++){
        int total = (int)(0.6 * studentMarks[id][j][0] + 0.4 * studentMarks[id][j][1]);
        printf("%-10d %-15d %-10d %-10d %-10s\n", j+1, studentMarks[id][j][0], studentMarks[id][j][1], total, subjectGrade[id][j]);
    }
    printf("CGPA: %.2f | Grade: %s\n", studentCGPA[id], studentGrade[id]);
}

void displayAll(){
    printf("\n%-5s %-20s %-10s %-10s\n", "No", "Name", "CGPA", "Grade");
    for(int i = 0; i < totalStudents; i++){
        printf("%-5d %-20s %-10.2f %-10s\n", i+1, studentName[i], studentCGPA[i], studentGrade[i]);
    }
}

void inputStudents(){
    int n;
    printf("How many students to enter (max %d): ", 50 - totalStudents);
    scanf("%d", &n);
    if(n <= 0 || n + totalStudents > 50){
        printf("Invalid number!\n");
        return;
    }
    for(int i = totalStudents; i < totalStudents + n; i++){
        printf("\n--- Student %d ---\n", i + 1);
        printf("Enter name: ");
        getchar();
        fgets(studentName[i], 100, stdin);
        studentName[i][strcspn(studentName[i], "\n")] = '\0';
        for(int j = 0; j < 7; j++){
            printf("Subject %d - Enter continuous assessment marks (out of 100): ", j + 1);
            scanf("%d", &studentMarks[i][j][0]);
            printf("Subject %d - Enter final exam marks (out of 100): ", j + 1);
            scanf("%d", &studentMarks[i][j][1]);
        }
        countCGPA(i);
        printf("CGPA: %.2f | Grade: %s\n", studentCGPA[i], studentGrade[i]);
    }
    totalStudents += n;
}

int main(){
    int choice;
    while(1){
        printf("\n===== Student Grading System =====\n");
        printf("1. Input Students\n");
        printf("2. Search Student by ID\n");
        printf("3. Display All Students\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1: inputStudents(); break;
            case 2: searchID(); break;
            case 3: displayAll(); break;
            case 4: return 0;
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}