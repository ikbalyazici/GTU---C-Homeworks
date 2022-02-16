#include <stdio.h>

#define NUM_CLASS 10 /* Element number of each class (it can change)*/

int main()
{
	float x,y, 				/*For every coordinate inputs from user x for apsises y for ordinates*/
		  sum_x=0,sum_y=0, 	/*Summation of each coordinate parts (for calculating averages)*/
		  tangent,			/*To finding line equations tangent of lines needed*/
		  ave_c1_x,ave_c2_x, /*Averages of each classes*/
		  ave_c1_y,ave_c2_y,
		  mid_x,mid_y; 		/*Mid point of the lines(Seperating or Connecting both of them)*/
	int   counter=1, 		/*Counts element number of classes*/
		  prog_count=0;		/*Counts line number on the terminal screen*/

	while(counter!=NUM_CLASS+1)
	{
		printf("Line %d > ",prog_count);
		scanf("%f %f",&x,&y); /*Taking first class points*/
		counter++; 			prog_count++;
		sum_x = sum_x + x;
		sum_y = sum_y + y;
	}
	ave_c1_x = sum_x / NUM_CLASS;		ave_c1_y = sum_y / NUM_CLASS; /*Averages of class 1 coordinates*/

	counter=1;	sum_x=0;	sum_y=0; /*Reseting loop for class 2*/

	while(counter!=NUM_CLASS+1)
	{
		printf("Line %d >: ",prog_count);
		scanf("%f %f",&x,&y); /*Taking second class points*/
		counter++;			prog_count++;
		sum_x = sum_x + x;
		sum_y = sum_y + y;
	}
	ave_c2_x = sum_x / NUM_CLASS;		ave_c2_y = sum_y / NUM_CLASS; /*Averages of classs 2 coordinates*/
	
	if (ave_c2_x != ave_c1_x)
		tangent = (ave_c2_y - ave_c1_y) / (ave_c2_x - ave_c1_x); /*Calculating tangent of the connecting line*/

	else
		tangent = (ave_c2_y - ave_c1_y) / (ave_c2_x - ave_c1_x)+0,0000001; /*Calculating tangent of the connecting line*/

	
	mid_x = (ave_c1_x + ave_c2_x)/2;		
	mid_y = (ave_c1_y + ave_c2_y)/2; /*Calculation of the mid points of the lines*/
	
	/*printf("The line connecting average points: y = %fx + (%f)\n",tangent,ave_c2_y-(tangent*ave_c2_x));
	/* Connecting line by y=ax+b format*/

	tangent = -1/ tangent; /*Calculating tangent of the seperating line via relation of two perpendicular line tangents*/
	
	/*printf("Seperating line: y = %fx + (%f)\n",tangent,mid_y-(mid_x*tangent)); 
	/*Seperating line by y=ax+b format*/

	printf("Line %d > ",prog_count);
	prog_count++;

	if(ave_c1_y > tangent*ave_c1_x + (mid_y - (mid_x * tangent))) /*Determining Classes locations according to Seperating Line*/
	{
		while (scanf("%f %f",&x,&y) != 0)
		{
			if(y > (tangent*x) + (mid_y - (mid_x * tangent)))
				printf("Line %d > CLASS 1\n",prog_count);

			else if(y < (tangent * x) + (mid_y - (mid_x * tangent)))
				printf("Line %d > CLASS 2\n",prog_count);
		
			prog_count++;
			printf("Line %d > ",prog_count);
			prog_count++;	
		}
	}
	else
	{
		while(scanf("%f %f",&x,&y) != 0)
		{
			if(y > (tangent * x) + (mid_y - (mid_x * tangent)))
				printf("Line %d > CLASS 2\n",prog_count);

			else if(y < (tangent * x) + (mid_y - (mid_x * tangent)))
				printf("Line %d > CLASS 1\n",prog_count);
			
			prog_count++;
			printf("Line %d > ",prog_count);
			prog_count++;	
		}
	}
	return 0;
}
