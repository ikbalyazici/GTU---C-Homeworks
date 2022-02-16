#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*Function prototipes*/
int draw_triangle(int side1,int side2,int side3);
void type_triangle(int side1,int side2, int side3);
int perimeter_triangle(int side1,int side2, int side3);
double area_triangle(int side1,int side2, int side3,int perimeter);
 


int main ()
{
	int side1,side2,side3,perimeter; 
	printf ("The length of first side: \n");
	scanf ("%d",&side1);
	printf ("The length of second side: \n");
	scanf ("%d",&side2);
	printf ("The length of third side: \n");
	scanf ("%d",&side3);
	
	draw_triangle (side1,side2,side3);
	
	if (draw_triangle (side1,side2,side3) == 1) /*To block continue with other functions altough it is can not drawn*/
	{
		printf("According to the triangle inequality theorem, this triangle can be drawn.\n\n");
	
		type_triangle (side1,side2,side3);
	    
		perimeter_triangle(side1,side2,side3);
	    printf ("The perimeter of the triangle: %d\n",perimeter_triangle(side1,side2,side3));
	    
		area_triangle(side1,side2,side3,perimeter);
		printf ("The area of the triangle: %f\n",area_triangle(side1,side2,side3,perimeter_triangle(side1,side2,side3)));
	}
	else if (draw_triangle (side1,side2,side3) == 0)
	{
		printf ("According to the triangle inequality theorem, this triangle cannot be drawn. \n");
	}
	return 0;
	 
}

/*Functions are used in program*/
int draw_triangle(int side1,int side2,int side3)
{
	int draw ; /*Output for determining process in main function*/
	
	if (abs(side1-side3)<side2 && side2<side1+side3)	/*Calculation for deciding it can drawn or not*/
	{
 		draw = 1; 
    }
	else 
	{
		draw =	0;
	}
	
	return draw; /*For sending output "draw" to main function*/
}

void type_triangle(int side1,int side2, int side3)
{
	if (side1 == side2 && side2 == side3) /*Deciding the type by comperating length of sides*/
	{
		printf ("It is a Equilateral Triangle \n");
	}
	else if (side1 == side2 || side2 == side3 || side1 == side3)
	{
		printf ("It is a Isosceles Triangle \n");
	}
	else 
	{
		printf ("It is a Scalene Triangle \n");
	}
}

int perimeter_triangle(int side1,int side2, int side3)
{
	int perimeter;
	perimeter = side1 + side2 + side3;
}

double area_triangle(int side1,int side2, int side3,int perimeter) 
{
float area,p; 
p = (float)perimeter/2;
area = sqrt(p*(p-side1)*(p-side2)*(p-side3));
} 

