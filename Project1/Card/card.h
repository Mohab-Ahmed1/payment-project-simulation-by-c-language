/*start of card.h*/
#ifndef card_h
#define card_h

//macros define
//______________________________________________
typedef unsigned char uint8_t;

//##type def defines###
//______________________________________________
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;


typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;
//#global variables
// -------------------------------------------------
ST_cardData_t input;
// ##prototypes defines##
//______________________________________________
//get card holder name function 
//input:pointer to card data struct to store data
//outputs: error flag as EN_cardError_t  enum
//function: 1- scan for the cardholder's name and store it into card data.
//          2-check for data range 20 to 24 and not null
//          3-print wrong name or card is ok 
EN_cardError_t getCardHolderName ( ST_cardData_t* cardData );

//get card expired date function 
//input:pointer to card data structure to store data
//output:error flag as EN_cardError_t  enum
//function:1-ask for the card expire date and stor data
 //        2-take the Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
//         3-print wrong formate if exp date is null or not 5 characters
//         4-print card ok if every check is ok 
EN_cardError_t getCardExpiryDate ( ST_cardData_t* cardData );

//get card primary account pan number
//input:pointer to card data structure to store data
//output:error flag as EN_cardError_t  enum
//function : 1-will ask for the card pan number
//           2-check number exists in range from 16 min to 19 max and not Null
//             3-will return wrong ban or card ok 
EN_cardError_t getCardPAN ( ST_cardData_t* cardData );
//#helping functions
//------------------------------------------------------
// is all the chracters are numbers
// input: the array i want to check 
// output: integer flag for the result
// function:returns 1 if all the array are numbers and 0 if not
int ISarrayallnumbers ( char* prr );

//is all the characters are letters
// input: the array i want to check 
// output: integer flag for the result
// function:returns 1 if all the array are letters and 0 if not
int ISarrayallletters ( char* arr );

//##test functions
// -----------------------------------------------------------------
//test fucntion get card holder name test function 
//input:void
//output :void
//functions: runs as a script to test all the possiple inputs to the system 
//			takes the data from "card_name_test.txt"
void getCardHolderNameTest ( void );

//test fucntion get card exp date test
//input :void
//output :void
//function :runs as script to test all the possible inputsand reads data from card_expdate_test.txt
void getCardExpiryDateTest ( void );
//test function get card pan number test
//input:void
//output :void
//functions:  runs as a script to test all the possiple inputs to the system 
//			takes the data from "card_pan_num_test.txt"
void getCardPANTest ( void );

#endif
/*end of card.h*/