#include "basic.h"
#include "print.h"

void print_event_date_list(){
  /* print start point for testing */
    Event_date *list = date_head;
    while(list != NULL){
        printf(":: %d %d\n",list->month, list->date);
        list = list -> next;
    }
}

void print_event_content_list(Event_content *list){
    Event_content *tmp = list;
    /* print time for testing */
    while(tmp != NULL){
        printf("%s: %d %d\n", tmp -> name, tmp -> start_time, tmp -> end_time);
        tmp = tmp -> next;
    }
}

void print_calendar(int year,int month,int date){
    int day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int leap[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    //system("CLS");
    Event_date *cur = find_current_date(month,date);
    printf("%s         %4d         %2d         \n",WHITE,year,month);
    printf("%s  SUN  MON  TUE  WED  TUE  FRI  SAT \n",WHITE);
    printf("%s+----+----+----+----+----+----+----+\n",BLUE);
    int d = find_weekday(year,month,1);
    printf("%s|",BLUE);
    int cur_date = 1;
    int cur_day = d;
    if(month ==2 && isleap(year)){
        while((cur_date - cur_day) <= leap[month-1] && cur_day <= 6){
            for(int i = cur_date - cur_day ; i < cur_date - cur_day + 7  ; ++i){
                if(i <= 0){
                    printf("%s    |",BLUE);
                }else if(i > leap[month-1]){
                    printf("%s    |",BLUE);
                }else{
                    printf("%s %2d ",YELLOW,i);
                    printf("%s|",BLUE);
                }
            }
            printf("%s\n|",BLUE);
            for(int i = cur_date - cur_day ; i < cur_date - cur_day + 7  ; ++i){
                if(i <= 0){
                    printf("%s    |",BLUE);
                    continue;
                }else{
                    if(cur == NULL){
                        printf("%s    |",BLUE);
                        continue;
                    }
                    if(i > leap[month-1]){
                        printf("%s    |",BLUE);
                        continue;
                    }
                    switch (cur -> event_num){
                    case 0:
                        printf("%s    |",BLUE);
                        break;
                    case 1:
                        printf("%s.   ",YELLOW);
                        printf("%s|",BLUE);
                        break;
                    case 2:
                        printf("%s..  ",YELLOW);
                        printf("%s|",BLUE);
                        break;
                    case 3:
                        printf("%s... ",YELLOW);
                        printf("%s|",BLUE);
                        break;
                    default:
                        printf("%s....",YELLOW);
                        printf("%s|",BLUE);
                        break;
                    }
                }
                cur = cur -> next;
            }
            printf("\n");
            printf("%s+----+----+----+----+----+----+----+\n",BLUE);
            if((cur_date - cur_day + 7) <= leap[month-1]){
                printf("|");
            }
            cur_date = cur_date + 7;
        }
    }else{
        while((cur_date - cur_day) <= day[month-1] && cur_day <= 6){
            for(int i = cur_date - cur_day ; i < cur_date - cur_day + 7  ; ++i){
                if(i <= 0){
                    printf("%s    |",BLUE);
                }else if(i > day[month-1]){
                    printf("%s    |",BLUE);
                }else{
                    printf("%s %2d ",YELLOW,i);
                    printf("%s|",BLUE);
                }
            }
            printf("%s\n|",BLUE);
            for(int i = cur_date - cur_day ; i < cur_date - cur_day + 7  ; ++i){
                if(i <= 0){
                    printf("%s    |",BLUE);
                    continue;
                }else{
                    if(cur == NULL){
                        printf("%s    |",BLUE);
                        continue;
                    }
                    if(i > day[month-1]){
                        printf("%s    |",BLUE);
                        continue;
                    }
                    switch (cur -> event_num){
                    case 0:
                        printf("%s    |",BLUE);
                        break;
                    case 1:
                        printf("%s.   ",YELLOW);
                        printf("%s|",BLUE);
                        break;
                    case 2:
                        printf("%s..  ",YELLOW);
                        printf("%s|",BLUE);
                        break;
                    case 3:
                        printf("%s... ",YELLOW);
                        printf("%s|",BLUE);
                        break;
                    default:
                        printf("%s....",YELLOW);
                        printf("%s|",BLUE);
                        break;
                    }
                }
                cur = cur -> next;
            }
            printf("\n");
            printf("%s+----+----+----+----+----+----+----+\n",BLUE);
            if((cur_date - cur_day + 7) <= day[month-1]){
                printf("|");
            }
            cur_date = cur_date + 7;
        }
    }
    printf("%s",WHITE);
    return;
}

//show one week of the calendar, and also the number of the event of the day on the calendar.
void print_week(int year,int month,int date){
    int day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int leap[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    Event_date *cur = find_current_date(month,date); //find the current day
    printf("%s         %4d         %2d         \n",WHITE,year,month);
    printf("  SUN  MON  TUE  WED  TUE  FRI  SAT \n");
    printf("%s+----+----+----+----+----+----+----+\n",BLUE);
    int d = find_weekday(year,month,date);
    printf("|");
    int A[7]={0};
    if(isleap(year)){
        date = date - d;
        for(int i = 0;i < 7; ++i){
            if(date <= 0){//go to last month
                if(month == 1){//go to december
                    date = date + leap[11];
                    month = 12;
                }else{
                    date = date + leap[month-2];
                    month--;
                }
            }else if(date > leap[month-1]){
                if(month == 12){//go to december
                    date = date - leap[11];
                    month = 1;
                }else{
                    date = date - leap[month-1];
                    month++;
                }
            }
            printf("%s %2d ",YELLOW,date);
            printf("%s|",BLUE);
            cur = find_current_date(month,date);
            if(cur == NULL){
                A[i] = 0;
            }else{
                A[i] = cur -> event_num;
            }
            date++;
        }
    }else{
        date = date - d;
        for(int i = 0;i < 7; ++i){
            if(date <= 0){//go to last month
                if(month == 1){//go to december
                    date = date + day[11];
                    month = 12;
                }else{
                    date = date + day[month-2];
                    month--;
                }
            }else if(date > day[month-1]){
                if(month == 12){//go to december
                    date = date - leap[11];
                    month = 1;
                }else{
                    date = date - day[month-1];
                    month++;
                }
            }
            printf("%s %2d ",YELLOW,date);
            printf("%s|",BLUE);
            cur = find_current_date(month,date);
            if(cur == NULL){
                A[i] = 0;
            }else{
                A[i] = cur -> event_num;
            }
            date++;
        }
    }
    printf("%s\n|",BLUE);
    for(int i = 0;i < 7; ++i){
        switch (A[i]){
            case 0:
                printf("%s    |",BLUE);
                break;
            case 1:
                printf("%s.   ",YELLOW);
                printf("%s|",BLUE);
                break;
            case 2:
                printf("%s..  ",YELLOW);
                printf("%s|",BLUE);
                break;
            case 3:
                printf("%s... ",YELLOW);
                printf("%s|",BLUE);
                break;
            default:
                printf("%s....",YELLOW);
                printf("%s|",BLUE);
                break;
        }
    }
    printf("\n");
    printf("%s+----+----+----+----+----+----+----+\n",BLUE);
    printf("%s",WHITE);
    return;
}

//show the date schedule and show the event name at the hour.
void print_date(int year,int month,int date){
    Event_date *cur = find_current_date(month,date);
    printf("   %4d   %2d   %2d   \n",year,month,date);
    Event_content *cur_event = cur->content;
    int A[24]={0};
    if(cur_event == NULL){
        for(int i = 0;i <= 23; ++i){
            printf("%s%2d------------------\n",WHITE,i);
            printf("                    \n");
        }
        printf("%s24------------------\n",WHITE);
        return;
    }
    while(cur_event != NULL){
        for(int i = cur_event->start_time ; i <= cur_event->end_time ; ++i){
            A[i]=1;
        }
        cur_event = cur_event->next;
    }
    cur_event = cur->content;
    for(int i = 0;i <= 23; ++i){
        printf("%s%2d------------------\n",WHITE,i);
        if(A[i]==0){
            printf("                    \n");
        }else{
            printf("%s.%-18s*\n",YELLOW,cur_event->name);
            if(i == cur_event->end_time){
                cur_event = cur_event->next;
            }
        }
    }
    printf("%s24------------------\n",WHITE);
    return;
}