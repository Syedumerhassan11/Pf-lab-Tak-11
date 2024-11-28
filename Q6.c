#include <stdio.h>
#include <string.h>

struct Invoice {
    char partNumber[50];
    char partDescription[100];
    int quantity;
    float pricePerItem;
};

void initializeInvoice(struct Invoice* invoice, const char* partNumber, const char* partDescription, int quantity, float pricePerItem) {
    strcpy(invoice->partNumber, partNumber);
    strcpy(invoice->partDescription, partDescription);
    if (quantity > 0) {
        invoice->quantity = quantity;
    } else {
        invoice->quantity = 0;
    }
    if (pricePerItem > 0) {
        invoice->pricePerItem = pricePerItem;
    } else {
        invoice->pricePerItem = 0.0f;
    }
}

float calculateInvoiceAmount(struct Invoice* invoice) {
    return invoice->quantity * invoice->pricePerItem;
}
void displayInvoice(struct Invoice* invoice) {
    printf("Part Number: %s\n", invoice->partNumber);
    printf("Part Description: %s\n", invoice->partDescription);
    printf("Quantity: %d\n", invoice->quantity);
    printf("Price per Item: $%.2f\n", invoice->pricePerItem);
    printf("Invoice Amount: $%.2f\n", calculateInvoiceAmount(invoice));
}

int main() {
    struct Invoice invoice1, invoice2;
    initializeInvoice(&invoice1, "P1234", "Hammer", 10, 15.99);
    char partNumber[50];
    char partDescription[100];
    int quantity;
    float pricePerItem;

    printf("Enter part number: ");
    scanf("%s", partNumber);

    printf("Enter part description: ");
    scanf(" %[^\n]", partDescription); 

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    printf("Enter price per item: ");
    scanf("%f", &pricePerItem);
    initializeInvoice(&invoice2, partNumber, partDescription, quantity, pricePerItem);
    printf("\n--- Invoice 1 ---\n");
    displayInvoice(&invoice1);

    printf("\n--- Invoice 2 ---\n");
    displayInvoice(&invoice2);

    return 0;
}

