#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include "basic.h"
#include "find.h"

Event_date *find_current_date(int start_month, int start_date){
    Event_date *tmp = date_head;
    while(tmp != NULL){
        if((tmp->month == start_month) && (tmp->date == start_date)) return tmp;
        else tmp = tmp->next;
    }
    if(tmp == NULL) return NULL;
    
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

int search_if_the_day_have_activity(int month, int date){
    Event_date *tmp = date_head;
    while( tmp != NULL){
        if((tmp->month == month) && (tmp->date == date)) return 1;
        else tmp = tmp->next;
    }
    if(tmp == NULL){
        return 0;
    }
}

int search_if_the_time_have_activity(struct event_content *list,int start_time, int end_time, int command){ //search if have things to do at the time
    /* 
    The function will be used in two condition by the different value of the variable "command".
    "0" is only used to check if the period of time is free
    "1" is to check and print out for user to know
    */
    while(list != NULL){
        int tmp_act = 0;
        if((list->end_time >= start_time) && (list->end_time <= end_time)) tmp_act = 1;
        if((list->start_time >= start_time) && (list->start_time <= end_time)) tmp_act = 1;

        if(tmp_act == 1){ //if the time has already assigned schedule
            if(command == 1) printf("You have %s from %d to %d",list->name, list->start_time, list->end_time);            //print the activity name
            return 1;
        }
        else{
            list=list->next;                                    //if not find yet, go on the next
        }
    }
    if(list == NULL){
        if(command == 1) printf("You are free at the time\n");          // if not find an activity for the whole list
        return 0;
    }
}

void search_all_day_free_time(Event_date *ptr,int month, int date){                //consider ptr sorted
    int free_time_str = 0;
    struct event_content *tmp = find_today(ptr,month,date);
    while((tmp != NULL)){
        if(free_time_str < (tmp->start_time)){                     //if free time is smaller than the first activity's star time, it is free    
            printf("You have free time from %d to %d.\n"
            ,free_time_str, tmp->start_time);                     //have the free time till the closest activity start
        }
        free_time_str = tmp->end_time;                            //set the free time start count point at the end of the activity
        tmp = tmp->next;                                          //go to the next closest activity
    }
    if(free_time_str < A_DAY_HOUR){
        printf("You have free time from %d to %d.\n", free_time_str, A_DAY_HOUR);                                  //if no more activity, it is free till 24
    }       
}

void search_scheduled_time_through_activity(Event_date *ptr, char *activity_name,int month,int date){
    /*
    This function is to look for the time when the activity takes place.
    1. look through the list and find the activity
        (1) if it finds, it will print out the time the activity starts and ends.
        (2) if not, it will print no-message.
    */
    Event_content *list=find_today(ptr,month,date);
    bool have_the_activity_or_not = 0;
    while(list != NULL){
        if(strcmp(list->name, activity_name) == 0){                 //if there's this activity in schedule
            printf("You have the activity from %d to %d", list->start_time,list->end_time); //print the activity name and time
            have_the_activity_or_not = 1;
        }
        list=list->next;                                        //if not find yet, go on the next
    }
    if(!have_the_activity_or_not){
        printf("You don't have activity today\n");              // if not find an activity for the whole list
    }
}

Event_date *add_to_list(Event_date *list,int st_mon,int st_da,int str_t,int end_t,char* ac,char *pl,char *ot){
    Event_date *tmp;
    tmp=malloc(sizeof(Event_date));
    strcpy(tmp->content->name,ac);
    tmp->month=st_mon;
    tmp->date=st_da;
    tmp->content->start_time=str_t;
    tmp->content->end_time=end_t;
    strcpy(tmp->content->place,pl);
    strcpy(tmp->content->others,ot);
    tmp->next=list;
    return tmp;
}

void search_if_have_activity_on_the_date(Event_date *date_head, int month, int date, int time){
    while(date_head!=NULL){
        if(date_head->month==month&&date_head->date==date){
            break;
        }
        date_head=date_head->next;
    }
    if(date_head==NULL){
        printf("You don't have activity at the time\n");
    }else{
        Event_content *tmp;
        tmp=date_head->content;
        while(tmp!=NULL){
            if(tmp->start_time==time){
                printf("You have the activity %s at the time\n",tmp->name);
                break;
            }
            tmp=tmp->next;
        }
        if(tmp==NULL){
            printf("You don't have activity at the time\n");
        }
    }
}

Event_content *find_day(Event_date *ptr,int month,int date){
    Event_content *cur=NULL;
    while(ptr->next!=NULL){       //因為從txt讀出來的東西不知道為啥在NULL前都會有一次是亂碼，所以長這樣
        if(ptr->month==month&&ptr->date==date){
            Event_content *tmp_content=NULL;
            tmp_content->name=ptr->content->name;
            tmp_content->start_time=ptr->content->start_time;
            tmp_content->end_time=ptr->content->end_time;
            tmp_content->place=ptr->content->place;
            tmp_content->others=ptr->content->others;
            tmp_content->next=cur;
            cur=tmp_content;
            free(tmp_content);
        }
        ptr=ptr->next;
    }
    return cur;
}

Event_content *find_today(Event_date *date_head,int month,int date){
    while(date_head!=NULL){
        if(date_head->month==month&&date_head->date==date){
            break;
        }
        date_head=date_head->next;
    }
    return (date_head->content);
}