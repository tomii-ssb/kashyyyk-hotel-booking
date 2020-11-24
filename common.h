#ifndef READING_WEEK_COMMON_H
#define READING_WEEK_COMMON_H
#include "types.h"

// -- GLOBAL VARIABLES -- //
int room_arr[7][3];
char *bookingid_arr[6];
Party parties_arr[6];
Table tables_arr[6];

// -- FUNCTIONS -- //

// utils
void welcome();
int dob_int(char* dob);
Date str_to_date(char *date_c);
int compare_dates(Date d1, Date d2);
int find_age(Date dob, Date date);
int verify_date(Date date);

// check in
int check_in();

// rooms
void init_arr();
int display_available_rooms();
int add_booking(int room_num, int total);

// table booking
int book_table();
void init_tables();

// check out
int checkout();

#endif //READING_WEEK_COMMON_H
