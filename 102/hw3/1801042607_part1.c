#include <stdio.h>

/*Prototypes of Functions are used in program*/
int sum  (int n, int flag);
int mult (int n, int flag);

int main() 
{	
	int n,operation,flag;/*Inputs*/

	printf("Enter an positive integer: "); /*Because Range of the program [1,n]. Non positive inputs are not fit for this program */
	scanf ("%d",&n); /*n is the number that limits the for statement in the sum and mult functions*/

	while (n<1) /*Program wants positive integers to run*/
	{
		printf("Enter an positive integer: ");
		scanf ("%d",&n);
	}

	printf("Please enter '0' for sum, '1' for multiplication\n");
	scanf ("%d",&operation);/*Operation input is for selecting sum/mult functions*/

	printf("Please enter '0' to work on even numbers, '1' to work on odd numbers \n");
	scanf ("%d",&flag); /*Flag input is for selecting even/odd statement*/

	switch (operation) 
	{ /*Sum - Multiplication selection */
		case 0:

			if (flag == 1 || flag == 0) /*Control of odd/even selection with function call*/
			{
				printf("%d\n",sum(n,flag));
			}
			else
			{
				printf("Invalid value for odd/even selection.\n");/*Error for undefined odd/even selection*/
			}
			break;

		case 1:
			
			if (flag == 1 || flag == 0) /*Control of odd/even selection with function call*/
			{ 
				printf("%d\n",mult(n,flag));
			}
			else 
			{
				printf("Invalid value for odd/even selection.\n");/*Error for undefined odd/even selection*/
			}
			break;

		default:
			printf("Unsupported operation.\n"); /*Error for undefined operation selection*/
	}
	return 0;	
}


/*FUNCTIONS IN THE PROGRAM*/
int sum (int n, int flag) 
{
	int i;
	int sum = 0; /*Output of sum function*/

	switch (flag) /*Odd/even selection*/
	{
		case 0: /*Even numbers*/
			for (i=2; i <= n ; i = i+2) 
			{
				sum = sum + i;

				/*Determination of last element based on input even or odd*/				
				if ((n % 2 == 0 && i == n)||(n % 2 == 1 && i == n - 1))
				{
					printf("%d = ",i);
				}
				else 
				{
					printf("%d + ",i);
				}
			}
			break;

		case 1: /*Odd numbers*/
			for (i=1; i <= n ; i = (i+2)) 
			{
				sum = sum + i;

				/*Determination of last element based on input even or odd*/
				if ((n % 2 == 1 && i == n)||(n % 2 == 0 && i == n - 1)) 
				{
					printf("%d = ",i);
				}
				else 
				{
					printf("%d + ",i);
				}
			}
			break;
	}
	return sum;
}

int mult (int n, int flag) 
{
	int i;
	int mult = 1; /*Output of multiplication function*/

	if (n == 1) /*Zero is the only even integer small than one for this program. (Negative numbers not included)*/
	{
		mult = 0;
		printf("0 = ");
	}

	else 
	{
		switch (flag) /*Odd/even selection*/
		{ 
			case 0:  /*Even numbers*/
				for (i=2; i <= n ; i = i+2) 
				{
					mult = mult * i;
					
					/*Determination of last element based on input even or odd*/
					if ((n % 2 == 0 && i == n)||(n % 2 == 1 && i == n - 1))
					{
						printf("%d = ",i);
					}
					else 
					{
						printf("%d * ",i);
					}
				}
				break;

			case 1: /*Odd numbers*/
				for (i=1; i<= n ; i = i+2) 
				{
					mult = mult * i;

					/*Determination of last element based on input even or odd*/
					if ((n % 2 == 1 && i == n)||(n % 2 == 0 && i == n - 1)) 
					{
						printf("%d = ",i);
					}
					else 
					{
						printf("%d * ",i);
					}
				}
				break;
		}
	}	
	return mult;
}

