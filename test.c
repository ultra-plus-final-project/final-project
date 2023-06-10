void daily_event(int start_month,int end_month,int start_date,int end_date,char* name,int start_time,int end_time,char* place,char* others){
    int normal_month_day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int leap_month_day[12]={31,29,31,30,31,30,31,31,30,31,30,31};
    if(isleap(today/10000)){                                            //if is leap year
        while(start_date>leap_month_day[start_month-1]||start_date<1){  //if input date has wrong
            printf("Invalid Input in start date!!!\n");
            printf("Please enter the start date again.\n");
            scanf("%d",&start_date);
        }
        while(end_date>leap_month_day[end_month-1]||end_date<1){
            printf("Invalid Input in end date!!!\n");
            printf("Please enter the end date again.\n");
            scanf("%d",&end_date);
        }
    }else{                                                              //if is normal year
        while(start_date>normal_month_day[start_month-1]||start_date<1){ //if input date has wrong
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
    if(start_month!=end_month){                               //if it is a long term daily across months
        for(int i=start_month;i<=end_month;i++){
            if(isleap(today/10000)){                       //if is leap year
                for(int j=(i==start_month? start_date: 1);j<=(i==end_month? end_date : leap_month_day[i-1]);j++){
                    if(check_if_already_have_event(date_head,i/*month*/,j/*date*/,start_time)){ //check if have planned
                        event_date_insert(i/*month*/,j/*date*/,0);
                        event_content_insert(i/*month*/,j/*date*/,name,start_time,end_time,place,others);
                    }
                }
            }else{                                         //if is normal year
                 for(int j=(i==start_month? start_date: 1);j<=(i==end_month? end_date : normal_month_day[i-1]);j++){
                    if(check_if_already_have_event(date_head,i/*month*/,j/*date*/,start_time)){
                        event_date_insert(i/*month*/,j/*date*/,0);
                        event_content_insert(i/*month*/,j/*date*/,name,start_time,end_time,place,others);
                    }
                }

            }
        }
    }else{                        //if is not across-month-daily-event
        for(int j=start_date;j<=end_date;j++){
            if(check_if_already_have_event(date_head,start_month,j,start_time)){
                event_date_insert(start_month,j/*date*/,0);      //month stay same, only mend date
                event_content_insert(start_month,j/*date*/,name,start_time,end_time,place,others);
            }
        }

    }
}
