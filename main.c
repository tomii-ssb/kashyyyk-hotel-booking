#include <stdio.h>
#include "common.h"


int main(){

    welcome();

    // Initialise rooms array
    init_arr();

    // Initialise tables array
    init_tables();

    for(;;){

        char usr_opt = ' '; // Option user chooses

        printf("\nWould you like to: \n1. Check in? \n2. Book a dinner table? \n3. Check out?\n");
        fflush(stdin);
        usr_opt = getchar();

        switch(usr_opt){
            case '1':
                if(check_in()) printf("\nSomething went wrong :(\n");
                break;
            case '2':
                book_table();
                break;
            case '3':
                if(checkout()) printf("\nSomething went wrong :(\n");
                break;
            default:
                printf("That is not a valid option :(\n");
                break;
        }
    }


    return 0;
}

