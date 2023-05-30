#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct event_content{
    char *name; //name of event
    int start_time; //unit: hour
    int end_time; //unit: hour
    int remainder; //0: the moment; 1: one hour ago; -1: no remainder
    //maybe add notes function...
    struct event_content *next; //point to next node
}Event_content;

typedef struct event_date{
    int start_month;
    int end_month;
    int start_date;
    int end_date;
    int event_num;
    struct event_date *next; //point to next node
    struct event_content *content; //point to event content(s)
}Event_date;

Event_date *date_head = NULL;

Event_date *event_date_insert(int start_month, int end_month, int start_date, int end_date){
    /* allocate node */
    Event_date *new_event_date = malloc(sizeof(struct event_date));
    
    if(new_event_date == NULL){
        printf("Error: malloc failed in event_date_insert\n");
        exit(3);//要不要用return 給使用者機會再輸一次
    }
 
    /* put in the data */
    new_event_date -> start_month = start_month;
    new_event_date -> end_month = end_month;
    new_event_date -> start_date = start_date;
    new_event_date -> end_date = end_date;
    new_event_date -> event_num = 0;
    new_event_date -> next = NULL;
    new_event_date -> content = NULL;
 
    /* If linked List is empty */
    if(date_head == NULL){
        date_head = new_event_date;
        return date_head;
    }
 
    Event_date *date_curr = date_head;
    Event_date *date_prev = NULL;

    while(date_curr != NULL){
        if(date_prev == NULL){
            new_event_date->next = date_curr;
            date_head = new_event_date;
            return date_head;
        }

        if(date_curr->start_month < new_event_date->start_month){
            new_event_date->next = date_curr;
            date_prev->next = new_event_date;
            return date_head;
        }
            
        else if(date_curr->start_month == new_event_date->start_month)
            if(date_curr->start_date < new_event_date->start_date){
                new_event_date->next = date_curr;
                date_prev->next = new_event_date;
                return date_head;
        }
                
        date_prev = date_curr;
        date_curr = date_curr->next;
    }
    if(date_curr == NULL){
        date_prev->next = new_event_date;
        return date_head;
    }
}

void event_content_insert(int start_month, int end_month, int start_date, int end_date, char *name, int start_time, int end_time, int remainder){
    /* allocate node */
    Event_content *new_event_content = malloc(sizeof(struct event_content));
    /*
    要搜尋該日期是否存在，若不存在則插入日期
    再插入時間
    然後要檢查該時段是否已經有事了，若有事則回傳？
    */
    Event_content *content_head = NULL;
    if(content_head = );
    else content_head = event_date_insert(start_month, end_month, start_date, end_date)->content;
    Event_content *curr = content_head;
    Event_content *prev = NULL;
    //Event_content *curr = content_head;//used to locate the needed node in linked list


    
    if(new_event_content == NULL){
        printf("Error: malloc failed in event_content_insert\n");
        exit(1);
    }

    /* put in the data */
    new_event_content -> name = name;
    new_event_content -> start_time = start_time;
    new_event_content -> end_time = end_time;
    new_event_content -> remainder = remainder;
    new_event_content -> next = NULL;
 
    /* If linked List is empty */
    if(content_head == NULL){
        content_head = new_event_content;
        return content_head;
    }
 
    /* locate the last node */
    
    while(curr != NULL){
        if(prev == NULL){
            new_event_content->next = curr;
            content_head = new_event_content;
            return content_head;
        }
        else if(curr->start_time < new_event_content->start_time){
            new_event_content->next = curr;
            prev->next = new_event_content;  
        }       
        prev = curr;
        curr = curr->next;
    }
}   

void print_list1(Event_date *list){
  /* print start point for testing */
    while(list != NULL){
        printf(":: %d %d\n",list -> start_month, list -> start_date);
        list = list -> next;
    }
}

void print_list2(Event_content *list){
    /* print time for testing */
    while(list != NULL){
        printf("%s: %d %d\n", list -> name, list -> start_time, list -> end_time);
        list = list -> next;
    }
}

void remove_enter(char *sentence){
    /* deal with '\0' */
    char *str = sentence;
    for(; *str && *str != '\n'; str++);
    *str = '\0';
}

int isleap(int year){ //return 1 if leapyear; return 0 if normal year
    if(year % 4000 == 0)
        return 0;
    else if(year % 400 == 0)
        return 1;
    else if(year % 100 == 0)
        return 0;
    else if(year % 4 == 0)
        return 1;
    else return 0;
}

int find_weekday(int year,int month,int date){
    int day[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days_count=0;
    int d;
    for(int i = 2023; i < year; ++i){//count days during 20230101 to YYYY0101
        if(isleap(i)==1){
            days_count+=366;
        }else{
            days_count+=365;
        }
    }
    for(int i = 1; i < month; ++i){//count days during YYYY0101 to YYYYMM01
        if((i == 2) && (isleap(year) == 1)){
            days_count += 29;
        }else{
            days_count += day[i - 1];
        }
    }
    days_count += date;
    days_count -= 1;
    d=(days_count) % 7;
    return d;
}

void print_calendar(int year,int month,int date){
    //system("CLS");
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


int main() {
    char user_name[50];
    int action;
    
    printf("Hello master, what should I call you.: ");
    scanf("%s", user_name);

    int year,month,date;
    printf("Hello %s, please enter when do you want to start your calender(e.g. 2025 05 16): ");
    scanf("%d %d %d",&year,&month,&date);
    print_calendar(year,month,date);

    printf("Next, %s ,What kind of action do you want to do\n", user_name);
    printf(" [1] enter a new event [2] search for an event [3] terminate this day [4] terminate this month.: ");
    scanf("%d", &action);

    if(action == 1){
        printf("Yeah, %s, let's start for buliding an event.\n");
        char name[30];
        int start_month, end_month, start_date, end_date;
        printf("Please enter your event's name(limited in 28 words): ");
        scanf("%29s", name);
        printf("Please enter the start month and date of your event(use spaces to seperate the two numbers, e.g.[10 31]): ");
        scanf("%d %d", &start_month, &start_date);
        printf("Please enter the end month and date of your event(use spaces to seperate the two numbers, e.g.[12 25]: ");
        scanf("%d %d", &end_month, &end_date);
        printf("\n");
        
        int start_time, end_time;
        bool is_whole_day;
        char temp;
        int remainder;//???????????????
        printf("Is it a whole day function(Y or N): ");
        scanf(" %c", &temp);
        if(temp == 'Y'){
            start_time = 0000;
            end_time = 2400;
        }
        else if(temp == 'N'){
            printf("What is the start time of the event(using 24-hour clock, e.g.1500): ");
            scanf("%d", &start_time);
            printf("What is the end time of the event(using 24-hour clock, e.g.1500): ");
            scanf("%d", &end_time);
        }
        else printf("Error in setting event's lasting time\n");
        event_content_insert(start_month, end_month, start_date, end_date, name, start_time, end_time, remainder);   
    }
    else if(action == 2){

    }
    else if(action == 3){

    }
    else if(action == 4){

    }

}