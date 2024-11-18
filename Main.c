// Track personal health like weight,height,age,exercise, diet.
#include<stdio.h>
void user_input(void);
typedef struct{
    int weight;
    int height;
    int calorie_burn;
    int calorie_intake;
}User;
char name[30];
int age;
int main(){

    return 0;
}
void user_input(){
    User days[30];
    printf("Enter User Name: ");
    scanf(" %s",&name);
    printf("Enter your age: ");
    scanf(" %d",&age);
    for (int i=0;i<30;i++){
        printf("Enter your height: ");
        scanf(" %d",&days[i].height);
        printf("Enter your weight: ");
        scanf(" %d",&days[i].weight);
        printf("Enter your calories burnt: ");
        scanf(" %d",&days[i].calorie_burn);
        printf("Enter your calorie intake: ");
        scanf(" %d",&days[i].calorie_intake);
    }
}