#include <stdio.h>
struct Phone {
    int areaCode;
    int exchange;
    int number;
};

int main() {
    struct Phone myNumber = {212, 767, 8900};
    struct Phone yourNumber;

    printf("Enter area code: ");
    scanf("%d", &yourNumber.areaCode);

    printf("Enter exchange: ");
    scanf("%d", &yourNumber.exchange);

    printf("Enter number: ");
    scanf("%d", &yourNumber.number);

    printf("\nMy number is (%d) %d-%d\n", myNumber.areaCode, myNumber.exchange, myNumber.number);
    printf("Your number is (%d) %d-%d\n", yourNumber.areaCode, yourNumber.exchange, yourNumber.number);

    return 0;
}

