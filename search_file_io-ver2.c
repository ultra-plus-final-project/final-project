#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define A_DAY 24
//#include "search_file_io.h"
//input 可印，但不完整且含亂碼
//重複登記 未完
/*************************************test*******************************************/
struct node{
    int strt_month;
    int strt_day;
    bool whole_day;
    bool alert;
    int strt_time;
    int end_time;
    char activity[100];
    char place[100];
    char others[100];
    struct node *next;
};
/**************************************test*********************************************/

int get_content_from_file(struct node *ptr) {
    FILE *input_file;
    char line[350]; 
    memset(line, '\0', sizeof(line));                            // create a string to store everthing 
    input_file = fopen("input.txt", "r");
    if (input_file == NULL) {
        printf("Error opening input file!\n");
        return 1;  
    }
    while (fgets(line, sizeof(line), input_file) != NULL) {
        sscanf(line, "%c/%c %d %d %d %d %[^\n] %[^\n] %[^\n]",
               &(ptr->strt_month), &(ptr->strt_day),
               &(ptr->whole_day), &(ptr->alert),
               &(ptr->strt_time), &(ptr->end_time),
               ptr->activity, ptr->place, ptr->others);

        ptr->next = (struct node*)malloc(sizeof(struct node));  // Allocate memory for the next node
        ptr = ptr->next;  // Move to the next node
        ptr->next = NULL;  // Set the next pointer to NULL for the last node
    }
    fclose(input_file);
    return 1;
}


int write_content_on_file(struct node *ptr){                  //write content on file
    FILE *output_file;
    output_file=fopen("output.txt","w");                      //connect output_file with output.txt (write only)
    if (output_file == NULL) {
        printf("Error opening output file!\n");               //if fail connecting
        return 1;
    }
    while(ptr!=NULL){                                         //put info into file
        fprintf(output_file,"%d/%d %d %d %d %d %s %s %s\n",ptr->strt_month,\
        ptr->strt_day,ptr->whole_day,ptr->alert,ptr->strt_time,ptr->end_time\
        ,ptr->activity,ptr->place,ptr->others);
        ptr=ptr->next;
    }
    fclose(output_file);                                       //close the file
    return 1;
}

void search_if_have_activity(struct node *list,int time){                       //search if have things to do at the time
    while(list!=NULL){
        if(list->strt_time==time){                             //if there's thing to do at the time
            printf("You have %s at %d",list->activity,time);            //print the activity name
            break;
        }else{
            list=list->next;                                   //if not find yet, go on the next
        }
    }
    if(list==NULL){
        printf("You don't have activity at %d\n",time);         // if not find an activity for the whole list
    }
}

void search_all_day_free_time(struct node *ptr){              //consider ptr sorted
    int free_time_str=0;
    struct node *tmp=ptr;
    while((tmp!=NULL)){
        if(free_time_str<(ptr->strt_time)){                   //if free time is smaller than the first activity's star time, it is free    
            printf("You have free time from %d to %d.\n",free_time_str,ptr->strt_time); //have the free time till the closest activity start
        }
        free_time_str=ptr->end_time;                  //set the free time start count point at the end of the activity
        tmp=tmp->next;                   //go to the next closest activity
    }
    if(free_time_str<A_DAY){
        printf("You have free time from %d to %d.\n",free_time_str,A_DAY);   //if no more activity, it is free till 24
    }       
}

void search_scheduled_time_through_activity(struct node *list,char *activity){
     bool have_the_activity_or_not=1;
     while(list!=NULL){
        if(strcmp(list->activity,activity)==0){                             //if there's this activity in schedule
            printf("You have the activity from %d to %d",list->strt_time,list->end_time);     //print the activity name and time
            have_the_activity_or_not=0;
        }
        list=list->next;                                   //if not find yet, go on the next
    }
    if(have_the_activity_or_not){
        printf("You don't have activity today\n");         // if not find an activity for the whole list
    }
}

/*void long_term_event(struct node *event_date_list, char *name, int start_time, int end_time, int remainder){
    char selection;
    bool default=1;
    while(default){
        printf("This activity a weekly event (press "w"), a monthly event (press "m"), or none of them (press "n")\n"); //ask whether and which long term type
        scanf("%c",&selection);                      //select type
        switch(selection){
            case 'w':  // if is week, insert activity after every seven days
                    for(int i=start_date;i<30;i+=7){
                       event_content_insert(event_date_list->event_content,name,start_time,end_time,remainder);
                        for(int j=0;j<7;j++){
                            event_date=event_date_list->next;
                        }
                    }
                    default=0;
                    break;
            case 'm':                //if is a monthy activity
                    for(int i=start_month;i<12;i++){
                        event_content_insert(event_date_list->event_content,name,start_time,end_time,remainder);
                    }
                    default=0;
                    break;
            case 'n':                  //if not long term activity, just insert
                    event_content_insert(event_date_list->event_content,name,start_time,end_time,remainder);
                    default=0;
                    break;
            default:
                    printf("Invalid input!!\n");
                    break;
        }
    }
}*/

/****************************************test********************************************/
struct node *add_to_list(struct node *list,int st_mon,int st_da,bool who,bool aler,int str_t,int end_t,char* ac,char *pl,char *ot){
    struct node *tmp;
    tmp=malloc(sizeof(struct node));
    strcpy(tmp->activity,ac);
    tmp->strt_month=st_mon;
    tmp->strt_day=st_da;
    tmp->whole_day=who;
    tmp->alert=aler;
    tmp->strt_time=str_t;
    tmp->end_time=end_t;
    strcpy(tmp->place,pl);
    strcpy(tmp->others,ot);
    tmp->next=list;
    return tmp;
}

int main(){
    struct node *ptr=NULL,*rec=malloc(sizeof(struct node));
    rec->next=NULL;
    ptr=add_to_list(ptr,5,5,1,1,9,20,"walk sheep","ROS","bring gress");
    ptr=add_to_list(ptr,7,2,1,1,8,16,"take test","hell","bring pen");
    write_content_on_file(ptr);
    get_content_from_file(rec);
    while(rec!=NULL){
        printf("%d/%d %d %d %d %d %s %s %s\n",rec->strt_month,\
        rec->strt_day,rec->whole_day,rec->alert,rec->strt_time,rec->end_time\
        ,rec->activity,rec->place,rec->others);
        rec=rec->next;
    }
    return 0;
}
/****************************************test*************************************************/