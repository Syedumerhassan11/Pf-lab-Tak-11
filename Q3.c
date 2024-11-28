#include <stdio.h>
#include <ctype.h>
void copyFileWithUppercase(const char *sourceFilename, const char *destFilename) {
    FILE *sourceFile = fopen(sourceFilename, "r");
    if (sourceFile == NULL) {
        printf("Error: Could not open source file %s\n", sourceFilename);
        exit(1);
    }

    FILE *destFile = fopen(destFilename, "w");
    if (destFile == NULL) {
        printf("Error: Could not open destination file %s\n", destFilename);
        fclose(sourceFile);
        exit(1);
    }

    char ch;

    while ((ch = fgetc(sourceFile)) != EOF) {
        fputc(toupper(ch), destFile);
    }
    fclose(sourceFile);
    fclose(destFile);
}

int main() {
    char sourceFilename[100], destFilename[100];
    printf("Enter the source file name: ");
    scanf("%s", sourceFilename);

    printf("Enter the destination file name: ");
    scanf("%s", destFilename);
    copyFileWithUppercase(sourceFilename, destFilename);

    printf("File copied successfully with lowercase characters converted to uppercase.\n");

    return 0;
}

