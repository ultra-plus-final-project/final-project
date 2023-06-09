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

Event_date *event_date_insert(int month, int date);

void event_content_insert(int start_month, int end_month, int start_date, int end_date, char *name, int start_time, int end_time, int remainder);

void print_event_date_list(Event_date *list);

void print_event_content_list(Event_content *list);

void remove_enter(char *sentence);

int isleap(int year);

int find_weekday(int year,int month,int date);

int to_new_day(int curr_date);

int to_new_month(int date);

void print_calendar(int year,int month,int date);

void game_1a2b(int *points_of_master);

int main() {
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
        int start_month, end_month, start_date, end_date;
        printf("Please enter your event's name(limited in 28 words): ");
        scanf("%29s", name);
        printf("Please enter the start month and date of your event (use spaces to seperate the two numbers, e.g.[10 31]): ");
        scanf("%d %d", &start_month, &start_date);
        printf("Please enter the end month and date of your event (use spaces to seperate the two numbers, e.g.[12 25]: ");
        scanf("%d %d", &end_month, &end_date);
        printf("\n");
        
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
        event_content_insert(start_month, end_month, start_date, end_date, name, start_time, end_time, remainder);   
    }
    else if(action == 2){ //[2] search for an event

    }
    else if(action == 3){ //[3] print out the schedule 

    }
    else if(action == 4){ //[4] terminate this day 
        int ans1;
        print("How was your day? Congratulations on making it through!\n");
        printf("Did you manage to complete all the tasks for today (Y or N): ");
        scanf("%d", &ans1);
        if(ans1 == 'Y'){
            print("Excellent! Congratulations on scoring 500 points.\n");
            print("Let's play a little game to relax.\n");
            game_1a2b(points_of_master);
        }
        else if(ans1 == 'N'){
            print("Don't worry, rest is essential to embark on a longer journey.\n");
            print("You still scored 300 points. Keep up the good work and continue to strive tomorrow.\n");
        }
        today = to_new_day(today);
    }
    else if(action == 5){ //[5] terminate this month.: 
        int ans1;
        print("How was your month? Congratulations on making it through!\n");
        printf("Did you manage to complete all the tasks for this month (Y or N): ");
        scanf("%d", &ans1);
        if(ans1 == 'Y'){
            print("Excellent! Congratulations on scoring 5000 points.\n");
            print("Let's play a little game to relax.\n");
            game_1a2b(points_of_master);
        }
        else if(ans1 == 'N'){
            print("Don't worry, rest is essential to embark on a longer journey.\n");
            print("You still scored 3000 points. Keep up the good work and continue to strive tomorrow.\n");
        }
        today = to_new_month(today);
    }

}


Event_date *event_date_insert(int start_month, int start_date, int command){
    /* allocate node */
    Event_date *new_event_date = malloc(sizeof(struct event_date));
    
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

void event_content_insert(int start_month, int end_month, int start_date, int end_date, char *name, int start_time, int end_time){
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
            invalid_input_message();
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
            invalid_input_message();
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
            invalid_input_message();
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
            invalid_input_message();
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
    while(date_head != NULL){
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

struct event_content *annual_activity;

void long_term_event(struct event_content *event_date_list, int month, int date, bool whole_day, bool alert, char *name, int start_time, int end_time, char *place, int remainder, int today){
    /*
    This function is to help user repeat the function automatically.
    1. It will receive a character representing four periods of time.
        (1) w: weekly (2) m: monthly (3) a: annually” and (4) n: do not repeat
    2. It will then put the event into the schedule automatically in different periods of time that user prefers.
    3. when it comes to the annual event
        (1) the function will insert the event into the date of the year and the annual_activity list, which is a global variable.
        (2) As there is a static declaration of “this_year” that will only be declared once,
    each time the function is called, the function will check if “this_year” equals “year”. If the equality is true, every activity in the annual_activity list will be inserted into the event list, and plus one to “this_year”, so that the activities won’t be added again until the next year.

    */
    
    char selection;
    int normal_month_day[12]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int leap_month_day[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    if(isleap(today / 10000)){   //default of improper input of date
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
    
    static int this_year= ((today/10000) + 1); //the program will only declare this_year=year once
    if(this_year == (today / 10000)){  //if this year == year
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
                   if(((month==1||month==3) || (month==5||month==7)) || ((month==8||month==10) || month==12)){ //if big month
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
    struct event_content *event;              //put ptr,which stores all info including month, date...
};
int tree_size=0;                      //global variable trace size of tree
struct priority_queue day_tree[100];  //only for the schedule of a day
void swap(struct priority_queue *a,struct priority_queue *b) {  //swap info in day_tree
   struct priority_queue temp=*a;
    *a=*b;
    *b=temp;
}
struct event_content *pop(struct  priority_queue *day_tree){   //pop out the smallest time's event name
    struct event_content *pop_activity=NULL;                   //store the ptr being popping out
    pop_activity=malloc(sizeof(struct event_content));
    if (tree_size<=0) {                               //if tree_size<=0, no more event
        struct event_content *no_activity=malloc(sizeof(struct event_content));
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
        if((rightChild<tree_size)&&(day_tree[rightChild].time>day_tree[smallest].time)){//R_child is not over the bound(size)&&the time of [small] is bigger, then the [small] should "sink" into the lower(further away from being print)
        if((rightChild<tree_size)&&(day_tree[rightChild].time<day_tree[smallest].time)){//R_child is not over the bound(size)&&the time of [small] is bigger, then the [small] should "sink" into the lower(further away from being print)
            smallest=rightChild;
        }
        if(smallest!=currentIndex){                               //exchange the content
        if(smallest!=currentIndex){                               //exchange the content if the former last array is not yet in the right place that is smaller than its children
            swap(&day_tree[currentIndex],&day_tree[smallest]); 
            currentIndex=smallest;
        }else{                                                     //when the first([0],root) is the smallest time, stop
        }else{                                                     //when the the former last is no longer bigger than any of its children
            break;                     
        }
    }
    return pop_activity;           //return day_tree[0].event
}
void push(struct priority_queue *day_tree, int strt_time, struct event_content *list ){
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
    }else{                                                    //do the  "float" and "sink" same as pop
    }else{                                                    //do the  "float" and "sink" same as pop and push
        int currentIndex=i;
        int parentIndex=(currentIndex-1)/2;
        if ((currentIndex>0)&&(day_tree[currentIndex].time<day_tree[parentIndex].time)) {     //if the time replacing the user_enter_time is smaller than parent
            while (currentIndex>0&&day_tree[currentIndex].time<day_tree[parentIndex].time) {
        if ((currentIndex>0)&&(day_tree[currentIndex].time<day_tree[parentIndex].time)) {     //do same as push when the one being delete is not root, and see if the time replacing the user_enter_time is smaller than parent
            while(currentIndex>0&&day_tree[currentIndex].time<day_tree[parentIndex].time) {
                swap(&day_tree[currentIndex],&day_tree[parentIndex]);                           //keep exchane till bigger than parent
                currentIndex=parentIndex;
                parentIndex=(currentIndex-1)/2;
            }
        } else {
            while (1) {
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

