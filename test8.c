void event_content_insert(int start_month, int end_month, int start_date, int end_date, char *name, int start_time, int end_time, char* place, char* others){
    /*
    In this function, we have few steps to do
    1. find if the day has any activity before, if not, then add a nw node of event_date
    2. check if the time is free
        (1) if not, then print out the oriinal schedule and end the action
        (2) if is, then insert the schedule
    */
    Event_date *cur_date = find_current_date(start_month, start_date);
    
    if(cur_date == NULL)
        cur_date = event_date_insert(start_month, start_date, 1);
    else if(search_if_the_time_have_activity(cur_date->content, start_time, end_time, 1)) return;
    
    Event_content *new_event_content = malloc(sizeof(struct event_content));
    Event_content *content_head = cur_date->content;
    Event_content *prev = content_head;

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

 //***********************************待檢查
    /* 
    if(content_head == NULL){ //If linked List is empty
        cur_date->content = new_event_content;
    }

    while(curr != NULL){
        if(prev == NULL){
            new_event_content->next = curr;
            cur_date->content = new_event_content;
        }
        else if(curr->start_time < new_event_content->start_time){
            new_event_content->next = curr;
            prev->next = new_event_content;  
        }       
        prev = curr;
        curr = curr->next;
    } */
}   

int get_content_from_file(Event_date *ptr) {                        //get content from file(**while(ptr->next!=NULL){ptr=ptr->next;})
    FILE *input_file;                                           
    char line[350]; 
    memset(line,'\0', sizeof(line));                                  
    input_file=fopen("file_io.txt", "r");                           //connect input_file to input.txt (read only)
    if (input_file==NULL) {                                       //if fail connecting
        printf("Error opening input file!\n");
        return 0;  
    }
    while (fgets(line, sizeof(line), input_file) != NULL) {        //put a line of input_file into line 
        sscanf(line,"%d.%d/%d %d-%d",                          //distribute the things in line to ptr
               &(ptr->event_num),&(ptr->month), &(ptr->date),
              &(ptr->content->start_time),&(ptr->content->end_time));
        char *token;
        token=strtok(line,",");                                 //split the strings using commas as separators
        if (token!=NULL) {
            ptr->content->name=strdup(token);                        //activity is the first string before ","
        }
        token=strtok(NULL,",");                                //split the strings using commas as separators
        if (token!=NULL) {
             ptr->content->place=strdup(token);                         //place is the second string before ","
        }

        token=strtok(NULL,",");                              //split the strings using commas as separators
        if (token!=NULL) {
             ptr->content->others=strdup(token);                       //others is the first string before ","
        }
        ptr->next=(struct node*)malloc(sizeof(struct node));  //allocate memory for the next node
        ptr=ptr->next;                                        //move to the next node
        ptr->next=NULL;                                       //set the next pointer to NULL for the last node
    }
    fclose(input_file);                                         //close the file
    return 1;
}
int write_content_on_file(Event_date *ptr){                    //write content on file
    FILE *output_file;
    output_file=fopen("file_io.txt","w");                        //connect output_file with output.txt (write only)
    if (output_file == NULL) {
        printf("Error opening output file!\n");                 //if fail connecting
        return 1;
    }
    while(ptr!=NULL){                                           //put info into file
        fprintf(output_file,"%d.%d/%d %d-%d %s, %s, %s\n",ptr->event_num,\
        ptr->month,ptr->date,ptr->content->start_time,ptr->content->end_time\
        ,ptr->content->name,ptr->content->place,ptr->content->others);
        ptr=ptr->next;
    }
    fclose(output_file);                                        //close the file
    return 1;
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

Event_date *annual_activity;

void long_term_event(Event_date *event_date_list, int month, int date, int start_time, int end_time,  char *name, char *place, char* others){
    char selection;
    int normal_month_day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int leap_month_day[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    static int this_year=((today/10000)+1);       //only declare this_year=year once
    if(this_year==(today/10000)){  //if this year == year
            while(annual_activity!=NULL){  //put every event in the annual_activity list into the event list
                event_date_insert(annual_activity->month,annual_activity->date,0);
                event_content_insert(annual_activity->content->name,annual_activity->content->start_time,annual_activity->content->end_time,annual_activity->content->place,annual_activity->content->others);
                annual_activity=annual_activity->next;
            }
            this_year++;  //this_year+1, so the events won't be add again till next year
        }
    int deflaw=1;
    while(deflaw){
       selection=ask_event_length(int month, int date);
        switch(selection){
            case 'w':                                           // if is week, insert activity after every seven days
                   if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){ //if big month
                        for(int i=date;i<31;i+=7){
                            if(check_if_already_have_event_w(date_head,month,i)){
                                event_date_insert(month,i/*date*/,0)
                                event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                        }
                   }else if(month==4||month==6||month==9||month==11){ //if small month
                        for(int i=date;i<30;i+=7){
                           if(check_if_already_have_event_w(date_head,month,i)){
                                event_date_insert(month,i/*date*/,0)
                                event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                        }
                   }else if(event_date_list->strt_month==2){    //if feb
                        if(isleap(today/10000)){              //leap year
                            for(int i=event_date_list->strt_day;i<29;i+=7){
                                if(check_if_already_have_event_w(date_head,month,i)){
                                    event_date_insert(month,i/*date*/,0)
                                    event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                            }
                        }else{                                  //normal year
                            for(int i=event_date_list->strt_day;i<30;i+=7){
                                if(check_if_already_have_event_w(date_head,month,i)){
                                    event_date_insert(month,i/*date*/,0)
                                    event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                            }
                        }
                   }
                    deflaw=0;
                    break;
            case 'm':                                           //if is a monthy activity
                    for(int i=my_schedule->month;i<12;i++){  
                        if(isleap(i)){
                            if(date<=leap_month_day[i-1]){
                                if(check_if_already_have_event(date_head,i,date)){
                                    event_date_insert(i/*month*/,date);                               //every month same date
                                     event_content_insert(i/*month*/,date,name,start_time,end_time,place,others);
                                }
                            }
                        }else{
                            if(date<=normal_month_day[i-1]){
                                if(check_if_already_have_event(date_head,i,date)){
                                    event_date_insert(i/*month*/, date);                               //every month same date
                                    event_content_insert(i/*month*/,date,name,start_time,end_time,place,others);
                                }
                            }
                        }  
                    }
                    deflaw=0;
                    break;   
           case 'y':                                          //if is an annual event                  
                    if(check_if_already_have_event(date_head,month,date)){
                        annual_activity=add_to_list(annual_activity,month,date,start_time,end_time,name,place,others); //add the event into annual_activity list
                        event_date_insert(month, date);                               //every month same date
                        event_content_insert(month,date,name,start_time,end_time,place,others);
                    }
                    deflaw=0;
                    break;
            case 'n':                                            //if not long term activity, just insert
                    if(check_if_already_have_event(date_head,month,date)){
                        event_date_insert(month, date); //******************************
                        event_content_insert(month,date,name,start_time,end_time,place,others);
                    }
                    deflaw=0;
                    break;
            default:
                    printf("Invalid input in term selection.\n"); //if(variable default isn't set to zero, the function will ask again in the while loop)
                    break;
        }
    }
}

char ask_event_length(int month, int date){
    char selection;
     printf("This activity a weekly event (press w), a monthly event (press m), a annual event (press y), or none of them (press n)\n");           //ask whether and which long term type
        scanf("%c",&selection); 
    if(isleap(my_schedule->year)){   //default of improper input of date***********可被放到前面程式重新輸入**************
        if(date>leap_month_day[month-1]){
            printf("Invalid Input in date.\n");
            return;
        }
    }else{
        if(date>normal_month_day[month-1]){
            printf("Invalid Input in date.\n");
            return;
        }
    }
    return selection;                                //select type
}

int check_if_already_have_event(Event_date *date_head,int month,int date){    //check if there is already event ont the day
    while(date_head!=NULL){
        if(date_head->start_month==month&&date_head->start_date==date){
            break;
        }
        date_head=date_head->next;
    }
    if(date_head!=NULL){
        Event_content tmp;
        tmp=date_head->content;
        while(tmp!=NULL){
            if(tmp->start_time==time){
                printf("You already have the activity %s at the time\n",tmp->name);
                return 0;
                break;
            }
            tmp=tmp->next;
        }
    }
    return 1;
}

void search_if_have_activity_on_the_date(Event_date *date_head, int month, int date, int time){
    while(date_head!=NULL){
        if(date_head->start_month==month&&date_head->start_date==date){
            break;
        }
        date_head=date_head->next;
    }
    if(date_head==NULL){
        printf("You don't have activity at the time\n");
    }else{
        Event_content tmp;
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

char *pop(struct  priority_queue *day_tree){   //pop out the smallest time's event name
    Event_content *pop_activity=NULL;                   //store the ptr being popping out
    pop_activity=malloc(sizeof(struct node));
    if (tree_size<=0) {                               //if tree_size<=0, no more event
        Event_content *no_activity=malloc(sizeof(struct node));
        no_activity->name=malloc(30);
        no_activity->name="No more activity today.";   //make the string printing out the msg
        pop_activity=no_activity;
        return pop_activity->name;                             //return the msg
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
    return pop_activity->name;           //return day_tree[0].event
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

Event_content *add_to_ptrlist(Event_content *list,int str_t,int end_t,char* ac,char *pl,char *ot){  //for testing, put thing in ptr altogather
    Event_content *tmp;
    tmp=malloc(sizeof(Event_content));
    tmp->name=malloc(strlen(ac)+1);  //allocate memory for activity
    tmp->place=malloc(strlen(pl)+1);     //allocate memory for place
    tmp->others=malloc(strlen(ot)+1);    //allocate memory for others
    strcpy(tmp->name,ac);
    tmp->start_time=str_t;
    tmp->end_time=end_t;
    strcpy(tmp->place,pl);
    strcpy(tmp->others,ot);
    return tmp;
}
/**************************************priority queue************************************/