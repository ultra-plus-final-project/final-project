//#include "search_file_io.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define A_DAY 24

/*************************************test*******************************************/
struct node{
    int strt_month;
    int strt_day;
    bool whole_day;
    bool alert;
    int strt_time;
    int end_time;
    char *activity;
    char *place;
    char *others;
    struct node *next;
};

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
/**************************************test*********************************************/

int get_content_from_file(struct node *ptr) {                        //get content from file(**while(ptr->next!=NULL){ptr=ptr->next;})
    FILE *input_file;                                           
    char line[350]; 
    memset(line,'\0', sizeof(line));                                  
    input_file=fopen("input.txt", "r");                           //connect input_file to input.txt (read only)
    if (input_file==NULL) {                                       //if fail connecting
        printf("Error opening input file!\n");
        return 0;  
    }
    while (fgets(line, sizeof(line), input_file) != NULL) {        //put a line of input_file into line 
        sscanf(line,"%d/%d %d %d %d %d",                          //distribute the things in line to ptr
               &(ptr->strt_month), &(ptr->strt_day),
               &(ptr->whole_day), &(ptr->alert),
               &(ptr->strt_time), &(ptr->end_time));
        char *token;
        token=strtok(line,",");                                 //split the strings using commas as separators
        if (token!=NULL) {
            ptr->activity=strdup(token);                        //activity is the first string before ","
        }
        token=strtok(NULL,",");                                //split the strings using commas as separators
        if (token!=NULL) {
             ptr->place=strdup(token);                         //place is the second string before ","
        }

        token=strtok(NULL,",");                              //split the strings using commas as separators
        if (token!=NULL) {
             ptr->others=strdup(token);                       //others is the first string before ","
        }
        ptr->next=(struct node*)malloc(sizeof(struct node));  //allocate memory for the next node
        ptr=ptr->next;                                        //move to the next node
        ptr->next=NULL;                                       //set the next pointer to NULL for the last node
    }
    fclose(input_file);                                         //close the file
    return 1;
}

int write_content_on_file(struct node *ptr){                    //write content on file
    FILE *output_file;
    output_file=fopen("output.txt","w");                        //connect output_file with output.txt (write only)
    if (output_file == NULL) {
        printf("Error opening output file!\n");                 //if fail connecting
        return 1;
    }
    while(ptr!=NULL){                                           //put info into file
        fprintf(output_file,"%d/%d %d %d %d %d %s %s %s\n",ptr->strt_month,\
        ptr->strt_day,ptr->whole_day,ptr->alert,ptr->strt_time,ptr->end_time\
        ,ptr->activity,ptr->place,ptr->others);
        ptr=ptr->next;
    }
    fclose(output_file);                                        //close the file
    return 1;
}

void search_if_have_activity(struct node *list,int time){       //search if have things to do at the time
    while(list!=NULL){
        if(list->strt_time<=time&&list->end_time>=time){                              //if there's thing to do at the time
            printf("You have %s at %d",list->activity,time);            //print the activity name
            break;
        }else{
            list=list->next;                                    //if not find yet, go on the next
        }
    }
    if(list==NULL){
        printf("You don't have activity at %d\n",time);          // if not find an activity for the whole list
    }
}

void search_all_day_free_time(struct node *ptr){                //consider ptr sorted
    int free_time_str=0;
    struct node *tmp=ptr;
    while((tmp!=NULL)){
        if(free_time_str<(ptr->strt_time)){                     //if free time is smaller than the first activity's star time, it is free    
            printf("You have free time from %d to %d.\n"
            ,free_time_str,ptr->strt_time);                     //have the free time till the closest activity start
        }
        free_time_str=ptr->end_time;                            //set the free time start count point at the end of the activity
        tmp=tmp->next;                                          //go to the next closest activity
    }
    if(free_time_str<A_DAY){
        printf("You have free time from %d to %d.\n"
        ,free_time_str,A_DAY);                                  //if no more activity, it is free till 24
    }       
}

void search_scheduled_time_through_activity(struct node *list,char *activity){
     bool have_the_activity_or_not=1;
     while(list!=NULL){
        if(strcmp(list->activity,activity)==0){                 //if there's this activity in schedule
            printf("You have the activity from %d to %d"
            ,list->strt_time,list->end_time);                   //print the activity name and time
            have_the_activity_or_not=0;
        }
        list=list->next;                                        //if not find yet, go on the next
    }
    if(have_the_activity_or_not){
        printf("You don't have activity today\n");              // if not find an activity for the whole list
    }
}

struct node *annual_activity;

void long_term_event(struct node *event_date_list, int month, int date, bool whole_day, bool alert, char *name, int start_time, int end_time, char *place, int remainder){
    char selection;
    int normal_month_day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int leap_month_day[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    if(isleap(my_schedule->year)){   //default of improper input of date
        if(date>leap_month_day[month-1]){
            printf("Invalid Input!!!\n");
            return;
        }
    }else{
        if(date>normal_month_day[month-1]){
            printf("Invalid Input!!!\n");
            return;
        }
    }
    static int this_year=(my_schedule->year+1);       //only declare this_year=year once
    if(this_year==my_schedule->year){  //if this year == year
            while(annual_activity!=NULL){  //put every event in the annual_activity list into the event list
                event_date_insert(event_date_list, annual_activity->strt_month, annual_activity->strt_day); //******************************
                event_content_insert(event_date_list->event_content, annual_activity->activity,annual_activity->start_time,annual_activity->end_time,annual_activity->others);
                annual_activity=annual_activity->next;
            }
            this_year++;  //this_year+1, so the events won't be add again till next year
        }
    int deflaw=1;
    while(deflaw){
        printf("This activity a weekly event (press w), a monthly event (press m), a annual event (press y), or none of them (press n)\n");           //ask whether and which long term type
        scanf("%c",&selection);                                 //select type
        switch(selection){
            case 'w':                                           // if is week, insert activity after every seven days
                   if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){ //if big month
                        for(int i=event_date_list->strt_day;i<31;i+=7){
                            event_date_insert(event_date_list, month, i/*date*/); //******************************
                            event_content_insert(event_date_list->event_content,name,start_time,end_time,remainder);
                        }
                   }else if(month==4||month==6||month==9||month==11){ //if small month
                        for(int i=event_date_list->strt_day;i<30;i+=7){
                            event_date_insert(event_date_list, month, i/*date*/); //******************************
                            event_content_insert(event_date_list->event_content,name,start_time,end_time,remainder);
                        }
                   }else if(event_date_list->strt_month==2){    //if feb
                        if(my_schedule->year%4==0){              //leap year
                            for(int i=event_date_list->strt_day;i<29;i+=7){
                                event_date_insert(event_date_list, month, i/*date*/); //******************************
                                event_content_insert(event_date_list->event_content,name,start_time,end_time,remainder);
                            }
                        }else{                                  //normal year
                            for(int i=event_date_list->strt_day;i<30;i+=7){
                                event_date_insert(event_date_list, month, i/*date*/); //******************************
                                event_content_insert(event_date_list->event_content,name,start_time,end_time,remainder);
                            }
                        }
                   }
                    deflaw=0;
                    break;
            case 'm':                                           //if is a monthy activity
                    for(int i=my_schedule->month;i<12;i++){  
                        if(isleap(i)){
                            if(date<=leap_month_day[i-1])
                            event_date_insert(event_date_list, i/*month*/, date); //******************************//every month same date
                            event_content_insert(event_date_list->event_content,name,start_time,end_time,remainder);
                        }else{
                            if(date<=normal_month_day[i-1]){
                                event_date_insert(event_date_list, i/*month*/, date); //******************************//every month same date
                                event_content_insert(event_date_list->event_content,name,start_time,end_time,remainder);
                            }
                        }  
                    }
                    deflaw=0;
                    break;   
           case 'y':                                          //if is an annual event                  
                    annual_activity=add_to_list(annual_activity,month,date,whole_day,alert,start_time,end_time,name,place,remainder); //add the event into annual_activity list
                    event_date_insert(event_date_list, month, date); //******************************
                    event_content_insert(event_date_list->event_content,name,start_time,end_time,remainder);
            case 'n':                                            //if not long term activity, just insert
                    event_date_insert(event_date_list, month, date); //******************************//that month that date
                    event_content_insert(event_date_list->event_content,name,start_time,end_time,remainder);
                    deflaw=0;
                    break;
            default:
                    printf("Invalid input!!\n"); //if(variable default isn't set to zero, the function will ask again in the while loop)
                    break;
        }
    }
}

/**************************************priority queue************************************/
struct priority_queue{
    int time;
    struct node *event;              //put ptr,which stores all info including month, date...
};

int tree_size=0;                      //global variable trace size of tree
struct priority_queue day_tree[100];  //only for the schedule of a day

void swap(struct priority_queue *a,struct priority_queue *b) {  //swap info in day_tree
   struct priority_queue temp=*a;
    *a=*b;
    *b=temp;
}

struct node *pop(struct  priority_queue *day_tree){   //pop out the smallest time's event name
    struct node *pop_activity=NULL;                   //store the ptr being popping out
    pop_activity=malloc(sizeof(struct node));
    if (tree_size<=0) {                               //if tree_size<=0, no more event
        struct node *no_activity=malloc(sizeof(struct node));
        no_activity->activity=malloc(30);
        no_activity->activity="No more activity today.";   //make the string printing out the msg
        pop_activity=no_activity;
        return pop_activity;                             //return the msg
    }
    pop_activity=day_tree[0].event;                    //if tree_size!=0, set popping out activity pointing to the first(day_tree[0])'s event
    day_tree[0]=day_tree[tree_size-1];                 //let the last activity=the first
    tree_size--;                                       //minus one so the size shrink one, the last activity got rid
    int currentIndex=0;                                //start comparing from [0]
    while (1) {
        int leftChild=2*currentIndex+1;               //L_child
        int rightChild=2*currentIndex+2;              //R_child
        int smallest=currentIndex;
        if((leftChild<tree_size)&&(day_tree[leftChild].time<day_tree[smallest].time)){  //L_child is not over the bound(size)&&the time of [small] is bigger, then the [small] should "sink" into the lower(further away from being print)
            smallest=leftChild;
        }
        if((rightChild<tree_size)&&(day_tree[rightChild].time<day_tree[smallest].time)){//R_child is not over the bound(size)&&the time of [small] is bigger, then the [small] should "sink" into the lower(further away from being print)
            smallest=rightChild;
        }
        if(smallest!=currentIndex){                               //exchange the content if the former last array is not yet in the right place that is smaller than its children
            swap(&day_tree[currentIndex],&day_tree[smallest]); 
            currentIndex=smallest;
        }else{                                                     //when the the former last is no longer bigger than any of its children
            break;                     
        }
    }
    return pop_activity;           //return day_tree[0].event
}

void push(struct priority_queue *day_tree, int strt_time, struct node *list ){
    if (tree_size>=100) {                 //over the max size of day_tree
        printf("The schedule for today is full.\n");
        return;
    }
    day_tree[tree_size].time=strt_time;              //put info into the empty arr
    day_tree[tree_size].event=list;
    int currentIndex=tree_size;
    int parentIndex=(currentIndex-1)/2;
    while ((currentIndex>0)&&(day_tree[currentIndex].time<day_tree[parentIndex].time)) {  //if time < parent, "float" up into [smaller] arr(cuz [smaller] print out first)
        swap(&day_tree[currentIndex], &day_tree[parentIndex]);
        currentIndex=parentIndex;
        parentIndex=(currentIndex-1)/2;
    }
    tree_size++;                  //tree_size+1
}

void clean_day_tree(){                 //reset the whole day_tree
    for(int i=0;i<100;i++){
        day_tree[i].time=-1;
        day_tree[i].event=NULL;
    }
}

void delete(struct priority_queue *day_tree, int strt_time){  //delete the time of event
    int i;
    for(i=0;i<tree_size;i++) {                               //look for the time
        if (day_tree[i].time==strt_time) {                   //if found
            day_tree[i]=day_tree[tree_size-1];               //set the time to last arr 
            tree_size--;                                     //minus one in size (so the last arr become the former [last-1])
            break;
        }
    }
    if (i==tree_size) {                                       //if not find event at the time
        printf("No event at the time.\n");
    }else{                                                    //do the  "float" and "sink" same as pop and push
        int currentIndex=i;
        int parentIndex=(currentIndex-1)/2;
        if ((currentIndex>0)&&(day_tree[currentIndex].time<day_tree[parentIndex].time)) {     //do same as push when the one being delete is not root, and see if the time replacing the user_enter_time is smaller than parent
            while(currentIndex>0&&day_tree[currentIndex].time<day_tree[parentIndex].time) {
                swap(&day_tree[currentIndex],&day_tree[parentIndex]);                           //keep exchane till bigger than parent
                currentIndex=parentIndex;
                parentIndex=(currentIndex-1)/2;
            }
        } else {                                              //do the same as pop when the one being removed is root
            while(1) {
                int leftChild=2*currentIndex+1;
                int rightChild=2*currentIndex+2;
                int smallest=currentIndex;
                if((leftChild<tree_size)&&(day_tree[leftChild].time<day_tree[smallest].time)){
                    smallest=leftChild;
                }
                if((rightChild<tree_size)&&(day_tree[rightChild].time<day_tree[smallest].time)){
                    smallest=rightChild;
                }
                if(smallest!=currentIndex) {
                    swap(&day_tree[currentIndex],&day_tree[smallest]);
                    currentIndex=smallest;
                } else {
                    break;
                }
            }
        }
    }
    
}

struct node *add_to_ptrlist(struct node *list,int st_mon,int st_da,bool who,bool aler,int str_t,int end_t,char* ac,char *pl,char *ot){  //for testing, put thing in ptr altogather
    struct node *tmp;
    tmp=malloc(sizeof(struct node));
    tmp->activity=malloc(strlen(ac)+1);  //allocate memory for activity
    tmp->place=malloc(strlen(pl)+1);     //allocate memory for place
    tmp->others=malloc(strlen(ot)+1);    //allocate memory for others
    strcpy(tmp->activity,ac);
    tmp->strt_month=st_mon;
    tmp->strt_day=st_da;
    tmp->whole_day=who;
    tmp->alert=aler;
    tmp->strt_time=str_t;
    tmp->end_time=end_t;
    strcpy(tmp->place,pl);
    strcpy(tmp->others,ot);
    return tmp;
}
/**************************************priority queue************************************/

/****************************************test********************************************/
int main(){                                                                     //test for file i/o
    struct node *ptr=NULL,*rec=malloc(sizeof(struct node));
    rec->next=NULL;
    ptr=add_to_ptrlist(ptr,5,5,1,1,9,20,"walk sheep","ROS","bring gress");
    ptr=add_to_ptrlist(ptr,7,2,1,1,8,16,"take test","hell","bring pen");
    write_content_on_file(ptr);
    get_content_from_file(rec);
    while(rec->next!=NULL){
        printf("%d/%d %d %d %d %d %s %s %s\n",rec->strt_month,\
        rec->strt_day,rec->whole_day,rec->alert,rec->strt_time,rec->end_time\
        ,rec->activity,rec->place,rec->others);
        rec=rec->next;
    }
    return 0;
}

int main() {                                                                 //test for priority queue
    struct node *ptr=NULL,*rec=malloc(sizeof(struct node));
    rec->next=NULL;
    ptr=add_to_ptrlist(ptr,5,5,1,1,9,20,"walk sheep","ROS","bring gress");
    push(day_tree,ptr->strt_time,ptr);
    ptr=add_to_ptrlist(ptr,7,2,1,1,8,16,"take test","hell","bring pen");
    push(day_tree,ptr->strt_time,ptr);
    struct node *popped=pop(day_tree);
    printf("%s\n",popped->activity);
    ptr=add_to_ptrlist(ptr,7,2,1,1,8,16,"take test","hell","bring pen");
    push(day_tree,ptr->strt_time,ptr);
    delete(day_tree,9);
    popped=pop(day_tree);
    printf("%s\n",popped->activity);
    popped=pop(day_tree);
    printf("%s\n",popped->activity);
    popped=pop(day_tree);
    printf("%s\n",popped->activity);
    free(popped->activity);
    free(popped->place);
    free(popped->others);
    free(popped);
    free(rec);
    return 0;
} 
/****************************************test*************************************************/

