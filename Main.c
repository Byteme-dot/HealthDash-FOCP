// Track personal health like weight,height,age,exercise, diet.
#include<stdio.h>
void user_input(void);
void user_info_print(void);


// STRUCTURE
typedef struct{
    int day;
    int weight;
    int calorie_burn;
    int calorie_intake;
    float BMI;
}User;

//Global Declaration
User days[30];
char name[30];
int age;
int height;
int global_choice;

//Exercises Global Decl.
// printf("\nRunning/Jogging \nCycling \nJumping Rope \nSwimming \nPushup \nSquats \nPlank \nYpga \nStretch \nBurpees \nHigh Knees \nSingle Leg Stand \nBosu Ball \nJump Squats \nTricep Dip \nCruches \nWalking\n");
int arr_exercies_cal[17]={600,500,700,400,1,1,4,300,150,600,500,200,400,1,1,1,300};
int Running_Jogging=600;
int Cycling=500;
int Jumping_Rope=700;
int Swimming=400;
float Push_Up=0.5;
float Squats=0.4;
int plank=4;
int yoga=300;
int stretch=150;
int Burpees=600;
int high_knees=500;
int single_leg_stand=200;
int bosu_ball=400;
int jump_Squats=1;
int tricep_dip=1;
float crunches=0.5;
int walking=300;

//Main Function
int main(){
    user_input();
    user_info_print();
    return 0;
}

// Details Input 
void user_input(){
    int choice;
    FILE *fptr;
    fptr=fopen("user_info.txt","w");
    printf("Enter User Name: ");
    scanf("%[^\n]",&name);
    printf("Enter your age: ");
    scanf(" %d",&age);
    printf("Enter your height: ");
    scanf(" %d",&height);
    printf("Enter no of days to input data: ");
    scanf("%d",&choice);
    global_choice=choice;
    fprintf(fptr,"Name: %s \nAge=%dY \nHeight=%dcm\n",name,age,height);
    for (int i=0;i<choice;i++){
        printf("*****DAY %d*****\n",i+1);
        days[i].day=i+1;
        int num_ex=0;
        printf("\n1.Running/Jogging    2.Cycling \n3.Jumping Rope    4.Swimming \n5.Pushup    6.Squats \n7.Plank    8.Ypga \n9.Stretch    10.Burpees \n11.High Knees    12.Single Leg Stand \n13.Bosu Ball    14.Jump Squats \n15.Tricep Dip    16.Cruches \n17.Walking\n");
        printf("Enter Number of Exercises Done: ");
        scanf("%d",&num_ex);
        int type_ex;
        int amt;
        printf("Enter Exercises One By One\n");
        days[i].calorie_burn=0;
        for (int j=0;j<num_ex;j++){
            printf("Enter Exercise Number: ");
            scanf("%d",&type_ex);
            if (type_ex==7){
                printf("Enter No of minutes: ");
                scanf("%d",&amt);
                days[i].calorie_burn+=amt*(arr_exercies_cal[type_ex-1]);
            }else{
                printf("Enter No of Reps/Hours: ");
                scanf("%d",&amt);
                days[i].calorie_burn+=amt*(arr_exercies_cal[type_ex-1]);
            }
        }
        printf("Enter your weight: ");
        scanf(" %d",&days[i].weight);
        printf("Enter your calorie intake: ");
        scanf(" %d",&days[i].calorie_intake);
        float height_m=(float)height/100;
        float height_sq=height_m*height_m;
        days[i].BMI=days[i].weight/height_sq;
        fprintf(fptr,"Day%d : Weight=%d - Calorie Burnt=%d - Calorie Intake=%d \n",days[i].day,days[i].weight,days[i].calorie_burn,days[i].calorie_intake,days[i].BMI);
    }
    fclose(fptr);
}

// Detail Printer
void user_info_print(){
    for(int i=0;i<global_choice;i++){
        printf("Day%d : Weight=%d - Calorie Burnt=%d - Calorie Intake=%d \n",days[i].day,days[i].weight,days[i].calorie_burn,days[i].calorie_intake,days[i].BMI);
    }
}