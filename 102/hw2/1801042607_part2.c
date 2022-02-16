#include <stdio.h>
#include <math.h>

/*Function Prototypes*/
int number_length (int number);
int find_digit (int number , int index);

int main ()
{
	int number,index;
	
	printf ("Enter a number (Maximum 6 digits):  \n");
	scanf ("%d",&number);
	number = fabs(number); /* To make certain of this program has no problem with negative numbers I took their absolute value*/


	number_length (number);
	
	if (number_length (number) > 6) /* Program wants max 6 digit numbers, so I ignored 7 or more digits.*/
	{
		printf ("This number has more than 6 digits. Next time please be careful!\n");
		main();        /* I gave a new chance to user. In this way user does not have to restart program*/
		
	}
	else /* Normal 6 or less digit numbers*/
	{
	
	printf ("Your number has %d digits \n\n",number_length(number));
	
	printf ("When your number is written 100 times next to each other, which digit of this number would you like to see? :  \n");
	scanf ("%d",&index);
	
	find_digit (number,index);
	
	if (index > number_length(number)*100) /* Program wants 100 times writing. If user gives bigger index, normally this program can find it,
	                                          but I think it will be a mistake. So I added a warning */
	{
		printf ("Your given index %d is greater than when your number is written 100 times next to each other \n",index);
	}
	else if (index !=0)  /* Normal process of program.*/
	{
		printf ("%d th digit of the big number sequence: %d ",index,find_digit(number,index));
	}	
	else  /* Term numbers are counting numbers so any number has at least one term. Becasue of it I added a warning for index = 0 situation*/
	{
		printf ("%d th term is not invalid",index);
	}
	return 0;
	}
}

/*Functions are used in program*/

int number_length (int number)
{
	double digit_quantity = log10(number); /* Ten based logarithm function parts numbers according to integer powers of ten.*/
	int the_digit; /* Its the output that returns the result to main function*/
	
	if (digit_quantity < 1 ) /*Logarithm function will create problems for 1 and 0 so I seperate them*/
	{
		the_digit = 1;
	}
	else
	{
		the_digit = (int)ceil(digit_quantity); /* Logarithm function (ten based) gives result between 2 integer values. Big one shows the digit number */
	}
	return the_digit;
	
}

int find_digit (int number, int index)
{
	int digit_value, power;
	
	int digit_want = index % number_length(number); 
	
	power = pow(10,(number_length(number) - digit_want));
	
		if (digit_want == 0) 
	{
		power = 1;
	}
	
	digit_value = (int)(number/power) % 10;
	
	return digit_value;
	
}
