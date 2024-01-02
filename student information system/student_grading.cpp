#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_STUDENTS 100
#define MAX_GRADES 6

#define FILENAME "information.txt"

typedef struct {
    int id;
    int notes;
    char name[50];
    int grades[MAX_GRADES];
    int pass;
} Student;

void readStudentsFromFile(Student students[], int *numStudents);
void determinePassStatus(Student students[], int numStudents);
void printStudentInfo(Student students[], int numStudents);
void showStudentInfoByName(Student students[], int numStudents, const char *searchName);
void addNewStudent(Student students[], int *numStudents);
void writeStudentsToFile(Student students[], int numStudents);

int main() {
    Student students[MAX_STUDENTS];
    int numStudents = 0;

    readStudentsFromFile(students, &numStudents);
    determinePassStatus(students, numStudents);

    char searchName[50];
    printf("-**CANKAYA STUDENT GRADING SYSTEM**-\n");

    printf("\t  USERNAME:");
    scanf("%s", searchName);
    showStudentInfoByName(students, numStudents, searchName);

   
    addNewStudent(students, &numStudents);

    printStudentInfo(students, numStudents);

    writeStudentsToFile(students, numStudents);

    return 0;
}

void readStudentsFromFile(Student students[], int *numStudents) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error this  file  %s is not available for reading.\n", FILENAME);
        exit(1);
    }

    while (*numStudents < MAX_STUDENTS && fscanf(file, "%d %s", &students[*numStudents].id, students[*numStudents].name) == 2) {
        for (int i = 0; i < MAX_GRADES; ++i) {
            fscanf(file, "%d", &students[*numStudents].grades[i]);
        }
        students[*numStudents].pass = 0;
        (*numStudents)++;
    }

    fclose(file);
}

void determinePassStatus(Student students[], int numStudents) {
    for (int i = 0; i < numStudents; ++i) {
        int sum = 0;
        for (int j = 0; j < MAX_GRADES; ++j) {
            sum += students[i].grades[j];
        }
        float average = (float)sum / MAX_GRADES;
        students[i].pass = (average >= 50) ? 1 : 0;
    }
}

void showStudentInfoByName(Student students[], int numStudents, const char *searchName) {
    int found = 0;
    for (int i = 0; i < numStudents; ++i) {
        if (strcmp(students[i].name, searchName) == 0) {
            printf("\nStudent Information for %s:\n", searchName);
            printf("Student ID: %d\n", students[i].id);
            printf("Pass Status: %s\n", (students[i].pass) ? "Passed" : "Failed");
            printf("  CNG ENG  MTH  CIF  CPR  INF \n");

            for (int j = 0; j < MAX_GRADES; ++j) {
                printf("  %d ", students[i].grades[j]);
            }

            printf("\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nStudent %s not founded.\n", searchName);
    }
}

void addNewStudent(Student students[], int *numStudents) {
    if (*numStudents >= MAX_STUDENTS) {
        printf("Maximum limit reached.You can't add new student more. \n");
        return;
    }

    printf("\n Please enter a new student information:\n");
    printf("Student ID: ");
    scanf("%d", &students[*numStudents].id);

    printf("Student Name: ");
    scanf("%s", students[*numStudents].name);

    printf("Enter grades for CNG ENG MTH CIF CPR INF:\n");
    for (int i = 0; i < MAX_GRADES; ++i) {
        printf("Grade %d: ", i + 1);
        scanf("%d", &students[*numStudents].grades[i]);
    }
    determinePassStatus(&students[*numStudents], 1);

    (*numStudents)++;
}

void writeStudentsToFile(Student students[], int numStudents) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error this file %s is not available for writing.\n", FILENAME);
        exit(1);
    }

    for (int i = 0; i < numStudents; ++i) {
        fprintf(file, "%d %s", students[i].id, students[i].name);
        for (int j = 0; j < MAX_GRADES; ++j) {
            fprintf(file, " %d", students[i].grades[j]);
        }
        fprintf(file, "\n");

        printf("Cankaya University Student Information System-Barış Demirer-Melih Özdemirci");
    }

    fclose(file);
}

void printStudentInfo(Student students[], int numStudents) {
    printf("\nUpdated Student Information:\n");
    for (int i = 0; i < numStudents; ++i) {
        printf("Student ID: %d\n", students[i].id);
        printf("Pass Status: %s\n", (students[i].pass) ? "Passed" : "Failed");
        printf("  CNG  ENG  MTH  CIF  CPR  INF \n");

        for (int j = 0; j < MAX_GRADES; ++j) {
            printf("  %d ", students[i].grades[j]);
        }

        printf("\n\n\n");
    }
}