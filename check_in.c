// Written by Tommy

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

// dob was behaving strangely when parsed
char dob[50];

Party parties_arr[6];

void generate_booking_id(char *id, const char *sur){

    srand(time(0));

    // Random number ( random enough :) )
    int rand_num = 1000+(rand()%9000);

    char rand_num_str[5];
    sprintf(rand_num_str, "%d", rand_num);

    strcat(id, sur);
    strcat(id, rand_num_str);
}

int get_usr_info(char *sur, char* brd, int* ln, int* c_num, int* a_num, int* wakeup){

    // While loop conditions
    int j = 0;
    int k = 0;
    int x = 0;

    // Confirmation from the user, y/n
    char user_conf = ' ';

    // Will store 'y' or 'n', depending on whether user wants a daily wake-up call or not
    char wakeup_inp = ' ';

    printf("Please enter your surname:\n");
    fflush(stdin);
    if (!scanf("%s", sur)) return 1;
    lower(sur);

    // Check for integers in surname
    for (int i=0;i<strlen(sur);i++){
        if(atoi(&sur[i])){
            printf("\nYou cannot have integers in your surname :/\n");
            return 1;
        }
    }

    printf("Please enter your date of birth (format DDMMYYYY):\n");
    fflush(stdin);
    if(!scanf("%s", dob)) return 1;

    // Check for chars in DOB
    for (int i=0;i<strlen(dob);i++){
        if(!atoi(&dob[i])){
            printf("\nYou cannot have characters in your DOB :/\n");
            return 1;
        }
    }

    printf("How many adults will be staying?\n");
    fflush(stdin);
    if(!scanf("%d", a_num)) return 1;

    printf("How many children will be staying? (If none, please enter 0)\n");
    fflush(stdin);
    if(!scanf("%d", c_num)) return 1;

    printf("How long will you be staying? (In full days)\n");
    fflush(stdin);
    if(!scanf("%d", ln)) return 1;

    while(!j) {
        printf("Please enter F for full board, H for half board, or B for bed & breakfast:\n");
        fflush(stdin);
        if (scanf("%c", brd)){}
        else {
            printf("\nAn error occurred, please try again :/\n");
            get_usr_info(sur, brd, ln, c_num, a_num, wakeup);
        }

        switch(*brd){
            case 'f':
            case 'h':
            case 'b': j++; break;
            default:
                printf("\nNot a valid option, please try again :)\n");
                break;
        }
    }

    while(!k) {
        printf("Would you like a daily wake-up call? (y for yes, n for no)\n");
        fflush(stdin);
        if(!scanf("%c", &wakeup_inp)) return 1;

        switch(wakeup_inp){
            case 'y': *wakeup = 1, k++; break;
            case 'n': *wakeup = 0, k++; break;
            default:
                printf("\nNot a valid option, please try again :)\n");
                break;
        }
    }

    printf("\nIs this correct? (y for yes, n for no, q for quit)\n");
    printf("Surname: %s\nDOB: %s\nAdults: %d\nChildren: %d\nWake Up Call?: %c\n",
           sur, dob, *a_num, *c_num, wakeup_inp);

    while(!x){
        fflush(stdin);
        user_conf = getchar();
        switch(user_conf){
            case 'y': x++; break;
            case 'n':
                printf("Ok, let's do it again!!\n");
                get_usr_info(sur, brd, ln, c_num, a_num, wakeup);
                x++;
                break;
            case 'q': return 2;
            default:
                printf("That is not a valid option :/\n");
                break;
        }
    }

    return 0;

}

int add_party_to_array(Party booked_party){

    // Index at which the party struct will be stored
    int party_index = 0;

    for(int i=0;i<6;i++){

        // DOB as int
        int dob = dob_int(parties_arr[i].dob);

        if (dob < 1){
            parties_arr[i] = booked_party;
            party_index = i;
            i = 6;
        }
    }

    return party_index;
}

int book(int a_num, int c_num, int ln, int wake_up, const char *id, char brd){

    // var
    int total = a_num + c_num; // Total people staying
    int current_capacity = 18 - room_arr[6][0]; // max capacity - current guests
    char needed_room_num_c = ' ';
    int needed_room_num = 0;
    int needed_rooms[6][2];
    int booked_people = total;
    int available_rooms = 0;

    // Init needed_rooms
    for(int i=0;i<6;i++) needed_rooms[i][1] = 0;

    // Loop var
    int k = 0;

    if(total>current_capacity){
        printf("We do not currently have the capacity for your party :(((\n");
        return 1;
    }
    //does not accept a party of less than 1 guest
    else if(total<1){
        printf("We do not accept parties of less than 1 person\n");
        return 1;
    }

    // DOB must be in DDMMYYYY format
    if (strlen(dob) != 8) return 1;

    printf("At the current time, these rooms are available:\n");
    available_rooms = display_available_rooms();

    while(booked_people){ //while booked_people != 0

        printf("How many rooms will you need?\n");
        fflush(stdin);
        needed_room_num_c = getchar();

        if(needed_room_num_c == 'q') return 2;

        needed_room_num = atoi(&needed_room_num_c);
        if(!needed_room_num) return 1; // If 0 is returned, meaning wasn't a valid integer

        if(0 < needed_room_num <= available_rooms){
            while(k < needed_room_num) {

                char room_to_stay_c = ' ';
                int room_to_stay = 0;

                int staying_number = 0;
                int room_capacity = 0;

                printf("Please enter the number of the room you would like to book (one at a time):\n");
                fflush(stdin);
                room_to_stay_c = getchar();

                if (room_to_stay_c == 'q') return 2;

                room_to_stay = (atoi(&room_to_stay_c) - 1);

                if (room_to_stay > 5){
                    printf("\nThat is not a valid room :/\n");
                    return 1;
                }


                if (room_arr[room_to_stay][0]){
                    printf("\nRoom is already booked :/\n");
                    return 1;
                }

                room_capacity = room_arr[room_to_stay][1];

                printf("How many people will be staying in this room?\n");
                fflush(stdin);
                if (scanf("%d", &staying_number)){}
                else return 1;

                if (staying_number > total){
                    printf("You have only made a booking for %d person/people :/\n", total);
                    return 1;
                }

                if (staying_number <= room_capacity && staying_number>0){
                    needed_rooms[room_to_stay][1] = staying_number;
                    booked_people -= staying_number;
                    k++;
                }else if (staying_number > room_capacity){
                    printf("Room %d's capacity is %d! Please try again :)\n", room_to_stay, room_capacity);
                }else if (staying_number<=0){
                    printf("You cannot book less than 1 person into a room! Please try again! If you would like to quit, press q\n");
                }
            }

            if (!booked_people) break; // If booked_people == 0 (everyone has been booked)
            else printf("\nYou did not account for every person in your party :( Please try again ^_^\n");
        }
        else{
            char user_opt = ' ';
            printf("There are %d available rooms man :(\n", available_rooms);
            printf("Please enter 'q' to exit or 'c' to continue ._.\n");
            fflush(stdin);
            user_opt = getchar();

            switch(user_opt){
                case 'q': return 2;
                case 'c': break;
                default:
                    printf("Wasn't one of the options :/\n");
                    return 2;
            }
        }

    }

    Party booked_party;

    // Party structure assignment
    booked_party.a_num = a_num;
    booked_party.c_num = c_num;
    booked_party.brd = brd;
    booked_party.stay_ln = ln;
    booked_party.wake_up = wake_up;

    strcpy(booked_party.dob, dob);
    strcpy(booked_party.booking_id, id);

    // Assign needed_room array values to stayed_rooms 'Party' struct element array
    for(int i=0;i<6;i++){
        for(int j=0;j<2;j++) booked_party.stayed_rooms[i][j] = needed_rooms[i][j];
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
    int adult_num = 0; // Number of adult guests
    int child_num = 0;
    char brd = ' '; // Board type
    int wakeup_call = 0; // Whether they want a wake-up call or not
    int ln = 0; // Length of stay (in full days)
    char booking_id[50];

    switch(get_usr_info(usr_surname, &brd, &ln, &child_num, &adult_num, &wakeup_call)){
        case 1: return 1;
        case 2:
            printf("\nQuit successfully\n");
            return 2;
    };

    generate_booking_id(booking_id, usr_surname);

    switch(book(adult_num,child_num,ln,wakeup_call,booking_id,brd)){
        case 1: return 1;
        case 2:
            printf("\nQuit successfully :)\n");
            return 0;
    }

    printf("\nHere is your booking ID: %s ^_^\n"
           "Please try to remember it as you need it to book a table and check out :)\n\n", booking_id);

    return 0;
}
