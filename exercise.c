#include <stdio.h>

int main() {
    char exerciseName[50];
    int duration, caloriesBurned;

    // Introduction
    printf("Welcome to the Exercise Tracker!\n");

    // Get exercise details
    printf("Enter the name of your exercise: ");
    getchar();  
    fgets(exerciseName, sizeof(exerciseName), stdin);

    printf("Enter the duration of the exercise in minutes: ");
    scanf("%d", &duration);

    printf("Enter the calories burned during the exercise: ");
    scanf("%d", &caloriesBurned);

    // Output the details
    printf("\n--- Exercise Summary ---\n");
    printf("Exercise: %s", exerciseName);
    printf("Duration: %d minutes\n", duration);
    printf("Calories burned: %d kcal\n", caloriesBurned);

    return 0;
}
