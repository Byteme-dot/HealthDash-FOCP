// Track personal health like weight,height,age,exercise, diet.
#include<stdio.h>
#include "input_output.h"

#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>


// Callback function for the login button
void on_login_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entries[1]));
    
    FILE *file;
    file = fopen("logindata.txt", "r");
    if (file == NULL) {
        g_print("Error opening file for reading.\n");
        return;
    }

    char file_username[100], file_password[100];
    gboolean login_success = FALSE;

    while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
            login_success = TRUE;
            break;
        }
    }
    fclose(file);

    if (login_success) {
        g_print("Login successful. Username: %s\n", username);
    } else {
        g_print("Login failed. Invalid username or password.\n");
    }
}

// Callback function for the sign-up button
void on_signup_button_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data;
    const gchar *username = gtk_entry_get_text(GTK_ENTRY(entries[0]));
    const gchar *password = gtk_entry_get_text(GTK_ENTRY(entries[1]));

    FILE *file = fopen("logindata.txt", "a");
    if (file == NULL) {
        g_print("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);

    // Read back the file contents to verify the write operation
    file = fopen("logindata.txt", "r");
    if (file == NULL) {
        g_print("Error opening file for verification.\n");
        return;
    }

    g_print("File contents after sign up:\n");
    char line[200];
    while (fgets(line, sizeof(line), file) != NULL) {
        g_print("%s", line);
    }
    fclose(file);

    g_print("Sign Up successful. Username: %s added.\n", username);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *username_label;
    GtkWidget *password_label;
    GtkWidget *username_entry;
    GtkWidget *password_entry;
    GtkWidget *login_button;
    GtkWidget *signup_button;
    GtkWidget *separator;

    gtk_init(&argc, &argv);

    // Create a new window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Login Interface");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    // Create a grid
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create username and password labels
    username_label = gtk_label_new("Username:");
    password_label = gtk_label_new("Password:");

    // Create username and password entries
    username_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(username_entry), "Enter Username");
    password_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(password_entry), "Enter Password");
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE); // Hide password text

    // Create login button
    login_button = gtk_button_new_with_label("Login");
    
    // Create sign-up button
    signup_button = gtk_button_new_with_label("Sign Up");
    
    // Create a separator
    separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);

    // Array to pass both entries to the callback
    GtkWidget *entries[2] = {username_entry, password_entry};
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_button_clicked), entries);
    g_signal_connect(signup_button, "clicked", G_CALLBACK(on_signup_button_clicked), entries);

    // Attach widgets to the grid
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), username_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), password_entry, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), login_button, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), separator, 0, 3, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), signup_button, 1, 4, 1, 1);

    // Connect the window close button to the main quit function
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Show all widgets
    gtk_widget_show_all(window);

    // Main loop
    gtk_main();

    return 0;
}




