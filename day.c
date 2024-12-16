#include <stdio.h>

int main() {
    int day, month, year;
    char exerciseName[50];
    int duration, caloriesBurned;

    // Ask for the date
    printf("Enter the date ,day , month year: ");
    scanf("%d %d %d", &day, &month, &year);

    // Ask for exercise details
    printf("Enter the name of the exercise: ");
    // getchar();  // To clear the newline character from previous input
    // fgets(exerciseName, sizeof(exerciseName), stdin);

    printf("/n Enter the duration of the exercise in minutes: ");
    scanf("%d", &duration);

    printf("Enter the calories burned during the exercise: ");
    scanf("%d", &caloriesBurned);

    // Display the entered data
    printf("\n--- Exercise Data for %d/%d/%d ---\n", day, month, year);
    printf("Exercise: %s", exerciseName);
    printf("Duration: %d minutes\n", duration);
    printf("Calories burned: %d kcal\n", caloriesBurned);

    return 0;
}
