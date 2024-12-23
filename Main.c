#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int login_signup();
void user_input_old_user();
void print_exercises();
void user_input_new_user();
void printHealthData(char filename_need[]);
void deleteDataByDate(char filename_need[]);
void printDatesFromFile(char filename[]);

typedef struct{
    char date[11];
    int weight;
    int calorie_burn;
    int calorie_intake;
    float BMI;
    int water_intake;
}User;


// Define Global Variables
int check_log_stat=-1;
int E_xit=0;
int arr_exercies_cal[16]={600,500,700,400,1,1,4,300,150,600,500,400,1,1,1,300};
char filename[100];
int Signin_status=0;
char filename_need[100];

int main() {
    while(E_xit==0){
        if (Signin_status!=1){
            if (check_log_stat>-1){  
                if(check_log_stat==1){
                    printf("\n!  L O G I N  S U C C E S S F U L  !\n\n");
                    Signin_status=1;
                }else if (check_log_stat==2){
                    printf("\n!  S I G N  U P  S U C C E S S F U L  !\n\n");
                    Signin_status=1;
                    user_input_new_user();
                }else if (check_log_stat==3){
                    E_xit=1;
                    Signin_status=0;
                    break;
                }else{
                    Signin_status=0;
                    printf("\nAn Error Occured! OR Wrong Username/Password\n\n");
                    E_xit=1;
                    break;
                }
            }else{
                check_log_stat=login_signup();
            }
        }else{
            if(Signin_status==1){
                int choice;
                printf("1. Insert Data\n");
                printf("2. Delete Data\n");
                printf("3. Display Data\n");
                printf("4. Exit\n");
                printf("5. Sign Out\n\n");
                printf("Enter Your Choice: ");
                scanf("%d",&choice);
                if(choice==1){
                    user_input_old_user();
                }else if (choice==2){
                    deleteDataByDate(filename_need);
                }else if (choice==3){
                    printHealthData(filename_need);
                }else if (choice==4){
                    printf("Ended Program!");
                    E_xit=1;                     
                }else if (choice==5){
                    printf("Signed Out\n");
                    Signin_status=0;
                    check_log_stat=login_signup();           
                }else{
                    printf("Enter a Valid Choice !!!");
                }
            }
        }
    }
    return 0;
}

int login_signup(){
    int choice=0;
    printf("---WELCOME TO HEALTH-DASH APP---\n");
    printf("1. Login\n");
    printf("2. SignUp\n");
    printf("3. Exit\n\n");
    printf("Enter Your Choice: ");
    scanf("%d",&choice);
    if (choice==1){
        FILE *fpas;
        fpas=fopen("user_pas.txt","w+");
        if (fpas==NULL){
            printf("Error Opening File!");
            return 0;
        }else{
            char fileusername[50], filepassword[50];
            char inputusername[50], inputpassword[50];

            printf("Enter Username: ");
            scanf("%s", inputusername);
            printf("Enter Password: ");
            scanf("%s", inputpassword);

            FILE *file = fopen("user_pas.txt", "r");
            while (fscanf(fpas, "%[^,],%[^,],%s\n", fileusername, filepassword, filename_need) != EOF){
                if (strcmp(inputusername, fileusername) == 0 && strcmp(inputpassword, filepassword) == 0){
                    fclose(file);
                    return 1;
                }
            }
            fclose(file);
            return 0;   
        }
    }

    else if (choice==2){
        char username[50],password[50],suffix[10],gender,fileusername[50], filepassword[50];
        srand(time(NULL));
        int randnum=(rand()%(9999-1000+1))+1000;
        snprintf(suffix, sizeof(suffix), "%d", randnum);
        printf("Random Number Suffix: %s\n", suffix);
        printf("Enter Username: ");
        scanf("%s", username);
        printf("Enter Password: ");
        scanf("%s", password);
        snprintf(filename, sizeof(filename), "%s%s.txt", username, suffix);
        strcpy(filename_need,filename);
        FILE *file = fopen("user_pas.txt","a");
        if (file==NULL){
            printf("Error Opening File!");
            return 0;
        }else{
            fprintf(file,"%s,%s,%s,%c\r\n",username,password,filename);
            fclose(file);
            return 2;
        }
    }else if (choice==3){
        printf("Ended Program!");
        E_xit=1;
        return 3;
    }
    
}

void user_input_new_user(){
    int choice, age, height, num_ex, type_ex, amt;
    char name[30],gender;
    FILE *fptr = fopen(filename, "a");
    if (fptr == NULL) {
        printf("Error opening file for writing.\n");
        exit(1);
    }
    // Asking user who just signed up for details
    printf("Enter your name: ");
    scanf(" %[^\n]s",name);
    printf("Enter your age: ");
    scanf("%d", &age);
    printf("Enter your height (in cm): ");
    scanf("%d", &height);
    printf("Enter Your Gender (M/F): ");
    scanf(" %c",&gender);
    printf("Enter the date (DD-MM-YYYY): ");
    User user;
    scanf("%s", user.date);
    fprintf(fptr, "Name: %s\nAge: %d years\nHeight: %d cm\nGender: %c\n//\n", name, age, height,gender);
    // Asking for Details related to the user's health 
    printf("- - - - - - - - - - For %s - - - - - - - - - -\n", user.date);
    print_exercises();
    printf("Enter Number of Exercises Done: ");
    scanf("%d",&num_ex);
    user.calorie_burn = 0;
    printf("Enter Exercises One By One\n");
    for (int j=0;j<num_ex;j++){
        printf("Enter Exercise Number (1-16): ");
        scanf("%d", &type_ex);
        if (type_ex==7){
            printf("Enter Number of minutes: ");
            scanf("%d",&amt);
            user.calorie_burn += amt * arr_exercies_cal[type_ex-1]; //Type_ex - 1 tells the index value of the calorie burnt by the ex.
        }else{
            printf("Enter Number of Reps/Hours: ");
            scanf("%d",&amt);
            user.calorie_burn+=amt*arr_exercies_cal[type_ex-1];
        }
    }
    printf("Enter Your Weight (in kg): ");
    scanf("%d", &user.weight);
    printf("Enter Your Calorie Intake: ");
    scanf("%d", &user.calorie_intake);
    printf("Enter Number of Glasses of water you drank: ");
    scanf("%d",&user.water_intake);
    float height_m = (float)height / 100;
    float height_sq = height_m * height_m;
    user.BMI = (float)user.weight / height_sq;
    char BMI_status[20];
    if (user.BMI>24.9){
        strcpy(BMI_status,"Overweight");
    }else if (user.BMI<25.00 && user.BMI>18.4){
        strcpy(BMI_status,"Healthy");
    }else if (user.BMI<18.5){
        strcpy(BMI_status,"Underweight");
    }else{
        strcpy(BMI_status,"Obesity");
    }
    fprintf(fptr, "Date: %s \nWeight = %d kg \nCalorie Burnt = %d \nCalorie Intake = %d \nBMI = %.2f [%s] \nWater Intake = %d Glasses\n/\n",user.date, user.weight, user.calorie_burn, user.calorie_intake, user.BMI, BMI_status,user.water_intake);
    fclose(fptr);
    printf("Data saved successfully.\n\n");
}

void user_input_old_user(){
    int num_ex, type_ex, amt,height;
    char name[30];
    FILE *fptr = fopen(filename_need, "a+");
    if (fptr == NULL) {
        printf("Error opening file for writing.\n");
        exit(1);
    }
    // Reading height from the text file for bmi
    FILE *freadptr=fopen(filename_need, "r");
    if (freadptr==NULL) {
        printf("Error opening file for reading.\n");
        exit(1);
    }

    char line[100];
    while (fgets(line, sizeof(line), freadptr)) {
        if (strstr(line, "Height:") != NULL) {
            sscanf(line, "Height: %d", &height);
            break; 
        }
    }
    fclose(freadptr);
    printDatesFromFile(filename_need);
    printf("Enter the date (DD-MM-YYYY): ");
    User user;
    scanf("%s", user.date);
    printf("***** %s *****\n", user.date);
    print_exercises();
    printf("Enter Number of Exercises Done: ");
    scanf("%d",&num_ex);
    user.calorie_burn = 0;
    printf("Enter Exercises One By One\n");
    for (int j=0;j<num_ex;j++){
        printf("Enter Exercise Number (1-16): ");
        scanf("%d", &type_ex);
        if (type_ex==7){
            printf("Enter Number of minutes: ");
            scanf("%d",&amt);
            user.calorie_burn += amt * arr_exercies_cal[type_ex-1]; //Type_ex - 1 tells the index value of the calorie burnt by the ex.
        }else{
            printf("Enter Number of Reps/Hours: ");
            scanf("%d",&amt);
            user.calorie_burn+=amt*arr_exercies_cal[type_ex-1];
        }
    }
    printf("Enter Your Weight (in kg): ");
    scanf("%d", &user.weight);
    printf("Enter Your Calorie Intake: ");
    scanf("%d", &user.calorie_intake);
    printf("Enter Number of Glasses of water you drank: ");
    scanf("%d",&user.water_intake);
    float height_m = (float)height / 100;
    float height_sq = height_m * height_m;
    user.BMI = (float)user.weight / height_sq;
    char BMI_status[20];
    if (user.BMI>24.9){
        strcpy(BMI_status,"Overweight");
    }else if (user.BMI<25.00 && user.BMI>18.4){
        strcpy(BMI_status,"Healthy");
    }else if (user.BMI<18.5){
        strcpy(BMI_status,"Underweight");
    }else{
        strcpy(BMI_status,"Obesity");
    }
    fprintf(fptr, "Date: %s \nWeight = %d kg \nCalorie Burnt = %d \nCalorie Intake = %d \nBMI = %.2f [%s] \nWater Intake = %d Glasses/\n",user.date, user.weight, user.calorie_burn, user.calorie_intake, user.BMI, BMI_status,user.water_intake);
    fclose(fptr);
    printf("Data saved successfully.\n\n");
}

void print_exercises(){
    char *Exercises_p[]={"1. Running/Jogging","2. Cycling","3. Jumping Rope","4. Swimming","5. Pushup","6. Squats","7. Plank","8. Yoga","9. Stretch","10. Burpees","11. High Knees","12. Bosu Ball","13. Jump Squats","14. Tricep Dip","15. Crunches","16. Walking"};
    int a=0;
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _Exercises_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
    while(a<16){
        if (a>0 && a%4==0){
            printf("\n");
            printf("%-20s",Exercises_p[a]);
            a++;
        }else{
            printf("%-20s",Exercises_p[a]);
            a++;
        }
    }
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
}


void printHealthData(char filename_need[]){
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    FILE *file=fopen(filename_need,"r");
    if(file==NULL){
        printf("Error: Could not open file %s\n", filename_need);
        return;
    }
    char line[256];
    int info_record_div=1; // separating userinfo from records (used as a true or false flag)
    printf("User Information:\n");
    while (fgets(line,256,file)!=NULL){
        line[strcspn(line,"\n")]='\0'; //removing new line char
        if (strcmp(line,"//")==0){
            printf("\nDaily Records:\n");
            info_record_div=0;
            continue;
        }
        if (strcmp(line,"/")==0){
            printf("\n");
            continue;
        }
        if (info_record_div){
            printf("  %s\n",line);
        }else{
            printf("  %s\n",line);
        }
    }
    printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    fclose(file);
}

void deleteDataByDate(char filename_need[]){
    printDatesFromFile(filename_need);
    char targetDate[11];
    printf("Enter Target Date (DD-MM-YYYY): ");
    scanf("%s", targetDate);
    FILE *file=fopen(filename_need,"r");
    if (file==NULL){
        printf("Error: Could not open file %s\n",filename_need);
        return;
    }
    FILE *temp_file=fopen("temp_file.txt","w");
    if (temp_file==NULL){
        printf("Error: Could not open file temp_file.txt\n");
        fclose(file);
        return;
    }
    char line[256];
    int isDeleting = 0; 
    while (fgets(line, sizeof(line), file) != NULL){
        if (strncmp(line, "Date:", 5) == 0){
            if (strncmp(line + 6, targetDate, 10) == 0){
                isDeleting = 1;
            }else{
                if (!isDeleting){
                    fputs(line, temp_file);
                }
                if (isDeleting && strncmp(line,"Date:", 5) == 0){
                    isDeleting=0;
                    fputs(line,temp_file); 
                }
            }
        }else{
            // Copy other lines that aren't part of the block we're deleting
            if (!isDeleting){
                fputs(line, temp_file);
            }
        }
    }

    fclose(file);
    fclose(temp_file);

    // Replace the original file with the updated temp file
    remove(filename_need);
    rename("temp_file.txt", filename_need);

    printf("\nData for %s has been deleted successfully.\n\n", targetDate);
}


void printDatesFromFile(char filename[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }
    char line[256];
    printf("Existing Data:\n");
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Date:", 5) == 0) {
            printf("   %s", line + 6);  
        }
    }

    fclose(file);
}
