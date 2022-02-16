#include <stdio.h>
#include <math.h>

/*functions I used in my code*/
void find_root ();
void find_newtonian_root ();
int find_multiple_closest(int a, int b);

int main()
{
		printf("Root Finder\n");
		find_root();

		printf("\nNewtonian Root Finder\n");
		find_newtonian_root();

		printf("\nClosest Value Finder\n");
		
		int a,b; /* inputs for 3rd function*/
		
		printf("Enter the first integer:\n");
  		scanf("%d",&a);
		printf("Enter the second integer:\n");
		scanf("%d",&b);	
		find_multiple_closest(a,b);
		
		return 0;
	
}

void find_root ()
{
	int x,y,z,d; 
	
	printf ("\n Please enter the first coefficient: " );
	scanf ("%d", &x);
	printf ("\n Please enter the second coefficient: " );
	scanf ("%d",&y);
	printf ("\n Please enter the third coefficient:  ");
	scanf  ("%d", &z);
	
	d = sqrt(y*y-4*x*z); /*calculating diskriminant*/
	
	if (y*y-4*x*z < 0)
	{
		printf("\n Your equation %dx^2 %+dx %+d  does not have any real roots.\n", x,y,z);
	}
	
	else if (y*y-4*x*z == 0)
	{
		printf("\n Your equation %dx^2 %+dx %+d has one real root = %d\n",x,y,z,-y/(2*x));
	}
	else if (y*y-4*x*z > 0)
	{
		printf("\n Your equation %dx^2 %+dx %+d have real roots {%d , %d}\n",x,y,z,(-y-d)/2*x,(-y+d)/2*x);
	}	
}


void find_newtonian_root ()
{
	int x,y,z;
	float init,fx,root,d,derx;
	
	printf ("\n Please enter the first coefficient: " );
	scanf ("%d", &x);
	printf ("\n Please enter the second coefficient: " );
	scanf ("%d",&y);
	printf ("\n Please enter the third coefficient:  ");
	scanf  ("%d", &z);
	printf ("\n Please enter the initial:  ");
	scanf  ("%f", &init);
	
		d = sqrt(y*y-4*x*z);
		if (fabs(init - ((-y+d)/(2*x))) < fabs(init - ((-y-d)/(2*x)))) /* for choosing the root which we will get close*/
		{
			root= (-y+d)/(2*x);
		}
		else
		{
			root= (-y-d)/(2*x);
		}
	
	printf ("\n Your equation is %dx^2 %+dx %+d and iterations are", x,y,z);
	printf ("\n Step       x           f(x)         Difference \n");

    int i=1;
    void print_table()
	{
		fx = (x*init*init) + (y*init) + z; /* calculating result of our equation*/
		derx = (2*x*init) + y; /*calculating result of the first derivative of our equaiton*/
		init = init - fx/derx;
		fx = (x*init*init) + (y*init) + z;
		printf (" X%d       %.4f       %.4f       %.4f\n", i,init,fx,fabs(root-init));
		i++;
	}
	/*printing the table for 5 times*/
	print_table ();
	print_table ();
	print_table ();
	print_table ();
	print_table ();
}


int find_multiple_closest(int a, int b)
{
     int div,css1,css2; 
    if (a>b) /* If small number entered first it would create mistake. I compare them to each other*/
    {
	    div= a/b;
	    /*Multiple closest must be multiple of division of big and small numbers. Small number times this division will give us true result.  */
		css1 = b*div; 
	    css2 = b*(div+1); /*Sometimes big number may be closer to one above multiple of small number */
	    if (fabs(css2-a)<fabs(css1-a)||fabs(css2-a)==fabs(css1-a)) /*Comparison for determining which one closer to big input*/
	    {
	    	printf("Closest number to %d that is multiple of %d is %d.",a,b,css2);
		}
		else 
		{
				if (css1==b)
			{
				printf(" Closest number to %d that is multiple of %d is itself %d.",a,b,css1);
			}
			else
			{
				printf(" Closest number to %d that is multiple of %d is %d.",a,b,css1);
			}
		}
	}
	else 
	{
		div= b/a;
		/*Multiple closest must be multiple of division of big and small numbers. Small number times this division will give us true result.  */
	    css1 = a*div;
	    css2 = a*(div+1);  /*Sometimes big number may be closer to one above multiple of small number */
	    if (fabs(css2-b)<fabs(css1-b)||fabs(css2-b)==fabs(css1-b)) /*Comparison for determining which one closer to big input*/
	    {
	    	printf("Closest number to %d that is multiple of %d is %d.",b,a,css2);
		}
		else 
		{
			if (css1==b)
			{
				printf(" Closest number to %d that is multiple of %d is itself.",b,a);
			}
			else
			{
				printf(" Closest number to %d that is multiple of %d is %d.",b,a,css1);
			}
		}
	}
}	
	
	
	

