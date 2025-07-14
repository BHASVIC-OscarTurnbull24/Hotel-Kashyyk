//
// Check In and Book Dinner table
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //needed for random number - Alex
#include <time.h> //needed for random number - Alex


char mainUserName[6][50];
int dateOfBirth[6][3]; //[x][0] is DD, [1] is MM, [2] is YY, All together is DD/MM/YY
// (For this variable, when a zero is entered anywhere, it is automatically removed
// e.g. "01/01/08" is 1 1 8, "5/11/25" is 5 11 25) - Alex
int numAGuests[6];
int numCGuests[6];
// int guestTotalBills[6]; Hi alex! I made this a local variable since it is only needed in checkOut
char boardType[6][3];
int lengthOfStay[6];
char newspaper[6]; //y == yes, n == no - Alex
int currentUser;
int room[6] = {0, 0, 0, 0, 0, 0}; //stores 0 for available, 1 for unavailable - Alex
char bookingID[6][50]; //-Alex
int table[3][2] = {
    /*Endor*/ {-1, -1},
    /*Naboo*/{-1, -1},
    /*Tatooine*/{-1, -1}
}; //Endor, Naboo, Tatooine. 7pm and 9pm.
//-1 = available, any other number is the room number (in room array) that has booked the table. - Alex

void checkIn();
void bookDinnerTable();



int main(void) {
    checkIn();

    //testing inputs go through
    printf("\nFor Room number '%d':", currentUser + 1);
    printf("\nUsername: %s", mainUserName[currentUser]);
    printf("\nDoB: %d %d %d", dateOfBirth[currentUser][0], dateOfBirth[currentUser][1], dateOfBirth[currentUser][2]);
    printf("\nNum A guests: %d", numAGuests[currentUser]);
    printf("\nNum C guests: %d", numCGuests[currentUser]);
    printf("\nBoard type: %s", boardType[currentUser]);
    printf("\nLength of stay: %d", lengthOfStay[currentUser]);
    printf("\ny/n Newspaper: %c", newspaper[currentUser]);
    printf("\nBooking ID: %s\n", bookingID[currentUser]);
    //end of input tests

    bookDinnerTable();

    return 0;
}


//checkIn subprogram
void checkIn(){
    //If rooms are free print them
    printf("\nThese rooms are currently available:\n");
    for (int i = 0; i < 6; i++){
        if(room[i] == 0){
            printf("\nRoom %d is available", i+1);
        }
    }

    //If no rooms are available
    if(room[0] == 1 && room[1] == 1 && room[2] == 1 && room[3] == 1 && room[4] == 1 && room[5] == 1){
        printf("\nApologies, all rooms are currently unavailable");
        return;
    }

    //Enter Room
    printf("\n\n------------- Room Rates (in GBP)  *PER ROOM*, *PER DAY* -------------");
    printf("\n     Rooms 1 & 2 = 100, Room 3 = 85, Room 4 & 5 = 75, Room 6 = 50");
    printf("\n\nChoose a Room (1/2/3/4/5/6):");
    scanf("%d", &currentUser);

    //Chosen Room unavailable
    if(room[currentUser - 1] == 1){
        printf("\nApologies, this room is currently unavailable");
        return;
    }

    //chosen room available
    if(room[currentUser - 1] == 1){
        printf("\nBooking Room %d:", currentUser);
        room[currentUser] = 1; //Makes chosen room unavailable
        currentUser -= 1; //Converts room number to correct array number
    }

    //Enter Name
    printf("\nEnter Your Full Name (Please enter it without any spaces):");
    fflush(stdin);
    scanf("%s", &mainUserName[currentUser]);

    //Enter Date of Birth
    printf("\nEnter Your Date of Birth (DD/MM/YY):"); //e.g: "01/01/08", "5/11/25"
    fflush(stdin);
    scanf("%d/%d/%d", &dateOfBirth[currentUser][0], &dateOfBirth[currentUser][1], &dateOfBirth[currentUser][2]);

    //Enter Number of Adult guests
    printf("\nHow many adults are staying in the room? (?/4):");
    fflush(stdin);
    scanf("%d", &numAGuests[currentUser]);

    //Enter Number of Child guests
    printf("\nHow many children (=<16) are staying in the room? (?/4):");
    fflush(stdin);
    scanf("%d", &numCGuests[currentUser]);

    //Enter Board type
    printf("\n\n------------- Board Rates (in GBP) --- *PER PERSON*, *PER DAY* -------------");
    printf("\n           Full Board = 20, Half Board = 15, Bed & Breakfast = 5");
    printf("\n\nChoose a board: 'FB' - Full Board, 'HB' - Half Board, 'BB' - Bed & Breakfast:");
    fflush(stdin);
    scanf("%s", &boardType[currentUser]);

    //Enter length of stay
    printf("\nEnter your length of stay (in days):");
    fflush(stdin);
    scanf("%d", &lengthOfStay[currentUser]);

    //Enter Newspaper
    printf("\nDo you want a daily newspaper? (y/n):");
    fflush(stdin);
    scanf("%c", &newspaper[currentUser]);

    //Generate bookingID
    srand(time(0));
    int randomNumber = rand() % 900 + 100;
    strcpy(bookingID[currentUser], mainUserName[currentUser]);
    sprintf(bookingID[currentUser] + strlen(bookingID[currentUser]), "%d", randomNumber);
    printf("\nYour Booking ID is: %s\n", bookingID[currentUser]);
}


//bookDinnerTable subprogram
void bookDinnerTable(){
    char input[50];
    int numInput = 1;
    int placeHolder = -1; //For BookingID's respective room number
    int notAnIdCount = 0;

    printf("\nPlease enter your BookingID:");
    fflush(stdin);
    scanf("%s", &input);

    for(int i = 0; i < 6; i++){
        if(strcmp(input, bookingID[i]) == 0){
            printf("\nBookingID found in system...\n");
            placeHolder = i;
            i = 6;
        }
        else{
            notAnIdCount++;
        }
    }

    if(notAnIdCount == 6){
        printf("\nBookingID not found in system.\nReturning to main menu...");
        return;
    }

    if(strcmp(boardType[placeHolder], "BB") == 0){
        printf("\nYou chose B&B, you cannot book a table.\n");
        return;
    }

    //int table[3][2] = {{},{0,0} }; //Endor, Naboo, Tatooine. 7pm and 9pm - Alex
    //i=table, j=time
    printf("\nTable numbers:\n1 = Endor, 2 = Naboo, 3 = Tatooine\nThese tables are free:");
    for (int i = 0; i < 3; ++i){
        if(table[i][0] == -1 && table[i][1] == -1){
            printf("\nTable %d is free at 7pm and 9pm", i+1);
        }
        if(table[i][0] == -1 && table[i][1] != -1){
            printf("\nTable %d is free at 7pm", i+1);
        }
        if(table[i][0] != -1 && table[i][1] == -1){
            printf("\nTable %d is free at 9pm", i+1);}
    }

    if(table[0][0] != -1 && table[0][1] != -1 && table[1][0] != -1 && table[1][1] != -1 && table[2][0] != -1 && table[2][1] != -1){
        printf("\nApologies, all tables are currently unavailable");
        return;
    }

    printf("\nWhat table would you like? (1/2/3):");
    fflush(stdin);
    scanf("%d", &numInput);


    //ALL BOOKINGS ARE DONE IN THE CODE BELOW! -1 = AVAILABLE, OTHERWISE THE ARRAY VALUE IS THE ROOM ARRAY VALUE THAT HAS BOOKED THE ROOM
    //ENDOR BOOKINGS -----------------------------------------------------------------------
    //ENDOR chosen when all times free
    if(numInput == 1 && table[0][0] == -1 && table[0][1] == -1){
        printf("\nBooking for table number 1 - Endor:");
        printf("\nWhat time would you like to book for? Option 1: 7pm, Option 2: 9pm");
        printf("\n(1/2):");
        scanf("%d", &numInput);
        if(numInput == 1){
            printf("\nThank you for booking Endor at 7pm");
            table[0][0] = placeHolder;
            return;
        }
        if(numInput == 2){
            printf("\nThank you for booking Endor at 9pm");
            table[0][1] = placeHolder;
            return;
        }
    }

    //ENDOR booked when only  7pm is free
    if(numInput == 1 && table[0][0] == -1 && table[0][1] != -1){
        printf("\nBooking for table number 1 - Endor:");
        printf("\nThank you for booking Endor at 7pm");
        table[0][0] = placeHolder;
        return;
    }

    //ENDOR booked when only  9pm is free
    if(numInput == 1 && table[0][0] != -1 && table[0][1] == -1){
        printf("\nBooking for table number 1 - Endor:");
        printf("\nThank you for booking Endor at 9pm");
        table[0][1] = placeHolder;
        return;
    }

    //ENDOR booked when no times are free
    if(numInput == 1 && table[0][0] != -1 && table[0][1] != -1){
        printf("\nBooking for table number 1 - Endor:");
        printf("\nApologies, all times for Endor are currently unavailable");
        return;
    }
    //ENDOR BOOKINGS END -------------------------------------------------------------------



    //NABOO BOOKINGS -----------------------------------------------------------------------
    //NABOO chosen when all times free
    if(numInput == 2 && table[1][0] == -1 && table[1][1] == -1){
        printf("\nBooking for table number 2 - Naboo:");
        printf("\nWhat time would you like to book for? Option 1: 7pm, Option 2: 9pm");
        printf("\n(1/2):");
        scanf("%d", &numInput);
        if(numInput == 1){
            printf("\nThank you for booking Naboo at 7pm");
            table[1][0] = placeHolder;
            return;
        }
        if(numInput == 2){
            printf("\nThank you for booking Naboo at 9pm");
            table[1][1] = placeHolder;
            return;
        }
    }

    //NABOO booked when only  7pm is free
    if(numInput == 2 && table[1][0] == -1 && table[1][1] != -1){
        printf("\nBooking for table number 2 - Naboo:");
        printf("\nThank you for booking Naboo at 7pm");
        table[1][0] = placeHolder;
        return;
    }

    //NABOO booked when only  9pm is free
    if(numInput == 2 && table[1][0] != -1 && table[1][1] == -1){
        printf("\nBooking for table number 2 - Naboo:");
        printf("\nThank you for booking Naboo at 9pm");
        table[1][1] = placeHolder;
        return;
    }

    //NABOO booked when no times are free
    if(numInput == 2 && table[1][0] != -1 && table[1][1] != -1){
        printf("\nBooking for table number 2 - Naboo:");
        printf("\nApologies, all times for Naboo are currently unavailable");
        return;
    }
    //NABOO BOOKINGS END -------------------------------------------------------------------



    //TATOOINE BOOKINGS -----------------------------------------------------------------------
    //TATOOINE chosen when all times free
    if(numInput == 3 && table[2][0] == -1 && table[2][1] == -1){
        printf("\nBooking for table number 3 - Tatooine:");
        printf("\nWhat time would you like to book for? Option 1: 7pm, Option 2: 9pm");
        printf("\n(1/2):");
        scanf("%d", &numInput);
        if(numInput == 1){
            printf("\nThank you for booking Tatooine at 7pm");
            table[2][0] = placeHolder;
            return;
        }
        if(numInput == 2){
            printf("\nThank you for booking Tatooine at 9pm");
            table[2][1] = placeHolder;
            return;
        }
    }

    //TATOOINE booked when only  7pm is free
    if(numInput == 3 && table[2][0] == -1 && table[2][1] != -1){
        printf("\nBooking for table number 3 - Tatooine:");
        printf("\nThank you for booking Tatooine at 7pm");
        table[2][0] = placeHolder;
        return;
    }

    //TATOOINE booked when only  9pm is free
    if(numInput == 3 && table[2][0] != -1 && table[2][1] == -1){
        printf("\nBooking for table number 3 - Tatooine:");
        printf("\nThank you for booking Tatooine at 9pm");
        table[2][1] = placeHolder;
        return;
    }

    //TATOOINE booked when no times are free
    if(numInput == 3 && table[2][0] != -1 && table[2][1] != -1){
        printf("\nBooking for table number 3 - Tatooine:");
        printf("\nApologies, all times for Tatooine are currently unavailable");
        return;
    }
    //TATOOINE BOOKINGS END -------------------------------------------------------------------
}
