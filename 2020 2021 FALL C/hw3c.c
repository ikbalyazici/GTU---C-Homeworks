#include <stdio.h>
#include <string.h>

void makereverse (char input2[100][251], char reverse[250][101], int max); /*This function changes input2's rows to columns and colmuns to rows*/
void maxlength (char input2[100][251], int *max, int ar2_rc); /*This function find length of longest row of input2*/
void makeoutput (char input2[100][251], char reverse[250][101], int max, int ar2_rc); /*This reads input1 and creates output*/

int main ()
{
	char input2 [100][251], reverse [250][101]; /*Arrays to store input2 and its reverse (reverse for vertical searching)*/
	int ar2_rc=0,max=0; /*input2's row counter (ar2_rc) and longest rows magnitude (max) */

	FILE *fp2;
	fp2 = fopen ("input2.txt","r"); /*Opening of input2 to read*/

	while(!feof(fp2))
	{
		fscanf(fp2,"%s",input2[ar2_rc]); /*All characters in input2.txt stored in input2 array*/
		ar2_rc++; /*Counting how many rows are in input2. Program need it later*/
	}
	fclose (fp2); /*Closing input2.txt*/

	maxlength (input2,&max,ar2_rc);			/*First find max row length*/
	makereverse(input2,reverse,max);		/*Then create reverse of input2*/
	makeoutput(input2,reverse,max,ar2_rc);	/*Finally searching and creating output*/
	
	return 0;
}

void makereverse (char input2[100][251], char reverse[250][101],int max)
{
	int r=0,c=0; /*r ->row  c-> column counters*/

	while(input2[c][0]!='\0')
	{
		for (r = 0 ; r < max; r++) 
		{
			if (input2[c][r]=='\0')
				reverse [r][c] = '.'; /*Up to max all empty points filled with '.' for an easy searching*/
			else
				reverse [r][c] = input2 [c][r]; /*input 2's columns turns to reverse's rows (first column -> first row)*/
		}
		c++;
	}
}

void maxlength (char input2[100][251], int *max, int ar2_rc)
{
	int i;
	for (i=0; i<=ar2_rc; i++) /*ar2_rc is row number of input2*/
	{
		if(strlen(input2[i])> *max)
			*max = strlen(input2[i]); /*Founds max one by looking every row of input2*/
	}
}

void makeoutput (char input2[100][251], char reverse[250][101], int max, int ar2_rc)
{
	char input1 [11]; /*It stores next searching word (max 10 letter and \0 = 11)*/
	
	FILE *fp1; FILE *fp3;
	fp1 = fopen("input1.txt","r"); /*Opens input 1 to read*/
	fp3 = fopen("output.txt","w"); /*Creates or opens output.txt to write*/

	int flag=0,i=0; /*Flag is a controller looks search is succesful or not -- i is ordinary counter for loops*/
	do
	{
		flag = 0; /*Resetting flag for next searchings*/
		fscanf(fp1,"%s ",input1); /*Stores next searching word in array*/

		for(i=0; i<= ar2_rc ; i++) /*First it tries to find horizontally (by looking in input2 array)*/
		{
			if(strstr(input2[i],input1)!=NULL) /*strstr function gives NULL if it couldn't find. If it finds gives the adress of it*/
			{
				fprintf(fp3, "%s (%d,%ld) Horizontal\n",input1,i+1,strstr(input2[i],input1)-input2[i]+1); 
												/*adress of searched - adress of line beginning = coordinate of the word*/
				flag = 1;  /*Program found the word (1 means succesful)*/
				break;
			}
		}
		if (flag!=1) /*Program did not found horizontally*/
		{
			for(i=0; i<=max ; i++) /*so it tries to find vertically (by looking in reverse (array)*/
			{
				if (strstr(reverse[i],input1)!=NULL) /*strstr function gives NULL if it couldn't find. If it finds gives the adress of it*/
				{
					fprintf(fp3, "%s (%ld,%d) Vertical\n",input1,strstr(reverse[i],input1)-reverse[i]+1,i+1 );
												/*adress of searched - adress of line beginning = coordinate of the word*/
					flag = 1; /*Program found the word (1 means succesful)*/
					break;
				}
			}
		}
		/*Program makes nothing if a word not found. It turns to begining and searches new one*/
	} while (!feof(fp1)); /*Searching ends when input1 ends*/
	
	fclose (fp1);	fclose (fp3); /*Closing input1.txt and output.txt */
}