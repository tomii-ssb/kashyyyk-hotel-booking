// Written by Tommy

#include <stdio.h>
#include "common.h"

/* The array room_arr holds values that represent certain information about each room
 * It is found in the following format:
 * [room number - 1][0] : Determines whether the room is free or not, holding 0 for no, 1 for yes
 * [room number - 1][1] : Holds the capacity of the room, e.g. 4 people
 * [room number - 1][2] : The daily rate to be payed for the room, e.g. £100
 * [6][0] : Number of people currently staying in hotel */
int room_arr[7][3];

void init_arr(){

    // Init room 1, 2, 3
    for(int i=0;i<3;i++){

        /* Room availability (0 = empty, 1 = full)
         * Program just started so all rooms empty, set to 0 */
        room_arr[i][0] = 0;

        // Room capacity
        room_arr[i][1] = 4;

        /* Room rate /day
         * If i == 2, price is 85, if else 100 */
        room_arr[i][2] = i == 2 ? 85 : 100;
    }

    // Init room 4, 5, 6
    for(int i=3;i<6;i++){

        room_arr[i][0] = 0;

        room_arr[i][1] = 2;

        room_arr[i][2] = i == 5 ? 50 : 75;
    }

    room_arr[6][0] = 0;
}

int display_available_rooms(){

    int available_rooms = 0;

    // Check through each row (room)
    for(int i=0;i<6;i++){

        // If room is free, output room number
        if(room_arr[i][0] == 0){
            printf("Room %d (GBP %d/day), Capacity : %d\n", i+1, room_arr[i][2], room_arr[i][1]);
            available_rooms++;
        }
    }

    return available_rooms;
}

int add_booking(int room_num, int total){

    // If successful, 0, if not, 1
    int res;

    if (room_arr[room_num][0] == 0){

        room_arr[room_num][0]++, room_arr[6][0]++;

        res = 0;
    }
    else res = 1;

    // Update number staying in hotel
    room_arr[6][0] += total;

    return res;
}
