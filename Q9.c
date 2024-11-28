#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSES 5
#define MAX_STUDENTS 5
#define MAX_DEPARTMENTS 3

struct Student {
    int studentID;
    char studentName[100];
};
struct Instructor {
    char instructorName[100];
    char departmentName[100];
};
struct Course {
    int courseID;
    char courseName[100];
    struct Instructor instructor;
    struct Student students[MAX_STUDENTS];  
    int studentCount;
};
struct Department {
    char departmentName[100];
    struct Course courses[MAX_COURSES]; 
    int courseCount;
};
void addDepartment(struct Department *departments, int *deptCount) {
    printf("\nEnter Department Name: ");
    getchar();
    fgets(departments[*deptCount].departmentName, sizeof(departments[*deptCount].departmentName), stdin);
    departments[*deptCount].departmentName[strcspn(departments[*deptCount].departmentName, "\n")] = '\0'; 
    (*deptCount)++;
    printf("Department added successfully.\n");
}
void addCourse(struct Department *department) {
    if (department->courseCount < MAX_COURSES) {
        struct Course *course = &department->courses[department->courseCount];

        printf("\nEnter Course ID: ");
        scanf("%d", &course->courseID);
        getchar(); 

        printf("Enter Course Name: ");
        fgets(course->courseName, sizeof(course->courseName), stdin);
        course->courseName[strcspn(course->courseName, "\n")] = '\0';

        printf("Enter Instructor Name: ");
        fgets(course->instructor.instructorName, sizeof(course->instructor.instructorName), stdin);
        course->instructor.instructorName[strcspn(course->instructor.instructorName, "\n")] = '\0'; 

        printf("Enter Instructor Department: ");
        fgets(course->instructor.departmentName, sizeof(course->instructor.departmentName), stdin);
        course->instructor.departmentName[strcspn(course->instructor.departmentName, "\n")] = '\0'; 

        course->studentCount = 0; 
        department->courseCount++;
        printf("Course added successfully.\n");
    } else {
        printf("Cannot add more courses. Maximum limit reached.\n");
    }
}

void enrollStudents(struct Course *course) {
    if (course->studentCount < MAX_STUDENTS) {
        struct Student *student = &course->students[course->studentCount];

        printf("\nEnter Student ID: ");
        scanf("%d", &student->studentID);
        getchar(); 

        printf("Enter Student Name: ");
        fgets(student->studentName, sizeof(student->studentName), stdin);
        student->studentName[strcspn(student->studentName, "\n")] = '\0';

        course->studentCount++;
        printf("Student enrolled successfully.\n");
    } else {
        printf("Cannot enroll more students. Maximum limit reached.\n");
    }
}
void displayUniversity(struct Department *departments, int deptCount) {
	int i;
	int j;
	int k;
    for (i = 0; i < deptCount; i++) {
        printf("\nDepartment: %s\n", departments[i].departmentName);
        for (j = 0; j < departments[i].courseCount; j++) {
            struct Course *course = &departments[i].courses[j];
            printf("  Course ID: %d, Course Name: %s\n", course->courseID, course->courseName);
            printf("    Instructor: %s, Department: %s\n", course->instructor.instructorName, course->instructor.departmentName);

            printf("    Enrolled Students:\n");
            for (k = 0; k < course->studentCount; k++) {
                printf("      ID: %d, Name: %s\n", course->students[k].studentID, course->students[k].studentName);
            }
        }
    }
}

int main() {
    struct Department departments[MAX_DEPARTMENTS];
    int deptCount = 0;
    int choice;

    while (1) {
        printf("\nUniversity Management System\n");
        printf("1. Add Department\n");
        printf("2. Add Course\n");
        printf("3. Enroll Students in Course\n");
        printf("4. Display All Departments and Courses\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addDepartment(departments, &deptCount);
                break;
            case 2:
                if (deptCount > 0) {
                    int deptIndex;
                    printf("Enter department index (0 to %d): ", deptCount - 1);
                    scanf("%d", &deptIndex);
                    if (deptIndex >= 0 && deptIndex < deptCount) {
                        addCourse(&departments[deptIndex]);
                    } else {
                        printf("Invalid department index.\n");
                    }
                } else {
                    printf("No departments available. Add a department first.\n");
                }
                break;
            case 3:
                if (deptCount > 0) {
                    int deptIndex, courseIndex;
                    printf("Enter department index (0 to %d): ", deptCount - 1);
                    scanf("%d", &deptIndex);
                    if (deptIndex >= 0 && deptIndex < deptCount) {
                        printf("Enter course index (0 to %d): ", departments[deptIndex].courseCount - 1);
                        scanf("%d", &courseIndex);
                        if (courseIndex >= 0 && courseIndex < departments[deptIndex].courseCount) {
                            enrollStudents(&departments[deptIndex].courses[courseIndex]);
                        } else {
                            printf("Invalid course index.\n");
                        }
                    } else {
                        printf("Invalid department index.\n");
                    }
                } else {
                    printf("No departments available. Add a department first.\n");
                }
                break;
            case 4:
                if (deptCount > 0) {
                    displayUniversity(departments, deptCount);
                } else {
                    printf("No departments available.\n");
                }
                break;
            case 5:
                printf("Exiting system...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

