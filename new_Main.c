#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Global variables
int arr_exercises_cal[17] = {600, 500, 700, 400, 1, 1, 4, 300, 150, 600, 500, 200, 400, 1, 1, 1, 300};
char name[30];
int age, height, days_to_input;

// Structure for daily data
typedef struct {
    int day;
    int weight;
    int calorie_burn;
    int calorie_intake;
    float BMI;
} UserDay;

UserDay days[30];

// Function prototypes
void save_user_data();

// Utility to generate a unique file name
void generate_unique_filename(char *buffer, const char *username) {
    srand(time(NULL));
    int random_number = rand() % 100000;
    sprintf(buffer, "%s_%d.txt", username, random_number);
}

// Callback for collecting general user info
void on_submit_user_info(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;

    // Retrieve user input
    strcpy(name, gtk_entry_get_text(GTK_ENTRY(entries[0])));
    age = atoi(gtk_entry_get_text(GTK_ENTRY(entries[1])));
    height = atoi(gtk_entry_get_text(GTK_ENTRY(entries[2])));
    days_to_input = atoi(gtk_entry_get_text(GTK_ENTRY(entries[3])));

    gtk_main_quit();
}

// Function to display the user info form
void display_user_info_form() {
    GtkWidget *window, *grid, *label, *entry, *button;
    GtkWidget *entries[4];

    gtk_init(NULL, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "User Information");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    label = gtk_label_new("Name:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    entry = gtk_entry_new();
    entries[0] = entry;
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);

    label = gtk_label_new("Age:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 1, 1, 1);
    entry = gtk_entry_new();
    entries[1] = entry;
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 1, 1, 1);

    label = gtk_label_new("Height (cm):");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 2, 1, 1);
    entry = gtk_entry_new();
    entries[2] = entry;
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 2, 1, 1);

    label = gtk_label_new("Days to Input:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 1, 1);
    entry = gtk_entry_new();
    entries[3] = entry;
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 3, 1, 1);

    button = gtk_button_new_with_label("Submit");
    g_signal_connect(button, "clicked", G_CALLBACK(on_submit_user_info), entries);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 2, 1);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}

// Callback for collecting exercise data
void on_submit_exercise_data(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    int day_index = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "day_index"));
    int num_exercises = atoi(gtk_entry_get_text(GTK_ENTRY(entries[0])));
    
    days[day_index].calorie_burn = 0;
    for (int i = 0; i < num_exercises; i++) {
        int exercise_type = atoi(gtk_entry_get_text(GTK_ENTRY(entries[1 + i * 2])));
        int amount = atoi(gtk_entry_get_text(GTK_ENTRY(entries[2 + i * 2])));

        if (exercise_type == 7) {
            days[day_index].calorie_burn += amount * arr_exercises_cal[exercise_type - 1];
        } else {
            days[day_index].calorie_burn += amount * arr_exercises_cal[exercise_type - 1];
        }
    }

    days[day_index].weight = atoi(gtk_entry_get_text(GTK_ENTRY(entries[1 + num_exercises * 2])));
    days[day_index].calorie_intake = atoi(gtk_entry_get_text(GTK_ENTRY(entries[2 + num_exercises * 2])));
    float height_m = (float)height / 100;
    days[day_index].BMI = days[day_index].weight / (height_m * height_m);

    gtk_main_quit();
}

// Callback to handle exercise checkbox selections
void on_exercise_checkbox_toggled(GtkToggleButton *toggle_button, gpointer data) {
    int *exercise_selected = (int *)data;
    *exercise_selected = gtk_toggle_button_get_active(toggle_button);
}

// Callback for collecting exercise data with checkboxes
void on_submit_exercise_data_with_checkboxes(GtkWidget *widget, gpointer data) {
    GtkWidget **widgets = (GtkWidget **)data;
    int day_index = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "day_index"));

    days[day_index].calorie_burn = 0;

    // Iterate over the checkboxes
    for (int i = 0; i < 17; i++) {
        GtkWidget *checkbox = widgets[i];
        GtkWidget *entry_reps_or_minutes = widgets[17 + i];

        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox))) {
            int amount = atoi(gtk_entry_get_text(GTK_ENTRY(entry_reps_or_minutes)));

            if (i == 6) { // Plank (index 6) uses minutes
                days[day_index].calorie_burn += amount * arr_exercises_cal[i];
            } else { // Other exercises use reps or hours
                days[day_index].calorie_burn += amount * arr_exercises_cal[i];
            }
        }
    }

    // Collect weight and calorie intake
    GtkWidget *entry_weight = widgets[34]; // Assuming weight is at index 34
    GtkWidget *entry_calories = widgets[35]; // Assuming calorie intake is at index 35

    days[day_index].weight = atoi(gtk_entry_get_text(GTK_ENTRY(entry_weight)));
    days[day_index].calorie_intake = atoi(gtk_entry_get_text(GTK_ENTRY(entry_calories)));

    float height_m = (float)height / 100;
    days[day_index].BMI = days[day_index].weight / (height_m * height_m);

    gtk_main_quit();
}

// Function to display the updated exercise data form with checkboxes
void display_exercise_data_form(int day_index) {
    GtkWidget *window, *grid, *label, *entry, *checkbox, *button;
    GtkWidget *entries[36]; // For 17 exercises + weight + calorie intake

    gtk_init(NULL, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Exercise Data - Day");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    const char *exercise_names[] = {
        "Running/Jogging", "Cycling", "Jumping Rope", "Swimming", "Pushups", "Squats",
        "Plank", "Yoga", "Stretch", "Burpees", "High Knees", "Single Leg Stand",
        "Bosu Ball", "Jump Squats", "Tricep Dip", "Crunches", "Walking"
    };

    for (int i = 0; i < 17; i++) {
        checkbox = gtk_check_button_new_with_label(exercise_names[i]);
        g_object_set_data(G_OBJECT(checkbox), "exercise_selected", GINT_TO_POINTER(0));
        g_signal_connect(checkbox, "toggled", G_CALLBACK(on_exercise_checkbox_toggled), &entries[i * 2]);

        gtk_grid_attach(GTK_GRID(grid), checkbox, 0, i, 1, 1);
        entries[i * 2] = checkbox;

        label = gtk_label_new(i == 6 ? "Minutes:" : "Reps/Hours:");
        gtk_grid_attach(GTK_GRID(grid), label, 1, i, 1, 1);

        entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(grid), entry, 2, i, 1, 1);
        entries[i * 2 + 1] = entry;
    }

    label = gtk_label_new("Weight:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 18, 1, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 18, 2, 1);
    entries[34] = entry;

    label = gtk_label_new("Calorie Intake:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 19, 1, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 19, 2, 1);
    entries[35] = entry;

    button = gtk_button_new_with_label("Submit");
    g_signal_connect(button, "clicked", G_CALLBACK(on_submit_exercise_data_with_checkboxes), entries);
    g_object_set_data(G_OBJECT(button), "day_index", GINT_TO_POINTER(day_index));
    gtk_grid_attach(GTK_GRID(grid), button, 0, 20, 3, 1);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();
}

// Save user data to a file
void save_user_data() {
    char filename[50];
    generate_unique_filename(filename, name);

    FILE *fptr = fopen(filename, "w");
    if (!fptr) {
        perror("Error opening file");
        return;
    }

    fprintf(fptr, "Name: %s\nAge: %d\nHeight: %d\n", name, age, height);

    for (int i = 0; i < days_to_input; i++) {
        fprintf(fptr, "Day %d:\n", days[i].day);
        fprintf(fptr, "  Weight: %d kg\n", days[i].weight);
        fprintf(fptr, "  Calorie Burnt: %d kcal\n", days[i].calorie_burn);
        fprintf(fptr, "  Calorie Intake: %d kcal\n", days[i].calorie_intake);
        fprintf(fptr, "  BMI: %.2f\n", days[i].BMI);
    }

    fclose(fptr);
    printf("Data saved to file: %s\n", filename);
}

// Main function
int main() {
    // Collect general user information
    display_user_info_form();

    // Collect daily exercise and weight data
    for (int i = 0; i < days_to_input; i++) {
        days[i].day = i + 1;
        display_exercise_data_form(i);
    }

    // Save the collected data to a file
    save_user_data();

    return 0;
}
        