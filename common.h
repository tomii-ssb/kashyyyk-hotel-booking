#ifndef READING_WEEK_COMMON_H
#define READING_WEEK_COMMON_H

// -- GLOBAL VARIABLES -- //
int room_arr[7][3];
char *bookingid_arr[6];

struct Party
{
    char booking_id[50];
    int dob;
    int a_num;
    int c_num;
    char brd;
    int stay_ln;
    int wake_up;
    int stayed_rooms[6][2];
};

typedef struct Party party;
party parties_arr[6];
int parties_index_arr[6][2];


// -- FUNCTIONS -- //

// check in
int check_in();
int get_int_id(const char *id, char *sur);


// rooms
void init_arr();
void display_available_rooms();
int add_booking(int room_num, int total);

// table booking
int book_table();

// check out
int checkout();



#endif //READING_WEEK_COMMON_H
