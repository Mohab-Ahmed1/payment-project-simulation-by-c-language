#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include "server.h"
ST_accountsDB_t ServerRefrence;
ST_cardData_t input;
ST_terminalData_t terminalinput;
ST_transaction_t transectioninput;
int Line_to_edit_in_data_base;
int value_to_be_edited;
int transeseq=0;
int NEW_RECEITE_LINE = 0;

//function is valid account function
//input: card date of the user and account refrence to the provided pan number in the server db
//output: an enum flag (ACCOUNT_NOT_FOUND & SERVER_OK ) and refrence to accoun or NULL if not existing
//function :1-this function takes card date and validate if the account to this card exists or not 
//          2-checks the pan exists in server db or not
//          3-returns a flag enum ACCOUNT_NOT_FOUND  or SERVER_OK 
//          4-refrence to account if exists or null if not exist
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
//#define DEBUG
	FILE* server_DB;
	char   line[40];
	int i = 1;
	int getdata = 0;
	server_DB = fopen("server date base/server_side_accounts_db.txt", "r");
	if (server_DB == NULL) {
		printf("Error!");
	}
	while (fgets(line, 40, server_DB)) {
		
			line[strlen(line) - 1] = '\0';  //##### Imp to comment when reding from text#####//
		
		if (getdata == 0) {
			if (i % 3 == 1 && strcmp(cardData->primaryAccountNumber, line) == 0) {
				getdata=2;
				strcpy(accountRefrence->primaryAccountNumber, line);
				Line_to_edit_in_data_base = i+2;
#ifdef DEBUG
				printf("found at %d\n", i);
				printf(line);
#endif // DEBUG

				//the tested code
				//end of tested code
			}
			else {
				i++;
				//printf(line);
			}	
		}else if(getdata ==2 ) {
#ifdef DEBUG
			printf("\n%s", line);

#endif // DEBUG
			accountRefrence->state = atoi(line);

			i++;
			getdata--;
		}
		else {
#ifdef DEBUG
			printf("\n%d", atoi(line));
#endif // DEBUG
			accountRefrence->balance = atoi(line);
			value_to_be_edited= atoi(line);
			i++;
			getdata--;
			fclose(server_DB);
			return SERVER_OK;
		}

	}
	fclose(server_DB);
#ifdef DEBUG
		printf("account not found");
#endif // DEBUG
	accountRefrence->balance = 0;
	accountRefrence->state = BLOCKED;
	strcpy(accountRefrence->primaryAccountNumber, cardData->primaryAccountNumber);
	return ACCOUNT_NOT_FOUND;
	
}

//testfunction isValidAccount Test
//input:void
//output:void
//function: will take the data existed in text file "is_valid_account_test.txt" and 
//          compare it with an existing data base in txt file" server_side_accounts_db.txt"
//          1-if i found the data i return server ok and put data in account refrence 
//          2-if not found the data it return ACCOUNT_NOT_FOUND and null to refrence data
void isValidAccountTest(void) {

	//declerations
	FILE* textfile;
	char   read[40];
	int i = 1;
	int j = 1;



	textfile = fopen("Test_scripts/is_valid_account_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : is valid account");

	while (fgets(read, 50, textfile)) {
		
			if (i % 2 == 1) {
				printf("\nTest case %d\n", j);
				j++;
				printf("input data: %s", read);
				//tested code

				strcpy(input.primaryAccountNumber, read);

				if (isValidAccount(&input, &ServerRefrence) == SERVER_OK) {
					printf(" Actual result: server ok \n");
				}
				else {
					printf(" Actual result:  Account Not Found \n");
				}

			}
			else {
				printf(read);

			}
			i++;

		

	}


	fclose(textfile);
}


//is blocked account function
//input:pointer to the refrence to the account
//output:flag as enum SERVER_OK or BLOCKED_ACCOUNT
//function:it checks the acount refrence to be blocked or not 
//          if blocked it returns BLOCKED_ACCOUNT if not it returns SERVER_OK
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence) {

	if (accountRefrence->state == BLOCKED) {
#ifdef DEBUG
		printf("account blocked");
#endif // DEBUG

		return  BLOCKED_ACCOUNT;
	}
	else {
#ifdef DEBUG
		printf("account valid");
#endif // DEBUG

		return SERVER_OK;
	}
}


//testfunction is blocked account
//input:void
//output:void
//function :takes the pan numbers from the test accounts in txt file "IS_Blocked_account_test.txt"
//          if the refrenced pan is blocked it prints blocked account if valid it prints valid account
void isBlockedAccountTest(void) {
	FILE* textfile;
	char   read[50];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/IS_Blocked_account_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : is blocked account");

	while (fgets(read, 50, textfile)) {
		if (i % 2 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input data: %s", read);
			strcpy(input.primaryAccountNumber, read);
			isValidAccount(&input, &ServerRefrence);
			//the tested code
			if (isBlockedAccount(&ServerRefrence) == BLOCKED_ACCOUNT) {
				printf("Actual Result: Blocked Account\n");
			}
			else
			{
				printf("Actual Result: valid account \n");

			}
			//end of tested code
		}
		else {
			printf(read);

		}
		i++;

	}

	fclose(textfile);

}

//is amount avilable function
//input :pointer to the account refrence and pointer to the terminal date 
//output:a flag enum that will return LOW_BALANCE or SERVER_OK
//function:it cpmpare data from terminal data with the data from the refrence account
//         if the transection greater than the avilable balance it returns LOW_BALANCE
//         if not it returns SERVER_OK
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	if (termData->transAmount > accountRefrence->balance) {
	#ifdef DEBUG
		printf("low balance");
	#endif // DEBUG
		return LOW_BALANCE;
	}
	else {
	#ifdef DEBUG

		printf("server is ok ");
	#endif // DEBUG
		return SERVER_OK;
	}
}


//test function is amount avilable
//input: void
//output: void
//function this function reads a script of pan numbers and transection values from txt file "is_Amount_avilable_test.txt"
//          if the balnce is enough it prints "SERVER_OK" else returns "Low balance"
void isAmountAvailableTest(void) {
	FILE* textfile;
	char   read[50];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/is_Amount_avilable_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : is Amount avilable");

	while (fgets(read, 50, textfile)) {
		if (i % 3 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input data: %s", read);
			strcpy(input.primaryAccountNumber, read);
			isValidAccount(&input, &ServerRefrence);
			//the tested code
			
			//end of tested code
		}
		else if (i%3 ==2) {
			printf("input data: %s", read);
			terminalinput.transAmount = atoi(read);
			if (isAmountAvailable(&terminalinput, &ServerRefrence)== LOW_BALANCE) {
				printf("Actual result: low Balance\n");
			}
			else {
				printf("Actual Result : server is ok \n");
			}
		}
		else {
			printf(read);

		}
		i++;

	}

	fclose(textfile);

}

//is save transaction date
//input: pointer to the teransaction struct
//output: save all the required data in the trans date & returns a flag enum of the transection current state
//function: 1-store all transaction data in the transactions database.
//          2- gives a sequence number to a transaction that increase with each proccess
//          3-it saves any type of transaction, APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
//          4-will list all saved transactions using the listSavedTransactions function.
EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	transeseq++;
	transData->transactionSequenceNumber = transeseq;
	//printf("%d", transData->transactionSequenceNumber);
	isValidAccount(&transData->cardHolderData, &ServerRefrence);
	if (isValidCardPAN(&transData->cardHolderData)== INVALID_CARD) {

		//printf("\nfraud_card");
		transData->transState = FRAUD_CARD;
		
		//printf("\n%d",transData->transState);
	}
	else if (isBlockedAccount(&ServerRefrence) == BLOCKED_ACCOUNT) {
		//printf("\nDECLINED_STOLEN_CARD");
		transData->transState = DECLINED_STOLEN_CARD;
		return BLOCKED_ACCOUNT;
		//printf("\n%d", transData->transState);
		
	}
	else if (isAmountAvailable(&transData->terminalData, &ServerRefrence)==LOW_BALANCE) {
		//printf("\DECLINED_INSUFFECIENT_FUND");
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return LOW_BALANCE;
		//printf("\n%d", transData->transState);
	
	}
	else {
		transData->transState = SERVER_OK;
		return SERVER_OK;
	}
	
	
	//return	SERVER_OK;
}



//testfunction save transection test 
//input:void
//output void
//this function takes the pan number and the transection ammount from a text file "save_transection_test.txt"
//      and if the card is fraud it prints fraud card ,if no suffient funds it prints DECLINED_INSUFFECIENT_FUND
//     and if blocked card it prints decliend stolen card and if all ok it prints approved
void saveTransactionTest(void) {

	FILE* textfile;
	char   read[50];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/save_transection_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : save transection function");

	while (fgets(read, 50, textfile)) {
		if (i % 3 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input pan number data: %s", read);
			strcpy(transectioninput.cardHolderData.primaryAccountNumber, read);
			getCardPAN(&transectioninput.cardHolderData);
			//the tested code

			//end of tested code
		}
		else if (i % 3 == 2) {
			printf("input transfer data: %s", read);
			transectioninput.terminalData.transAmount = atoi(read);
			saveTransaction(&transectioninput);
			
			if (transectioninput.transState == FRAUD_CARD) {
				printf("Actual result: FRAUD CARD \n");
			}
			else if(transectioninput.transState ==DECLINED_INSUFFECIENT_FUND) {
				printf("Actual Result : DECLINED INSUFFECIENT FUND\n");
			}
			else if (transectioninput.transState == DECLINED_STOLEN_CARD) {
				printf("Actual Result : DECLINED STOLEN CARD\n");
			}
			else {
				printf("Actual result: Approved \n");
			}

		}
		else {
			printf(read);

		}
		i++;

	}

	fclose(textfile);

}

//list saved transaction function
//input:void
//output:pinter to the 
//function: this function prints al the transaction found in the transection db

void listSavedTransactions(ST_transaction_t* transData2) {
	//int NEW_RECEITE_LINE = 0; declared global
	FILE* receite;
	FILE* Newreceite;
	char   read[50];
	//char   write[50];
	
	int j = 1;
	receite = fopen("server date base/server_side_transectio_db.txt", "r");
	Newreceite= fopen("server date base/server_side_transectio_db.tmp.txt", "w");
	
	if (receite == NULL&& Newreceite==NULL) {
		printf("Error!");
	}
	transData2->transactionSequenceNumber;
	while (1) {

		if (j == 1 && transData2->transactionSequenceNumber ==1) {
			fprintf(Newreceite, "##################\n");
			fprintf(Newreceite, "Transaction Sequence Number:%d\n", transData2->transactionSequenceNumber);
			fprintf(Newreceite, "Transaction Date:%s\n", transData2->terminalData.transactionDate);
			fprintf(Newreceite, "Transaction Amount:%f\n", transData2->terminalData.transAmount);
			if (transData2->transState == FRAUD_CARD) {
				fprintf(Newreceite, "Transaction State: FRAUD CARD \n");
			}
			else if (transData2->transState == DECLINED_INSUFFECIENT_FUND) {
				fprintf(Newreceite, "Transaction State: DECLINED INSUFFECIENT FUND\n");
			}
			else if (transData2->transState == DECLINED_STOLEN_CARD) {
				fprintf(Newreceite, "Transaction State: DECLINED STOLEN CARD\n");
			}
			else if (isCardExpired(&transData2->cardHolderData, &transData2->terminalData) == EXPIRED_CARD) {

				fprintf(Newreceite, "Transaction State: DECLINED Expired CARD\n");
			}
			else if (isBelowMaxAmount(&transData2->terminalData) == EXCEED_MAX_AMOUNT) {

				fprintf(Newreceite, "Transaction State: DECLINED Exceeded terminal max amount\n");
			}
			else {
				fprintf(Newreceite, "Transaction State: Approved \n");
			}
			fprintf(Newreceite, "Terminal Max Amount:%f\n", transData2->terminalData.maxTransAmount);
			fprintf(Newreceite, "Cardholder Name:%s\n", transData2->cardHolderData.cardHolderName);
			fprintf(Newreceite, "pan:%s\n", transData2->cardHolderData.primaryAccountNumber);
			fprintf(Newreceite, "Card Expiration Date:%s\n", transData2->cardHolderData.cardExpirationDate);
			fprintf(Newreceite, "##################\n");
			j++;
				break ;
		}
		else if (j== (transData2->transactionSequenceNumber-1)*11) {
			fprintf(Newreceite, "##################\n");
			fprintf(Newreceite, "Transaction Sequence Number:%d\n", transData2->transactionSequenceNumber);
			fprintf(Newreceite, "Transaction Date:%s\n", transData2->terminalData.transactionDate);
			fprintf(Newreceite, "Transaction Amount:%f\n", transData2->terminalData.transAmount);
			if (transData2->transState == FRAUD_CARD) {
				fprintf(Newreceite, "Transaction State: FRAUD CARD \n");
			}
			else if (transData2->transState == DECLINED_INSUFFECIENT_FUND) {
				fprintf(Newreceite, "Transaction State: DECLINED INSUFFECIENT FUND\n");
			}
			else if (transData2->transState == DECLINED_STOLEN_CARD) {
				fprintf(Newreceite, "Transaction State: DECLINED STOLEN CARD\n");
			}
			else if (isCardExpired(&transData2->cardHolderData, &transData2->terminalData) == EXPIRED_CARD) {

				fprintf(Newreceite, "Transaction State: DECLINED Expired CARD\n");
			}
			else if (isBelowMaxAmount(&transData2->terminalData) == EXCEED_MAX_AMOUNT) {

				fprintf(Newreceite, "Transaction State: DECLINED Exceeded terminal max amount\n");
			}
			else {
				fprintf(Newreceite, "Transaction State: Approved \n");
			}
			fprintf(Newreceite, "Terminal Max Amount:%f\n", transData2->terminalData.maxTransAmount);
			fprintf(Newreceite, "Cardholder Name:%s\n", transData2->cardHolderData.cardHolderName);
			fprintf(Newreceite, "pan:%s\n", transData2->cardHolderData.primaryAccountNumber);
			fprintf(Newreceite, "Card Expiration Date:%s\n", transData2->cardHolderData.cardExpirationDate);
			fprintf(Newreceite, "##################\n");
			j++;
			break;
		}
		else {
			fgets(read, 50, receite);
			fprintf(Newreceite, "%s",read);
			j++;
		}
		
	}
	fclose(receite);
	fclose(Newreceite);
    remove("server date base/server_side_transectio_db.txt");
	rename("server date base/server_side_transectio_db.tmp.txt", "server date base/server_side_transectio_db.txt");
	
}


//test list function
//input: void
//output:void
//function: it takes data from a txt file "list_saved_transection_test.txt" 
//and list the output recite in txt file "server_side_transectio_db.txt"
void listSavedTransactionsTest(void) {

	FILE* textfile;
	char   read[50];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/list_saved_transection_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name :list save transection function");

	while (fgets(read, 50, textfile)) {
		if (i % 3 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input pan number data: %s", read);
			strcpy(transectioninput.cardHolderData.primaryAccountNumber, read);
			getCardPAN(&transectioninput.cardHolderData);
			transectioninput.cardHolderData.primaryAccountNumber[strlen(transectioninput.cardHolderData.primaryAccountNumber) - 1] = '\0';
			getTransactionDateauto(&transectioninput.terminalData);
			//the tested code

			//end of tested code
		}
		else if (i % 3 == 2) {
			printf("input transfer data: %s", read);
			transectioninput.terminalData.transAmount = atoi(read);
			saveTransaction(&transectioninput);
			listSavedTransactions(&transectioninput);
			

		}
		else {
			printf(read);

		}
		i++;

	}

	fclose(textfile);
}
//function receive transaction data function
//input:pointer to the ST_transaction_t servar data pointer
//output : an enum flag of FRAUD_CARD or DECLINED_INSUFFECIENT_FUND or DECLINED_STOLEN_CARD or APPROVED or INTERNAL_SERVER_ERROR
//function ; 1-takes all the transaction data
//          2-validate the date and returns a flag of FRAUD_CARD or DECLINED_INSUFFECIENT_FUND or DECLINED_STOLEN_CARD or APPROVED or INTERNAL_SERVER_ERROR
//          3-update the date base with the result of approved transactions
EN_transState_t recieveTransactionData(ST_transaction_t* transData) {
//#define DEBUG

	EN_serverError_t x = 0;
	getTransactionDateauto(&transData->terminalData);
	x=saveTransaction(transData);
	listSavedTransactions(transData);
	if (isCardExpired(&transData->cardHolderData, &transData->terminalData)== EXPIRED_CARD) {
#ifdef DEBUG
		printf("expired card");
#endif // DEBUG

		return INTERNAL_SERVER_ERROR;
	}
	else if (isBelowMaxAmount(&transData->terminalData) == EXCEED_MAX_AMOUNT) {
#ifdef DEBUG
		printf("Exceed max amount of terminal");
#endif // DEBUG

		return INTERNAL_SERVER_ERROR;
	}
	else {
		listSavedTransactions(transData);
		//isCardExpired(&transData->cardHolderData, &transData->terminalData);
//	isBelowMaxAmount(&transData->terminalData);
	//listSavedTransactions(transData);
		if (isValidAccount(&transData->cardHolderData, &ServerRefrence) == ACCOUNT_NOT_FOUND) {
			return FRAUD_CARD;
		}
		else if (x == LOW_BALANCE) {
			return DECLINED_INSUFFECIENT_FUND;
		}
		else if (x == BLOCKED_ACCOUNT) {
			return DECLINED_STOLEN_CARD;
		}
		else {
			 databaseedit(transData);
			return APPROVED;
		}
	}
	
	
	

	
}
//helping function
// input a pointer to the refrence data
// output:void
// function this function edit the data base of the system after every approved oberation

void databaseedit(ST_transaction_t* transData3) {
	//
	FILE* olddatabase;
	FILE* newdatabase;
	char   read[50];
	//char   write[50];

	int j = 1;
	olddatabase = fopen("server date base/server_side_accounts_db.txt", "r");
	newdatabase = fopen("server date base/server_side_accounts_db.tmp.txt", "w");

	if (olddatabase == NULL && newdatabase == NULL) {
		printf("Error!");
	}
	
	while ((fgets(read, 40, olddatabase)) != NULL) {
		
		if (j == Line_to_edit_in_data_base) {
			fprintf(newdatabase, "%f\n", value_to_be_edited-transData3->terminalData.transAmount);
		}
		else {
			fputs(read, newdatabase);
		}
		j++;
	}
	fclose(olddatabase);
	fclose(newdatabase);
	remove("server date base/server_side_accounts_db.txt");
	rename("server date base/server_side_accounts_db.tmp.txt", "server date base/server_side_accounts_db.txt");

}


//test receive transaction data function
//input: void
//output void
//function :it takes a script of data from text file "receive_transaction_data_test.txt" and 
//          edit the data base if any approved operations and returns a receit for all the operations
void recieveTransactionDataTest(void) {

	FILE* textfile;
	char   read[50];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/receive_transaction_data_test.txt", "r");
	transectioninput.terminalData.maxTransAmount = 100000;
	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : recieveTransactionData ");

	while (fgets(read, 50, textfile)) {
		if (i % 5 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input pan data: %s", read);
			
			strcpy(transectioninput.cardHolderData.primaryAccountNumber, read);
			//the tested code

			//end of tested code
		}
		else if (i % 5 == 2) {
			printf("input Name data: %s", read);
			strcpy(transectioninput.cardHolderData.cardHolderName, read);
		
			
		}
		else if (i%5 ==3) {
			printf("input exp data: %s", read);
			strcpy(transectioninput.cardHolderData.cardExpirationDate, read);
		}
		else if (i%5 == 4) {
			printf("input transection amount data: %s", read);
			transectioninput.terminalData.transAmount = atoi(read);
			EN_transState_t x = recieveTransactionData(&transectioninput);
			if (x == FRAUD_CARD) {
				printf("Actual Result : FRAUD_CARD\n");
			}
			else if (x== DECLINED_INSUFFECIENT_FUND) {
				printf("Actual Result:DECLINED_INSUFFECIENT_FUND\n");
			}
			else if (x==DECLINED_STOLEN_CARD) {
				printf("Actual Result:DECLINED_STOLEN_CARD\n");

			}
			else if (x == INTERNAL_SERVER_ERROR) {
				printf("Actual Result : INTERNAL_SERVER_ERROR\n");
			}
			else {
				printf("Actual Result : Approved\n");
			}
		}
		else {
			printf(read);

		}
		i++;

	}

	fclose(textfile);
}