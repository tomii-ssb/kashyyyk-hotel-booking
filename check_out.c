#include <stdio.h>
#include <string.h>
#include "common.h"
/*========================================================================================================
 NOTE TO TOMMY:
 the errors are due to me having removed the temporary global variables that were in my code,
 once you paste this into your code there should be zero errors.

 The current errors should only be due to:
 -party_array not being declared
 -bookingID not being declared
 -rooms_arr not being declared
 ========================================================================================================*/

 /*** KNOWN BUGS

 ***/

//function declarations
void checkout();



int main() {
    checkout();
    return 0;
}



void checkout(){

    //loop variables
    int i,x;

    char input_bookingID[50];//stores the booking id that the user inputs
    party guest;
    int q = 0;

    //enter booking id and validate it
    while(!q){
        printf("enter your booking ID\n");
        fflush(stdin);
        scanf("%s",input_bookingID);//had problems with gets
        for (i = 0; i < 6; i++) {
            //compares the id user entered and stored ID's
            if (strcmp(input_bookingID, parties_arr[i].booking_id)) {
                guest = parties_arr[i];
                q++;
            }
        }
        printf("\nYou are not a current guest, please go back and enter your name and details.\n");
    }

    //variables
    int room_num;//temporary storage of one of the users room numbers
    float total_cost;//stores the total cost of the user's stay
    int len_stay=guest.stay_ln;//stores the length of the party's stay
    int num_adults = guest.a_num;
    int num_children = guest.c_num;//calculates number of guests
    float room_cost=0,board_cost=0,wakeupcall_cost=0,discount=0;//used to calculate the cost of each service

    //calculate the cost of the rooms used
    for(i=0;i<6;i++){
        //if the room number is > 1
        if(guest.stayed_rooms[i][1]>0)
            room_cost += room_arr[i][2];
    }



    //calculate if age is over 65
    //splits current date and date of birth into dd mm yyyy
    //current dd mm yyyy
    int current_date = 0,year,month,date,dob_ddmmyyyy,dob_year, dob_month, dob_date;
    do {
        current_date = 0;
        dob_ddmmyyyy = party_array[1][index];
        dob_year = dob_ddmmyyyy, dob_month = dob_ddmmyyyy, dob_date = dob_ddmmyyyy;
        do {
            printf("enter today's date (DDMMYYYY)");
            scanf("%d", &current_date);
            if (current_date < 01012020) {
                printf("too few characters entered");
            }
        } while (current_date < 01012020);
        year = current_date; month=current_date;date=current_date;
        //year
        do {
            year = year - 10000;
        } while (year > 9999);
        //month
        do {
            month = month - 1000000;
        } while (month > 999999);
        month = (month - year) / 10000;
        //date
        date = (date - month - year) / 1000000;



        //splits date of birth into dd mm yy
        //year
        do {
            dob_year = dob_year - 10000;
        } while (dob_year > 9999);
        //month
        do {
            dob_month = dob_month - 1000000;
        } while (dob_month > 999999);
        dob_month = (dob_month - dob_year) / 10000;
        //date
        dob_date = (dob_date - dob_month - dob_year) / 1000000;

        //calculates if booker is over 65
        if (year - dob_year > 65) {
            //if over 65 room rate is 10%less
            discount = discount + room_cost * 0.1;
            room_cost = room_cost * 0.9;
        } else if (year - dob_year == 65) {
            if (dob_month <= month) {
                if (dob_date <= date) {
                    //if over 65 room rate is 10%less
                    discount = discount + room_cost * 0.1;
                    room_cost = room_cost * 0.9;
                }
            }
        }
        if(dob_year>year || dob_year == year && dob_month>=month && dob_date>date){
            printf("date of birth entered is greater than today's date");
        }
    }while(dob_year>year || dob_year == year && dob_month>=month && dob_date>date);



    //calculate cost of board
    if(party_array[4][index] == 1){//if board type is full board
        board_cost = board_cost + (20*len_stay*num_adults) + (10*len_stay*num_children);
        discount = discount+(10*len_stay*num_children);
    }
    else if(party_array[4][index] == 2){//if board type is half board
        board_cost = board_cost + (15*len_stay*num_adults) + (7.5*len_stay*num_children);
        discount = discount+(7.5*len_stay*num_children);
    }
    else if(party_array[4][index] == 3){//if board type is full board
        board_cost = board_cost + (5*len_stay*num_adults) + (2.5*len_stay*num_children);
        discount = discount+(2.5*len_stay*num_children);
    }



    //daily wakeup calls?
    //1 = true
    if(party_array[5][index]==1){
        wakeupcall_cost = wakeupcall_cost + 5;
    }



    //calculate total cost
    total_cost = room_cost + board_cost + wakeupcall_cost;

    //print bill
    printf("\n\n\n\n\n\n\n\n\n\nBooking ID: %s\nCOSTS:\nRoom Cost:      %.2fGBP\nBoard Cost:      %.2fGBP\n",input_bookingID,room_cost,board_cost);
    if(wakeupcall_cost>0){
        printf("Wakeup Call Cost:   %.2fGBP\n",wakeupcall_cost);
    }
    if(discount > 0){
        printf("\nDISCOUNT TOTAL:  %.2fGBP\n",discount);
    }
    printf("Total Cost:     %.2fGBP",total_cost);



    //clears all data stored about this guest
    for(i=0;i<6;i++){
        party_array[i][0] = 0;
        if(party_array[index+7][i] >0){
            rooms_arr[party_array[index + 7][i] - 1] = 0;
        }
        party_array[index+7][i] = 0;
    }
    for(x=0;x<strlen(bookingID[index]);x++){
        bookingID[index][x] = "\0";
    }

}