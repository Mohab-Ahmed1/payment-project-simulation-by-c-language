# payment-project-simulation-by-c-language
this is a c based project that simulates the payment proccess
it is composed of 3 parts

1-card

2-terminal

3-server

the card :
1-this gett data holder name
2- get card expired date
3-get card pan number

the terminal :
1-get the card date + the transaction data
2-checks if the card is expired 
3-ceck if the pan number is correct according to the luhun algorithm
4-get the transaction amount
5-checks if the transaction amount is not exceeding the maximum amount 

the server:
1-checks if the account is valid in the data base
2-checks if the account have sufficient funds
3-execute the payment procces and returns a receite
4-update the acoounts data base
5-save the transaction proccess
