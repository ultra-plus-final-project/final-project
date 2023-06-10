#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define A_DAY_HOUR 24
int today;
enum activity_type{WORK, CELEBRATION, LEISURE};
int return_today(){
    return today;
}
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
Event_date *event_date_insert(int month, int date, int command);

void event_content_insert(int month, int date, char *name, int start_time, int end_time, char* place, char* others);

void daily_event(int start_month,int end_month,int start_date,int end_date,char* name,int start_time,int end_time,char* place,char* others);

void print_event_date_list(Event_date *list);

void print_event_content_list(Event_content *list);

void remove_enter(char *sentence);

char ask_event_length(int month, int date);
char ask_event_length();

int check_if_already_have_event(Event_date *date_head,int month,int date,int time)

int isleap(int year);

int find_weekday(int year,int month,int date);
int to_new_day(int curr_date);

int to_new_month(int date);

int search_if_the_time_have_activity(struct event_content *list,int start_time, int end_time, int command);

void print_calendar(int year,int month,int date);

void game_1a2b(int *points_of_master);
void long_term_event(char selection, int month, int date, int start_time, int end_time,  char *name, char *place, char* others);

int check_if_already_have_event(Event_date *date_head,int month,int date);
void game_1a2b(int *points_of_master);

void print_week(int year,int month,int date);

void print_date(int year,int month,int date);

int main() {
    int normal_month_day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int leap_month_day[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    char user_name[50];
    int points_of_master = 0;
    int action;
    int working_hour;
    {//initialize
    printf("Hello master, what should I call you.: ");
    scanf("%s", user_name);
    int year,month,date;
    printf("Hello %s, please enter when do you want to start your calender(e.g. 2025 05 16): ");
    scanf("%d %d %d",&year,&month,&date);
    print_calendar(year,month,date);
    today = 10000 * year + 100 * month + date;
    printf("Next, %s ,What kind of action do you want to do\n", user_name);
    printf(" [1] enter a new event [2] search for an event [3] print out the schedule [4] terminate this day [5] terminate this month.: ");
    scanf("%d", &action);
    }

    if(action == 1){
        printf("Yeah, %s, let's start for buliding an event.\n");
        char name[30];
        char name[30],place[30],others[30],selection;
        int start_month, end_month, start_date, end_date;
        printf("Please enter your event's name(limited in 28 words): ");
        scanf("%29s", name);
        printf("Please enter the start month and date of your event (use spaces to seperate the two numbers, e.g.[10 31]): ");
        scanf("%d %d", &start_month, &start_date);
        printf("Please enter the end month and date of your event (use spaces to seperate the two numbers, e.g.[12 25]: ");
        scanf("%d %d", &end_month, &end_date);
        printf("\n");

        printf("Please enter the place the event takes place (limited in 28 words): ");
        scanf("%29s", place);
        printf("Please enter the things you want to memo for the event (limited in 28 words): ");
        scanf("%29s", others);
        int start_time, end_time;
        bool is_whole_day;
        char temp;
        int remainder;
        printf("Is it a whole day function (Y or N): ");
        scanf(" %c", &temp);
        if(temp == 'Y'){
            start_time = 0000;
            end_time = 2400;
        }
        else if(temp == 'N'){
            printf("What is the start time of the event (using 24-hour clock, e.g.1500): ");
            scanf("%d", &start_time);
            printf("What is the end time of the event (using 24-hour clock, e.g.1500): ");
            scanf("%d", &end_time);
        }
        else printf("Error in setting event's lasting time\n");
        event_content_insert(month, date, name, start_time, end_time, place, others);   
        while(1){
            printf("Is it a whole day function (Y or N): ");
            scanf(" %c", &temp);
            if(temp == 'Y'){
                start_time = 0000;
                end_time = 2400;
                break;
            }
            else if(temp == 'N'){
                printf("What is the start time of the event (using 24-hour clock, e.g.1500): ");
                scanf("%d", &start_time);
                printf("What is the end time of the event (using 24-hour clock, e.g.1500): ");
                scanf("%d", &end_time);
                break;
            }
            else printf("Error in setting event's lasting time\n");
        }
        selection=ask_event_length();
        if(selection=='d'){
            while(1){
            printf("Please enter the start month and date of your event (use spaces to seperate the two numbers, e.g.[10 31]): ");
            scanf("%d %d", &start_month, &start_date);
            printf("Please enter the end month and date of your event (use spaces to seperate the two numbers, e.g.[12 25]: ");
            scanf("%d %d", &end_month, &end_date);
            if(isleap(today/10000)){   
                if((start_date>leap_month_day[start_month-1])||(end_date>leap_month_day[end_month-1])||(start_date<1)||(end_date<1)||(start_month<end_month)){
                    printf("Invalid Input in date.\n");
                }else{
                    break;
                }
            }else{
                if((start_date>normal_month_day[start_month-1])||(end_date>normal_month_day[end_month-1])||(start_date<1)||(end_date<1)||(start_month<end_month)){
                    printf("Invalid Input in date.\n");
                }else{
                    break;
                }
            }
        }
        printf("\n");
        daily_event(start_month, end_month, start_date, end_date, name, start_time, end_time, place, others);
        }else{
            while(1){
                printf("Please enter the start month and date of your event (use spaces to seperate the two numbers, e.g.[10 31]): ");
                scanf("%d %d", &start_month, &start_date);
                if(isleap(today/10000)){   
                    if((start_date>leap_month_day[start_month-1])||(start_date<1)){
                        printf("Invalid Input in date.\n");
                    }else{
                        break;
                    }
                }else{
                    if((start_date>normal_month_day[start_month-1])||(start_date<1)){
                        printf("Invalid Input in date.\n");
                    }else{
                        break;
                    }
                }
            }
            long_term_event(selection, start_month, start_date, start_time, end_time,  name, place,  others);
        }
    }
    else if(action == 2){ //[2] search for an event

    }
    else if(action == 3){ //[3] print out the schedule 
    }
    else if(action == 4){ //[4] terminate this day 
        int ans1;
        printf("How was your day? Congratulate on making it through!\n");
        printf("Did you manage to complete all the tasks for today (Y or N): ");
        scanf("%d", &ans1);
        if(ans1 == 'Y'){
            print("Excellent! Congratulates on scoring 500 points.\n");
            print("Let's play a little game to relax.\n");
            printf("Excellent! Congratulates on scoring 500 points.\n");
            printf("Let's play a little game to relax.\n");
            game_1a2b(&points_of_master);
        }
        else if(ans1 == 'N'){
            print("Don't worry, rest is essential to embark on a longer journey.\n");
            print("You still scored 300 points. Keep up the good work and continue to strive tomorrow.\n");
            printf("Don't worry, rest is essential to embark on a longer journey.\n");
            printf("You still scored 300 points. Keep up the good work and continue to strive tomorrow.\n");
        }
        today = to_new_day(today);
    }
    else if(action == 5){ //[5] terminate this month.: 
        int ans1;
        print("How was your month? Congratulations on making it through!\n");
        printf("How was your month? Congratulations on making it through!\n");
        printf("Did you manage to complete all the tasks for this month (Y or N): ");
        scanf("%d", &ans1);
        if(ans1 == 'Y'){
            print("Excellent! Congratulations on scoring 5000 points.\n");
            print("Let's play a little game to relax.\n");
            printf("Excellent! Congratulations on scoring 5000 points.\n");
            printf("Let's play a little game to relax.\n");
            game_1a2b(&points_of_master);
        }
        else if(ans1 == 'N'){
            print("Don't worry, rest is essential to embark on a longer journey.\n");
            print("You still scored 3000 points. Keep up the good work and continue to strive tomorrow.\n");
            printf("Don't worry, rest is essential to embark on a longer journey.\n");
            printf("You still scored 3000 points. Keep up the good work and continue to strive tomorrow.\n");
        }
        today = to_new_month(today);
    }
}
Event_date *event_date_insert(int start_month, int start_date, int command){
    /* allocate node */
    Event_date *new_event_date = malloc(sizeof(Event_date));
    
    if(new_event_date == NULL){
        printf("Error: malloc failed in event_date_insert\n");
        exit(3);//要不要用return 給使用者機會再輸一次
    }
 
    /* put in the data */
    new_event_date -> month = start_month;
    new_event_date -> date = start_date;
    new_event_date -> event_num = 0;
    new_event_date -> next = NULL;
    new_event_date -> content = NULL;
 
    /* If linked List is empty */
    if(date_head == NULL){
        date_head = new_event_date;
    }
 
    Event_date *date_curr = date_head;
    Event_date *date_prev = NULL;
    while(date_curr != NULL){
        if(date_prev == NULL){
            new_event_date->next = date_curr;
            date_head = new_event_date;
        }
        if(date_curr->month < new_event_date->month){
            new_event_date->next = date_curr;
            date_prev->next = new_event_date;
        }
            
        else if(date_curr->month == new_event_date->month)
            if(date_curr->date < new_event_date->date){
                new_event_date->next = date_curr;
                date_prev->next = new_event_date;
        }
                
        date_prev = date_curr;
        date_curr = date_curr->next;
    }
    if(date_curr == NULL) date_prev->next = new_event_date;
    if(command == 1) return new_event_date;
}
Event_date *find_current_date(int start_month, int start_date){
    Event_date *tmp = date_head;
    while(tmp != NULL){
        if((tmp->month == start_month) && (tmp->month == start_date)) return tmp;
        else tmp = tmp->next;
    }
    if(tmp == NULL) return NULL;
    
}
void event_content_insert(int month, int date, char *name, int start_time, int end_time, char* place, char* others){
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
void print_event_date_list(Event_date *list){
  /* print start point for testing */
    while(list != NULL){
        printf(":: %d %d\n",list->month, list->date);
        list = list -> next;
    }
}
void print_event_content_list(Event_content *list){
    /* print time for testing */
    while(list != NULL){
        printf("%s: %d %d\n", list -> name, list -> start_time, list -> end_time);
        list = list -> next;
    }
}
void remove_enter(char *sentence){
    /* deal with '\0' */
    char *str = sentence;
    for(; *str && *str != '\n'; str++);
    if(*str == '\n') *str = '\0';
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
void print_calendar(int year,int month,int date){
    //system("CLS");
    int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int d=find_weekday(year,month,date);
    printf("  SUN  MON  TUE  WED  TUE  FRI  SAT \n");
    printf("+----+----+----+----+----+----+----+\n");
    printf("|");
    for(int i=0;i<d;++i){
        printf("    |");
    }
    for(int i=1;i<=day[month-1];++i){
        d=find_weekday(year,month,i);
        printf(" %2d |",i);
        if(d==6){
            printf("\n");
            printf("|....|....|....|....|....|....|....|\n");
            printf("+----+----+----+----+----+----+----+\n");
            printf("|");
        }
    }
    if(month == 2 && isleap(year) == 1){
        printf(" %2d  \n");//what is "%d" here
    }else if(d == 6){
        printf("\n");
    }else{
        printf("\n");
        printf("|....|....|....|....|....|....|....|\n");
        printf("+----+----+----+----+----+----+----+\n");
    }
    return;
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
void search_all_day_free_time(struct event_content *ptr){                //consider ptr sorted
    int free_time_str = 0;
    struct event_content *tmp = ptr;
    while((tmp != NULL)){
        if(free_time_str < (ptr->start_time)){                     //if free time is smaller than the first activity's star time, it is free    
            printf("You have free time from %d to %d.\n"
            ,free_time_str, ptr->start_time);                     //have the free time till the closest activity start
        }
        free_time_str = ptr->end_time;                            //set the free time start count point at the end of the activity
        tmp = tmp->next;                                          //go to the next closest activity
    }
    if(free_time_str < A_DAY_HOUR){
        printf("You have free time from %d to %d.\n", free_time_str, A_DAY_HOUR);                                  //if no more activity, it is free till 24
    }       
}
void search_scheduled_time_through_activity(struct event_content *list, char *activity_name){
    /*
    This function is to look for the time when the activity takes place.
    1. look through the list and find the activity
        (1) if it finds, it will print out the time the activity starts and ends.
        (2) if not, it will print no-message.
    */
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
        fprintf(output_file,"%d. %d/%d %d-%d %s,%s,%s\n",ptr->event_num,\
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
void long_term_event(char selection, int month, int date, int start_time, int end_time,  char *name, char *place, char* others){
    int normal_month_day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int leap_month_day[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    int year=((today/10000)+1);
    static int this_year=year;       //only declare this_year=year once
    if(this_year==(today/10000)){  //if this year == year
            while(annual_activity!=NULL){  //put every event in the annual_activity list into the event list
                event_date_insert(annual_activity->month,annual_activity->date,0);
                event_content_insert(annual_activity->month,annual_activity->date,annual_activity->content->name,annual_activity->content->start_time,annual_activity->content->end_time,annual_activity->content->place,annual_activity->content->others);
                annual_activity=annual_activity->next;
            }
            this_year++;  //this_year+1, so the events won't be add again till next year
        }
    int deflaw=1;
    while(deflaw){     
       selection=ask_event_length(month,date);
        }   
        switch(selection){
            case 'w':                                           // if is week, insert activity after every seven days
                   if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){ //if big month
                        for(int i=date;i<31;i+=7){
                            if(check_if_already_have_event_w(date_head,month,i)){
                                event_date_insert(month,i/*date*/,0)
                            if(check_if_already_have_event(date_head,month,i,start_time)){
                                event_date_insert(month,i/*date*/,0);
                                event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                        }
                   }else if(month==4||month==6||month==9||month==11){ //if small month
                        for(int i=date;i<30;i+=7){
                           if(check_if_already_have_event_w(date_head,month,i)){
                                event_date_insert(month,i/*date*/,0)
                           if(check_if_already_have_event(date_head,month,i,start_time)){
                                event_date_insert(month,i/*date*/,0);
                                event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                        }
                   }else if(event_date_list->strt_month==2){    //if feb
                   }else if(month==2){    //if feb
                        if(isleap(today/10000)){              //leap year
                            for(int i=event_date_list->strt_day;i<29;i+=7){
                                if(check_if_already_have_event_w(date_head,month,i)){
                                    event_date_insert(month,i/*date*/,0)
                            for(int i=date;i<29;i+=7){
                                if(check_if_already_have_event(date_head,month,i,start_time)){
                                    event_date_insert(month,i/*date*/,0);
                                    event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                            }
                        }else{                                  //normal year
                            for(int i=event_date_list->strt_day;i<30;i+=7){
                                if(check_if_already_have_event_w(date_head,month,i)){
                                    event_date_insert(month,i/*date*/,0)
                            for(int i=date;i<30;i+=7){
                                if(check_if_already_have_event(date_head,month,i,start_time)){
                                    event_date_insert(month,i/*date*/,0);
                                    event_content_insert(month,i/*date*/,name,start_time,end_time,place,others);
                            }
                            }
                        }
                   }
                    deflaw=0;
                    break;
            case 'm':                                           //if is a monthy activity
                    for(int i=my_schedule->month;i<12;i++){  
                    for(int i=month;i<12;i++){  
                        if(isleap(i)){
                            if(date<=leap_month_day[i-1]){
                                if(check_if_already_have_event(date_head,i,date)){
                                    event_date_insert(i/*month*/,date);                               //every month same date
                                if(check_if_already_have_event(date_head,i,date,start_time)){
                                    event_date_insert(i/*month*/,date,0);                               //every month same date
                                     event_content_insert(i/*month*/,date,name,start_time,end_time,place,others);
                                }
                            }
                        }else{
                            if(date<=normal_month_day[i-1]){
                                if(check_if_already_have_event(date_head,i,date)){
                                    event_date_insert(i/*month*/, date);                               //every month same date
                                if(check_if_already_have_event(date_head,i,date,start_time)){
                                    event_date_insert(i/*month*/, date,0);                               //every month same date
                                    event_content_insert(i/*month*/,date,name,start_time,end_time,place,others);
                                }
                            }
                        }  
                    }
                    deflaw=0;
                    break;   
           case 'y':                                          //if is an annual event                  
                    if(check_if_already_have_event(date_head,month,date)){
                    if(check_if_already_have_event(date_head,month,date,start_time)){
                        annual_activity=add_to_list(annual_activity,month,date,start_time,end_time,name,place,others); //add the event into annual_activity list
                        event_date_insert(month, date);                               //every month same date
                        event_date_insert(month, date,0);                               //every month same date
                        event_content_insert(month,date,name,start_time,end_time,place,others);
                    }
                    deflaw=0;
                    break;
            case 'n':                                            //if not long term activity, just insert
                    if(check_if_already_have_event(date_head,month,date)){
                        event_date_insert(month, date); //******************************
                    if(check_if_already_have_event(date_head,month,date,start_time)){
                        event_date_insert(month, date,0); //******************************
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
char ask_event_length(){
    char selection;
     printf("This activity a weekly event (press w), a monthly event (press m), a annual event (press y), or none of them (press n)\n");           //ask whether and which long term type
    while(1){
        printf("This activity a daily event (press d), weekly event (press w), a monthly event (press m), a annual event (press y), or none of them (press n)\n");           //ask whether and which long term type
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
        if(selection!='d'&&selection!='w'&&selection!='m'&&selection!='y'&&selection!='n'){
            printf("Invalid Input in selection!!!\n");
        }else{
            break;
        }
    }
    return selection;                                //select type
}

int check_if_already_have_event(Event_date *date_head,int month,int date){    //check if there is already event ont the day
int check_if_already_have_event(Event_date *date_head,int month,int date,time){    //check if there is already event ont the day
    while(date_head!=NULL){
        if(date_head->start_month==month&&date_head->start_date==date){
        if(date_head->month==month&&date_head->date==date){
            break;
        }
        date_head=date_head->next;
    }
    if(date_head!=NULL){
        Event_content tmp;
        Event_content *tmp;
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
        if(date_head->month==month&&date_head->date==date){
            break;
        }
        date_head=date_head->next;
    }
    if(date_head==NULL){
        printf("You don't have activity at the time\n");
    }else{
        Event_content tmp;
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
                    if(check_if_already_have_event_w(date_head,i/*month*/,j/*date*/)){
                        event_date_insert(i/*month*/,j/*date*/,0);
                        event_content_insert(i/*month*/,j/*date*/,name,start_time,end_time,place,others);
                    }
                }
            }else{
                 for(int j=(i==start_month? start_date: 1);j<=(i==end_month? end_date : normal_month_day[i-1]);j++){
                    if(check_if_already_have_event_w(date_head,i/*month*/,j/*date*/)){
                        event_date_insert(i/*month*/,j/*date*/,0);
                        event_content_insert(i/*month*/,j/*date*/,name,start_time,end_time,place,others);
                    }
                }

            }
        }
    }else{
        for(int j=start_date;j<=end_date;j++){
            if(check_if_already_have_event_w(date_head,start_month,j)){
                event_date_insert(start_month,j/*date*/,0);
                event_content_insert(start_month,j/*date*/,name,start_time,end_time,place,others);
            }
        }

    }
}

/**************************************priority queue************************************/
struct priority_queue{
    int time;
    Event_content *event;              //put ptr,which stores all info including month, date...
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
    pop_activity=malloc(sizeof(Event_content));
    if (tree_size<=0) {                               //if tree_size<=0, no more event
        Event_content *no_activity=malloc(sizeof(Event_content));
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
void push(struct priority_queue *day_tree, int strt_time, Event_content *list ){
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

    

    
    
    
    
/*******************************UI**********************************/
    
void print_week(int year,int month,int date){
    int day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    system("CLS");
    Event_date *cur = find_current_date(month,date);
    printf("         %4d         %2d         \n",year,month);
    printf("  SUN  MON  TUE  WED  TUE  FRI  SAT \n");
    printf("+----+----+----+----+----+----+----+\n");
    int d = find_weekday(year,month,date);
    printf("|");
    for(int i = date - d ; i < date - d + 7  ; ++i){
        if(i <= 0){
            printf(" %2d |", i + day[month-2]);
        }else if(i > day[month-1]){
            printf(" %2d |",i - day[month-1]);
        }else{
            printf(" %2d |",i);
        }
    }
    printf("\n|");
    for(int i = date - d ; i < date - d + 7  ; ++i){
        if(i < date){
            printf("    |");
            continue;
        }else{
            switch (cur -> event_num){
            case 0:
                printf("    |");
                break;
            case 1:
                printf(".   |");
                break;
            case 2:
                printf("..  |");
                break;
            case 3:
                printf("... |");
                break;
            default:
                printf("....|");
                break;
            }
        }
        cur = cur -> next;
    }
    printf("\n");
    printf("+----+----+----+----+----+----+----+\n");
    return;
}
    
void print_date(int year,int month,int date){
    Event_date *cur = find_current_date(month,date);
    //system("cls");  //我不知道為什麼把這行註解就可以過了
    printf("   %4d   %2d   %2d   \n",year,month,date);
    Event_content *cur_event = cur->content;
    int A[24]={0};
    while(cur_event != NULL){
        for(int i = cur_event->start_time ; i <= cur_event->end_time ; ++i){
            A[i]=1;
        }
        cur_event = cur_event->next;
    }
    cur_event = cur->content;
    for(int i = 0;i <= 23; ++i){
        printf("%2d------------------\n",i);
        if(A[i]==0){
            printf("                    \n");
        }else{
            printf(".%-18s*\n",cur_event->name);
            if(i == cur_event->end_time){
                cur_event = cur_event->next;
            }
        }
    }
    printf("24------------------\n");
    return;
}
