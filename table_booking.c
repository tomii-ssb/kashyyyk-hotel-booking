// written by Tom S

#include <stdio.h>
#include <string.h>
#include "common.h"

// the general booking procedure which checks whether the guest can actually book a table
int general_booking();
//the specific procedure which "books" a table (edits an element in the table array)
int booking();

// Index for table the user is booking in table arr
int tab_arr_i = 0;
//table that the user books
Table booked_table;

int i = 0, num = 0;

//the array which stores the tables
Table tables_arr[6];

void init_tables(){
    strcpy(tables_arr[0].name, "Endor");
    strcpy(tables_arr[0].time, "7pm");

    strcpy(tables_arr[1].name, "Endor");
    strcpy(tables_arr[1].time, "9pm");

    strcpy(tables_arr[2].name, "Naboo");
    strcpy(tables_arr[2].time, "7pm");

    strcpy(tables_arr[3].name, "Naboo");
    strcpy(tables_arr[3].time, "9pm");

    strcpy(tables_arr[4].name, "Tatooine");
    strcpy(tables_arr[4].time, "7pm");

    strcpy(tables_arr[5].name, "Tatooine");
    strcpy(tables_arr[5].time, "9pm");
}

int book_table() {

    int q = 0;

    //variable which corresponds to the users bookingID and other details
    Party guest;

    char restaurantID[8];

    while (q == 0) //easy way to end code and return to start
    {
        printf("Please enter booking ID "
               "(If you haven't yet booked, please enter q to quit ^_^):\n");
        scanf("%s", restaurantID);

        for (i = 0; i < 6; i++)
        {
            // If strcmp returns 0 (strings are identical)
            if (!strcmp(restaurantID, parties_arr[i].booking_id))
            {
                guest = parties_arr[i];
                general_booking(guest); //subroutine
                q++;
                break;
            }else if(!strcmp(restaurantID, "q")){
                printf("Quit successfully\n");
                return 0;
            }
        }

        if (q > 0) break;
        printf("\nYour details were not found, please try again :)\n");
    }

    return 0;
}

int general_booking(Party guest) {

    int p = 0;
    int total_staying = guest.a_num + guest.c_num;

    while (1) {
        if (guest.brd == 'b') { //checks that the user isn't staying for B&B
            printf("\nAs you are booked in for Bed and Breakfast, you cannot book a table.\n");
            break;
        } else {
            if (total_staying > 4 || total_staying <= 0 ){ //checks that there aren't more than 4 people or less than 0 people
                printf("I'm afraid that due to the number of people you have, you cannot book a table.");
                return 1;
            } else{
                printf("The available tables and their times are:\n"); //for loop outputs all the table names (excluding ones that are already booked, which outputs "BOOKED" in its place)
                for (i = 0; i < 6; i++) {
                    Table current_table = tables_arr[i];
                    if(current_table.booked == 0){
                        printf("%d. %s at %s\n", i+1, current_table.name, current_table.time);
                    }else p++; //use this to potentially end this code early in case all tables are booked
                }
                if (p == 6) {
                    printf("There are no more available tables. Please try another day.\n");
                    return 0;
                }
                printf("Which table? For the first table and time, type '1', "
                       "the second table and time, type '2', etc.");
                scanf("%d", &num);
                tab_arr_i = num - 1;
                switch (num) {
                    case 1:
                    case 2:
                    case 3:
                    case 4:
                    case 5:
                    case 6:
                        booked_table = tables_arr[num-1];
                        if (booking()) return 1;
                        else return 0;
                    default:
                        printf("Not valid\n");
                }

            }
        }
    }

    return 0;
}



int booking() {

    if (booked_table.booked) //checks if table is already booked and breaks without booking if so
    {
        printf("Table already booked.");
        return 1;
    } else {
        tables_arr[tab_arr_i].booked = 1; //changes elements name to "BOOKED" so that it cannot be booked again until the program is rebooted

        printf("\nYou have successfully booked the %s table at %s :)\n", booked_table.name, booked_table.time);
    }

    return 0;
}