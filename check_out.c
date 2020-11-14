#include <stdio.h>
#include <string.h>
#include "common.h"

void checkout(char *party_array[]);

//temporary values
char bookingID[6][30] = {"barnes1","smith2","james3","johnson4","richardson5","bailey6"};

//board_type = board type of each room &
//room_num

void checkout(char *party_array[]){
    //variables
    char input_bookingID[50];//the booking id that the user inputs
    char user_bookingID[30];//stores the booking ID of the current user

    //loop variables
    int i,x;
    int room_num=0;//temporary storage of one of the users room numbers
    float total_cost=0;//stores the total cost of the users stay
    int index=0;//stores the index of party_array that the users data is in
    int age=0;//stores the age of the booker
    float room_cost=0,board_cost=0,wakeupcall_cost=0,discount=0;

    //enter booking id and validate it
    printf("enter your booking ID");
    gets(input_bookingID);
    for(i=0;i<6;i++){
        if(strcmp(input_bookingID,bookingID[parties_arr[i].booking_id]) == 0){
            index = i;
        }
    }

    int len_stay = parties_arr[index].stay_ln;
    int num_adults = parties_arr[index].a_num;
    int num_children = parties_arr[index].c_num;

    //calculate the cost of the rooms used
    for(i=0;i<6;i++){
        //if the room number is > 1
        if(party_array[index+7][i]>0){
            room_num = party_array[index+7][i];
            //finds cost for this particular room
            room_cost = room_arr[room_num - 1][2];
        }
    }

    //splits current date and date of birth into dd mm yyyy
    //current dd mm yyyy
    int current_date = 10112020;
    int year=current_date,month=current_date,date=current_date;

    //year
    do{
        year = year-10000;
    }while(year>9999);

    //month
    do{
        month = month-1000000;
    }while(month>999999);
    month= (month-year)/1000;

    //date
    date = (date-month-year)/1000000;



    //birthday dd mm yyyy
    int dob_ddmmyyyy = party_array[1][index];
    int dob_year=dob_ddmmyyyy,dob_month=dob_ddmmyyyy,dob_date=dob_ddmmyyyy;

    //year
    do{
        dob_year = dob_year-10000;
    }while(dob_year>9999);

    //month
    do{
        dob_month = dob_month-1000000;
    }while(dob_month>999999);
    dob_month= (dob_month-dob_year)/1000;

    //date
    dob_date = (dob_date-dob_month-dob_year)/1000000;



    //calculates if over 65
    if(year-dob_year > 65){
        age = 65;
        //if over 65 room rate is 10%less
        room_cost = room_cost*0.9;
        discount = room_cost*0.1;
    }
    else if(year-dob_year == 65){
        if(dob_month <= month){
            if(dob_date <= date){
                age = 65;
                //if over 65 room rate is 10%less
                room_cost = room_cost*0.9;
                discount = room_cost*0.1;
            }
        }
    }




    //calculate cost of board
    if(party_array[4][index] == 0){//if board type is full board
        board_cost = board_cost + (20*len_stay*num_adults) + (10*len_stay*num_children);
        discount = (10*len_stay*num_children);
    }
    else if(party_array[4][index] == 1){//if board type is half board
        board_cost = board_cost + (15*len_stay*num_adults) + (7.5*len_stay*num_children);
        discount = (7.5*len_stay*num_children);
    }
    else if(party_array[4][index] == 0){//if board type is full board
        board_cost = board_cost + (5*len_stay*num_adults) + (2.5*len_stay*num_children);
        discount = (2.5*len_stay*num_children);
    }


    //daily wakup calls?
    //1 = true
    if(party_array[5][index]==1){
        wakeupcall_cost = wakeupcall_cost + 5;
    }


    //calculate total cost
    total_cost = room_cost + board_cost + wakeupcall_cost;

    //print bill
    printf("\n\n\n\n\n\n\n\n\n\nBooking ID: %s\n\nCOSTS:\nRoom Cost: %f\nBoard Cost:%f\n",input_bookingID,room_cost,board_cost);
    if(wakeupcall_cost>0){
        printf("Wakeup Call Cost:%f\n",wakeupcall_cost);
    }
    if(discount > 0){
        printf("\nDISCOUNT TOTAL: %f",discount);
    }


}