//
// Created by tomii on 15/11/2020.
//

#ifndef READING_WEEK_TYPES_H
#define READING_WEEK_TYPES_H

typedef struct party {
    char booking_id[50];
    char dob[50];
    int a_num;
    int c_num;
    char brd;
    int stay_ln;
    int wake_up;
    int stayed_rooms[6][2];
} Party;

typedef struct table {
    char name[10];
    char time[4];
    int booked;
} Table;

typedef struct date {
    int day;
    int month;
    int year;
} Date;

#endif //READING_WEEK_TYPES_H
