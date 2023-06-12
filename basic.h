#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct event_date{
    int month;
    int date;
    int event_num;
    struct event_date *next; //point to next node
    struct event_content *content; //point to event content(s)
}Event_date;

typedef struct event_content{
    char *name; //name of event
    char *place;
    char *others;
    int start_time; //unit: hour
    int end_time; //unit: hour
    struct event_content *next; //point to next node
}Event_content;

Event_date *date_head = NULL;

Event_date *annual_activity;

Event_date *event_date_insert(int month, int date, int command);

void event_content_insert(int month, int date, char *name, int start_time, int end_time, char* place, char* others);

Event_date *delete_date(int month, int date);

Event_content *delete_content(Event_date *cur_date, char *name);

void remove_enter(char *sentence);

int isleap(int year);

int to_new_day(int curr_date);

int to_new_month(int date);

void game_1a2b(int *points_of_master);

void long_term_event(char selection, int month, int date, int start_time, int end_time,  char *name, char *place, char* others);

int check_if_already_have_event(Event_date *date_head, int month, int date, int start_time,int end_time);

int search_if_the_time_have_activity(struct event_content *list,int start_time, int end_time, int command);

char ask_event_length();

void daily_event(int start_month,int end_month,int start_date,int end_date,char* name,int start_time,int end_time,char* place,char* others);

int get_content_from_file(Event_date *ptr);

int write_content_on_file(Event_date *ptr);
