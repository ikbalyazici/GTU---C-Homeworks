#include <stdio.h>

/*Prototypes of functions are used in program*/
int andop (int a , int b);

int main()
{
	int a,b; /*Inputs - Binary numbers, program will want them from user*/
	
	printf("First integer: ");
	scanf ("%d",&a);
	printf("Second integer: ");
	scanf ("%d",&b);

	int a_saver = a, b_saver = b; /*These two integers for saving the real values given by user of a and b */

	while (a >= 1) 
	{
		if (((a % 10 == 1)||(a % 10 == 0)) && ((b % 10 == 1)|| (b % 10 == 0))) /*Control of inputs are binary or not. Binary numbers does not give answer bigger than one for modulus for any digits*/
		{
			if (a >= 10) /*It is for controlling every digit is binary or not by division*/
			{
				a = a/10; /*For integer numbers dividing by 10 gives one less digit*/
				b = b/10;
			}
			else
			{
				if (((a > (a-b) && a > (b-a)) && (b > (a-b) && b > (b-a)))) /*Controlling length by subtraction. If two binary numbers have same length their subtract must be smaller than both two inputs*/
				{
					a = a_saver; /*No errors have seen. Real values of inputs must come their home*/
					b = b_saver;

					printf("%d AND %d = %d\n",a,b,andop(a,b)); /*It is what user wants: THE ANSWER*/
					break;
				}
				else
				{
					printf("Integers should have the same length, please enter 2 new integers.\n");
					main ();
					break;
				}
			}	
		}	 
		else 
		{
			printf("Integers should be binary, please enter 2 new integers.\n");
			main ();
			break;
		}
	}
	return 0;	
}

/*Functions are used in the program*/
int andop (int a, int b)
{
	int and = 0, and_adder = 1; /*And is the output - final result of the AND operation. | and_adder determines the true value based on digit */

	while (a != 0) /*Operation runs by dividing. It checks operation ended or not.*/
	{
		if ((a % 10 == 1)&&(b % 10 == 1)) /*Control for AND operation. To obtain '1' as a result both two inputs must be '1'*/
		{
			and = and + and_adder; /*Operation starts from the min digit and runs to max digit.*/
		}
		else
		{
			and = and; /*If result of step is '0' no changes required. When result '1' comes all necessary zeros will be at their locations */
		}
		
		and_adder = and_adder * 10; /*By this way input and output digits be synchronized*/

		a = a/10; /*Every step program checks the smallest digit. By this way program checks bigger digits after small ones*/
		b = b/10;
	}
	return and; /*It sends the result to main function*/
}