// Track personal health like weight,height,age,exercise, diet.
#include<stdio.h>
void user_input(void);
void user_info_print(void);
typedef struct{
    int day;
    int weight;
    int calorie_burn;
    int calorie_intake;
}User;
User days[30];
char name[30];
int age;
int height;
int global_choice;
int main(){
    user_input();
    user_info_print();
    return 0;
}
void user_input(){
    int choice;
    FILE *fptr;
    fptr=fopen("user_info.txt","w");
    printf("Enter User Name: ");
    scanf(" %s",&name);
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
        printf("Enter your weight: ");
        scanf(" %d",&days[i].weight);
        printf("Enter your calories burnt: ");
        scanf(" %d",&days[i].calorie_burn);
        printf("Enter your calorie intake: ");
        scanf(" %d",&days[i].calorie_intake);
        fprintf(fptr,"Day%d : Weight=%d - Calorie Burnt=%d - Calorie Intake=%d \n",days[i].day,days[i].weight,days[i].calorie_burn,days[i].calorie_intake);
    }
    fclose(fptr);
    free(fptr);
}
void user_info_print(){
    for(int i=0;i<global_choice;i++){
        printf("Day%d : Weight=%d - Calorie Burnt=%d - Calorie Intake=%d \n",days[i].day,days[i].weight,days[i].calorie_burn,days[i].calorie_intake);
    }
}