#include <stdio.h>
#include <cs50.c>

long long get_cardNumber(void);
int getDigit(long long cardNumber, int digit);
long long powerOf(int num, int power);
int get_cardType(long long cardNumber);
bool checkCardNumValidity(long long cardNumber, int cardType);


int main(void)
{
	// Get card number from the user
	long long cardNum = get_cardNumber();

	// 1 => MASTERCARD = 16 digits; start with 51,52,53,54 or 55
	// 2 => VISA = 16 digits; start with 4
	// 3 => AMEX = 15 digits; start with 34 or 37
	// 4 => VISA = 13 digits; start with 4
	// 0 => INVALID CARD NUMBER
	int cardType = get_cardType(cardNum);

	bool isCardValid = checkCardNumValidity(cardNum, cardType);

	if(isCardValid)
	{
		switch (cardType)
		{
			case 0:
				printf("INVALID\n");
				break;

			case 1:
				printf("MASTERCARD\n");
				break;

			case 2:
			case 4:
				printf("VISA\n");
				break;

			case 3:
				printf("AMEX\n");
				break;
			
			default:
				printf("INVALID\n");
				break;
		}
	}
	else printf("INVALID\n");
}


// Get a card number from user
long long get_cardNumber(void)
{
	long long getCardNum;

	// VISA = 13 or 16 digits; start with 4
	// AMEX = 15 digits; start with 34 or 37
	// MASTERCARD = 16 digits; start with 51,52,53,54 or 55
	// The smallest card number can be Visa with 13 digits starting with 4 = 4 0000 0000 0000
	// Every card number below that number is invalid input
	do
	{
		getCardNum = get_long_long("Insert your card number: ");
	} while (getCardNum < 1);

	return getCardNum;
}

// Get the choosen digit from the card number
int getDigit(long long cardNumber, int digit)
{
	return (cardNumber % powerOf(10, digit)) / powerOf(10, digit-1);
}

// Get the power of the given number; num^power
long long powerOf(int num, int power)
{
	// Every number on power of 0 equals to 1
	if(power == 0) return 1;

	long long powerOfNum = num;

	for(int i = 1; i < power; i++)
	{
		powerOfNum *= num;
	}

	return powerOfNum;
}

// Get card type 
int get_cardType(long long cardNumber)
{
	int digit13 = getDigit(cardNumber, 13);
	int digit14 = getDigit(cardNumber, 14);
	int digit15 = getDigit(cardNumber, 15);
	int digit16 = getDigit(cardNumber, 16);

	// MASTERCARD = 16 digits; start with 51,52,53,54 or 55
	if (digit16 == 5 && (digit15 == 1 || digit15 == 2 || digit15 == 3 || digit15 == 4 || digit15 == 5))
	{
		return 1;
	}

	// VISA = 16 digits; start with 4
	if (digit16 == 4)
	{
		return 2;
	}

	// AMEX = 15 digits; start with 34 or 37
	if (digit15 == 3 && (digit14 == 4 || digit14 == 7))
	{
		return 3;
	}

	// VISA = 13 digits; start with 4
	if (digit13 == 4)
	{
		return 4;
	}

	return 0;
}

bool checkCardNumValidity(long long cardNumber, int cardType)
{
	int digits;

	switch (cardType)
	{
	case 0:
		return false;
		break;

	case 1:
	case 2:
		digits = 16;
		break;

	case 3:
		digits = 15;
		break;

	case 4:
		digits = 13;
		break;
	
	default:
		return false;
		break;
	}

	int sumOfSecondToLast;

	for(int i = 2; i <= digits; i+=2)
	{
		int j = getDigit(cardNumber, i) * 2;

		sumOfSecondToLast = sumOfSecondToLast + getDigit(j , 1) + getDigit(j , 2);
	}

	for(int i = 1; i <= digits; i+=2)
	{
		sumOfSecondToLast = sumOfSecondToLast + getDigit(cardNumber, i);
	}

	if(getDigit(sumOfSecondToLast, 1) == 0) return true;
	else return false;
}