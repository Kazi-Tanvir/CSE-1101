#include <stdio.h>
#include <string.h>

#define MAX_ROSTER 150

typedef struct Student {
    int studentID;
    char name[100];
    float midtermMarks;
    float finalMarks;
    float totalMarks;
} Student;

Student CourseRoster[MAX_ROSTER];
int rosterSize = 0;

void promptStudentDetails(Student *studentPtr);
void displayStudent(const Student *studentPtr);
int findStudentIndexByID(const Student roster[], int size, int searchID);
int findTopStudentIndex(const Student roster[], int size);

void promptStudentDetails(Student *studentPtr) {
    printf("Enter your student name: ");
    scanf(" %[^\n]", studentPtr->name);

    printf("Enter Mid Term Marks: ");
    scanf("%f", &studentPtr->midtermMarks);

    printf("Enter Final Term Marks: ");
    scanf("%f", &studentPtr->finalMarks);

    studentPtr->totalMarks = studentPtr->midtermMarks + studentPtr->finalMarks;
    printf("Student total Marks: %.2f\n", studentPtr->totalMarks);
}

void displayStudent(const Student *studentPtr) {
    printf("Student ID: %d\n", studentPtr->studentID);
    printf("Student name:  %s\n", studentPtr->name);
    printf("Mid Term Marks:  %.2f\n", studentPtr->midtermMarks);
    printf("Final Term Marks:  %.2f\n", studentPtr->finalMarks);
    printf("Student total Marks: %.2f\n", studentPtr->totalMarks);
}

int findStudentIndexByID(const Student roster[], int size, int searchID) {
    for (int i = 0; i < size; i++) {
        if (roster[i].studentID == searchID) {
            printf("Student Found !\n");
            printf("Student Details\n");
            displayStudent(&roster[i]);
            return i;
        }
    }
    printf("Student with this ID not found.\n");
    return -1;
}

int findTopStudentIndex(const Student roster[], int size) {
    if (size <= 0) {
        printf("Roster is empty.\n");
        return -1;
    }

    int topIndex = 0;
    for (int i = 1; i < size; i++) {
        if (roster[i].totalMarks > roster[topIndex].totalMarks) {
            topIndex = i;
        }
    }

    printf("Id of the top student is %d\nmax marks is %.2f\n", roster[topIndex].studentID, roster[topIndex].totalMarks);
    return topIndex;
}

void checkStudent() {
    if (rosterSize >= MAX_ROSTER) {
        printf("Exceeded maximum roster rosterSize.\n");
        return;
    }

    int tempID;
    printf("Enter your student ID: ");
    scanf("%d", &tempID);

    for (int i = 0; i < rosterSize; i++) {
        if (tempID == CourseRoster[i].studentID) {
            printf("Student with this ID already exists.\n");
            return;
        }
    }

    CourseRoster[rosterSize].studentID = tempID;
    promptStudentDetails(&CourseRoster[rosterSize]);
    rosterSize++;
    printf("Adding Student was successful!\n");
}

void displayFullRoster() {
    if (rosterSize == 0) {
        printf("Roster is empty.\n");
        return;
    }

    for (int i = 0; i < rosterSize; i++) {
        displayStudent(&CourseRoster[i]);
        printf("\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n1. Add Student\n");
        printf("2. Display Full Roster\n");
        printf("3. Find Student by ID\n");
        printf("4. Show Top Student\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            checkStudent();
        } else if (choice == 2) {
            displayFullRoster();
        } else if (choice == 3) {
            int tempID;
            printf("Searching for student\n");
            printf("Enter your student ID : ");
            scanf("%d", &tempID);
            findStudentIndexByID(CourseRoster, rosterSize, tempID);
        } else if (choice == 4) {
            findTopStudentIndex(CourseRoster, rosterSize);
        } else if (choice == 5) {
            break;
        }
    }

    return 0;
}