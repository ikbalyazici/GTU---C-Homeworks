#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10

typedef struct gate /*INPUT, AND, OR, NOT, FLIPFLOP gates all stores as a struct*/
{
	char name[SIZE]; 	/*identifier names*/
	int type; 		 	/*Numeric information about the gate is INPUT, AND, OR, NOT or FLIPFLOP*/
	char input1[SIZE];  /*for all gates except INPUT it stores names of gates first inputs name*/
	char input2[SIZE];  /*for AND and OR gates it stores names of gates second inputs name*/
	int out;			/*for INPUT gates (ironic) it stores next gates input value*/
	int memory;			/*for FLIPFLOP gates it stores last FLIPFLOP output*/
	struct gate *inp1;  /*for all gates it stores adress of first input*/
	struct gate *inp2;  /*for AND and OR gates it stores adress of second input*/
	struct gate *next;  /*for all gates it stores next gate adress by creation order*/
	
}gate;

void create_gates(gate *root); /*This function creates gates in circuit.txt by text order*/
void link_gates(gate *root);   /*This function links gates each other by input output hierarchy*/
int evaluate (gate *g);		   /*This function evaluates output of input group*/

int main()
{
	FILE *inp, *outp;
	outp = fopen("output.txt","w");
	inp = fopen("input.txt","r");

	gate *root;
	gate *iter , *searcher;		/*iter and searcher pointers for some operations on the linked list*/
	root = (gate *)malloc(sizeof(gate));
	iter = root;
	searcher = root;
	int flag = 0; 				/*flag is for controlling repeated identifier name*/

	create_gates(root);			/*At first all gates will create*/
	link_gates(root);			/*After creation gates linked each other needed order*/
	
	while(!feof(inp))			/*Outputs will evaluate for inputs in input.txt*/
	{
		iter = root;
		while(iter->type ==0)
		{
			fscanf(inp,"%d ",&iter->out);	/*For evaluation INPUT gates takes their values*/
			iter=iter->next;
		}
		iter = root;
		while(iter->next!=NULL)
		{
			flag = 0;
			searcher=root;
			if(strcmp(iter->name,"FLIPFLOP")==0)	/*Resetting FLIPFLOP memory*/
				iter->memory=0;
			while(searcher->next!=NULL)
			{
				if(strcmp(iter->name,searcher->input1)==0 || strcmp(iter->name,searcher->input2)==0)
				{
					flag=1; /*identifier used as an input. Its not evaluation starting point*/
					break;
				}
				else
					searcher=searcher->next;
			}
			if(flag==0) /*identifier not used as an input. Its evaluation starting point*/
				break;
			else
				iter=iter->next;
		}
		fprintf(outp,"%d\n",evaluate(iter)); /*Printing outputs to output.txt*/
	}
	return 0;
}

void create_gates(gate *root)
{
	int flag=0; /*flag is for input line control. Input line is slightly different*/
	char ch='a'; /*ch is for newlinw symbol control*/
	
	FILE *cir;
	cir = fopen("circuit.txt","r");

	gate *iter;
	iter = root;

	while(!feof(cir))
	{
		if(flag==0)
		{
			while(ch!='\n')
			{
				fscanf(cir,"%s",iter->name);
				iter->type = 0;
				ch = getc(cir);
				if(ch=='\n')
					break;
				if(strcmp(iter->name,"INPUT")!=0) /*Creation input gates*/
				{
					iter->next = (gate *)malloc(sizeof(gate));
					iter = iter->next;
				}
			}
			flag = 1;
		}
		else
		{
			iter->next = (gate *)malloc(sizeof(gate)); /*Creating other gates and determining name and types*/
			iter = iter->next;

			fscanf(cir,"%s",iter->name);
			if(strcmp(iter->name,"AND")==0)
			{
				fscanf(cir,"%s",iter->name);
				iter->type = 1;
				fscanf(cir,"%s %s",iter->input1, iter->input2);
			}

			if(strcmp(iter->name,"OR")==0)
			{
				fscanf(cir,"%s",iter->name);
				iter->type = 2;
				fscanf(cir,"%s %s",iter->input1, iter->input2);
			}

			if(strcmp(iter->name,"NOT")==0)
			{
				fscanf(cir,"%s",iter->name);
				iter->type = 3;
				fscanf(cir,"%s",iter->input1);
			}

			if(strcmp(iter->name,"FLIPFLOP")==0)
			{
				fscanf(cir,"%s",iter->name);
				iter->type = 4;
				fscanf(cir,"%s",iter->input1);
			}
		}
	}
	iter->next = NULL;
}

void link_gates (gate *root)
{
	gate *iter;
	gate *linker;
	iter = root;

	while(iter->next != NULL)
	{
		linker = root;

		if(iter->type == 1 || iter->type == 2) /*It is AND gate or OR gate*/
		{
			while(strcmp(linker->name,iter->input1)!=0)
				linker = linker->next;

			iter->inp1 = linker;
			linker = root;

			while(strcmp(linker->name,iter->input2)!=0)
				linker = linker->next;

			iter->inp2 = linker;
		}
		else if (iter->type == 3 || iter->type == 4) /*It is NOT gate or FLIPFLOP gate*/
		{
			while(strcmp(linker->name,iter->input1)!=0)
				linker = linker->next;

			iter->inp1 = linker;
		}
		iter = iter->next;
	}
}

int evaluate (gate *g)
{
	int i1,i2;
	switch (g->type)
	{
		case 1: //gate type is AND
			i1 = evaluate(g->inp1);
			i2 = evaluate(g->inp2);
			g->out = (i1 && i2);
			return (g->out);
			break;
		case 2: //gate type is OR
			i1 = evaluate(g->inp1);
			i2 = evaluate(g->inp2);
			g->out = (i1 || i2);
			return (g->out);
			break;
		case 3: //gate type is NOT
			i1 = evaluate(g->inp1);
			switch (i1)
			{
				case 1: g->out = 0;
					break;
				case 0: g->out = 1;
					break;
			}
			return (g->out);
			break;
		case 4: //gate type is FLIPFLOP
			i1 = evaluate(g->inp1);
			i2 = g->memory;
			if(i1==i2)
				g->memory = 0;
			else 
				g->memory = 1;
			g->out = g->memory;
			return(g->out);
			break;
		default: //gate type is INPUT
			return (g->out);
	}
}