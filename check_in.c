// Written by Tommy

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "common.h"

party parties_arr[6];

void generate_booking_id(char *id, const char *sur, int len){
    srand(time(0));

    // Random number ( random enough :) )
    int rand_num = 1000+(rand()%9000);

    char rand_num_str[5];
    sprintf(rand_num_str, "%d", rand_num);

    strcat(id, sur);
    strcat(id, rand_num_str);
}

int get_int_id(const char *id, char *sur){
    int ln = strlen(sur);
    char int_id_c[4];
    int int_id = 0;

    for(int i=ln;i<ln+4;i++)
        int_id_c[i-(ln)] = id[i];

    int_id = atoi(int_id_c);

    return int_id;
}

void get_usr_info(char *sur, char* brd, int* dob, int* ln, int* c_num, int* a_num, int* wakeup){

    // Will store 'y' or 'n', depending on whether user wants a daily wake-up call or not
    char wakeup_inp = ' ';

    printf("Please enter your surname:\n");
    scanf("%s", sur);

    printf("Please enter your date of birth (format DDMMYYYY):\n");
    scanf("%d", dob);

    printf("How many adults will be staying?\n");
    scanf("%d", a_num);

    printf("How many children will be staying? (If none, please enter 0)\n");
    scanf("%d", c_num);

    printf("How long will you be staying? (In full days)\n");
    scanf("%d", ln);

    printf("Please enter F for full board, H for half board, or B for bed & breakfast:\n");
    scanf("%c ", brd);

    printf("Would you like a daily wake-up call? (y for yes, n for no)\n");
    scanf("%c ", &wakeup_inp);

    if (wakeup_inp == 'y') *wakeup = 1;
    else if (wakeup_inp == 'n') *wakeup = 0;
}

int add_party_to_array(party booked_party){

    // Index at which the party struct will be stored
    int party_index = 0;

    for(int i=0;i<6;i++){
        if (parties_arr[i].dob < 1){
            parties_arr[i] = booked_party;
            party_index = i;
            i = 6;
        }
    }

    return party_index;
}

int book(int a_num, int c_num, int dob, int ln, int wake_up, const char* id, char brd, char* sur){

    // var
    int total = a_num + c_num; // Total people staying
    int current_capacity = 18 - room_arr[6][0]; // max capacity - current guests
    int needed_room_num = 0;
    int needed_rooms[6][2];
    char dob_str[50] = "";

    itoa(dob, dob_str, 10);

    if(total>current_capacity){
        printf("We do not currently have the capacity for your party :(((");
        return 1;
    }

    // DOB must be in DDMMYYYY format
    if(strlen(dob_str) != 8) return 1;

    printf("At the current time, these rooms are available:\n");
    display_available_rooms();

    printf("How many rooms will you need?\n");
    fflush(stdin);
    scanf("%d", &needed_room_num);

    for(int i=0;i<needed_room_num;i++) {

        char room_to_stay_c = ' ';
        int room_to_stay = 0;

        int staying_number = 0;
        int room_capacity = 0;

        printf("Please enter the number of the room you would like to book (only one):\n");
        fflush(stdin);
        room_to_stay_c = getchar();
        room_to_stay = (atoi(&room_to_stay_c) - 1);

        printf("you want to stay in room %d, index %d", room_to_stay + 1, room_to_stay);

        room_capacity = room_arr[room_to_stay][1];

        printf("How many people will be staying in this room?\n");
        if (scanf("%d", &staying_number)) printf("scanf worked");

        if (staying_number <= room_capacity){
            needed_rooms[i][1] = staying_number;
            printf("\nthis happened\n");
        }else{
            printf("Room %d's capacity is %d! Please try again :)", room_to_stay, room_capacity);
            i--;
        }
    }

    party booked_party;

    // Party structure assignment
    booked_party.dob = dob;
    booked_party.a_num = a_num;
    booked_party.c_num = c_num;
    booked_party.brd = brd;
    booked_party.stay_ln = ln;
    booked_party.wake_up = wake_up;

    // Assign needed_room array values to stayed_rooms 'Party' struct element array
    for(int i=0;i<6;i++){
        for(int j=0;j<2;j++) booked_party.stayed_rooms[i][j] = needed_rooms[i][j];
    }

    for(int i=0;i<strlen(id);i++){
        booked_party.booking_id[i] = id[i];
    }

    add_party_to_array(booked_party);

    // Sort through needed_rooms array
    for(int i=0;i<6;i++)

        // Add booking for each room needed
        if(needed_rooms[i][1] > 0) add_booking(i, needed_rooms[i][1]);


    return 0;
}

int check_in (){

    // Variables
    char usr_surname[100];
    int dob = 0;
    int adult_num = 0; // Number of adult guests
    int child_num = 0;
    char brd = ' '; // Board type
    int wakeup_call = 0; // Whether they want a wake-up call or not
    int ln = 0; // Length of stay (in full days)
    char booking_id[50];

    get_usr_info(usr_surname, &brd, &dob, &ln, &child_num, &adult_num, &wakeup_call);

    generate_booking_id(booking_id, usr_surname, strlen(usr_surname));

    printf("id with sur: %s", booking_id);
    get_int_id(booking_id, usr_surname);

    if(book(adult_num,child_num,dob,ln,wakeup_call,booking_id,brd,usr_surname)
            ) return 1;

    printf("\nHere is your booking ID: %s ^_^\n"
           "Please try to remember it as you need it to book a table and check out :)", booking_id);

    return 0;
}
