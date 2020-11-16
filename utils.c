#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "common.h"

void welcome(){

    // Tried to have it in txt, read from it and output, didn't work
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    printf("- - - W E L C O M E   T O   T H E   K A S H Y Y Y K   H O T E L - - -\n");
    printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

}

int find_age(Date dob, Date date){

    // Days of every month
    int month[] = { 31, 28, 31, 30, 31, 30, 31,
                    31, 30, 31, 30, 31 };


    if (dob.day > date.day) {
        date.day += month[dob.month - 1];
        date.month = dob.month - 1;
    }

    if (dob.month > date.month) {
        date.year -= 1;
        date.month += 12;
    }

    // calculate date, month, year
    int calculated_year = date.year - dob.year;

    return calculated_year;
}

Date str_to_date(char *date_c){

    // Date to be returned
    Date date;

    // Day, month, year as int
    int day = 0;
    int mth = 0;
    char yr = 0;

    // Day, month, year as str
    char day_c[2];
    char mth_c[2];
    char yr_c[4];

    strncpy(day_c, date_c, 2);
    strncpy(mth_c, date_c+2, 2);
    strncpy(yr_c, date_c+4, 4);

    if(day_c[0] == '0') strcpy(day_c, &day_c[1]);
    if(mth_c[0] == '0') strcpy(mth_c, &mth_c[1]);

    date.day = atoi(day_c);
    date.month = atoi(mth_c);
    date.year = atoi(yr_c);

    return date;
}

int compare_dates (Date d1, Date d2)
{
    if (d1.year < d2.year)
        return -1;

    else if (d1.year > d2.year)
        return 1;

    if (d1.year == d2.year)
    {
        if (d1.month<d2.month) return -1;

        else if (d1.month>d2.month) return 1;

        else if (d1.day<d2.day) return -1;

        else if(d1.day>d2.day) return 1;

        else return 0;
    }
}

int dob_int(char *dob){

    if (dob[0] == '0'){
        for (int i=1;i<8;i++){
            dob[i-1] = dob[i];
        }
    }

    return atoi(dob);
}

