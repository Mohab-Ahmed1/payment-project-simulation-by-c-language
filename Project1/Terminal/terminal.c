#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include "terminal.h"
ST_terminalData_t terminalinput;

//get transection date from user
//input:pointer to terminal data struct to store data
//outputs: error flag as ST_terminalData_t  enum
//function:1-will ask the user for the transetion date and store it in the terminal
//         2-check for data to not be null or not 10 chracters       
//         3-will check the formate DD/MM/YYYY,
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
//#define DEBUG
#ifdef DEBUG

	printf("please enter card's transection date as DD/MM/YYYY =");
	gets(termData->transactionDate);
#endif
	if (strlen(termData->transactionDate) !=11) {//###########
		#ifdef DEBUG
		printf("\n wrong transition date \n");
		#endif // DEBUG

		
		return WRONG_DATE;
	}
	else if ((termData->transactionDate[0] < '0' || termData->transactionDate[0]>'3') || //first digit 0->3
		(termData->transactionDate[1] < '0' || termData->transactionDate[1] > '9') ||// secand digit 0->9
		(termData->transactionDate[0] == '3' && termData->transactionDate[1] > '1') ||//secand digit cant be >1 when first digit =3
		(termData->transactionDate[0] == '0' && termData->transactionDate[1] == '0') ||//secand digit cant be 0 when first digit =0

		(termData->transactionDate[2] != '/') ||//third digit = '/'

		(termData->transactionDate[3] < '0' || termData->transactionDate[3]>'1') || //fourth digit 0->1
		(termData->transactionDate[4] < '0' || termData->transactionDate[4] > '9') ||// fifth digit 0->9
		(termData->transactionDate[3] == '1' && termData->transactionDate[4] > '2') ||//fifth digit cant be >2 when fourth digit =1
		(termData->transactionDate[3] == '0' && termData->transactionDate[4] == '0') ||//fifth digit cant be 0 when fourth digit =0

		(termData->transactionDate[5] != '/') ||//six digit = '/'

		(termData->transactionDate[6] < '0' || termData->transactionDate[6]>'9') ||//seventh digit from 0 to 9
		(termData->transactionDate[7] < '0' || termData->transactionDate[7]>'9') ||//eigth digit from 0 to 9
		(termData->transactionDate[8] < '0' || termData->transactionDate[8]>'9') ||//nine digit from 0 to 9
		(termData->transactionDate[9] < '0' || termData->transactionDate[9] > '9'))//tenth digit from 0 to 9
	{
#ifdef DEBUG
		printf("\n wrong transition date date\n");
#endif // DEBUG
		return WRONG_DATE;
	}
	else {
#ifdef DEBUG
		printf("\n terminal ok\n");
#endif // DEBUG
		
		return TERMINAL_OK;
	}

}
//get transection date from the system
//input:pointer to terminal data struct to store data
//outputs: void
//function: get the DD/MM/YYYY from ths system then save it to the struct
void getTransactionDateauto(ST_terminalData_t* termData) {
	time_t date = time(NULL);
	struct tm tm = *localtime(&date);
	
	sprintf(termData->transactionDate, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	//puts(termData->transactionDate);
	
}
//test fucntion get transaction date test function 
//input:void
//output :void
//functions: runs as a script to test all the possiple inputs to the system 
//			takes the data from "Transaction_date_test.txt"
void getTransactionDateTest(void) {

	//declerations
	FILE* textfile;
	char   line[50];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/Transaction_date_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : getCardexpdate");

	while (fgets(line, 50, textfile)) {
		line[strlen(line)-1] = '\0';
		if (i % 2 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input data: %s\n", line);
			//tested code
			strcpy(terminalinput.transactionDate, line);

			//printf("\nline=%d", strlen(input.cardExpirationDate));

			if (getTransactionDate(&terminalinput) == CARD_OK) {
				printf(" Actual result:terminal ok\n");
			}
			else {
				printf(" Actual result: wrong transition date date\n");
			}

			
		}
		else {
			printf(line);

		}
		i++;

	}


	fclose(textfile);

}

//to check if the card expired
//input: pointer to card data and a pointer to terminal data
// output :flag of the output as EN_terminalError_t enum
// function :it compares the card expiry date with the transaction date.
//if expire date >= transection date returns terminal ok else returns expired_card
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
	
	//compare years
	//printf("\ncard=%c \n terminal=%c", cardData->cardExpirationDate[1], termData->transactionDate[3]);

	if (cardData->cardExpirationDate[3] > termData->transactionDate[8]) {
		#ifdef DEBUG
		printf("This card is valid\n");
		#endif // DEBUG

		

		return TERMINAL_OK;
	}
	else if (cardData->cardExpirationDate[3] == termData->transactionDate[8]) {
		if (cardData->cardExpirationDate[4] > termData->transactionDate[9]) {
			#ifdef DEBUG
			printf("This card is valid\n");
			#endif // DEBUG
			return TERMINAL_OK;
		}else if(cardData->cardExpirationDate[4] == termData->transactionDate[9]) {
			if (cardData->cardExpirationDate[0] > termData->transactionDate[3]) {
				#ifdef DEBUG
				printf("This card is valid\n");
				#endif // DEBUG
				return TERMINAL_OK;
			}else if(cardData->cardExpirationDate[0] == termData->transactionDate[3]) {
				if (cardData->cardExpirationDate[1] > termData->transactionDate[4]) {
				#ifdef DEBUG
					printf("This card is valid\n");
				#endif // DEBUG
					return TERMINAL_OK;
				}
				else {
					#ifdef DEBUG
					printf("the card is expired\n");
					#endif // DEBUG
					
					return EXPIRED_CARD;

				}
			}
			else {
				#ifdef DEBUG
				printf("the card is expired\n");
				#endif // DEBUG
				return EXPIRED_CARD;

			}
		}
		else {
			#ifdef DEBUG
			printf("the card is expired\n");
			#endif // DEBUG
			return EXPIRED_CARD;

		}
	}	
	else {
		#ifdef DEBUG
		printf("the card is expired\n");
		#endif // DEBUG
		return EXPIRED_CARD;
 
	}
}


//test fucntion get transaction date test function 
//input:void
//output :void
//function :this function runs as script to compare the exp dates with transetion dates
void isCardExpiredtest(void) {
	//declerations
	FILE* textfile;
	char   line[50];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/IS_card_expired_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : getCardexpdate");

	while (fgets(line, 50, textfile)) {
		if (i % 3 == 1) {

			printf("\nTest case %d\n", j);
			j++;
			printf("input data card exp: %s", line);
			//tested code
			strcpy(input.cardExpirationDate, line);
			
			//end of tested code
			//printf("%d", strlen(line));
		}
		else if (i % 3 == 2) {
			printf("input transaction date: %s", line);
			//tested code
			
			strcpy(terminalinput.transactionDate, line);
			
			if (getTransactionDate(&terminalinput) == TERMINAL_OK && getCardExpiryDate(&input) == CARD_OK) {
				//printf("\ncard= %s  \nterminal=%s", user1.cardExpirationDate, terminal1.transactionDate);
				if (isCardExpired(&input, &terminalinput)== TERMINAL_OK) {
					printf("Actual Result:Terminal Is ok\n");

				}
				else {
					printf("Actual Result:Expired card\n");
				}

			}
			else if (getTransactionDate(&terminalinput) == WRONG_DATE) {
				printf("Actual Result:Wrong transection Date\n");


			}
			else {
				printf("Actual Result:Wrong Exp Date\n");

			}

		}
		else {
			printf(line);

		}
		i++;
	}
	fclose(textfile);

}



//to get the transection amount from the user
//input:pointer to the terminal data 
//output: is a error flag as enum 
//function 1-asks for the transection data and save in the terminal data
//         2-check the ammount is less than or equal 0 
//         3-if 0 or less it returns invalid_ammount else returns Terminal_ok
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	
#define DEBUG//################comment if taking from text############
	
	char buf[20];
		#ifdef DEBUG
		printf("please enter the transaction ammount =");
		fgets(buf,10,stdin);
		if (ISarrayallnumbers(buf)==1) {

			termData->transAmount = atof(buf);
			if ((termData->transAmount) == 0) {

			
			//	printf("\n not avalid ammount");
			
				return INVALID_AMOUNT;
			}
			else {
			
				//printf("\nterminal is ok ");
			
				return TERMINAL_OK;
			}
		}
		else {
			printf("pleas enter a valid number\n");
				return INVALID_AMOUNT ;
		}
#endif // DEBUG

	//	printf("%f", termData->transAmount);
		if ((termData->transAmount) <= 0) {
			return INVALID_AMOUNT;
		}
		else {
			return TERMINAL_OK;
		}
		

}
//test function get transection amount test
//input: void
//output:void
//function :this function runs a script of inputs from "transaction_amount_test.txt"
//          to test all the possiple inputs to the system
void getTransactionAmountTest(void) {
	//declerations
	FILE* textfile;
	char   line[50];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/transaction_amount_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : getTransactionAmount");

	while (fgets(line, 50, textfile)) {
		if (i % 2 == 1) {

			printf("\nTest case %d\n", j);
			j++;
			
			//tested code
			strcpy(input.cardExpirationDate, line);
			printf("input transaction Amount: %s", line);
			
			//tested code
			if (ISarrayallnumbers(line) == 1) {
				terminalinput.transAmount =atof( line);
				if (getTransactionAmount(&terminalinput)== TERMINAL_OK) {

					printf("Expected Answer:Terminal ok\n");
				}
				else {
					printf("Expected Answer:not a valid Amount\n");
				}

			}
			else {
				printf("Expected Answer :please enter a valid number\n");
				
			}
			// end of test file
		}
		else {
			printf(line);

		}
		i++;

	}
	fclose(textfile);

}

//check is blow max amount
//input :pointer to the terminal data struct address
// output : is a flag as enum  EXCEED_MAX_AMOUNT  &  TERMINAL_OK
//function: this function compares the terminal transamount with the max amunt of the system
//          1- if less than it returns Terminal ok if exceed it returns Exceed_max_Amount 
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {


	if (termData->maxTransAmount >= termData->transAmount) {
		#ifdef DEBUG
		//printf("\n Terminal is ok");
		#endif // DEBUG
		return TERMINAL_OK;
	}
	else {
		#ifdef DEBUG
		//printf("\n Exceed max amount");
		#endif // DEBUG
		return EXCEED_MAX_AMOUNT;
	}


}

//test function isbelow max amount test
//input:void
// output:void
// function :this function reads from a script of text file "is_below_max_amount_test.txt" and compare it with 
//           a pre defined max amount in #define MAX_Amount
void isBelowMaxAmountTest(void) {

	//declerations
#define MAX_AMount 10000
	FILE* textfile;
	char   line[40];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/is_below_max_amount_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : isBelowMaxAmount");

	while (fgets(line, 40, textfile)) {
		if (i % 2 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input data: %s", line);
			//the tested code
			terminalinput.transAmount = atof(line);
			terminalinput.maxTransAmount = MAX_AMount;

			if (isBelowMaxAmount(&terminalinput)==TERMINAL_OK) {
				printf("Actual Result :Terminal is ok\n");

			}
			else
			{
				printf("Actual Result:Exceed Max Amount\n");
			}

			//end of tested code
		}
		else {
			printf(line);

		}
		i++;

	}

	fclose(textfile);

}

//set the Max amount
//input:pointer to the terminal data input struct address and a float variable of the max amount required
// output: is an error flag as enum INVALID_MAX_AMOUNT  or TERMINAL_OK
// function:1-check that the max amount is not 0  
//          2-will take the maxmimumamount and stor it in the terminalinput Max trans amount
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
//#define DEBUG
	if (maxAmount>0) {
		termData->maxTransAmount = maxAmount;
#ifdef DEBUG
		//printf("Terminal is ok =%f", termData->maxTransAmount);
#endif // DEBUG

		return TERMINAL_OK;
	}
	else {
#ifdef DEBUG
		//printf("Invalid max amount ");
#endif // DEBUG
		return INVALID_MAX_AMOUNT;
	}

}

//test function to set max amount
//input:void
//output: void
//function:1-this function reads from a script of text file from "Set_max_amount_Test.txt"
//         2-checks every input to be not 0 and its a number
void setMaxAmountTest(void) {
	//declerations
	FILE* textfile;
	char   line[50];
	float Max_amount;
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/Set_max_amount_Test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : setMaxAmount");

	while (fgets(line, 50, textfile)) {
		if (i % 2 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input data: %s", line);
			//the tested code
			if (ISarrayallnumbers(line)==1) {
				Max_amount = atof(line);

				if (setMaxAmount(&terminalinput, Max_amount) == TERMINAL_OK) {
					printf("Actual result :terminal is ok\n");
				}
				else {
					printf("Actual Result:In valid max Amount\n");
				}

			}
			else {
				printf("Actual Result: please enter a valid number\n");
			}
			
			

			

			//end of tested code
		}
		else {
			printf(line);

		}
		i++;

	}

	fclose(textfile);


}
//check  is valid card pan
//input: pointer to the card data input struct
// output :a eror flag as enum INVALID_CARD or TERMINAL_OK
//function : 1-this function takes the input from the user then checks if the luhn algorith applies to it or not
//           2-if the card is valid it returns TERMINAL_OK else returns INVALID_CARD
EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	
	int i=0;
	int even=0;
	int odd=0;
	int input = 0;
	int sum = 0;
	int c;
	for (i = 0; i < strlen(cardData->primaryAccountNumber); i++) {
		input = (int)cardData->primaryAccountNumber[i] - 48;
		//printf("\n%c", cardData->primaryAccountNumber[i]);
		if (input != (- 38)) {
			if (i % 2 == 0) {
				//printf("\neven");
				if (input * 2 > 9) {
					even += (input * 2 - 9);
					#ifdef DEBUG
				//	printf("\neven sum=%d", even);
					#endif // DEBUG

				}
				else
				{
					even += (input * 2);
					#ifdef DEBUG
				//	printf("\neven sum=%d", even);
					#endif // DEBUG
				}
			}
			else
			{
				//printf("\nodd");
				odd += (input);
				#ifdef DEBUG
				//printf("\nodd sum=%d", odd);
				#endif // DEBUG
			}
		}
		
	
	}
	sum = even + odd;
	#ifdef DEBUG
	//printf("\n sum=%d", sum);
	c = (10 - (sum % 10)) % 10;
	//printf("\n check=%d", c);
	#endif // DEBUG

	if (sum % 10 == 0) {
		#ifdef DEBUG
		//printf("\n terminal is ok");
		#endif // DEBUG
		
		return TERMINAL_OK;
	}
	else {
		#ifdef DEBUG
		//printf("\ninvalid card");
		#endif // DEBUG
		
		return INVALID_CARD;
	}
}

//test function is valid card pan
//input:void
//output void
//function :this function runs a script from "is_valid_card_pan_test.txt" 
//          and checks if the pan number is luhn number or not
void isValidCardPANTest(void) {


	FILE* textfile;
	char   line[40];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/is_valid_card_pan_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : isvalidcardpan");

	while (fgets(line, 40, textfile)) {
		if (i % 2 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input data: %s", line);
			//start of test code
			line[strlen(line)] = '\0';
			strcpy(input.primaryAccountNumber, line);

			if (isValidCardPAN(&input)== TERMINAL_OK) {
				printf(" Actual result: terminal ok\n");
			}
			else {
				printf(" Actual result: invalid card \n");
			}
			
			//end of tested code
		}
		else {
			printf(line);

		}
		i++;

	}

	fclose(textfile);

}