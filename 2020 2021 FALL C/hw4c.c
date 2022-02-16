#include <stdio.h>
#include <string.h>
#include <math.h>

int main()
{
	double values[100],coef[50],power[50],sum=0,constant,evaluation;
	char poly [1000],c;
	int i=0,j=0,k=0,a=0,val_num;

	FILE *val;		FILE *pol;		FILE *eva; 

	val = fopen("values.txt","r");
	pol = fopen("polynomial.txt","r");

	while(!feof(val))
	{
		fscanf (val,"%lf ",&values[i]); /*Values in values.txt storing in values array as double numbers*/
		i++;
	}
	val_num=i; /*It stores how many values program stored. In the end when it calculate evaluations its necessary*/

	for(i=0;i<1000;i++) /*Before storing polynomial array make empty as an precaution for possible errors*/
		poly[i]='\0';

	i=0;	
	while(!feof(pol))
	{
		fscanf(pol,"%c ",&poly[i]); /*All characters in polynomial.txt stored in poly array except spaces*/
		i++;
	}
	fclose(val);	fclose(pol); /*No need to values.txt and polynomial.txt after this point. Both of them are closing*/

	i=0;
	while(poly[i]!='\0') /*Every character will controlling until the end*/
	{
		c='\0'; /*c is any character after any double number. As an precaution it will empty before each cycle*/
		if(i==0 && poly[i]>= '0' && poly[i]<='9') /*First element control. Starting with number possible only first element*/
		{
			sscanf(poly+i,"%lf %c",&constant,&c); /*Takes number and character*/
			if(c=='x') /*If character is 'x' number is coefficient unless number is constant*/
			{
				coef[j]=constant; /*If it is coefficient it stores in coef array until calculation of evaluations*/
				j++;
			}
			else
				sum=sum+constant; /*If it is constant it will directly added to evaluation. It stores in sum until calculation*/
		}

		if(poly[i]=='+' ||(poly[i]=='-' && poly[i-1]!='^')) /*Coefficient or constant will comes*/
		{
			if(poly[i+1]=='x') /*There is no coefficient but normally coefficient is 1...*/
			{
				if(poly[i]=='+')
					coef[j]=1; /*...so it stores coefficient array 1*/
				else 
					coef[j]=-1;/*...so it stores coefficient array -1 because operation is negation*/
				j++;
			}
			else /*Next number still can be coefficient ot constant*/
			{
				sscanf(poly+i,"%lf %c ",&constant,&c); /*Takes a number and a character*/
				if(c=='x') /*The character is 'x', it means number is a coefficient*/
				{
					coef[j]=constant; /*so it stores as coefficient*/
					j++;
				}
				else	/*The character is not 'x', it means number is constant*/
					sum=sum+constant;  /*Constants will directly added to evaluation, it stores in summation*/
			}
		}

		if(poly[i]=='x') 
		{
			if(poly[i+1]=='^')
				sscanf(poly+(i+2),"%lf",&power[k]); /*It takes power of x*/

			else
				power[k]=1; /*If power is not written after x , power is 1*/
				
			k++;	
		}
		i++;
	}
	
	eva = fopen("evaluations.txt","w");

	while(a!=val_num) /*Calculation of evaluation for each value in values array */
	{
		evaluation = sum; 
		for (k = 0; k < j; k++)
			evaluation = evaluation + pow(values[a],power[k])*coef[k];
			
		fprintf(eva,"%.2lf\n",evaluation);
		a++;
	}
	fclose(eva);
	return 0;
}