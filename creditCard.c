#include <stdio.h>
#include <cs50.c>

long get_cardNumber(void);

int main(void)
{
	// Get card number from the user
	long cardNum = get_cardNumber();
}

// Get a card number from user
long get_cardNumber(void)
{
	long getCardNum;

	// VISA = 13 or 16 digits; start with 4
	// AMEX = 15 digits; start with 34 or 37
	// MASTERCARD = 16 digits; start with 51,52,53,54 or 55
	// The smallest card number can be Visa with 13 digits starting with 4 = 4 0000 0000 0000
	// Every card number below that number is invalid input
	do
	{
		getCardNum = get_long("Insert your card number: ");
	} while (getCardNum < 4000000000000);

	return getCardNum;
}