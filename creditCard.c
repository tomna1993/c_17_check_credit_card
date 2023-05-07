#include <cs50.h>
#include <stdio.h>

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
	//To get the digit I take the modulo of the number then divide it
	//Example: Number = 123 and i want to get the 2nd digit
	//The calculation would be the next: (123 % (10 on power of 2)) / (10 on power of 1) = (123 % 100) / 10 = 23 / 10 = 2
	// any number on power of 1 is 1 and on power of 0 is 1, this way we can calculate the first digit (ones place) too
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
	// Get the last 4 digits of the card number
	int digit13 = getDigit(cardNumber, 13);
	int digit14 = getDigit(cardNumber, 14);
	int digit15 = getDigit(cardNumber, 15);
	int digit16 = getDigit(cardNumber, 16);

	// MASTERCARD = 16 digits; start with 51,52,53,54 or 55
	if (digit16 == 5 && digit15 >= 1 && digit15 <= 5)
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

	// Invalid card
	return 0;
}

/*Most cards use an algorithm invented by Hans Peter Luhn of IBM. 
According to Luhn’s algorithm, you can determine if a credit card number is (syntactically) valid as follows:

1. Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
2. Add the sum to the sum of the digits that weren’t multiplied by 2 
3. If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

That’s kind of confusing, so let’s try an example with Visa: 4003600000000014.

1. For the sake of discussion, let’s first mark ( put in () ) every other digit, 
starting with the number’s second-to-last digit:

	(4) 0 (0) 3 (6) 0 (0) 0 (0) 0 (0) 0 (0) 0 (1) 4

	Okay, let’s multiply each of the marked (in () ) digits by 2:

	4x2 + 0x2 + 6x2 + 0x2 + 0x2 + 0x2 + 0x2 + 1x2

	That gives us:

	8 + 0 + 12 + 0 + 0 + 0 + 0 + 2

	Now let’s add those products’ digits (i.e., not the products themselves) together:

	8 + 0 + 1 + 2 + 0 + 0 + 0 + 0 + 2 = 13

2. Now let’s add that sum (13) to the sum of the digits that weren’t multiplied by 2 (starting from the end):

	13 + 4 + 0 + 0 + 0 + 0 + 0 + 3 + 0 = 20

3. The last digit in that sum (20) is a 0, so the card is legit! */

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