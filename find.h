#include "basic.h"

Event_date *find_current_date(int start_month, int start_date);

int find_weekday(int year,int month,int date);

int search_if_the_day_have_activity(int month, int date);

int search_if_the_time_have_activity(struct event_content *list,int start_time, int end_time, int command);
    
void search_all_day_free_time(Event_date *ptr,int month, int date);

void search_scheduled_time_through_activity(Event_date *ptr, char *activity_name,int month,int date);

Event_date *add_to_list(Event_date *list,int st_mon,int st_da,int str_t,int end_t,char* ac,char *pl,char *ot);

void search_if_have_activity_on_the_date(Event_date *date_head, int month, int date, int time);

Event_content *find_day(Event_date *ptr,int month,int date);

Event_content *find_today(Event_date *date_head,int month,int date);