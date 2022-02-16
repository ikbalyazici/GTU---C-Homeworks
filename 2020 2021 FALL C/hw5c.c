#include <stdio.h>
#include <string.h>

int tree(char inputs[250] , int counter , int bracket_counter , FILE *outp); /*Recursive function checks and prints the tree*/

int main()
{
	int counter=0 , bracket_counter=0 , i=0; /*Counter and bracket counter are for recursive function. i for loops in main*/
	char inputs[250],ch;
	
	FILE *inp;		FILE *outp;
	
	inp = fopen("input.txt","r");
	outp = fopen ("output.txt","w");

	i=0;
	while(!feof(inp)) /*Until end of input.txt*/
	{
		ch = getc(inp); /*Gets 1 character from input.txt (it gets spaces too)*/
		if(ch=='\n') /*input.txt is only one line so no need for newlinw character and newline is the end*/
			break;
		inputs[i]= ch; /*All characters readed from input.txt are stored in array*/
		i++;
	}
	tree(inputs,counter,bracket_counter,outp); /*Function call*/
	
	fclose(inp); fclose(outp); /*Closing files*/
	return 0;
}

int tree(char inputs[250] , int counter , int bracket_counter , FILE *outp)
{
	int len = strlen(inputs),i; /*Len is length of inputs array, i is array counter*/
	
	if (counter == len) /*Program reaches end of array so its the end*/
		return 1;		
	else 
	{
		if(inputs[counter]=='(') /*Its open bracket, it incraeses number of '-'*/
			bracket_counter++;
		else if(inputs[counter]==')') /*Its closebracket, it decreases number of '-'*/
			bracket_counter--;
		else if(inputs[counter]==',') /*Its comma, it shows new node starts so prints newline*/
			fprintf(outp,"\n"); 
		else	/*All other characters are in the node*/
		{
			if(inputs[counter-1]==',' || inputs[counter-1]=='(') /*It means its the 1st element of node, program print necesssary number of '-' before characters*/
			{
				for(i=0;i<bracket_counter;i++)
					fprintf(outp,"-"); /*Printing bracket counter times '-' */
			}
			fprintf(outp,"%c",inputs[counter]); /*Prints normal node characters*/
		}	
		counter++; 
		tree(inputs,counter,bracket_counter,outp); /*Function restart for next character*/
	}	
}
