#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct event_content{
    char *name; //name of event
    int start_time; //unit: hour
    int end_time; //unit: hour
    int remainder; //0: the moment,
                   //1: one hour ago
                   //-1: no remainder
    //maybe add notes function...
    struct event_content *next; //point to next node
};

struct event_date{
    int start_month;
    int end_month;
    int start_date;
    int end_date;
    int event_num;
    struct event_date *next; //point to next node
    struct event_content *sub; //point to event content(s)
};

struct event_date *event_date_insert(struct event_date *event_date_list, int start_month, int end_month, int start_date, int end_date)
{
    /* allocate node */
    struct event_date *new_event_date;
    struct event_content *new_event_content;
    struct event_date *prev = NULL;
    new_event_date = malloc(sizeof(struct event_date));
    new_event_content = malloc(sizeof(struct event_content));
    if(new_event_date == NULL)
    {
        printf("Error: malloc failed in event_date_insert\n");
        exit(1);
    }
    if(new_event_content == NULL)
    {
        printf("Error: malloc failed in event_date_insert\n");
        exit(1);
    }
 
    struct event_date *cur = event_date_list; //used to locate the needed node in linked list
 
    /* put in the data */
    new_event_date -> start_month = start_month;
    new_event_date -> end_month = end_month;
    new_event_date -> start_date = start_date;
    new_event_date -> end_date = end_date;
    new_event_date -> event_num = 0;
    new_event_date -> next = NULL;
    new_event_date -> sub = NULL;
 
    /* If linked List is empty */
    if (event_date_list == NULL) {
        event_date_list = new_event_date;
        return event_date_list;
    }
 
    /* insert the node */
    while(1){
        if((cur -> start_month == new_event_date -> start_month && cur -> start_date > new_event_date -> start_date) || (cur -> start_month > new_event_date -> start_month)){
            if(prev == NULL){
                new_event_date -> next = cur;
                event_date_list = new_event_date;
                break;
            }
            prev -> next = new_event_date;
            new_event_date -> next = cur;
            break;
        }
        if(cur -> next == NULL){
            cur -> next = new_event_date;
            break;
        }
        prev = cur;
        cur = cur -> next;
    }
    /*
    while(cur -> next != NULL)
        cur = cur -> next;
    */
 
    
    /* insert the last node */
    /*
    cur -> next = new_event_date;
    */
    return event_date_list;
}

struct event_content *event_content_insert(struct event_content *event_content_list, char *name, int start_time, int end_time, int remainder)
{
    /* allocate node */
    struct event_content *new_event_content;
    struct event_content *prev = NULL;
    new_event_content = malloc(sizeof(struct event_content));
    if(new_event_content == NULL)
    {
        printf("Error: malloc failed in event_content_insert\n");
        exit(1);
    }

    struct event_content *cur = event_content_list; //used to locate the needed node in linked list

    /* put in the data */
    new_event_content -> name = name;
    new_event_content -> start_time = start_time;
    new_event_content -> end_time = end_time;
    new_event_content -> remainder = remainder;
    new_event_content -> next = NULL;
 
    /* If linked List is empty */
    if (event_content_list == NULL) {
        event_content_list = new_event_content;
        return event_content_list;
    }
 
    /* locate the last node */
    while(1){
        if(cur -> start_time > new_event_content -> start_time){
            if(prev == NULL){
                new_event_content -> next = cur;
                event_content_list = new_event_content;
                break;
            }
            prev -> next = new_event_content;
            new_event_content -> next = cur;
            break;
        }
        if(cur -> next == NULL){
            cur -> next = new_event_content;
            break;
        }
        prev = cur;
        cur = cur -> next;
    }
 
    /* insert the last node */
    return event_content_list;
}

void print_list1(struct event_date *list)
{
  /* print start point for testing */
    while(list != NULL) {
        printf(":: %d %d\n",list -> start_month, list -> start_date);
        list = list -> next;
    }
}

void print_list2(struct event_content *list)
{
    /* print time for testing */
    while(list != NULL) {
        printf("%s: %d %d\n", list -> name, list -> start_time, list -> end_time);
        list = list -> next;
    }
}

void remove_enter(char *sentence)
{
    /* deal with '\0' */
    char *str = sentence;
    for(; *str && *str != '\n'; str++);
    *str = '\0';
}


int main(int argc, const char * argv[]) {
    // insert code here for testing...
    struct event_date *first1 = NULL;
    struct event_content *first2 = NULL;
    char *str = malloc(1024);
    //fgets(str, 1024, stdin);

    first1 = event_date_insert(first1, 9, 9, 10, 12);
    str = (char*)realloc(NULL, 1024);
    first1 = event_date_insert(first1, 12, 10, 9, 20);
    str = (char*)realloc(NULL, 1024);
    first1 = event_date_insert(first1, 10, 1, 2, 3);
    print_list1(first1);

    first2 = event_content_insert(first2, "A", 9, 10, 12);
    first2 = event_content_insert(first2, "J", 1, 2, 3);
    first1 -> sub = first2;
    print_list2(first1 -> sub);
    return 0;
}
