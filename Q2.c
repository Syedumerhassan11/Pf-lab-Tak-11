#include <stdio.h>
#include <stdlib.h>

void displayFileWithLineNumbers(const char *filename) {
    FILE *file = fopen(filename, "r");  // Open file in read mode
    if (file == NULL) {
        // If the file cannot be opened, print an error message and exit
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    char line[256];
    int lineNumber = 1;  
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%d: %s", lineNumber, line);
        lineNumber++;
    }

    fclose(file);
}

int main() {
    char filename[100];
    printf("Enter the filename to read: ");
    scanf("%s", filename);
    displayFileWithLineNumbers(filename);

    return 0;
}

