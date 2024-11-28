#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Employee {
    char name[100];
    char dob[20];
    int empID;
    char department[50];
    float salary;
};
void addEmployee(struct Employee employees[], int *count) {
    if (*count >= 10) {  
        printf("Error: Maximum employee limit reached.\n");
        return;
    }

    struct Employee emp;
    printf("Enter Name: ");
    getchar();
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = '\0';

    printf("Enter Date of Birth (dd-mm-yyyy): ");
    fgets(emp.dob, sizeof(emp.dob), stdin);
    emp.dob[strcspn(emp.dob, "\n")] = '\0';

    printf("Enter Employee ID: ");
    scanf("%d", &emp.empID);

    printf("Enter Department: ");
    getchar(); 
    fgets(emp.department, sizeof(emp.department), stdin);
    emp.department[strcspn(emp.department, "\n")] = '\0';

    printf("Enter Salary: ");
    scanf("%f", &emp.salary);
    employees[*count] = emp;
    (*count)++; 
    printf("Employee added successfully.\n");
}
void deleteEmployee(struct Employee employees[], int *count, int empID) {
    int found = 0;
int i;
int j;
    for (i = 0; i < *count; i++) {
        if (employees[i].empID == empID) {
            found = 1;
            for (j = i; j < *count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            (*count)--; 
            printf("Employee with ID %d deleted successfully.\n", empID);
            break;
        }
    }

    if (!found) {
        printf("Error: Employee with ID %d not found.\n", empID);
    }
}
void displayEmployees(struct Employee employees[], int count) {
    if (count == 0) {
        printf("No employees to display.\n");
        return;
    }

    printf("\n%-30s %-15s %-10s %-20s %-10s\n", "Name", "Date of Birth", "Emp ID", "Department", "Salary");
    printf("---------------------------------------------------------------\n");
int i;
    for (i = 0; i < count; i++) {
        printf("%-30s %-15s %-10d %-20s %-10.2f\n", 
               employees[i].name, employees[i].dob, employees[i].empID, employees[i].department, employees[i].salary);
    }
}

int main() {
    struct Employee employees[10];  
    int employeeCount = 0; 
    int choice, empID;

    while (1) {

        printf("\nEmployee Management System\n");
        printf("1. Add an Employee\n");
        printf("2. Delete an Employee\n");
        printf("3. Display All Employees\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &employeeCount);
                break;
            case 2:
                printf("Enter Employee ID to delete: ");
                scanf("%d", &empID);
                deleteEmployee(employees, &employeeCount, empID);
                break;
            case 3:
                displayEmployees(employees, employeeCount);
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);  // Exit the program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

