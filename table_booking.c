//alright so after a full on week, this is what i got. some quick things you should prolly know:
// the q++, supposing it works, should end the program (as the whole thing is inside a while q = 0), however when it is added to the main code, this instead should send the user back to the selection screen
// a lot of variables here have very vague names like i, q, p, etc. i know its not good practice however


#include <stdio.h>
#include <string.h>

// the general booking procedure which checks whether the guest can actually book a table
void general_booking();
//the specific procedure which "books" a table (edits an element in the table array)
void booking();

int i = 0, q = 0, num = 0, x = 0;

//the array which stores the tables
char tables[6][50];

int main() {
    //variable which corresponds to the users bookingID and other details
    int guest;

    char restaurantID, ID;

    while (q == 0) //easy way to end code and return to start
    {
        printf("Please enter booking ID");
        scanf("%s", &restaurantID);

        for (i = 0; i < 1000; i++) //it goes to a very high number because i dont know how to find the exact length of the array, so it should run through the whole array and stop when it reaches an empty position
        {
            if (restaurantID = party_array[0][i])
            {
                i = guest; //as each guest takes up one position on each array row, this number should be the guests number for every row
                general_booking(guest); //subroutine
                q++;
            }
            else if (party_array[0][i] = "\0")
            {
                break; //breaks the program when the positions stop being occupied, aka it has run through the whole array
            }
        }
        printf("You are not a current guest, please go back and enter your name and details.");
        q++;
    }
}

void general_booking(int guest) {
    //strcpy(tables[0], "BOOKED"); //initialising tables as already booked, used to test so can get rid of this if you'd like
    //strcpy(tables[1], "BOOKED");
    //strcpy(tables[2], "BOOKED");
    //strcpy(tables[3], "BOOKED");
    //strcpy(tables[4], "BOOKED");
    //strcpy(tables[5], "BOOKED");

    strcpy(tables[0], "1. Endor7pm"); //actual table names and times
    strcpy(tables[1], "2. Endor9pm");
    strcpy(tables[2], "3. Naboo7pm");
    strcpy(tables[3], "4. Naboo9pm");
    strcpy(tables[4], "5. Tatooine7pm");
    strcpy(tables[5], "6. Tatooine9pm");

    int p = 0;

    while (q == 0) {
        if (party_array[4][guest] = 3) { //checks that the user isn't staying for B&B
            printf("As you are booked in for Bed and Breakfast, you cannot book a table.");
            q++;
        } else {
            if (0 < (party_array[2][guest] + party_array[3][guest]) >=4) { //checks that there aren't more than 4 people or less than 0 people
                printf("I'm afraid that due to the number of people you have, you cannot book a table.");
                q++;
            } else {

                printf("The available tables and their times are:"); //for loop outputs all the table names (excluding ones that are already booked, which outputs "BOOKED" in its place)
                for (i = 0; i <= 6; i++) {
                    printf("\n%s", tables[i]);

                    if (strcmp(tables[i], "BOOKED") == 0) { //to see if all of the tables are "BOOKED"
                        p = p + 1; //use this to potentially end this code early in case all tables are booked
                    }
                }
                if (p == 6) {
                    printf("There are no more available tables. Please try another day.");
                    q++;
                }
                printf("%d\n", p);
                printf("Which table? For the first table and time, type '1', the second table and time, type '2', etc."); //had to use switch case as last resort - cheap i know but it works :/
                scanf("%d", &num);
                switch (num) {
                    case 1:
                        booking();
                        q++;
                    case 2:
                        booking();
                        q++;
                    case 3:
                        booking();
                        q++;
                    case 4:
                        booking();
                        q++;
                    case 5:
                        booking();
                        q++;
                    case 6:
                        booking();
                        q++;
                    default:
                        printf("Not valid");
                        q++;
                }

            }
        }
    }
}



void booking() {
    if (strcmp(tables[num - 1], "BOOKED") ==
        0) //checks if table is already booked and breaks without booking if so
    {
        printf("Table already booked.");
        q++;
    } else {
        strcpy(tables[num - 1],
               "BOOKED"); //changes elements name to "BOOKED" so that it cannot be booked again until the program is rebooted
        for (x = 0; x <= 6; x++) {
            printf("\n%s", tables[x]); //outputs list of tables without the booked table, to show that its been booked
        }
        printf("You have successfully booked a table.");
    }
}