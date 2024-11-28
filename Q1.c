#include <stdio.h>
#include <stdlib.h>
struct Rectangle {
    float length;
    float width;
};
float perimeter(struct Rectangle *rect) {
    return 2 * (rect->length + rect->width);
}
float area(struct Rectangle *rect) {
    return rect->length * rect->width;
}
void check(float length, float width) {
    if (length <= 0.0 || length >= 20.0 || width <= 0.0 || width >= 20.0) {
        printf("Error: Length and width must be greater than 0.0 and less than 20.0\n");
        exit(1);
    }
}
void initRectangle(struct Rectangle *rect, float length, float width) {
    check(length, width);
    rect->length = length;
    rect->width = width;
}

int main() {
    struct Rectangle rect;
    float length, width;
    printf("Enter the length of the rectangle (0 < length < 20): ");
    scanf("%f", &length);
    
    printf("Enter the width of the rectangle (0 < width < 20): ");
    scanf("%f", &width);
    initRectangle(&rect, length, width);
    printf("Perimeter: %.2f\n", perimeter(&rect));
    printf("Area: %.2f\n", area(&rect));

    return 0;
}

