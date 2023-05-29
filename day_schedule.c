#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//1. input date data and schedule data
//2. clear the terminal
//3. show the day schedule


typedef struct schedule{
    int year;
    int month;
    int date;
    int hour;
    char name[50];
};

struct schedule *my_schedule=(struct schedule*)malloc(sizeof(struct schedule));
//全域中不可以用malloc()！！！

void show_schedule(){
    system("CLS");
    printf("   %4d   %2d   %2d   \n",my_schedule->year,my_schedule->month,my_schedule->date);
    for(int i = 0;i <= 23; ++i){
        printf("%2d------------------\n",i);
        if(my_schedule->hour != i){
            printf("                    \n");
        }else{
            printf(".%-18s*\n",my_schedule->name);
        }
    }
    printf("24------------------\n");
    return;
}

/*main function                    */
/*input year, month, and date data */
/*show the day schedule in terminal*/
int main(){
    int year;
    int month;
    int date;
    int hour;
    char names[50];
    scanf("%d %d %d %d ",&year,&month,&date,&hour);
    my_schedule ->year = year;
    my_schedule ->month = month;
    my_schedule ->date = date;
    my_schedule ->hour = hour;
    gets(names);
    strcpy(my_schedule->name,names);
    show_schedule();
    return 0;
}
