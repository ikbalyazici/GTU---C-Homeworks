#include <stdio.h>
#include <math.h>

/*Prototypes of Functions are used in program*/
int isprime (int a);

int main()
{
	int n; /*Input - We will control it is prime or not.*/

	printf("Please enter an integer: ");
	scanf ("%d",&n);

	int a; /*Input value of isprime function.*/
	for ( a = 2; a < n; a++)
	{
		if (isprime(a) == 1)
		{
			printf("\n%d is a prime number\n",a );
		}
		else
		{
			printf("\n%d is not a prime number, it is dividable by %d\n",a,isprime(a));
		}
	}
	return 0;
}

/*Functions are used in Program*/
int isprime(int a) /*This function checks is a prime or not*/
{
	int square = sqrt(a); /*To determine primeness of a controlling up to its squareroot is enough*/
	int flag = 1; /*Flag is output of isprime function. It will return result of checking primeness*/
	int divider; /* To determine is a prime or not, we will control divisibility of a by divider */
	for (divider = 2; divider <= square; divider++)
	{
		
		/*Checking primeness of a. If it is dividable by any number except itself and 1 it is not a prime number*/
		if (a % divider == 0)
		{	
			flag = divider;
			break;
		}
		else 
		{
			flag = 1;
		}
	}
	return flag;
}



