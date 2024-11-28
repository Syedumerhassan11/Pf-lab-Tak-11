#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "books.txt"

struct Book {
    int bookID;
    char title[100];
    char author[100];
    int quantity;
    float price;
};
void addBook() {
    FILE *file = fopen(FILENAME, "a");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    struct Book book;
    printf("Enter Book ID: ");
    scanf("%d", &book.bookID);
    FILE *checkFile = fopen(FILENAME, "r");
    if (checkFile) {
        struct Book existingBook;
        while (fread(&existingBook, sizeof(struct Book), 1, checkFile)) {
            if (existingBook.bookID == book.bookID) {
                printf("Book ID already exists.\n");
                fclose(checkFile);
                fclose(file);
                return;
            }
        }
        fclose(checkFile);
    }
 printf("Enter Title: ");
    fgets(book.title, sizeof(book.title), stdin);
    book.title[strcspn(book.title, "\n")] = '\0'; 

    printf("Enter Author: ");
    fgets(book.author, sizeof(book.author), stdin);
    book.author[strcspn(book.author, "\n")] = '\0';

    printf("Enter Quantity: ");
    scanf("%d", &book.quantity);
    if (book.quantity < 0) {
        printf("Quantity cannot be negative. Setting to 0.\n");
        book.quantity = 0;
    }

    printf("Enter Price: ");
    scanf("%f", &book.price);
    if (book.price < 0) {
        printf("Price cannot be negative. Setting to 0.\n");
        book.price = 0.0;
    }

    fwrite(&book, sizeof(struct Book), 1, file);
    printf("Book added successfully.\n");
    fclose(file);
}
void displayBooks() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Error opening file or file is empty.\n");
        return;
    }

    struct Book book;
    printf("All Books in Library:\n");
    while (fread(&book, sizeof(struct Book), 1, file)) {
        printf("ID: %d, Title: %s, Author: %s, Quantity: %d, Price: %.2f\n",
               book.bookID, book.title, book.author, book.quantity, book.price);
    }
    fclose(file);
}
void searchByID() {
    int bookID;
    printf("Enter Book ID to search: ");
    scanf("%d", &bookID);

    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Error opening file or file is empty.\n");
        return;
    }

    struct Book book;
    int found = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (book.bookID == bookID) {
            printf("Book found: ID: %d, Title: %s, Author: %s, Quantity: %d, Price: %.2f\n",
                   book.bookID, book.title, book.author, book.quantity, book.price);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No book found with ID %d.\n", bookID);
    }
    fclose(file);
}
void searchByTitle() {
    char title[100];
    printf("Enter Title to search: ");
    getchar(); 
    fgets(title, sizeof(title), stdin);
    title[strcspn(title, "\n")] = '\0';

    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Error opening file or file is empty.\n");
        return;
    }

    struct Book book;
    int found = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (strstr(book.title, title)) {
            printf("Book found: ID: %d, Title: %s, Author: %s, Quantity: %d, Price: %.2f\n",
                   book.bookID, book.title, book.author, book.quantity, book.price);
            found = 1;
        }
    }
    if (!found) {
        printf("No book found with Title containing '%s'.\n", title);
    }
    fclose(file);
}
void updateBook() {
    int bookID;
    printf("Enter Book ID to update: ");
    scanf("%d", &bookID);

    FILE *file = fopen(FILENAME, "r+");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    struct Book book;
    int found = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (book.bookID == bookID) {
            found = 1;
            printf("Current details: ID: %d, Title: %s, Author: %s, Quantity: %d, Price: %.2f\n",
                   book.bookID, book.title, book.author, book.quantity, book.price);

            printf("Enter new Quantity: ");
            scanf("%d", &book.quantity);
            if (book.quantity < 0) {
                printf("Quantity cannot be negative. Setting to 0.\n");
                book.quantity = 0;
            }

            printf("Enter new Price: ");
            scanf("%f", &book.price);
            if (book.price < 0) {
                printf("Price cannot be negative. Setting to 0.\n");
                book.price = 0.0;
            }

            fseek(file, -sizeof(struct Book), SEEK_CUR);
            fwrite(&book, sizeof(struct Book), 1, file);
            printf("Book updated successfully.\n");
            break;
        }
    }
    if (!found) {
        printf("No book found with ID %d.\n", bookID);
    }
    fclose(file);
}

void deleteBook() {
    int bookID;
    printf("Enter Book ID to delete: ");
    scanf("%d", &bookID);

    FILE *file = fopen(FILENAME, "r");
    FILE *tempFile = fopen("temp.txt", "w");
    if (!file || !tempFile) {
        printf("Error opening file.\n");
        return;
    }

    struct Book book;
    int found = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (book.bookID != bookID) {
            fwrite(&book, sizeof(struct Book), 1, tempFile);
        } else {
            found = 1;
        }
    }
    if (found) {
        printf("Book with ID %d deleted successfully.\n", bookID);
        remove(FILENAME);
        rename("temp.txt", FILENAME);
    } else {
        printf("No book found with ID %d.\n", bookID);
    }

    fclose(file);
    fclose(tempFile);
}

void calculateInventoryValue() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        printf("Error opening file or file is empty.\n");
        return;
    }

    struct Book book;
    float totalValue = 0.0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        totalValue += book.quantity * book.price;
    }

    printf("Total inventory value: $%.2f\n", totalValue);
    fclose(file);
}

int main() {
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. View All Books\n");
        printf("3. Search Book by ID\n");
        printf("4. Search Book by Title\n");
        printf("5. Update Book Details\n");
        printf("6. Delete Book\n");
        printf("7. Calculate Inventory Value\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                searchByID();
                break;
            case 4:
                searchByTitle();
                break;
            case 5:
                updateBook();
                break;
 			 case 6:
                deleteBook();
                break;
            case 7:
                calculateInventoryValue();
                break;
            case 8:
                printf("Exiting system...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
