#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//version 1
//we have to unite our coding style
//there is some problems about print event amount

typedef struct schedule{
    struct schedule *next_day;
    int num;
};

int isleap(int year){
    //return 1 if leapyear
    //return 0 if normal year
    if(year % 4000 == 0){
        return 0;
    }else if(year % 400 == 0){
        return 1;
    }else if(year % 100 == 0){
        return 0;
    }else if(year % 4 == 0){
        return 1;
    }else return 0;
}

int find_weekday(int year,int month,int date){//return the weekday
    int day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int days_count = 0;
    int d;
    for(int i = 2023 ; i < year ; ++i){//count days during 20230101 to YYYY0101
        if(isleap(i) == 1){
            days_count += 366;
        }else{
            days_count += 365;
        }
    }
    for(int i = 1 ; i < month ; ++i){//count days during YYYY0101 to YYYYMM01
        if(i == 2 && isleap(year) == 1){
            days_count += 29;
        }else{
            days_count += day[i - 1];
        }
    }
    days_count += date;
    days_count -= 1;
    d = (days_count) % 7;
    return d;
}

void print_calendar(int year,int month,int date){
    system("CLS");                                          //clear the terminal
    int day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    struct schedule *first =NULL, *cur ,*last=NULL;
    int d = find_weekday(year,month,1);                     //d means the weekday of the firstday of the month
    printf("  SUN  MON  TUE  WED  TUE  FRI  SAT \n");
    printf("+----+----+----+----+----+----+----+\n");
    printf("|");
    for(int i = 0 ; i < d ; ++i){
        printf("    |");
    }
    for(int i = 1 ; i <= day[month - 1] ; ++i){
        first=NULL;
        last=NULL;
        for(int j = 0 ; j < 7 ; ++j){
            struct schedule *newnode = (struct schedule*)malloc(sizeof(struct schedule));
            newnode->num=j;
            if(first==NULL){
                first=newnode;
                last=newnode;
                newnode->next_day=NULL;
            }else{
                last->next_day=newnode;
                newnode->next_day=NULL;
                last=newnode;
            }
        }
        d = find_weekday(year,month,i);
        printf(" %2d |",i);
        if(i == day[month - 1]){
            for(int j = d ; j < 6 ; ++j){
                printf("    |");
            }
        }
        if(d == 6){
            printf("\n|");
            cur = first;
            for(int j = 0 ; j < 7 ; ++j){
                if(cur->num == 0){
                    printf("    |");
                }else if(cur->num == 1){
                    printf(".   |");
                }else if(cur->num == 2){
                    printf("..  |");
                }else if(cur->num == 3){
                    printf("... |");
                }else{
                    printf("....|");
                }
                cur = cur->next_day;
            }
            printf("\n+----+----+----+----+----+----+----+\n");
            if(i != day[month - 1]){
                printf("|");
            }
        }
        free(first);
    }
    if(month == 2 && isleap(year) == 1){
        printf(" %2d  \n",29); //what is "%d" here
    }else if(d == 6){
        printf("\n");
    }else{
        printf("\n|");
        cur = first;
        for(int j = 0 ; j < 7 ; ++j){
            if(cur->num == 0){
                printf("    |");
            }else if(cur->num == 1){
                printf(".   |");
            }else if(cur->num == 2){
                printf("..  |");
            }else if(cur->num == 3){
                printf("... |");
            }else{
                printf("....|");
            }
            cur = cur->next_day;
        }
        printf("\n+----+----+----+----+----+----+----+\n");
    }
    return;
}

int main(){
    int year,month,date;
    //can add some word to make the interface more user-friendly
    printf("%s\n", "please enter when do you want to start your calender: ");
    printf("%s\n","(year month date)");
   
    scanf("%d %d %d",&year,&month,&date);
    print_calendar(year,month,date);
    return 0;
}

//there is some problems at output