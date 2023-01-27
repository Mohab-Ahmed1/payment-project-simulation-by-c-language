/*start of terminal.h*/
#ifndef terminal_h
#define terminal_h
#include "../Card/card.h"
//##type def defines###
//______________________________________________
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

//#global variables
//---------------------------------
ST_terminalData_t terminalinput;

// ##prototypes defines##
//______________________________________________
 //get transection date from user
//input:pointer to terminal data struct to store data
//outputs: error flag as ST_terminalData_t  enum
//function:1-will ask the user for the transetion date and store it in the terminal
//         2-check for data to not be null or not 10 chracters       
//         3-will check the formate DD/MM/YYYY,
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);
//get transection date from the system
//input:pointer to terminal data struct to store data
//outputs: error flag as ST_terminalData_t  enum
//function: get the DD/MM/YYYY from ths system then save it to the struct
void getTransactionDateauto(ST_terminalData_t* termData);
//to check if the card expired
//input: pointer to card data and a pointer to terminal data
// output :flag of the output as EN_terminalError_t enum
// function :it compares the card expiry date with the transaction date.
//if expire date >= transection date returns terminal ok else returns expired_card
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);

//to get the transection amount from the user
//input:pointer to the terminal data 
//output: is a error flag as enum 
//function 1-asks for the transection data and save in the terminal data
//         2-check the ammount is less than or equal 0 
//         3-if 0 or less it returns invalid_ammount else returns Terminal_ok
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);
//check is blow max amount
//input :pointer to the terminal data struct address
// output : is a flag as enum  EXCEED_MAX_AMOUNT  &  TERMINAL_OK
//function: this function compares the terminal transamount with the max amunt of the system
//          1- if less than it returns Terminal ok if exceed it returns Exceed_max_Amount 
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);

//set the Max amount
//input:pointer to the terminal data input struct address and a float variable of the max amount required
// output: is an error flag as enum INVALID_MAX_AMOUNT  or TERMINAL_OK
// function:1-check that the max amount is not 0  
//          2-will take the maxmimumamount and stor it in the terminalinput Max trans amount
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);
//check  is valid card pan
//input: pointer to the card data input struct
// output :a eror flag as enum INVALID_CARD or TERMINAL_OK
//function : 1-this function takes the input from the user then checks if the luhn algorith applies to it or not
//           2-if the card is valid it returns TERMINAL_OK else returns INVALID_CARD
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData); // Optional

//##test functions
// -----------------------------------------------------------------
//test fucntion get transaction date test function 
//input:void
//output :void
//functions: runs as a script to test all the possiple inputs to the system 
//			takes the data from "Transaction_date_test.txt"
void getTransactionDateTest(void);

//test fucntion get transaction date test function 
//input:void
//output :void
//function :this function runs as script to compare the exp dates with transetion dates
void isCardExpiredtest(void);

//test function get transection amount test
//input: void
//output:void
//function :this function runs a script of inputs from "transaction_amount_test.txt"
//          to test all the possiple inputs to the system
void getTransactionAmountTest(void);

//test function isbelow max amount test
//input:void
// output:void
// function :this function reads from a script of text file "is_below_max_amount_test.txt" and compare it with 
//           a pre defined max amount in #define MAX_Amount
void isBelowMaxAmountTest(void);

//test function to set max amount
//input:void
//output: void
//function:1-this function reads from a script of text file from "Set_max_amount_Test.txt"
//         2-checks every input to be not 0 and its a number
void setMaxAmountTest(void);

//test function is valid card pan
//input:void
//output void
//function :this function runs a script from "is_valid_card_pan_test.txt" 
//          and checks if the pan number is luhn number or not
void isValidCardPANTest(void);
#endif
/*end of terminal.h*/