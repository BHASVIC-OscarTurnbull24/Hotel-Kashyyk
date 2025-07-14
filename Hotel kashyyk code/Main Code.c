// Created by alexc on 15/11/2024.
//
// The Main Code
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char mainUserName[6][50];
int dateOfBirth[6][3]; //[x][0] is DD, [1] is MM, [2] is YY, All together is DD/MM/YY.
// (For this variable, when a zero is entered anywhere, it is automatically removed
// e.g. "01/01/08" is 1 1 8, "5/11/25" is 5 11 25)
int numAGuests[6];
int numCGuests[6];
char boardType[6][3];
int lengthOfStay[6];
char newspaper[6]; //y == yes, n == no
int currentUser =-1; //HELLO OSCAR READ PLEASE - When printing this for the user to see the room number
//we need to add 1 to the value so it looks right (as the array is 0-5 not 1-6).
int room[6] = {0, 0, 0, 0, 0, 0}; //stores 0 for available, 1 for unavailable
char bookingID[6][50];
int table[3][2] = {
    /*Endor*/ {-1, -1},
    /*Naboo*/{-1, -1},
    /*Tatooine*/{-1, -1}
}; //Endor, Naboo, Tatooine. 7pm and 9pm.
//-1 = available, any other number is the room number (in room array) that has booked the table.

void checkIn();
void bookDinnerTable();
void checkOut();
void quitProgram();
int userValidation();



int main(void) {
    float placeHolder;
    int systemSwitch = 1; //1 = On, 0 = Off
    printf("\n\nHello, welcome to the Kashyyyk Hotel!\n\n");
    while(systemSwitch == 1){
        printf("\n1 - Check In\n2 - Book a Dinner Table\n3 - Check Out\n4 - Quit Program");
        printf("\nPlease choose a service (1/2/3/4):");
        fflush(stdin);
        scanf("%f", &placeHolder);
        int placeHolder2 = placeHolder;
        if(placeHolder != placeHolder2){
            printf("\nApologies, that is not an option\n");
        }

        else{
            int choice = placeHolder2;

            switch (choice){
            case 1: //RUNS checkIn SUBPROGRAM
                printf("\nChecking In...\n\n");
                checkIn();
                break;
            case 2: //RUNS bookDinnerTable SUBPROGRAM
                printf("\nBooking a Dinner Table...\n\n");
                bookDinnerTable();
                break;
            case 3: //RUNS checkOut SUBPROGRAM
                printf("\nChecking Out...\n\n");
                checkOut();
                break;
            case 4: //RUNS quitProgram SUBPROGRAM
                printf("\nQuitting Program...\n\n");
                quitProgram();
                break;
            case 12345: //ADMIN 'CODE' TO END ENTIRE PROGRAM/MAIN
                printf("\nAdmin code accepted. Exiting...\n\n");
                systemSwitch = 0;
                break;
            default: //ERROR WHEN INPUT IS NOT 1/2/3/4/12345
                printf("\nApologies, that is not an option\n");
            }
        }
    }

    return 0;
}



//checkIn subprogram
void checkIn(){
    float placeHolder;
    //If rooms are free print them
    printf("\nThese rooms are currently available:\n");
    for (int i = 0; i < 6; i++){
        if(room[i] == 0){
            printf("\nRoom %d is available", i+1);
        }
    }

    //If no rooms are available
    if(room[0] == 1 && room[1] == 1 && room[2] == 1 && room[3] == 1 && room[4] == 1 && room[5] == 1){
        printf("\nApologies, all rooms are currently unavailable\n");
        return;
    }

    //Enter Room
    printf("\n\n------------- Room Rates (in GBP)  *PER ROOM*, *PER DAY* -------------");
    printf("\n     Rooms 1 & 2 = 100, Room 3 = 85, Room 4 & 5 = 75, Room 6 = 50");
    printf("\n\nChoose a Room (1/2/3/4/5/6):");
    scanf("%f", &placeHolder);

    int placeHolder2 = placeHolder;
    if(placeHolder != placeHolder2){
        printf("\nApologies, this room is not an option\n");
        currentUser = -1;
        return;
    }

    currentUser = placeHolder2;
    currentUser -= 1; //Converts room number to correct array number

    //Chosen Room nonReal
    if(currentUser != 0 && currentUser != 1 && currentUser != 2 && currentUser != 3 && currentUser != 4 && currentUser != 5){
        printf("\nApologies, this room is not an option\n");
        currentUser = -1;
        return;
    }

    //Chosen Room unavailable
    if(room[currentUser] == 1){
        printf("\nApologies, this room is currently unavailable\n");
        currentUser = -1;
        return;
    }

    //chosen room available
    if(room[currentUser] == 0){
        printf("\nBooking Room %d:", currentUser+1);
        room[currentUser] = 1; //Makes chosen room unavailable

    }

    //Enter Name
    printf("\nEnter Your Full Name (Please enter it without any spaces):");
    fflush(stdin);
    scanf("%s", &mainUserName[currentUser]);

    //Enter Date of Birth
    do{
        printf("\nEnter Your Date of Birth (DD/MM/YY):"); //e.g: "01/01/08", "5/11/25"
        fflush(stdin);
        scanf("%d/%d/%d", &dateOfBirth[currentUser][0], &dateOfBirth[currentUser][1], &dateOfBirth[currentUser][2]);
    }while(dateOfBirth[currentUser][0] < 1 || dateOfBirth[currentUser][1] < 1 || dateOfBirth[currentUser][2] < 0 ||
        dateOfBirth[currentUser][0] > 31 || dateOfBirth[currentUser][1] > 12 || dateOfBirth[currentUser][2] > 99);


    //ENTER GUESTS
    do{
        //Enter Number of Adult guests
        do{
            printf("\nHow many adults are staying in the room? (?/4 total guests):");
            fflush(stdin);
            scanf("%f", &placeHolder);
            placeHolder2 = placeHolder;
        }while(placeHolder2 > 4  || placeHolder2 < 0 || placeHolder != placeHolder2 && placeHolder != 0);
        numAGuests[currentUser] = placeHolder2;

        int totalGuests = 4 - numAGuests[currentUser];

        //Enter Number of Child guests
        if(totalGuests > 0){
            do{
                printf("\nHow many children (=<16) are staying in the room? (?/4 total guests):");
                fflush(stdin);
                scanf("%f", &placeHolder);
                placeHolder2 = placeHolder;
            }while(placeHolder2 > totalGuests || placeHolder2 < 0 || placeHolder != placeHolder2 && placeHolder != 0);
            numCGuests[currentUser] = placeHolder2;
        }
    }while( numAGuests[currentUser] == 0 && numCGuests[currentUser] == 0 );


    //Enter Board type
    printf("\n\n------------- Board Rates (in GBP) --- *PER PERSON*, *PER DAY* -------------");
    printf("\n           Full Board = 20, Half Board = 15, Bed & Breakfast = 5");
    do{
        printf("\n\nChoose a board: 'FB' - Full Board, 'HB' - Half Board, 'BB' - Bed & Breakfast:");
        fflush(stdin);
        scanf("%s", &boardType[currentUser]);
    }while(strcmp(boardType[currentUser],"fb") != 0 && strcmp(boardType[currentUser],"hb") != 0 && strcmp(boardType[currentUser],"bb") != 0
        && strcmp(boardType[currentUser],"FB") != 0 && strcmp(boardType[currentUser],"HB") != 0 && strcmp(boardType[currentUser],"BB") != 0);

    //Enter length of stay
    do{
        printf("\nEnter your length of stay (in days):");
        fflush(stdin);
        scanf("%f", &placeHolder);
        placeHolder2 = placeHolder;
    }while(placeHolder2 < 1 || placeHolder != placeHolder2);
    lengthOfStay[currentUser] = placeHolder2;

    //Enter Newspaper
    do{
        printf("\nDo you want a daily newspaper? (y/n):");
        fflush(stdin);
        scanf("%c", &newspaper[currentUser]);
    }while(newspaper[currentUser] != 'y' && newspaper[currentUser] != 'n' && newspaper[currentUser] != 'Y' && newspaper[currentUser] != 'N');

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
    int placeHolder = -1; //For BookingID's respective room number
    int notAnIdCount = 0;
    float holder;

    if(bookingID[0][0] == '\0' && bookingID[1][0] == '\0' && bookingID[2][0] == '\0'
    && bookingID[3][0] == '\0' && bookingID[4][0] == '\0' && bookingID[5][0] == '\0'){
        printf("\nError - There are no guests checked in currently.\n\n");
        return;
    }

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
        printf("\nBookingID not found in system.\nReturning to main menu...\n");
        return;
    }

    if(strcmp(boardType[placeHolder], "BB") == 0){
        printf("\nYou chose B&B, you cannot book a table.\n");
        return;
    }

    //int table[3][2] = {{},{0,0} }; //Endor, Naboo, Tatooine. 7pm and 9pm - Alex
    //i=table, j=time
    printf("\nTable numbers:\n1 = Endor, 2 = Naboo, 3 = Tatooine\nThese tables are free:\n");
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
        printf("\nApologies, all tables are currently unavailable\n\n");
        return;
    }

    printf("\n\nWhat table would you like? (1/2/3):");
    fflush(stdin);
    scanf("%f", &holder);
    int holder2 = holder;
    int numInput = holder2;

    if(numInput != 1 && numInput != 2 && numInput != 3 || holder != holder2){
        printf("\n\nApologies, this table is not an option\n");
        return;
    }

    //ALL BOOKINGS ARE DONE IN THE CODE BELOW! -1 = AVAILABLE, OTHERWISE THE ARRAY VALUE IS THE ROOM ARRAY VALUE THAT HAS BOOKED THE ROOM
    //ENDOR BOOKINGS -----------------------------------------------------------------------
    //ENDOR chosen when all times free
    if(numInput == 1 && table[0][0] == -1 && table[0][1] == -1){
        printf("\nBooking for table number 1 - Endor:");
        printf("\nWhat time would you like to book for? Option 1: 7pm, Option 2: 9pm");
        printf("\n(1/2):");
        scanf("%f", &holder);
        holder2 = holder;
        numInput = holder2;
        if(numInput != 1 && numInput != 2 || holder != holder2){
            printf("\nApologies, this time is not an option\n");
            return;
        }
        if(numInput == 1){
            printf("\nThank you for booking Endor at 7pm\n");
            table[0][0] = placeHolder;
            return;
        }

        printf("\nThank you for booking Endor at 9pm\n");
        table[0][1] = placeHolder;
        return;
    }

    //ENDOR booked when only  7pm is free
    if(numInput == 1 && table[0][0] == -1 && table[0][1] != -1){
        printf("\nBooking for table number 1 - Endor:");
        printf("\nThank you for booking Endor at 7pm\n");
        table[0][0] = placeHolder;
        return;
    }

    //ENDOR booked when only  9pm is free
    if(numInput == 1 && table[0][0] != -1 && table[0][1] == -1){
        printf("\nBooking for table number 1 - Endor:");
        printf("\nThank you for booking Endor at 9pm\n");
        table[0][1] = placeHolder;
        return;
    }

    //ENDOR booked when no times are free
    if(numInput == 1 && table[0][0] != -1 && table[0][1] != -1){
        printf("\nBooking for table number 1 - Endor:");
        printf("\nApologies, all times for Endor are currently unavailable\n");
        return;
    }
    //ENDOR BOOKINGS END -------------------------------------------------------------------



    //NABOO BOOKINGS -----------------------------------------------------------------------
    //NABOO chosen when all times free
    if(numInput == 2 && table[1][0] == -1 && table[1][1] == -1){
        printf("\nBooking for table number 2 - Naboo:");
        printf("\nWhat time would you like to book for? Option 1: 7pm, Option 2: 9pm");
        printf("\n(1/2):");
        scanf("%f", &holder);
        holder2 = holder;
        numInput = holder2;
        if(numInput != 1 && numInput != 2 || holder != holder2){
            printf("\nApologies, this time is not an option\n");
            return;
        }
        if(numInput == 1){
            printf("\nThank you for booking Naboo at 7pm\n");
            table[1][0] = placeHolder;
            return;
        }

        printf("\nThank you for booking Naboo at 9pm\n");
        table[1][1] = placeHolder;
        return;
    }

    //NABOO booked when only  7pm is free
    if(numInput == 2 && table[1][0] == -1 && table[1][1] != -1){
        printf("\nBooking for table number 2 - Naboo:");
        printf("\nThank you for booking Naboo at 7pm\n");
        table[1][0] = placeHolder;
        return;
    }

    //NABOO booked when only  9pm is free
    if(numInput == 2 && table[1][0] != -1 && table[1][1] == -1){
        printf("\nBooking for table number 2 - Naboo:");
        printf("\nThank you for booking Naboo at 9pm\n");
        table[1][1] = placeHolder;
        return;
    }

    //NABOO booked when no times are free
    if(numInput == 2 && table[1][0] != -1 && table[1][1] != -1){
        printf("\nBooking for table number 2 - Naboo:");
        printf("\nApologies, all times for Naboo are currently unavailable\n");
        return;
    }
    //NABOO BOOKINGS END -------------------------------------------------------------------



    //TATOOINE BOOKINGS -----------------------------------------------------------------------
    //TATOOINE chosen when all times free
    if(numInput == 3 && table[2][0] == -1 && table[2][1] == -1){
        printf("\nBooking for table number 3 - Tatooine:");
        printf("\nWhat time would you like to book for? Option 1: 7pm, Option 2: 9pm");
        printf("\n(1/2):");
        scanf("%f", &holder);
        holder2 = holder;
        numInput = holder2;
        if(numInput != 1 && numInput != 2 || holder != holder2){
            printf("\nApologies, this time is not an option\n");
            return;
        }
        if(numInput == 1){
            printf("\nThank you for booking Tatooine at 7pm\n");
            table[2][0] = placeHolder;
            return;
        }

        printf("\nThank you for booking Tatooine at 9pm\n");
        table[2][1] = placeHolder;
        return;
    }

    //TATOOINE booked when only  7pm is free
    if(numInput == 3 && table[2][0] == -1 && table[2][1] != -1){
        printf("\nBooking for table number 3 - Tatooine:");
        printf("\nThank you for booking Tatooine at 7pm\n");
        table[2][0] = placeHolder;
        return;
    }

    //TATOOINE booked when only  9pm is free
    if(numInput == 3 && table[2][0] != -1 && table[2][1] == -1){
        printf("\nBooking for table number 3 - Tatooine:");
        printf("\nThank you for booking Tatooine at 9pm\n");
        table[2][1] = placeHolder;
        return;
    }

    //TATOOINE booked when no times are free
    if(numInput == 3 && table[2][0] != -1 && table[2][1] != -1){
        printf("\nBooking for table number 3 - Tatooine:");
        printf("\nApologies, all times for Tatooine are currently unavailable\n");
    }
    //TATOOINE BOOKINGS END -------------------------------------------------------------------
}


//check out subroutine
void checkOut() {
    //declares variables for this subroutine
    float roomCost = 0;
    float boardCost = 0;
    int is65Discount = 0;

    //If no user is currently logged in then userValidation is called to use the bookingID to log in
    if(currentUser == -1) {
        int temp = userValidation();
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
            //else means their birthday has happened, or it is their birthday
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
                roomCost *= 0.9;
                is65Discount = 1;
            }
        }
    }



    //ELSE the birth year of the user is less than or equal to the current year it is assumed they were born in the 2000s.
    //(this is meaningless for 2024, but I want this to work for any years 2000-2099)
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
            //else means their birthday has happened, or it is their birthday
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


    //CALCULATE USER'S AGE TO APPLY DISCOUNT END------------

    //calculates total cost
    float guestTotalBill = roomCost + boardCost;
    if(newspaper[currentUser] == 'y') {
        guestTotalBill += 5.50;
    }



    //produces the final bill for the group
    printf("Guest: '%s'     BookingId: '%s'\nThank you for staying with the Kasyyyk Hotel we hope you had a pleasant stay.\n\nBill:\n", mainUserName[currentUser], bookingID[currentUser]);
    if(is65Discount == 1) {
        printf("Room cost: $%.2f (with 10%% off for over 65's discount)\n",roomCost);
    }
    else {
        printf("Room cost: $%.2f\n", roomCost);
    }
    printf("Board cost: $%.2f\n", boardCost);
    if(newspaper[currentUser] == 'y') {
        printf("Daily newspaper cost: $5.50 \n");
    }
    printf("Total Cost of stay: $%.2f\n", guestTotalBill);

    //makes the room they were staying in available and quits the program
    boardType[currentUser][0] = '\0';
    numAGuests[currentUser] = 0;
    numCGuests[currentUser] = 0;
    room[currentUser] = 0;
    bookingID[currentUser][0] = '\0';
    
    for(int k = 0;k<3;k++) {
        for(int l = 0;l<2;l++) {
            if(table[k][l] == currentUser) {
                table[k][l] = -1;
            }
        }
    }

    quitProgram();
}


//quitProgram subroutine
void quitProgram() {
    printf("\n\nHello, welcome to the Kashyyyk Hotel!\n\n");
    // resets the current user so a new user can sign in
    currentUser = -1;
}

//userValidation subroutine
int userValidation() {
    char input[50];
    int placeHolder = -1; //For BookingID's respective room number
    int notAnIdCount = 0;

    if(bookingID[0][0] == '\0' && bookingID[1][0] == '\0' && bookingID[2][0] == '\0'
        && bookingID[3][0] == '\0' && bookingID[4][0] == '\0' && bookingID[5][0] == '\0'){
        printf("\nError - There are no guests checked in currently.\n\n");
        return -1;
    }

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
