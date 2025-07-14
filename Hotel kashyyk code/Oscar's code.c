#include <stdio.h>
#include <string.h>
#include <stdlib.h> //needed for random number - Alex
#include <time.h> //needed for random number - Alex
#include <math.h> //needed for rounding - Oscar

char mainUserName[6][50];
int dateOfBirth[6][3]; //[x][0] is DD, [1] is MM, [2] is YY, All together is DD/MM/YY.
// (For this variable, when a zero is entered anywhere, it is automatically removed
// e.g. "01/01/08" is 1 1 8, "5/11/25" is 5 11 25) - Alex
int numAGuests[6];
int numCGuests[6];
char boardType[6][3];
int lengthOfStay[6];
char newspaper[6]; //y == yes, n == no - Alex Sorry I had to change to Char instead of Boolean
int currentUser =-1; //HELLO OSCAR READ PLEASE - When printing this for the user to see the room number
//we need to add 1 to the value so it looks right (as the array is 0-5 not 1-6).
int room[6] = {0, 0, 0, 0, 0, 0}; //stores 0 for available, 1 for unavailable - Alex
char bookingID[6][50]; //-Alex
int table[3][2] = {
    /*Endor*/ {-1, -1},
    /*Naboo*/{-1, -1},
    /*Tatooine*/{-1, -1}
}; //Endor, Naboo, Tatooine. 7pm and 9pm.
//-1 = available, any other number is the room number (in room array) that has booked the table. - Alex

void checkOut();
void quitProgram();
int userValidation();

int main(void) {
    fflush(stdin);
    scanf("%s", &boardType[1]);
    numAGuests[1] = 1;
    numCGuests[1] = 2;
    lengthOfStay[1] = 1;
    dateOfBirth[1][0] = 17 ;
    dateOfBirth[1][1] = 11 ;
    dateOfBirth[1][2] = 58;
    newspaper[1] = 'y';
    scanf("%s", &mainUserName[1]);
    scanf("%s", &bookingID[1]);

    checkOut();
    return 0;
}


//check out subroutine
void checkOut() {
    //declares variables for this subroutine
    float guestTotalBill = 0;
    float roomCost = 0;
    float boardCost = 0;
    int is65Discount = 0;
    int temp;

    //If no user is currently logged in then userValidation is called to use the bookingID to log in
    if(currentUser == -1) {
        temp = userValidation();
        //If userValidation fails then the user will be returned to the main menu and unable to check out
        if(temp == -1) {
            return;
        }
        currentUser = temp;
    }


    //Calculates the cost of the room the user is staying in for the days stayed
    if(currentUser == 0 || currentUser == 1) {
        roomCost = 100 * lengthOfStay[currentUser];
    }
    else if(currentUser == 2) {
        roomCost = 85 * lengthOfStay[currentUser];
    }
    else if(currentUser == 3 || currentUser == 4) {
        roomCost = 75 * lengthOfStay[currentUser];
    }
    else if(currentUser == 5) {
        roomCost = 50 * lengthOfStay[currentUser];
    }

    //Calculates the cost of the Board type and adds it to the total bill
    if(strcmp(boardType[currentUser] , "FB") == 0) {
        boardCost = (20 * numAGuests[currentUser] + 10 * numCGuests[currentUser]) * lengthOfStay[currentUser];
   }
    else if(strcmp(boardType[currentUser] , "HB") == 0) {
        boardCost = (15 * numAGuests[currentUser] + 7.5 * numCGuests[currentUser]) * lengthOfStay[currentUser];

    }
    else if(strcmp(boardType[currentUser] , "BB") == 0) {
        boardCost = (5 * numAGuests[currentUser] + 2.5 * numCGuests[currentUser]) * lengthOfStay[currentUser];
    }


    //CALCULATE USER'S AGE TO APPLY DISCOUNT START---------

    //gets current date (using code I found on stack overflow)
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //checks main user's age to apply over 65 discount by comparing the current date with the date of birth of the user
    //if the birth year of the user is greater than the current year it is assumed they were born in the 1900s
    if(dateOfBirth[currentUser][2] > tm.tm_year - 100) {
        //if the birth month of the user has not happened yet (then later subtract 1 from the age)
        if(dateOfBirth[currentUser][1] > tm.tm_mon + 1) {
            //if the user is over 65 then room cost is 10% cheaper
            if(tm.tm_year - dateOfBirth[currentUser][2] - 1 > 65) {
                roomCost = roomCost * 0.9;
                is65Discount = 1;
            }
        }
        //if it is the user's birth month then check birthday
        else if(dateOfBirth[currentUser][1] == tm.tm_mon + 1) {
            //if their birthday hasn't happened
            if(dateOfBirth[currentUser][0] > tm.tm_mday) {
                //if the user is over 65 then room cost is 10% cheaper
                if(tm.tm_year - dateOfBirth[currentUser][2] - 1 > 65) {
                    roomCost = roomCost * 0.9;
                    is65Discount = 1;
                }
            }
            //else means their birthday has happened or it is their birthday
            else {
                //if the user is over 65 then room cost is 10% cheaper (with no -1 as it's past their birthday)
                if(tm.tm_year - dateOfBirth[currentUser][2] > 65) {
                    roomCost = roomCost * 0.9;
                    is65Discount = 1;
                }
            }

        }
        //If the user's birth month has already happened
        else {
            //if the user is over 65 then room cost is 10% cheaper (with no -1 as it's past their birthday)
            if(tm.tm_year - dateOfBirth[currentUser][2] > 65) {
                roomCost = roomCost * 0.9;
                is65Discount = 1;
            }
        }
    }



    //ELSE the birth year of the user is less than or equal to the current year it is assumed they were born in the 2000s (this is meaningless for 2024 but I want this to work for any years 2000-2099)
    else{
        //if the birth month of the user has not happened yet (then later subtract 1 from the age)
        if(dateOfBirth[currentUser][1] > tm.tm_mon + 1) {
            //if the user is over 65 then room cost is 10% cheaper
            if(tm.tm_year - dateOfBirth[currentUser][2] - 101 > 65) {
                roomCost = roomCost * 0.9;
                is65Discount = 1;
            }
        }
        //if it is the user's birth month then check birthday
        else if(dateOfBirth[currentUser][1] == tm.tm_mon + 1) {
            //if their birthday hasn't happened
            if(dateOfBirth[currentUser][0] > tm.tm_mday) {
                //if the user is over 65 then room cost is 10% cheaper
                if(tm.tm_year - dateOfBirth[currentUser][2] - 101 > 65) {
                    roomCost = roomCost * 0.9;
                    is65Discount = 1;
                }
            }
            //else means their birthday has happened or it is their birthday
            else {
                //if the user is over 65 then room cost is 10% cheaper (with no -1 as it's past their birthday)
                if(tm.tm_year - dateOfBirth[currentUser][2] - 100 > 65) {
                    roomCost = roomCost * 0.9;
                    is65Discount = 1;
                }
            }

        }
        //If the user's birth month has already happened
        else {
            //if the user is over 65 then room cost is 10% cheaper (with no -1 as it's past their birthday)
            if(tm.tm_year - dateOfBirth[currentUser][2] -100 > 65) {
                roomCost = roomCost * 0.9;
                is65Discount = 1;
            }
        }
    }


    //printf("%f", roomCost); for testing

    //CALCULATE USER'S AGE TO APPLY DISCOUNT END------------

    //calculates total cost
    guestTotalBill = roomCost + boardCost;
    if(newspaper[currentUser] == 'y') {
        guestTotalBill += 5.50;
    }



    //produces the final bill for the group
    printf("Guest: %s BookingId: %s\nThank you for staying with the Kasyyyk Hotel we hope you had a pleasant stay.\n\nBill:\n", mainUserName[currentUser], bookingID[currentUser]);
    if(is65Discount == 1) {
        printf("Room cost: $%f (with 10%% over 65 discount)\n",round(roomCost*100)/100);
    }
    else {
        printf("Room cost: $%.2f\n", roomCost);
    }
    printf("Board cost: $%f\n", round(boardCost*100)/100);
    if(newspaper[currentUser] == 'y') {
        printf("Daily newspaper cost: $5.50 \n");
    }
    printf("Total Cost of stay: $%f", guestTotalBill);

    //makes the room they were staying in available
    room[currentUser] = 0;
}

//quitProgram subroutine
void quitProgram() {
    // resets the current user so a new user can sign in
    currentUser = -1;
}

//userValidation subroutine
int userValidation() {
    char input[50];
    int placeHolder = -1; //For BookingID's respective room number
    int notAnIdCount = 0;

    printf("\nNo user is logged in so please enter your booking ID to check out:");
    fflush(stdin);
    scanf("%s", &input);

    for(int i = 0; i < 6; i++){
        if(strcmp(input, bookingID[i]) == 0){
            printf("\nBookingID found in system!\n\n");
            placeHolder = i;
            i = 6;
        }
        else{
            notAnIdCount++;
        }
    }

    if(notAnIdCount == 6){
        printf("\nBookingID not found in system.\nReturning to main menu...");
        return -1;
    }

    return placeHolder;
}