
/*start of server.h*/
#ifndef server_h
#define server_h
#include "../Card/card.h"
#include"../Terminal/terminal.h"
//##global variables###
// -------------------------------------
typedef unsigned int uint32_t;

//##Macros define###
//______________________________________________
typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transState_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;


typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;

typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;
// ##prototypes defines##
//______________________________________________
//function receive transaction data function
//input:pointer to the ST_transaction_t servar data pointer
//output : an enum flag of FRAUD_CARD or DECLINED_INSUFFECIENT_FUND or DECLINED_STOLEN_CARD or APPROVED or INTERNAL_SERVER_ERROR
//function ; 1-takes all the transaction data
//          2-validate the date and returns a flag of FRAUD_CARD or DECLINED_INSUFFECIENT_FUND or DECLINED_STOLEN_CARD or APPROVED or INTERNAL_SERVER_ERROR
//          3-update the date base with the result of approved transactions
EN_transState_t recieveTransactionData(ST_transaction_t* transData);
//function is valid account function
//input: card date of the user and account refrence to the provided pan number in the server db
//output: an enum flag (ACCOUNT_NOT_FOUND & SERVER_OK ) and refrence to accoun or NULL if not existing
//function :1-this function takes card date and validate if the account to this card exists or not 
//          2-checks the pan exists in server db or not
//          3-returns a flag enum ACCOUNT_NOT_FOUND  or SERVER_OK 
//          4-refrence to account if exists or null if not exist
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence);
//is blocked account function
//input:pointer to the refrence to the account
//output:flag as enum SERVER_OK or BLOCKED_ACCOUNT
//function:it checks the acount refrence to be blocked or not 
//          if blocked it returns BLOCKED_ACCOUNT if not it returns SERVER_OK
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);
//is amount avilable function
//input :pointer to the account refrence and pointer to the terminal date 
//output:a flag enum that will return LOW_BALANCE or SERVER_OK
//function:it cpmpare data from terminal data with the data from the refrence account
//         if the transection greater than the avilable balance it returns LOW_BALANCE
//         if not it returns SERVER_OK
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);

//is save transaction date
//input: pointer to the teransaction struct
//output: save all the required data in the trans date & returns a flag enum of the transection current state
//function: 1-store all transaction data in the transactions database.
//          2- gives a sequence number to a transaction that increase with each proccess
//          3-it saves any type of transaction, APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
//          4-will list all saved transactions using the listSavedTransactions function.
EN_serverError_t saveTransaction(ST_transaction_t* transData);

//helping function
// input a pointer to the refrence data
// output:void
// function this function edit the data base of the system after every approved oberation
void databaseedit(ST_transaction_t* transData3);
//list saved transaction function
//input:void
//output:pointer to the transectiondb
//function: this function prints al the transaction found in the transection db
void listSavedTransactions(ST_transaction_t* transData2);


//testfunction isValidAccount Test
//input:void
//output:void
//function: will take the data existed in text file "is_valid_account_test.txt" and 
//          compare it with an existing data base in txt file" server_side_accounts_db.txt"
//          1-if i found the data i return server ok and put data in account refrence 
//          2-if not found the data it return ACCOUNT_NOT_FOUND and null to refrence data
void isValidAccountTest(void);


//testfunction is blocked account
//input:void
//output:void
//function :takes the pan numbers from the test accounts in txt file "IS_Blocked_account_test.txt"
//          if the refrenced pan is blocked it prints blocked account if valid it prints valid account
void isBlockedAccountTest(void);

//test function is amount avilable
//input: void
//output: void
//function this function reads a script of pan numbers and transection values from txt file "is_Amount_avilable_test.txt"
//          if the balnce is enough it prints "SERVER_OK" else returns "Low balance"
void isAmountAvailableTest(void);

//testfunction save transection test 
//input:void
//output void
//this function takes the pan number and the transection ammount from a text file "save_transection_test.txt"
//      and if the card is fraud it prints fraud card ,if no suffient funds it prints DECLINED_INSUFFECIENT_FUND
//     and if blocked card it prints decliend stolen card and if all ok it prints approved
void saveTransactionTest(void);
//test list function
//input: void
//output:void
//function: it takes data from a txt file "list_saved_transection_test.txt" 
//and list the output recite in txt file "server_side_transectio_db.txt"
void listSavedTransactionsTest(void);

//test receive transaction data function
//input: void
//output void
//function :it takes a script of data from text file "receive_transaction_data_test.txt" and 
//          edit the data base if any approved operations and returns a receit for all the operations
void recieveTransactionDataTest(void);
#endif
/*end of server.h*/