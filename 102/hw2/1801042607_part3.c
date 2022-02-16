#include <stdio.h>

int main()
{
	float amount,tl,dollar,euro; 
	int currency; /*input for considering the money we have and we want */
	int controler; /*its for blocking process altough selected currency is invalid*/
	
	printf ("*****Welcome to ABC Exchange Office*****\n\n\n");
	
	printf ("Enter your amount:  \n");
	scanf ("%f",&amount);
	
	printf ("Please select your currency \n 1. Turkish Lira \n 2. Euro \n 3. Dollar\n");
	scanf ("%d",&currency);
	
	switch (currency)
	{
		case 1:
			tl = amount; /*All compuations based on the currency what is we have*/
			euro = tl / 6.69;
			dollar = tl / 6.14;
			
			printf ("You have %f Turkish Liras\n",tl);	
			controler = 1; 
			break;		
	
		case 2:
			euro = amount;
			tl = euro * 6.69;
			dollar = euro * 1.089576;
			printf ("You have %f Euros\n",euro);
			controler = 1;
			break;
			
		case 3:
			dollar = amount;
			tl = dollar * 6.14;
			euro = dollar * 0.917787 ;
			printf ("You have %f Dollars\n",dollar);
			controler = 1;
			break;
		
		default:
			printf ("Your selection is invalid\n");
			controler = 0; /*Controler has different value from previus ones because we dont want to continue altough we have invalid currency*/
			
	}
	
	if (controler == 1) /*It controls and considers what process will run based on controler value*/
	{
		printf ("Choose which currency you want to convert: \n 1. Turkish Lira \n 2. Euro \n 3. Dollar\n");
		scanf ("%d",&currency);
		
		switch (currency)
		{
			case 1:
				printf ("You have %f Turkish Liras",tl);	
				break;		
		
			case 2:
				printf ("You have %f Euro",euro);
				break;
				
			case 3:
				printf ("You have %f Dollar",dollar);
				break;
			
			default:
				printf ("Your selection is invalid");
				break;	
		}
	}
	
return 0;	
}
