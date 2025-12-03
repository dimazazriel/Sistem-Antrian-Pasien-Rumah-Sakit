#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENT 100
#define FILENAME "students.dat"

typedef struct {
    int id;
    char name[50];
    float gpa;
} Student;

Student students[MAX_STUDENT];
int count = 0;

// ---------------------- FUNCTION DECLARATIONS ----------------------
void loadData();
void saveData();
void addStudent();
void viewStudents();
void updateStudent();
void deleteStudent();
int findStudent(int id);
void clearInput();

// ---------------------- MAIN PROGRAM ----------------------
int main() {
    int choice;

    loadData();

    do {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Update Student\n");
        printf("4. Delete Student\n");
        printf("5. Save & Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        clearInput();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: saveData(); printf("Data saved. Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}

// ---------------------- FUNCTION DEFINITIONS ----------------------
void loadData() {
    FILE *file = fopen(FILENAME, "rb");
    if (file) {
        fread(&count, sizeof(int), 1, file);
        fread(students, sizeof(Student), count, file);
        fclose(file);
    }
}

void saveData() {
    FILE *file = fopen(FILENAME, "wb");
    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);
    fclose(file);
}

void addStudent() {
    if (count >= MAX_STUDENT) {
        printf("Database full!\n");
        return;
    }

    Student s;
    printf("Enter student ID: ");
    scanf("%d", &s.id);
    clearInput();

    if (findStudent(s.id) != -1) {
        printf("ID already exists!\n");
        return;
    }

    printf("Enter name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter GPA: ");
    scanf("%f", &s.gpa);

    students[count++] = s;

    printf("Student added successfully!\n");
}

void viewStudents() {
    if (count == 0) {
        printf("No data available.\n");
        return;
    }

    printf("\n%-5s %-20s %-5s\n", "ID", "Name", "GPA");
    printf("---------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n", students[i].id, students[i].name, students[i].gpa);
    }
}

void updateStudent() {
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);
    clearInput();

    int index = findStudent(id);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("Enter new name: ");
    fgets(students[index].name, sizeof(students[index].name), stdin);
    students[index].name[strcspn(students[index].name, "\n")] = 0;

    printf("Enter new GPA: ");
    scanf("%f", &students[index].gpa);

    printf("Student updated successfully!\n");
}

void deleteStudent() {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    clearInput();

    int index = findStudent(id);
    if (index == -1) {
        printf("Student not found!\n");
        return;
    }

    for (int i = index; i < count - 1; i++) {
        students[i] = students[i + 1];
    }

    count--;

    printf("Student deleted successfully!\n");
}

int findStudent(int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id)
            return i;
    }
    return -1;
}

void clearInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
