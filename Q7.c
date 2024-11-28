#include <stdio.h>
#include <string.h>

#define MAX_DEPARTMENTS 10
#define MAX_COURSES 5
#define MAX_STUDENTS 50

// Define a structure for Course
struct Course {
    char courseID[10];
    char courseName[100];
    char instructorName[100];
    int credits;
};

// Define a structure for Department
struct Department {
    char departmentName[100];
    struct Course courses[MAX_COURSES];
    int numCourses;
};

// Define a structure for Student
struct Student {
    char studentName[100];
    char courseID[10];  // Assuming one student enrolls in one course for simplicity
};

// Define the University structure which includes departments and students
struct University {
    struct Department departments[MAX_DEPARTMENTS];
    int numDepartments;
    struct Student students[MAX_STUDENTS];
    int numStudents;
};

// Function to initialize a new department
void addDepartment(struct University* uni, const char* deptName) {
    if (uni->numDepartments < MAX_DEPARTMENTS) {
        strcpy(uni->departments[uni->numDepartments].departmentName, deptName);
        uni->departments[uni->numDepartments].numCourses = 0;  // Initialize number of courses as 0
        uni->numDepartments++;
        printf("Department '%s' added successfully.\n", deptName);
    } else {
        printf("Cannot add more departments. Max limit reached.\n");
    }
}

// Function to add a new course to a department
void addCourse(struct University* uni, const char* deptName, const char* courseID, const char* courseName, const char* instructorName, int credits) {
	int i;
    for (i = 0; i < uni->numDepartments; i++) {
        if (strcmp(uni->departments[i].departmentName, deptName) == 0) {
            struct Department* dept = &uni->departments[i];
            if (dept->numCourses < MAX_COURSES) {
                struct Course* course = &dept->courses[dept->numCourses];
                strcpy(course->courseID, courseID);
                strcpy(course->courseName, courseName);
                strcpy(course->instructorName, instructorName);
                course->credits = credits;
                dept->numCourses++;
                printf("Course '%s' added successfully to department '%s'.\n", courseName, deptName);
            } else {
                printf("Cannot add more courses to department '%s'. Max limit reached.\n", deptName);
            }
            return;
        }
    }
    printf("Department '%s' not found.\n", deptName);
}

// Function to enroll a student in a course
void enrollStudent(struct University* uni, const char* studentName, const char* courseID) {
    if (uni->numStudents < MAX_STUDENTS) {
        struct Student* student = &uni->students[uni->numStudents];
        strcpy(student->studentName, studentName);
        strcpy(student->courseID, courseID);
        uni->numStudents++;
        printf("Student '%s' enrolled in course '%s'.\n", studentName, courseID);
    } else {
        printf("Cannot enroll more students. Max limit reached.\n");
    }
}

// Function to calculate the total credits for students in a department
void calculateTotalCredits(struct University* uni, const char* deptName) {
    int totalCredits = 0;
    int i;
    int j;
    int k;
    for (i = 0; i < uni->numDepartments; i++) {
        if (strcmp(uni->departments[i].departmentName, deptName) == 0) {
            struct Department* dept = &uni->departments[i];
            for (j = 0; j < dept->numCourses; j++) {
                struct Course* course = &dept->courses[j];
                // Count the total credits for all students enrolled in this course
                for (k = 0; k < uni->numStudents; k++) {
                    if (strcmp(uni->students[k].courseID, course->courseID) == 0) {
                        totalCredits += course->credits;
                    }
                }
            }
            printf("Total credits for students enrolled in department '%s': %d\n", deptName, totalCredits);
            return;
        }
    }
    printf("Department '%s' not found.\n", deptName);
}

// Function to display all departments and their courses
void displayUniversity(struct University* uni) {
    int i;
    int j;
	for (i = 0; i < uni->numDepartments; i++) {
        struct Department* dept = &uni->departments[i];
        printf("\nDepartment: %s\n", dept->departmentName);
        for (j = 0; j < dept->numCourses; j++) {
            struct Course* course = &dept->courses[j];
            printf("  Course ID: %s\n", course->courseID);
            printf("  Course Name: %s\n", course->courseName);
            printf("  Instructor: %s\n", course->instructorName);
            printf("  Credits: %d\n", course->credits);
        }
    }
}

int main() {
    struct University uni = {0}; // Initialize the university with no departments or students

    // Add departments
    addDepartment(&uni, "Computer Science");
    addDepartment(&uni, "Electrical Engineering");

    // Add courses to departments
    addCourse(&uni, "Computer Science", "CS101", "Introduction to Programming", "Dr. Smith", 4);
    addCourse(&uni, "Computer Science", "CS102", "Data Structures", "Dr. Johnson", 3);
    addCourse(&uni, "Electrical Engineering", "EE101", "Circuit Analysis", "Dr. Brown", 3);

    // Enroll students
    enrollStudent(&uni, "Alice", "CS101");
    enrollStudent(&uni, "Bob", "CS101");
    enrollStudent(&uni, "Charlie", "EE101");

    // Display university details
    displayUniversity(&uni);

    // Calculate total credits for a department
    calculateTotalCredits(&uni, "Computer Science");

    return 0;
}

