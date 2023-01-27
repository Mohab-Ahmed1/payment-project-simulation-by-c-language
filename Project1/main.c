#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include"Card/card.h"
#include "Application/app.h"
#include "Server/server.h"
#include "Terminal/terminal.h"

//ST_transaction_t transection1;

//note to change from script to manual mode you need to look in 
//getCardHolderName
//getCardExpiryDate
//getCardPAN
//getTransactionAmount
//isValidAccount

int main() {

	appStart();



	/*
	ST_cardData_t user1;//ST_cardData_t input;
ST_terminalData_t terminal1;//ST_terminalData_t terminalinput;
	ST_accountsDB_t account1; //ST_accountsDB_t ServerRefrence;
	*/

	//ST_transaction_t transection1;//ST_transaction_t transectioninput;
	
	//cards
 /*while (1) {
		getCardHolderName(&user1);
		printf("out  %d", ISarrayallletters( & user1.cardHolderName));
	}*/

	//getCardHolderNameTest();
	
	/*while (1) {
		getCardExpiryDate(&user1);
	}*/

//getCardExpiryDateTest();
	/*while (1) {
		getCardPAN(&user1);
		printf("\nout  %d\n", ISarrayallnumbers( & user1.primaryAccountNumber));
	}*/
//getCardPANTest();

	//terminal
	/*while (1)
	{
		getTransactionDate(&terminal1);
	}*/

	//getTransactionDateTest();
	
//	getTransactionDateauto(&terminal1);
	//puts(terminal1.transactionDate);
	/*while (1)
	{
		if (  getTransactionDate(&terminal1) == TERMINAL_OK && getCardExpiryDate(&user1) == CARD_OK) {
			//printf("\ncard= %s  \nterminal=%s", user1.cardExpirationDate, terminal1.transactionDate);
			isCardExpired(&user1, &terminal1);
		}
	}*/
//	isCardExpiredtest();



	/*while (1) {

		getTransactionAmount(&terminal1);
	}*/

	/*while (1)
	{
		scanf("%f",& terminal1.transAmount);
		getTransactionAmount(&terminal1);
	}
	*/

	//getTransactionAmountTest();
//server
/*	while (1)
	{
		terminal1.maxTransAmount = 1000;
		scanf("%f", &terminal1.transAmount);
		//gets(&terminal1.transAmount);
		isBelowMaxAmount(&terminal1);
	}*/


	//isBelowMaxAmountTest();
	/*float x;
	while (1)
	{ 
		scanf("%f", &x);
		setMaxAmount(&terminal1, x);
	}*/

	//setMaxAmountTest();

	/*while (1)
	{
		printf("\nplease enter card's pan Number=");
		gets(user1.primaryAccountNumber);
		isValidCardPAN(&user1);
	}*/

//	isValidCardPANTest();


	/*while (1)
	{
		getCardHolderName(&user1);
		getCardExpiryDate(&user1);
		getCardPAN(&user1);
		printf("out  %s", &user1.cardHolderName);
		printf("out  %s", &user1.cardExpirationDate);
		printf("out  %s", &user1.primaryAccountNumber);
	}*/



	/*getCardPAN(&user1);
	isValidAccount(&user1, &account1);
	printf("balance=%s\n", account1.primaryAccountNumber);
	printf("state=  %d\n",account1.state);
	printf("balance=  %f\n",account1.balance);
	*/

	//isValidAccountTest();

	/*while (1) {
		getCardPAN(&user1);
		isValidAccount(&user1, &account1);
		isBlockedAccount(&account1);
	}*/
	

//isBlockedAccountTest();

/*while (1) {
	getCardPAN(&user1);
	getTransactionAmount(&terminal1);
	isValidAccount(&user1, &account1);
	isAmountAvailable(&terminal1, &account1);
}*/

//isAmountAvailableTest();
/*
while (1) {
	getCardPAN(&user1);
	getTransactionAmount(&terminal1);
	isValidAccount(&user1, &account1);
	isAmountAvailable(&terminal1, &account1);
	saveTransaction(&transection1);
}*/

/*while (1) {
	getCardPAN(&transection1.cardHolderData);
	getTransactionAmount(&transection1.terminalData);
	
	//isAmountAvailable(&terminal1, &account1);
	saveTransaction(&transection1);
}*/


//saveTransactionTest();


/*while (1) {
	getCardPAN(&transection1.cardHolderData);
	getTransactionAmount(&transection1.terminalData);
	//getTransactionDate(&transection1.terminalData);
	//isAmountAvailable(&terminal1, &account1);
	getTransactionDateauto(&transection1.terminalData);
	saveTransaction(&transection1);

	listSavedTransactions(&transection1);
}
*/
//listSavedTransactionsTest();

//float value=10000;

/*while (1) {
	getCardHolderName(&transection1.cardHolderData);
	getCardExpiryDate(&transection1.cardHolderData);
	getCardPAN(&transection1.cardHolderData);
	getTransactionAmount(&transection1.terminalData);
	//automatic
	getTransactionDateauto(&transection1.terminalData);//
	setMaxAmount(&transection1.terminalData, value);
	//checks
	isCardExpired(&transection1.cardHolderData, &transection1.terminalData);//
    isBelowMaxAmount(&transection1.terminalData);//
	saveTransaction(&transection1);
	listSavedTransactions(&transection1);
}*/

/*
while (1) {
	getCardHolderName(&transection1.cardHolderData);
	getCardExpiryDate(&transection1.cardHolderData);
	getCardPAN(&transection1.cardHolderData);
	getTransactionAmount(&transection1.terminalData);
	setMaxAmount(&transection1.terminalData, value);

	recieveTransactionData(&transection1);
//	listSavedTransactions(&transection1);

}*/

//recieveTransactionDataTest();


	return 0;
}


