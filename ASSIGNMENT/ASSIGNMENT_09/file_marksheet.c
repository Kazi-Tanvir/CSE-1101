#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STUDENTS 50

typedef struct{
    float quizMarks;
    float assignmentMarks;
    float midtermMarks;
    float attendanceMarks;
    float finalMarks;
}Course;

typedef struct{
    int roll;
    char name[50];
    Course courses[7];
    float totalContMarks[7];
    float totalMarks[7];
    float cgpa;
    char grade[10];
}Student;

Student students[MAX_STUDENTS]; 

const struct { 
    float marks; 
    float gpa; 
    const char *grade; 
} 
gradeTable[] = {{80, 4.0, "A+"}, {75, 3.75, "A"}, {70, 3.5, "A-"}, {65, 3.25, "B+"}, {60, 3.0, "B"}, {55, 2.75, "B-"}, {50, 2.5, "C+"}, {45, 2.25, "C"}, {40, 2.0, "D"}};

float checkCGPA(float marks){
    if (marks < 40 || marks > 100) return 0;
    for (int i = 0; i < 9; i++)
        if (marks >= gradeTable[i].marks) return gradeTable[i].gpa;
    return 0;
}

void checkGrade(float cgpa, char grade[]){
    for (int i = 0; i < 9; i++)
        if (cgpa >= gradeTable[i].gpa) { strcpy(grade, gradeTable[i].grade); return; }
    strcpy(grade, "F");
}

float countCGPA(int idx){
    float cgpa = 0;
    for (int i = 0; i < 7; i++)
        cgpa += checkCGPA(students[idx].totalMarks[i]) * (i < 6 ? 3 : 1.5);
    students[idx].cgpa = cgpa / 19.5;
    checkGrade(students[idx].cgpa, students[idx].grade);
    return students[idx].cgpa;
}

void sortStudent(){
    for(int i = 0; i < MAX_STUDENTS; i++){
        for(int j = i + 1; j < MAX_STUDENTS; j++){
            if(students[i].cgpa < students[j].cgpa){
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

void getMarks(FILE *filename,int courseIndex) {
    fseek(filename, 0, SEEK_END);
    long fileSize = ftell(filename);
    rewind(filename);
    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
        fclose(filename);
        return;
    }
    int bytesRead = fread(buffer, 1, fileSize, filename);
    buffer[bytesRead] = '\0'; 
    fclose(filename);

    int count = 0;
    char *cursor = buffer;
    int bytesConsumed = 0;

    while (count < 50 && sscanf(cursor, "%f %f %f %f %f%n",&students[count].courses[courseIndex].quizMarks,
                                &students[count].courses[courseIndex].assignmentMarks,
                                &students[count].courses[courseIndex].midtermMarks,
                                &students[count].courses[courseIndex].attendanceMarks,
                                &students[count].courses[courseIndex].finalMarks,
                                &bytesConsumed) == 5) {
        students[count].totalContMarks[courseIndex] = 
            students[count].courses[courseIndex].quizMarks+
            students[count].courses[courseIndex].assignmentMarks+
            students[count].courses[courseIndex].midtermMarks+
            students[count].courses[courseIndex].attendanceMarks;
        students[count].totalMarks[courseIndex] = (students[count].totalContMarks[courseIndex])+(students[count].courses[courseIndex].finalMarks);
        cursor += bytesConsumed;
        count++;
    }
    free(buffer);
    return;
}


int main(void) {
    int count = 0;
    
    const char *courseFiles[] = {
        "data/1101_CSE.txt", "data/1101L_CSE.txt", "data/1102_CSE.txt",
        "data/1103_STAT.txt", "data/1105_GE.txt", "data/1106_SE.txt", "data/1107_MATH.txt"
    };

    FILE *name = fopen("data/name_cg.txt", "r"); 
    FILE *result = fopen("data/result.txt", "w"); 
    if (!name || !result) return 1;

    while (count < MAX_STUDENTS && fscanf(name, "%d %49s", &students[count].roll, students[count].name) == 2) count++;
    fclose(name);

    for (int i = 0; i < 7; i++) {
        FILE *filename = fopen(courseFiles[i], "r");
        if (!filename) return 1;
        getMarks(filename, i);
    }
    for (int i = 0; i < count; i++) countCGPA(i);
    sortStudent();

    for (int i = 0; i < count; i++) fprintf(result, "Roll: %d | Name: %-12s | Total Marks : %.2f |CGPA: %.2f | Grade: %s \n", students[i].roll, students[i].name, students[i].total, students[i].cgpa, students[i].grade);

    fclose(result);
    return 0;
}