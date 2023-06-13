#include "basic.h"

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
    Event_date *cur_date = find_current_date(month, date);
    cur_date -> event_num++;
    if(cur_date == NULL){
        cur_date = event_date_insert(month, date, 1);
    }
    else if(search_if_the_time_have_activity(cur_date->content, start_time, end_time, 1)==1) return;
    //printf("okok");
    Event_content *new_event_content = malloc(sizeof(Event_content));
    new_event_content -> name = malloc(30);
    new_event_content -> place = malloc(30);
    new_event_content -> others = malloc(30);
    Event_content *content_head = cur_date->content;
    Event_content *curr = content_head;
    Event_content *prev = NULL;
    //printf("okok");

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

    hash_table_insert(new_event_content);
    //print_table();

    if(content_head == NULL){ //If linked List is empty
        cur_date->content = new_event_content;
        //printf("okok");
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
    }
}   

Event_date *delete_date(int month, int date){ //month and date stand for target dates
    Event_date *tmp;
    tmp->month = month;
    tmp->date = date;

    Event_date *date_curr = date_head;
    Event_date *date_prev = NULL;

    while(date_curr != NULL){
        if(date_prev == NULL && date_curr->month < month){
            date_head = date_curr->next;
        }

        if(date_curr->month < month){
            date_prev->next = date_curr->next;
        }
            
        else if(date_curr->month == month)
            if(date_curr->date < date){
                date_prev->next = date_curr->next;
        }
                
        date_prev = date_curr;
        date_curr = date_curr->next;
    }
    if(date_curr == NULL) return NULL;
    else return tmp;
}

Event_content *delete_content(Event_date *cur_date, char *name){
    Event_content *tmp;
    tmp->name = name;

    Event_content *content_head = cur_date->content;
    Event_content *content_curr = content_head;
    Event_content *content_prev = NULL;

    while(content_curr != NULL){
        if(content_prev == NULL && strcmp(content_curr->name, name) == 0){
            cur_date->content = content_curr->next;
        }
        else if(strcmp(content_curr->name, name) == 0){
            content_prev->next = content_curr->next;
        }
                
        content_prev = content_curr;
        content_curr = content_curr->next;
    }
    if(content_curr == NULL) return NULL;
    else return tmp;
}

void remove_enter(char *sentence){
    /* deal with '\0' */
    char *str = sentence;
    for(; *str && *str != '\n'; str++);
    if(*str == '\n') *str = '\0';
}

//This function will return the value 1 if the year is a leap year
//, and return the value 0 if the year is not a leap year.
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

int to_new_day(int curr_date){
    int year = curr_date / 10000;
    int day = curr_date % 100;
    int month = (curr_date % 10000) /100;

    if(day < 28) return curr_date+1;
    else if(day == 28){
        if(month == 2){
            if(isleap(year)) return curr_date+1;
            else return curr_date - 28 + 101;
        }
        else return curr_date+1;
    }
    else if(day == 29){
        if(isleap(year)) return curr_date - 29 + 101;
        else return curr_date+1;
    }    
    else if(day == 30){
        if(((month == 1 || month == 3) || (month == 5 || month == 7)) || ((month == 8 || month == 10) || month == 12)) return curr_date + 1;
        else return curr_date - 30 + 101;
    }
    else if(month == 12) return curr_date - 1231 + 10001;
    else return curr_date - 31 + 101;
}

int to_new_month(int date){
    date -= date % 100;
    if(date%10000 == 1200) return date - 1200 + 10101;
    return date + 101;
}

void game_1a2b(int *points_of_master){
    int play = 0;
    while(1){
        printf("\n");
        printf("\033[1;37;43m1A2B is a puzzle game.\n");
        printf("If the number what you guess is in the right place then you get 1A.\n");
        printf("If the number is in the number but not in the right place would get 1B.\n");
        printf("If you can guess the correct number less than or equal to 9 times, \n");
        printf("you can get random points from 2,000 to 200,000\n");
        printf("Do you want to play 1A2B ? (No: 0/ Yes: 1) : \033[m");
        scanf("%d", &play);
        if(play == 1) break;
        else if(play == 0) return;
        else{
            printf("Invalid Input!!!\n");
        }
    }
    int answer[4];  // Array to store the answer
    for(int i = 0; i < 4; i++){
        while(1){
            answer[i] = rand() % 10; // Generate a random number between 0 and 9
            bool is_the_same = false;
            for(int j = 0; j < i; j++){
                if(answer[j] == answer[i]){
                    is_the_same = true;
                }
            }
            if(is_the_same == false) break; 
        }
    }

    int guess_count = 0;
    char guess_number[100];
    while(guess_count < 20){
        printf("This is your %dth guess : ", guess_count + 1);
        scanf("%s", &guess_number);
        if(strlen(guess_number) != 4){
            printf("Invalid Input!!!\n");
            printf("\033[37;41mNotice the length must be 4 digits.\033[m\n");
            continue;
        }
        bool is_all_digit = true;
        for(int i = 0 ; i < 4; i++){
            if(guess_number[i] >= '0' && guess_number[i] <= '9'){
                guess_number[i] -= 48; // Convert character to integer by subtracting ASCII value of '0'
            }
            else{
                is_all_digit = false;
            }
        }
        if(is_all_digit == false){
            printf("Invalid Input!!!\n");
            printf("\033[37;41mYou must input a 4 digit number.\033[m\n");
            continue;
        }
        bool have_same_number = false;
        for(int i = 0; i < 3; i++){
            for(int j = i + 1; j < 4; j++){
                if(guess_number[i] == guess_number[j]) have_same_number = true;
            }
        }
        if(have_same_number == true){
            printf("Invalid Input!!!\n");
            printf("\033[37;41mThe four digits must be different.\033[m\n");
            continue;
        }
        int A_num = 0, B_num = 0;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(guess_number[i] == answer[j]){
                    if(i == j) A_num++;
                    else B_num++;
                }
            }
        }
        if(A_num == 4){
            printf("All correct.\n");
            int prize = ((rand() % 100) + 1) * 1000;
            *points_of_master += prize;
            printf("You win %d points.\n", prize);
            return;
        }
        else{
            printf("%dA%dB\n", A_num, B_num);
            guess_count++;
        }
    }
    printf("You have been no chance already.\n");
}

void long_term_event(char selection, int month, int date, int start_time, int end_time,  char *name, char *place, char* others){
    int normal_month_day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int leap_month_day[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    if(this_year==(today/10000)){  //if this year == year
            while(annual_activity!=NULL){  //put every event in the annual_activity list into the event list
                event_content_insert(annual_activity->month,annual_activity->date,annual_activity->content->name,annual_activity->content->start_time,annual_activity->content->end_time,annual_activity->content->place,annual_activity->content->others);
                annual_activity=annual_activity->next;
            }
            this_year++;  //this_year+1, so the events won't be add again till next year
        }
        switch(selection){
            case 'w':                                           // if is week, insert activity after every seven days
                   if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){ //if big month
                        for(int i=date;i<31;i+=7){
                            if(check_if_already_have_event(date_head,month,i,start_time, end_time)){
                                event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                        }
                   }else if(month==4||month==6||month==9||month==11){ //if small month
                        for(int i=date;i<30;i+=7){
                            if(check_if_already_have_event(date_head,month,i,start_time, end_time)){
                                event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                        }
                   }else if(month==2){    //if feb
                        if(isleap(today/10000)){              //leap year
                            for(int i=date;i<29;i+=7){
                                if(check_if_already_have_event(date_head,month,i,start_time, end_time)){
                                    event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                            }
                        }else{                                  //normal year
                            for(int i=date;i<30;i+=7){
                                if(check_if_already_have_event(date_head,month,i,start_time, end_time)){
                                    event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                            }
                        }
                    }
                    break;
            case 'm':                                           //if is a monthy activity
                    for(int i=month;i<12;i++){  
                        if(isleap(i)){
                            if(date<=leap_month_day[i-1]){
                                if(check_if_already_have_event(date_head,i,date,start_time, end_time)){
                                    event_content_insert(i/*month*/,date,name,start_time,end_time,place,others); //every month same date
                                }
                            }
                        }else{
                            if(date<=normal_month_day[i-1]){
                                if(check_if_already_have_event(date_head,i,date,start_time, end_time)){                           
                                    event_content_insert(i/*month*/,date,name,start_time,end_time,place,others);  //every month same date
                                }
                            }
                        }  
                    }
                    break;
           case 'y':                                          //if is an annual event                  
                    if(check_if_already_have_event(date_head,month,date,start_time, end_time)){
                        annual_activity=add_to_list(annual_activity,month,date,start_time,end_time,name,place,others); //add the event into annual_activity list                      
                        event_content_insert(month,date,name,start_time,end_time,place,others); //every month same date
                    }
                    break;
            case 'n':                                            //if not long term activity, just insert
                    if(check_if_already_have_event(date_head,month,date,start_time, end_time)){
                        event_content_insert(month,date,name,start_time,end_time,place,others);
                    }
                    break;
        }
        write_content_on_file(date_head);
}

char ask_event_length(){
    char selection;
    while(1){
        printf("This activity a daily event (press d), weekly event (press w), a monthly event (press m), a annual event (press y), or none of them (press n)\n");           //ask whether and which long term type
        scanf(" %c",&selection); 
        if(selection!='d'&&selection!='w'&&selection!='m'&&selection!='y'&&selection!='n'){
            printf("Invalid Input in selection!!!\n");
        }else{
            break;
        }
    }
    return selection;                                //select type
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
                break;
            }
            tmp=tmp->next;
        }
    }
    return 1;
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
            if(check_if_already_have_event(date_head,start_month,j,start_time, end_time)){
                event_content_insert(start_month,j/*date*/,name,start_time,end_time,place,others);
            }
        }

    }
    write_content_on_file(date_head);
}

int get_content_from_file(Event_date *ptr) {                        //get content from file(**while(ptr->next!=NULL){ptr=ptr->next;})
    FILE *input_file;     
    input_file=fopen("file_io.txt", "r");                           //connect input_file to input.txt (read only)
    if (input_file == NULL) {
        //printf("Error opening input file!\n");
        input_file = fopen("file_io.txt", "w+");                    //create a new empty file if can't find one to read
        if (input_file == NULL) {
            printf("Error creating input file!\n");
            return 0;
        }
    }
    char line[350]; 
    memset(line,'\0', sizeof(line));                                  
    while (fgets(line, sizeof(line), input_file) != NULL) {        //put a line of input_file into line 
        sscanf(line,"%d. %d/%d %d-%d",                          //distribute the things in line to ptr
               &(ptr->event_num),&(ptr->month), &(ptr->date),
              &(ptr->content->start_time),&(ptr->content->end_time));
        char *token;
        Event_content *tmp_content = ptr-> content;
        tmp_content = malloc(sizeof(Event_content));
        token=strtok(line,",");                                 //split the strings using commas as separators
        if (token!=NULL) {
            tmp_content->name=malloc(sizeof(token)+1);
            tmp_content->name=strdup(token);                        //activity is the first string before ","
        }
        token=strtok(NULL,",");                                //split the strings using commas as separators
        if (token!=NULL) {
            tmp_content->place=malloc(sizeof(token)+1);
            tmp_content->place=strdup(token);                         //place is the second string before ","
        }

        token=strtok(NULL,",");                              //split the strings using commas as separators
        if (token!=NULL) {
            tmp_content->others=malloc(sizeof(token)+1);
            tmp_content->others=strdup(token);                       //others is the first string before ","
        }
        ptr->next=(Event_date*)malloc(sizeof(Event_date));  //allocate memory for the next node
        ptr=ptr->next; 
        ptr=malloc(sizeof(Event_date));                                     //move to the next node
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
        output_file = fopen("file_io.txt", "w+");
        if (output_file == NULL) {
            printf("Error creating output file!\n");
            return 1;
        }
    }
    while(ptr!=NULL){   //put info into file
        Event_content *tmp_content=ptr->content;   
        for(int i=1;i<=ptr->event_num;i++){
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
