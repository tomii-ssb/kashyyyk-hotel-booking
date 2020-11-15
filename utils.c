#include<stdio.h>
#include<stdlib.h>
#include "common.h"

int get_int_id(const char *id, char *sur){
    int ln = strlen(sur);
    char int_id_c[4];
    int int_id = 0;

    for(int i=ln;i<ln+4;i++)
        int_id_c[i-(ln)] = id[i];

    int_id = atoi(int_id_c);

    return int_id;
}

int dob_int(char *dob){

    if (dob[0] == '0'){
        for (int i=1;i<8;i++){
            dob[i-1] = dob[i];
        }
    }

    return atoi(dob);
}

