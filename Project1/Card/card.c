#include <stdio.h>
#include<stdlib.h>
#include "card.h"
ST_cardData_t input;

//##functions definitions##/


//get card holder name function 
//input:pointer to card data struct to store data
//outputs: error flag as EN_cardError_t  enum
//function: 1- scan for the cardholder's name and store it into card data.
//			2-check for data range 20 to 24 and not null
//          3-print wrong name or card is ok 
EN_cardError_t getCardHolderName(ST_cardData_t* cardData){
	
#define DEBUG//################comment if taking from text############
	

#ifdef DEBUG
		printf("please enter your name=");
		gets(cardData->cardHolderName);
#endif
		if (strlen(cardData->cardHolderName) < 20 || strlen(cardData->cardHolderName) >= 24||
			ISarrayallletters(&cardData->cardHolderName)==0) {
		#ifdef DEBUG
			printf("\n WRONG NAME\n");
		#endif 

			
			return WRONG_NAME;
		}
		else {
		#ifdef DEBUG
			//printf("\n card ok\n");
		#endif 
			return CARD_OK;
		}

}

//test fucntion get card holder name test function 
//input:void
//output :void
//functions: runs as a script to test all the possiple inputs to  the system 
//			takes the data from "card_name_test.txt"
void getCardHolderNameTest(void) {
	//declerations
	FILE * textfile;
	char   line[30];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/card_name_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");	
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : getCardHolderName");

	while (fgets(line, 30, textfile)) {
		if (i % 2 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input data: %s", line);
			strcpy(input.cardHolderName, line);
			//the tested code
				
			
			if (getCardHolderName(&input)== CARD_OK) {
				printf(" Actual result: card ok\n");
			}
			else {
				printf(" Actual result: WRONG NAME\n");
			}

			//end of tested code
		}else {
			printf(line);
			
		}
		i++;
		
	}

	fclose(textfile);
}
//get card expired date function 
//input:pointer to card data structure to store data
//output:error flag as EN_cardError_t  enum
//function:1-ask for the card expire date and stor data
 //        2-take the Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
//         3-print wrong formate if exp date is null or not 5 characters or has wrong formate
//         4-print card ok if every check is ok 
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	
#define DEBUG//################comment if taking from text############
	
#ifdef DEBUG
	printf("please enter card's expire date as MM/YY =");
	gets(cardData->cardExpirationDate);
#endif // DEBUG


	
	//printf("\nlength=%d", strlen(cardData->cardExpirationDate));
	if ( strlen(cardData->cardExpirationDate) ==0 || strlen(cardData->cardExpirationDate) <5|| strlen(cardData->cardExpirationDate) >6) {
#ifdef DEBUG
	//	printf("\n wrong exp date\n");
#endif // DEBUG

		return WRONG_EXP_DATE;
	}
	else if ((cardData->cardExpirationDate[0]<'0' || cardData->cardExpirationDate[0]>'1') || //first digit 0->1
		(cardData->cardExpirationDate[1] < '0' || cardData->cardExpirationDate[1] > '9') ||// secand digit 0->9
		(cardData->cardExpirationDate[0] =='1'&& cardData->cardExpirationDate[1]>'2') ||//secand digit cant be >2 when first digit =1
		(cardData->cardExpirationDate[0] == '0' && cardData->cardExpirationDate[1] == '0') ||//secand digit cant be 0 when first digit =0
		(cardData->cardExpirationDate[2]!='/') ||//third digit = '/'
		(cardData->cardExpirationDate[3]<'0' || cardData->cardExpirationDate[3]>'9') ||//fourth digit from 0 to 9
		(cardData->cardExpirationDate[4] < '0' || cardData->cardExpirationDate[4] > '9'))//fifth digit from 0 to 9
	{
		#ifdef DEBUG
		//printf("\n wrong exp date\n");
		#endif // DEBUG

		

		return WRONG_EXP_DATE;
	}
	else {
		#ifdef DEBUG
		//printf("\n card ok\n");	
		#endif // DEBUG

		return CARD_OK;
	}
	

}		

//test fucntion get card exp date test
//input :void
//output :void
//function :runs as script to test all the possible inputsand reads data from card_expdate_test.txt

void getCardExpiryDateTest(void) {

	//declerations
	FILE* textfile;
	char   line[35];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/card_expdate_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : getCardexpdate");

	while (fgets(line, 35, textfile)) {
		if (i % 2 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input data: %s", line);
			//tested code
			
			strcpy(input.cardExpirationDate,line);
			
			//printf("\nline=%d", strlen(input.cardExpirationDate));
			
			if (getCardExpiryDate(&input) == CARD_OK) {
				printf(" Actual result: card ok\n");
			}
			else {
				printf(" Actual result: WRONG Exp date\n");
			}
			
			//end of tested code
			//printf("%d", strlen(line));
		}
		else {
			printf(line);

		}
		i++;

	}


	fclose(textfile);

}

//get card primary account pan number
//input:pointer to card data structure to store data
//output:error flag as EN_cardError_t  enum
//function : 1-will ask for the card pan number
//           2-check number exists in range from 16 min to 19 max and not Null
//             3-will return wrong ban or card ok 
EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	
#define DEBUG //################comment if taking from text############
	
#ifdef DEBUG
	printf("please enter card's pan Number=");
	gets(cardData->primaryAccountNumber);
#endif // DEBUG


	
	
	if (strlen(cardData->primaryAccountNumber) < 16 || strlen(cardData->primaryAccountNumber) > 19 ||
		ISarrayallnumbers(&cardData->primaryAccountNumber)== 0) {
	#ifdef DEBUG
		printf("wrong pan number");
	#endif // DEBUG

		
		return WRONG_PAN;
	}else {
		#ifdef DEBUG
	//	printf("card ok");
	#endif // DEBUG

		
		return CARD_OK;
	}
	

}

//test function get card pan number test
//input:void
//output :void
//functions:  runs as a script to test all the possiple inputs to the system 
//			takes the data from "card_pan_num_test.txt"
void getCardPANTest(void) {

	FILE* textfile;
	char   line[40];
	int i = 1;
	int j = 1;
	textfile = fopen("Test_scripts/card_pan_num_test.txt", "r");

	if (textfile == NULL) {
		printf("Error!");
	}

	printf("Tester Name: mohab ahmed ramadan \n Function Name : getCardpannumber");

	while (fgets(line, 40, textfile)) {
		if (i % 2 == 1) {
			printf("\nTest case %d\n", j);
			j++;
			printf("input data: %s", line);
			//start of test code
			strcpy(input.primaryAccountNumber, line);

			//printf("\nline=%d", strlen(input.cardExpirationDate));

			if (getCardPAN(&input) == CARD_OK) {
				printf(" Actual result: card ok\n");
			}
			else {
				printf(" Actual result: WRONG PAN NUMBER\n");
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

//#helping functions
//------------------------------------------------------
// is all the chracters are numbers
// input: the array i want to check 
// output: integer flag for the result
// function:returns 1 if all the array are numbers and 0 if not
int ISarrayallnumbers(char* prr)
{
	int i = 0;
	int flg;
	
	for (i = 0; i < strlen(prr); i++)
	{
		if (prr[i]>='0' && prr[i]<='9'|| prr[i] == 10) {
			
			flg =1;

		}
		else {
			
			flg = 0 ;
			break;
		}

	}
	return flg;
	
}


//is all the characters are letters
// input: the array i want to check 
// output: integer flag for the result
// function:returns 1 if all the array are letters and 0 if not
int ISarrayallletters( char * arr) {
	int i = 0;
	int flg;
	for (i = 0; i < strlen(arr); i++)
	{
		if ((arr[i] >='A' && arr[i]<='Z')|| (arr[i] >= 'a' && arr[i] <= 'z')|| arr[i]==' '|| arr[i]==10) {
			flg = 1;
			
		}
		else {
			
			flg = 0;
			break;

		}

	}
	return flg;

}
