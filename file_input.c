#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define A_DAY_HOUR 24
#define NAME_SIZE 29
#define TABLE_SIZE 1000
#define DELETED_NODE (struct event_content*)(0xFFFFFFFFFFFFUL)
int today,this_year;
struct event_content *hash_table[TABLE_SIZE];


#define RED "\033[0;31m"
#define YELLOW "\033[1;33m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define WHITE "\033[1;37m"

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

int get_content_from_file(Event_date **ptr);
int write_content_on_file(Event_date *ptr);
Event_date *event_date_insert(int month, int date, int command);

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

Event_date *find_current_date(int start_month, int start_date){
    Event_date *tmp = date_head;
    while(tmp != NULL){
        if((tmp->month == start_month) && (tmp->date == start_date)){
             //printf("m:%d d:%d sm:%d sd:%d\n",tmp->month,tmp->date,start_month,start_date);
             return tmp;
        }
        else{
            tmp = tmp->next;
        } 
    }
    if(tmp == NULL){
        //printf("there\n");
        return NULL;
    } 
    
}

int check_if_already_have_event(Event_date *date_head, int month, int date, int start_time,int end_time){    //check if there is already event ont the day
    Event_date *cur_date = date_head;
    while(cur_date!=NULL){
        if(cur_date->month==month&&cur_date->date==date){
            break;
        }
        cur_date=cur_date->next;
    }
    if(cur_date!=NULL){
        Event_content *tmp;
        tmp=cur_date->content;
        while(tmp!=NULL){
            if((tmp->start_time<=start_time&&tmp->end_time>=start_time) || (tmp->end_time>=end_time&&tmp->start_time<=end_time)){
                printf("You already have the activity %s at the time\n",tmp->name);
                return 0;
            }
            tmp=tmp->next;
        }
    }
    return 1;
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




struct event_date *event_date_insert(int start_month, int start_date, int command){
    /* allocate node */
    Event_date *new_event_date;
    Event_content *new_event_content;
    Event_date *prev = NULL;
    new_event_date = malloc(sizeof(Event_date));
    new_event_content = malloc(sizeof(Event_content));
    if(new_event_date == NULL){
        printf("Error: malloc failed in event_date_insert\n");
        exit(1);
    }
    if(new_event_content == NULL){
        printf("Error: malloc failed in event_date_insert\n");
        exit(1);
    }
 
    Event_date *cur = date_head; //used to locate the needed node in linked list
 
    /* put in the data */
    new_event_date -> month = start_month;
    new_event_date -> date = start_date;
    new_event_date -> event_num = 0;
    new_event_date -> next = NULL;
    new_event_date -> content = NULL;
 
    /* If linked List is empty */
    if(date_head == NULL){
        date_head = new_event_date;
        return date_head;
    }
 
    /* insert the node */
    while(1){
        if((cur -> month == new_event_date -> month && cur -> date > new_event_date ->date) || (cur -> month > new_event_date -> month)){
            //if 
            if(prev == NULL){
                new_event_date -> next = cur;
                date_head = new_event_date;
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
    //printf("ttttttttt\n");
    return date_head;
}



void event_content_insert(int month, int date, char *name, int start_time, int end_time, char* place, char* others){
    /*
    In this function, we have few steps to do
    1. find if the day has any activity before, if not, then add a nw node of event_date
    2. check if the time is free
        (1) if not, then print out the orignal schedule and end the action
        (2) if is, then insert the schedule
    */
    //printf("m:%d d:%d\n",month,date);
    Event_date *cur_date = find_current_date(month, date);
    if(cur_date == NULL){
        cur_date = event_date_insert(month, date, 1);
        cur_date = find_current_date(month, date);
    }
    //printf("%d %d\n",cur_date->month,cur_date->date);
    if(cur_date!=NULL){
        cur_date -> event_num++; 
    }
    else if(check_if_already_have_event(date_head, month,date,start_time, end_time)==0) return;
    //printf("okok");
    Event_content *new_event_content = malloc(sizeof(Event_content));
    new_event_content -> name = malloc(30);
    new_event_content -> place = malloc(30);
    new_event_content -> others = malloc(30);
    Event_content *content_head = cur_date->content;
    Event_content *curr = content_head;
    Event_content *prev = NULL;
    Event_content *tmp = NULL;
    //printf("okok");
    //printf("bbbbbbbbbbb\n");
    if(new_event_content == NULL){
        printf("Error: malloc failed in event_content_insert\n");
        exit(1);
    }
    /* put in the data */
    new_event_content -> name = name;
    new_event_content -> start_time = start_time;
    new_event_content -> end_time = end_time;
    new_event_content -> place = place;
    new_event_content -> others = others;
    new_event_content -> next = NULL;
    //printf("ccccccccc\n");
    //hash_table_insert(new_event_content);
    //print_table();
    //printf("ddddddd\n");
    if(content_head == NULL){ //If linked List is empty
        cur_date->content = new_event_content;
        //printf("okok");
    }
    while(curr != NULL){
        if(prev == NULL){
           // printf("fffffff\n");
            new_event_content->next = curr;
            cur_date->content = new_event_content;
        }
        else if(prev->start_time <= new_event_content->start_time){
            //printf("gggggggggg\n");
            new_event_content->next = curr;
            prev->next = new_event_content;
            tmp -> next = prev;
        }
        tmp=malloc(sizeof(Event_content));
        tmp=prev;
        //tmp->next=malloc(sizeof(Event_content));
       // printf("eeeeeeeeee\n");
        prev = curr;
        curr = curr->next;
    }
}   




int write_content_on_file(Event_date *ptr){                    //write content on file
    FILE *output_file;
    output_file=fopen("file_io.txt","w");                        //connect output_file with output.txt (write only)
    if (output_file == NULL) {
        printf("Error opening output file!\n");                 //if fail connecting
        output_file = fopen("file_io.txt", "w+");
        if (output_file == NULL) {
            printf("Error creating output file!\n");
            return 1;
        }
    }
    while(ptr!=NULL){   //put info into file
        Event_content *tmp_content=ptr->content;   
        for(int i=1;i<=ptr->event_num;i++){
            if(tmp_content==NULL){
                break;
            }
            fprintf(output_file,"%d. %d/%d %d-%d %s,%s,%s\n",i/*event num*/,\
            ptr->month,ptr->date,tmp_content->start_time,tmp_content->end_time\
            ,tmp_content->name,tmp_content->place,tmp_content->others);
            tmp_content=tmp_content->next;
        }            
        ptr=ptr->next;                            
    }
    fclose(output_file);                                        //close the file
    return 1;
}

void daily_event(int start_month,int end_month,int start_date,int end_date,char* name,int start_time,int end_time,char* place,char* others){
    int normal_month_day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int leap_month_day[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    if(isleap(today/10000)){
        while(start_date>leap_month_day[start_month-1]||start_date<1){
            printf("Invalid Input in start date!!!\n");
            printf("Please enter the start date again.\n");
            scanf("%d",&start_date);
        }
        while(end_date>leap_month_day[end_month-1]||end_date<1){
            printf("Invalid Input in end date!!!\n");
            printf("Please enter the end date again.\n");
            scanf("%d",&end_date);
        }
    }else{
        while(start_date>normal_month_day[start_month-1]||start_date<1){
            printf("Invalid Input in start date!!!\n");
            printf("Please enter the start date again.\n");
            scanf("%d",&start_date);
        }
        while(end_date>normal_month_day[end_month-1]||end_date<1){
            printf("Invalid Input in end date!!!\n");
            printf("Please enter the end date again.\n");
            scanf("%d",&end_date);
        }

    }
    if(start_month!=end_month){
        for(int i=start_month;i<=end_month;i++){
            if(isleap(today/10000)){
                for(int j=(i==start_month? start_date: 1);j<=(i==end_month? end_date : leap_month_day[i-1]);j++){
                    if(check_if_already_have_event(date_head,i/*month*/,j/*date*/,start_time, end_time)){
                        event_content_insert(i/*month*/,j/*date*/,name,start_time,end_time,place,others);
                    }
                }
            }else{
                for(int j=(i==start_month? start_date: 1);j<=(i==end_month? end_date : normal_month_day[i-1]);j++){
                    if(check_if_already_have_event(date_head,i/*month*/,j/*date*/,start_time, end_time)){
                        event_content_insert(i/*month*/,j/*date*/,name,start_time,end_time,place,others);
                    }
                }

            }
        }
    }else{
        for(int j=start_date;j<=end_date;j++){
            //printf("%d\n",j);
            if(check_if_already_have_event(date_head,start_month,j,start_time, end_time)){
                event_content_insert(start_month,j/*date*/,name,start_time,end_time,place,others);
            }
        }

    }
    write_content_on_file(date_head);
}

/************************* update func ********************************/
Event_content *find_day(Event_date *ptr,int month,int date){
    Event_content *cur=NULL;
    while(ptr!=NULL){       
        if(ptr->month==month&&ptr->date==date){
            Event_content *tmp_content=malloc(sizeof(Event_content));
            tmp_content->name=ptr->content->name;
            tmp_content->start_time=ptr->content->start_time;
            tmp_content->end_time=ptr->content->end_time;
            tmp_content->place=ptr->content->place;
            tmp_content->others=ptr->content->others;
            tmp_content->next=cur;
            cur=tmp_content;
        }
        ptr=ptr->next;
    }
    return cur;
}

int get_content_from_file(Event_date **ptr) {
    FILE *input_file;
    input_file = fopen("file_io.txt", "r");
    if (input_file == NULL) {
        // Handle error
        return 0;
    }
    
    char line[350];
    while (fgets(line, sizeof(line), input_file) != NULL) {
        Event_date *new_node = malloc(sizeof(Event_date));
        new_node->content = malloc(sizeof(Event_content));
        new_node->content->name = malloc(30);
        new_node->content->place = malloc(30);
        new_node->content->others = malloc(30);
        
        sscanf(line, "%d. %d/%d %d-%d",
               &(new_node->event_num),
               &(new_node->month),
               &(new_node->date),
               &(new_node->content->start_time),
               &(new_node->content->end_time));

        char *token;
        token = strtok(line, ",");
        if (token != NULL) {
            // Skip numeric values in the name field
            while ((*token >= '0' && *token <= '9')||( *token=='.')) {
                token++;
            }
            // Remove leading whitespace, if any
            while (*token == ' ') {
                token++;
            }
            while ((*token >= '0' && *token <= '9')||(*token=='/')) {
                token++;
            }
            while (*token == ' ') {
                token++;
            }
            while ((*token >= '0' && *token <= '9')||(*token=='-')) {
                token++;
            }
            while (*token == ' ') {
                token++;
            }
            new_node->content->name = malloc(strlen(token) + 1);
            strcpy(new_node->content->name, token);
        }
        
        token = strtok(NULL, ",");
        if (token != NULL) {
            new_node->content->place = malloc(strlen(token) + 1);
            strcpy(new_node->content->place, token);
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            new_node->content->others = malloc(strlen(token) + 1);
            strcpy(new_node->content->others, token);
        }
        
        new_node->next = NULL;

        // Link the new node to the existing list
        if (*ptr == NULL) {
            *ptr = new_node;
        } else {
            Event_date *current = *ptr;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
    }

    fclose(input_file);
    return 1;
}


/************************ update func *********************************/

int main(){              
    daily_event(10,10,11,12,"sheep",1200,1500,"park","ba"); 
    daily_event(10,10,11,11,"lamb",1000,1100,"room","jog");  
    /****************************the part to add*****************************************/
    Event_date* tmp = NULL;
    if (get_content_from_file(&tmp) == 0) {
        printf("Error reading input file!\n");
        return 1;
    }
    Event_content* cur_event = find_day(tmp,10,11);
    /******************************************************************/
    while (cur_event != NULL) {
        printf("Name: %s\n", cur_event->name);
        printf("Start Time: %d\n", cur_event->start_time);
        printf("End Time: %d\n", cur_event->end_time);
        printf("Place: %s\n", cur_event->place);
        printf("Others: %s\n", cur_event->others);
        cur_event = cur_event->next;
    }
    return 0;
}
