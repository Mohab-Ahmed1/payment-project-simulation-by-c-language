
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include "app.h"
ST_transaction_t transection1;
//the intalizationfunction to the holeproject
//note to change from script to manual mode you need to look in 
//getCardHolderName
//getCardExpiryDate
//getCardPAN
//getTransactionAmount
//isValidAccount
void appStart(void) {
	float Max_Amount_for_terminal = 10000;
	EN_cardError_t steps;
	while (1) {
		EN_cardError_t steps;
		do {
			steps = getCardHolderName(&transection1.cardHolderData);

		} while (steps != CARD_OK);
		do {
			steps = getCardExpiryDate(&transection1.cardHolderData);
		}while (steps != CARD_OK);
		do {
			steps = getCardPAN(&transection1.cardHolderData);
		} while (steps != CARD_OK);
		do {
		steps=getTransactionAmount(&transection1.terminalData);
		}while (steps != CARD_OK);
		/*getCardHolderName(&transection1.cardHolderData);
		getCardExpiryDate(&transection1.cardHolderData);
		getCardPAN(&transection1.cardHolderData);
		getTransactionAmount(&transection1.terminalData);*/
		setMaxAmount(&transection1.terminalData, Max_Amount_for_terminal);

		recieveTransactionData(&transection1);
		//	listSavedTransactions(&transection1);

	}
}