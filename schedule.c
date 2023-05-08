#include<stdio.h>
#include<stdlib.h>

//we have to unite our coding style

int isleap(int year){
    //return 1 if leapyear
    //return 0 if normal year
    if(year%4000==0){
        return 0;
    }else if(year%400==0){
        return 1;
    }else if(year%100==0){
        return 0;
    }else if(year%4==0){
        return 1;
    }else return 0;
}

int find_weekday(int year,int month,int date){
    int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int days_count=0;
    int d;
    for(int i=2023;i<year;++i){//count days during 20230101 to YYYY0101
        if(isleap(i)==1){
            days_count+=366;
        }else{
            days_count+=365;
        }
    }
    for(int i=1;i<month;++i){//count days during YYYY0101 to YYYYMM01
        if(i==2&&isleap(year)==1){
            days_count+=29;
        }else{
            days_count+=day[i-1];
        }
    }
    days_count+=date;
    days_count-=1;
    d=(days_count)%7;
    return d;
}

void print_calendar(int year,int month,int date){
    system("CLS");
    int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int d=find_weekday(year,month,date);
    printf("  SUN  MON  TUE  WED  TUE  FRI  SAT \n");
    printf("+----+----+----+----+----+----+----+\n");
    printf("|");
    for(int i=0;i<d;++i){
        printf("    |");
    }
    for(int i=1;i<=day[month-1];++i){
        d=find_weekday(year,month,i);
        printf(" %2d |",i);
        if(d==6){
            printf("\n");
            printf("|....|....|....|....|....|....|....|\n");
            printf("+----+----+----+----+----+----+----+\n");
            printf("|");
        }
    }
    if(month==2&&isleap(year)==1){
        printf(" %2d  \n");//what is "%d" here
    }else if(d==6){
        printf("\n");
    }else{
        printf("\n");
        printf("|....|....|....|....|....|....|....|\n");
        printf("+----+----+----+----+----+----+----+\n");
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
