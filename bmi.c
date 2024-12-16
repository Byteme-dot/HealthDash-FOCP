#include <stdio.h>

int main() {
    float weight, height, bmi;

    // Input weight and height from user
    printf("Enter weight in kilograms: ");
    scanf("%f", &weight);

    printf("Enter height in meters: ");
    scanf("%f", &height);

    // Calculate BMI
    bmi = weight / (height * height);

    // Output the BMI value
    printf("Your BMI is: %.2f\n", bmi);

    // BMI categories
    if (bmi < 18.5) {
        printf("You are underweight.\n");
    } else if (bmi >= 18.5 && bmi < 24.9) {
        printf("You have a normal weight.\n");
    } else if (bmi >= 25 && bmi < 29.9) {
        printf("You are overweight.\n");
    } else {
        printf("You are obese.\n");
    }

    return 0;
}
