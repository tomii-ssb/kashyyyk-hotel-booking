// Written by Ollie

#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "common.h"

int checkout(){

    //loop variables
    int i,x;

    char input_bookingID[50];//stores the booking id that the user inputs
    int guest_index = 0;
    Party guest;
    int q = 0;

    //enter booking id and validate it
    while(1){
        printf("Please enter your booking ID "
               "(If you haven't yet booked, please enter q to quit ^_^):\n");
        fflush(stdin);
        scanf("%s",input_bookingID);//had problems with gets
        for (i = 0; i < 6; i++) {

            // If strcmp returns 0 (strings are identical)
            if (!strcmp(input_bookingID, parties_arr[i].booking_id)) {
                guest = parties_arr[i];
                guest_index = i;
                q++;
                break;
            }else if(!strcmp(input_bookingID, "q")){
                printf("Quit successfully\n");
                return 0;
            }

        }

        if (q > 0) break;
        else printf("\nYour details were not found, please try again :)\n");
    }

    //variables
    int age = 0;
    int room_num;//temporary storage of one of the users room numbers
    float total_cost;//stores the total cost of the user's stay
    int len_stay=guest.stay_ln;//stores the length of the party's stay
    int num_adults = guest.a_num;//number of adults
    int num_children = guest.c_num;//number of children
    float room_cost=0,board_cost=0,wakeupcall_cost=0,discount=0;//used to calculate the cost of each service
    Date current_date;
    Date dob;

    //calculate the cost of the rooms used
    for(i=0;i<6;i++){

        // if there are people staying in room
        if(guest.stayed_rooms[i][1]>0)
            room_cost += room_arr[i][2]*guest.stayed_rooms[i][1]*len_stay;
    }


    do {
        char current_date_inp[50];


        do {
            printf("Please enter today's date (DDMMYYYY)\n");
            scanf("%s", current_date_inp);

            if (atoi(current_date_inp) < 01012020) printf("Too few characters entered :(\n");

        } while (atoi(current_date_inp) < 01012020);

        current_date = str_to_date(current_date_inp);
        dob = str_to_date(guest.dob);
        age = find_age(dob, current_date);

        //calculates if booker is over 65
        if (age > 65) {
            //if over 65 room rate is 10%less
            discount += room_cost * 0.1;
            room_cost *= 0.9;
        }
        if(compare_dates(dob, current_date) == 1) {
            printf("Date of birth entered is greater than today's date :(\n");
            return 1;
        }

    }while(compare_dates(dob, current_date) == 1);



    //calculate cost of board
    if(guest.brd == 'f'){//if board type is full board
        board_cost += (20*len_stay*num_adults) + (10*len_stay*num_children);
        discount += (10*len_stay*num_children);
    }
    else if(guest.brd == 'h'){//if board type is half board
        board_cost += (15*len_stay*num_adults) + (7.5*len_stay*num_children);
        discount += (7.5*len_stay*num_children);
    }
    else if(guest.brd = 'b'){//if board type is b&b
        board_cost += (5*len_stay*num_adults) + (2.5*len_stay*num_children);
        discount += (2.5*len_stay*num_children);
    }



    //daily wakeup calls?
    //1 = true
    if(guest.wake_up){
        wakeupcall_cost += 5;
    }



    //calculate total cost
    total_cost = room_cost + board_cost + wakeupcall_cost;

    //print bill
    printf("\n\n\nBooking ID: %s\nCOSTS:\nRoom Cost:      %.2fGBP\nBoard Cost:      %.2fGBP\n",input_bookingID,room_cost,board_cost);
    if(wakeupcall_cost>0){
        printf("Wakeup Call Cost:   %.2fGBP\n",wakeupcall_cost);
    }
    if(discount > 0){
        printf("\nDISCOUNT TOTAL:  %.2fGBP\n",discount);
    }
    printf("Total Cost:     %.2fGBP\n\n",total_cost);

    // Free up rooms
    for (int j = 0; j < 6; j++){
        if (guest.stayed_rooms[j][1] > 0) room_arr[j][0] = 0;
    }

    //clears all data stored about this guest
    Party empty_guest;
    int id_len = strlen(empty_guest.booking_id);

    for(int j=0;j<id_len;j++) empty_guest.booking_id[j] = ' ';

    parties_arr[guest_index] = empty_guest;


    printf("Thank you for staying with us ^_^\n");
    return 0;
}
