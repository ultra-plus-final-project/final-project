#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
//#include "search_file_io.h"
//input 未完善
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

int get_content_from_file(struct node *ptr){                   // get content from file
    FILE *input_file;
    char *content;
    input_file=fopen("input.txt","r");                         //connect input_file with input.txt (read only)
    if (input_file == NULL) {                                  //if fail connecting
        printf("Error opening input file!\n");
        return 1;
    }
    while (fgets(content,sizeof(content),input_file)!=NULL) {  //put info into ptr
        fscanf(input_file,"%c/%c %d %d %d %d %s %s %s",ptr->strt_month,ptr->strt_day,\
        ptr->whole_day,ptr->alert,ptr->strt_time,ptr->end_time,ptr->activity,ptr->place,ptr->others);
        ptr=ptr->next;
    }
    fclose(input_file);                                        //close the file
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

void search(struct node *list,int time){                       //search if have things to do at the time
    while(list!=NULL){
        if(list->strt_time==time){                             //if there's thing to do at the time
            printf("%s at %d",list->activity,time);            //print the activity name
            break;
        }else{
            list=list->next;                                   //if not find yet, go on the next
        }
    }
    if(list==NULL){
        printf("You don't have activity at %d\n",time);         // if not find an activity for the whole list
    }
}

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
    struct node *ptr=NULL,*rec=NULL;
    rec=malloc(sizeof(struct node));
    ptr=add_to_list(ptr,5,5,1,1,9,20,"walk sheep","ROS","bring gress");
    ptr=add_to_list(ptr,7,2,1,1,8,16,"take test","hell","bring pen");
    write_content_on_file(ptr);
    //printf("********\n");
    get_content_from_file(rec);
    //printf("********\n");
    while(rec!=NULL){
        printf("############\n");
        printf("%d/%d %d %d %d %d %s %s %s\n",rec->strt_month,\
        rec->strt_day,rec->whole_day,rec->alert,rec->strt_time,rec->end_time\
        ,rec->activity,rec->place,rec->others);
        rec=rec->next;
    }
    //printf("********\n");
    return 0;
}
/****************************************test*************************************************/