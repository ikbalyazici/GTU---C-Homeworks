#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Prototypes of functions are used in program*/
void random_numbers(int array[10]); /*Determines ten random numbers different from each other*/
void keep_words(int array[10],char keeper[10][20]); /*Reads necessary words from file and keeps*/
void create_board (char printer[20][21], int columns[20]);/*Creates an empty board*/
void print_board (char printer[20][21],int columns[20], char keeper[10][20]); /*Prints board on the screen*/
void word_length(char keeper[10][20],int lengthof[10]); /*Calculates words letter number*/
void random_place (int places[4]); /*Determines random coordinates and directions*/
void add_board(int places[4],char keeper[10][20], int lengthof[10], char printer[20][21]);/*Adds words on the board*/
void play_and_enjoy(char pos[5],char move[15], char printer[20][21], char keeper[10][20],int columns[20]); /*Playing actions*/
int  search(char move[15],char printer[20][21],int a,int net,int getbigger[2][15]); /*Looking for guessed word on the table*/

int main()
{
	int array[10],columns[20],lengthof[10],places[4],a,b;
	char printer[20][21],keeper[10][20],pos[5],move[15];

	printf("******WELCOME THE HARDEST WORD HUNT GAME******\n\n");

	srand(time(NULL));

	random_numbers(array); /*For creating rotation numbers. After creating numbers save in array called array*/
	keep_words(array,keeper); /*For taking words (showed by rotation numbers) from file and keeping them in array called keeper*/	
	word_length (keeper,lengthof); /*For calculating length of words*/
	create_board(printer,columns); /*Creating empty board*/
	add_board(places,keeper,lengthof,printer); /*Adding words on random locations on board*/
	play_and_enjoy(pos,move,printer,keeper,columns); /*Looks for guessed word on the table*/

	return 0;			
}

/*FUNCTIONS*/
void random_numbers(int array[10])
{
	int temp, i, a; /*i and a are loop counters, temp is carrier*/

	temp = rand()%100;
	array[0] = temp; /*Determination of first rotation number. (Naturally first ball is free :D)*/

	for (a = 1; a <= 9 ; a++) /*First member of array is given, so loop starts from 1*/
	{
		temp = rand()%100+1; /*Creating candidates for rotation numbers.*/
		for (i=0; i<a; i++) /*Equality control loop. Controlling only certain numbers are enough, so loop is bounded above by 'a'*/
		{
			if (temp == array[i]) /*Candidate equals one of certain members*/
			{
				a--;   /*Loop counter decrease for retry uncertain order*/
				break; /*To retry determination need to go back older loop, so exits from this loop*/
			}
			else
				array[a]=temp; /*Candidate is fit, we can keep it*/
		}				
	}
}

void keep_words(int array[10],char keeper[10][20])
{
	int counter=0, a=0, i=0; /*a and i are loop counters, counter counts lines of words until program reach true line*/
	for (a=0; a<=9; a++) /*To take 10 words from file to array*/
	{
		counter = 0;
		
		FILE *fp;
		fp = fopen ("words.txt","r"); /*Opening file with reading mode*/
		
		while(!feof(fp)) /*Word selection loop*/
		{
			for (i=0;i<=19;i++) /*Array cleaning loop*/
				keeper[a][i]='\0';
			
			fgets(keeper[a],20,fp); /*Getting word in array keeper*/

			for (i=0;i<=19;i++)
			{
				if(!(keeper[a][i]>='a'&&keeper[a][i]<='z')) /*Empty the rest of array after word*/
					keeper[a][i]='\0';
			}

			if (counter == array[a]-1) /*Controlling the line of the taken word*/
				{
					fclose(fp); /*Closing file. (Program open and close file in loop for reseting file pointer)*/
					break; /*Program takes what it wants. No need for taking anything different :D*/
				}
			else				
				counter++; /*Program has not reached true line yet, to check new line counter increase*/
		}
	}
}

void word_length(char keeper[10][20], int lengthof[10])
{
	int a,b; /*Loop counters*/
	for (a=0; a<=9; a++) /*ID of word*/
	{
		for(b=0; b<=19; b++) /*Letters*/
		{
			if (keeper[a][b]=='\0') /*Controling the end of word*/
				break;
			lengthof[a]=b+1; /*Letter counter starts from zero but the first letter must be one. This addition balanced it.*/
		}		
	}
}

void create_board (char printer[20][21], int columns[20])
{
	int a,b; /*Loop counters for filling arrays*/

	for (a=0; a<=19; a++) /*Column loop*/
	{
		columns[a] = a; /*Column numbers for frame of board*/

		for (b=0; b<=20; b++) /*Row loop*/
		{
			if (b==0) /*Row numbers for frame of board at start of each row*/
				printer[a][b] = 'A'+ a; /*From A to T letters*/
			else
					printer[a][b] = '*'; /*Empty blocks of board*/
		}
	}
}

void print_board (char printer[20][21],int columns[20],char keeper[10][20])
{
	int a,b; /*Loop counters*/

	printf("\n");
	for (a=0;a<=9;a++) 
	{
		for (b = 0; b < 19; b++)
			printf("%c",keeper[a][b]); /*Printing hidden words up to board*/
		printf(" "); /*To seperate hints from each other*/
	}
	printf("\n\n"); /*Space between hints and board*/
	printf("   "); /*For balancing the position of column numbers*/

	for (a=0; a<=19; a++) /*Printing column numbers*/
		if (a<10) /*For seperation column numbers from each other because of a good view*/
			printf("%d  ",columns[a]);
		else
			printf("%d ",columns[a]);

	for (a=0; a<=19; a++) /*Column loop*/
	{
		printf("\n");
		
		for (b=0; b<=20; b++) /*Row loop*/
			printf("%c  ",printer[a][b]); /*Printing letters*/	
	}
	printf("\n"); /*New line after end of each row*/
}

void random_place(int places[4])
{
	places[0] = rand()%20+1; /*Column*/
	places[1] = rand()%20;   /*Row*/
	places[2] = rand()%4;    /*Direction*/
	places[3] = rand()%2;    /*Opposite way*/
}

void add_board(int places[4],char keeper[10][20], int lengthof[10], char printer[20][21])
{
	int a,b,c,d,i,j,flag=0,counter=0; 
	/*a-d are for carrying random place values, i and j are loop counters, flag is error controller, counter is only counter*/

	for (i=0; i<=9; i++) /*Word ID loop*/
	{
		flag = 0;
		random_place (places); /*Determination of coordinates randomly*/
		a = places[0];	b = places[1];	c = places[2];	d = places[3];

		if (printer[a][b] == '*') /*Emptiness control*/
		{
			switch (c) /*Direction*/
			{
				case 0: /*Left - Right direction*/
					for(j=b; j<=b+lengthof[i]; j++)
					{
						if(printer[a][j]=='*' && b+lengthof[i]<20) /*Controlling emptiness and wall*/
							flag = 1; /*It means no error detected*/
						else
						{
							flag = 0; /*An error detected*/
							break;
						}
					}
					if (flag == 1) /*No error case*/
					{
						switch(d) /*Tendency*/
						{
							case 0: /*From left to right*/
								counter = 0;
								for (j=b; j<=b+lengthof[i]; j++)
									{	
										if(keeper[i][counter]=='\0')/*Controlling end of the word*/
											break; /*Letters of the word is finished loop must not continue*/
										printer[a][j] = keeper[i][counter]; /*Saving word for printing on the board*/
										counter++;
									}
								break;
							case 1: /*From right to left*/
								counter = 0;
								for (j=b+lengthof[i]; j>=b; j--)
									{
										if(keeper[i][counter]=='\0') /*Controlling the end of the word*/
											break; /*Letters of the word is finished loop must not continue*/
										printer[a][j] = keeper[i][counter]; /*Saving word for printing on the board*/
										counter++;
									}
								break;
						}
					}
					else /*Error case*/
						i--; /*Retry this word*/
					break;
				case 1:/*Up - Down direction*/
					for(j=a; j<=a+lengthof[i]; j++)
					{
						if(printer[j][b]=='*' && a+lengthof[i]<20) /*Controlling the emptiness and wall*/
							flag = 1; /*No error detected*/
						else
						{
							flag = 0; /*An error detected*/
							break;
						}
					}
					if (flag == 1) /*No error case*/
					{
						switch(d) /*Tendency*/
						{
							case 0: /*From up to down*/
								counter = 0;
								for (j=a; j<=a+lengthof[i]; j++)
									{
										if(keeper[i][counter]=='\0') /*Controlling the end of the word*/
											break; /*Letters of the word is finished loop must not continue*/
										printer[j][b] = keeper[i][counter]; /*Saving word for printing on the board*/
										counter++;
									}
								break;
							case 1: /*From down to up*/
								counter = 0;
								for (j=a+lengthof[i]; j>=a; j--)
									{
										if(keeper[i][counter]=='\0')  /*Controlling the end of the word*/
											break; /*Letters of the word is finished loop must not continue*/
										printer[j][b] = keeper[i][counter]; /*Saving word for printing on the board*/
										counter++;
									}
								break;
						}
					}
					else /*Error case*/
						i--; /*Retry this word*/
					break;
				case 2: /*Left-Down to Right-Up Cross direction*/
					counter = 0;
					for (j=a; j<=a+lengthof[i]; j++)
					{
						if(printer[j][b+counter]=='*' && a+lengthof[i]<20 && b+lengthof[i]<20) /*Controlling the emptiness and wall*/
						{
							counter++;
							flag = 1; /*No error detected*/
						}
						else 
						{
							flag = 0;/*An error detected*/
							break;
						}
					}
					if (flag == 1) /*No error case*/
					{
						switch(d)
						{
							case 0: /*From left to right reading*/
								counter = 0;
								for (j=a; j<=a+lengthof[i]; j++)
									{
										if(keeper[i][counter]=='\0') /*Controlling the end of the word*/
											break; /*Letters of the word is finished loop must not continue*/
										printer[j][b+counter] = keeper[i][counter]; /*Saving the word for printing on the board*/
										counter++;
									}
								break;
							case 1: /*From right to left reading*/
								counter = 0;
								for (j=a+lengthof[i]; j>=a; j--)
									{
										if(keeper[i][counter]=='\0') /*Controlling the end of the word*/
											break; /*Letters of the word is finished loop must not continue*/
										printer[j][b+lengthof[i]-counter] = keeper[i][counter]; /*Saving the word for printing on the board*/
										counter++;
									}
								break;
						}
					}
					else /*Error case*/
						i--; /*Retry this word*/
					break;
				case 3: /*Right-Down to Left-Up Cross direction*/
					counter = 0;
					for (j=a+lengthof[i]; j>=a; j--)
					{
						if(printer[j][b+counter]=='*' && a+lengthof[i]<20 && b+lengthof[i]<20) /*Controlling the emptiness and wall*/
						{
							counter++;
							flag = 1; /*No error detected*/
						}
						else 
						{
							flag = 0; /*An error detected*/
							break;
						}
					}
					if (flag == 1) /*No error case*/
					{
						switch(d)
						{
							case 0: /*From left to right reading*/
								counter = 0;
								for (j=a+lengthof[i]; j>=a; j--)
									{
										if(keeper[i][counter]=='\0') /*Controlling the end of the word*/
											break; /*Letters of the word is finished loop must not continue*/
										printer[j][b+counter] = keeper[i][counter]; /*Saving the word for printing on the board*/
										counter++;
									}
								break;
							case 1: /*From right to left reading*/
								counter = 0;
								for (j=a; j<=a+lengthof[i]; j++)
									{
										if(keeper[i][counter]=='\0') /*Controlling the end of the word*/
											break; /*Letters of the word is finished loop must not continue*/
										printer[j][b+lengthof[i]-counter] = keeper[i][counter]; /*Saving the word for printing on the board*/
										counter++;
									}
								break;
						}
					}
					else /*Error case*/
						i--; /*Retry this word*/
					break;
			}
		}
		else /*This coordinate is not empty*/
			i--; /*Retry this word*/
	}

	for (i = 0; i <=19; i++) /*Column loop*/
	{
		for (j = 1; j <=20; j++) /*Row loop*/
		{
			if(printer[i][j]=='*')
				printer[i][j] = 'a'+ rand()%26; /*Filling all empty blocks with random letters*/
		}
	}
}

void play_and_enjoy(char pos[5], char move[15], char printer[20][21], char keeper[10][20],int columns[20])
{
	int flag=11,a,b,c,net,getbigger[2][15],col,row,counter=0,second_flag=0,i,ID;

	print_board(printer,columns,keeper);
	while(flag != 1) /*When flag reaches 1 game will end*/
	{
		for(counter=0; counter<=4; counter++)
			pos[counter]='\0';
												/*Clearing arrays for next loop stage*/
		for(counter=0; counter<=14; counter++)
			move [counter]='\0';

		printf("Write your move, not a mistake, are you bored, just exit: ");
		scanf("%s",pos); /*Asking user the coordinates of guessed word*/
		if ((pos[0]=='e'||pos[0]=='E') && (pos[1]=='x'||pos[1]=='X') && (pos[2]=='i'||pos[2]=='I') && (pos[3]=='t'||pos[3]=='T') && pos[4]=='\0')
		{	
			printf("GAME OVER\n"); /*When user writes "exit" program finishes*/
			flag =1;
		}
		else
		{	
			scanf("%s",move); /*Users guess*/

			second_flag = 0; /*For controlling is guess from wanted words*/
			for(counter=0; counter<=9; counter++)
			{
				i =0;
				while(move[i]!='\0')
				{
					if(move[i]==keeper[counter][i])
						second_flag = 1; /*Letters are same*/
					else
					{
						second_flag = 0;
						break; /*These two words are not same*/
					}
					i++;
				}
				if (second_flag == 1) /*Words looks same*/
				{	
					ID = counter; /*Keeping words order between all looking words*/
					break;
				}
			}
			if (second_flag == 1) /*Words are same*/
			{
				a = pos[0] - 65; /*Changing row names to integer numbers*/
				b = pos[1] - 48; /*Type changing char to int*/
				
				if(pos[2]>='0' && pos[2]<='9') /*Two digit int numbers keeped by two char. It controls col number is 2 digit or 1 digit*/
				{
					b = b*10; 
					c = pos[2] - 48;
					net = b+c+1; /*Regaining column number as integer*/
				}
				else
					net = b+1;

				if((a>=0 && a<=19) && (net>=0 && net<=19))
				{
					if (search(move,printer,a,net,getbigger) == 1) /*Program searched the word by starting given position and find it*/
					{
						counter = 0;
						while(move[counter]!='\0') /*Making big founded words*/
						{
							col = getbigger[0][counter];
							row = getbigger[1][counter];
							printer[col][row] = printer[col][row] - 32; 
							keeper[ID][counter] = keeper[ID][counter] - 32;
							counter++;
						}
						flag--; /*A word founded finish is more close*/
						print_board(printer,columns,keeper);
						if(flag == 1)
							printf("YOU ARE JUST LUCKY ROOKIE\n");
					}
					else
						printf("WRONG REPLY, AGAİN TRY\n");
				}
				else
					printf("WRONG REPLY, AGAİN TRY\n");
			}
			else
				printf("WRONG REPLY, AGAİN TRY\n");
		}
	}
}

int  search(char move[15],char printer[20][21],int a,int net,int getbigger[2][15])
{
	int flag = 0,c=0,d=1;

	while(move[c]!='\0')
	{
		switch (d) /*Searcing all 8 ways*/
			{
				case 1:
				if (move[c]==printer[a][net+c])
				{
					getbigger[0][c] = a;
					getbigger[1][c] = net + c;
					flag = 1;
					break;
				}
				else
				{
					c = 0;	flag = 0;	d++;
				}

			case 2:
				if (move[c]==printer[a][net-c])
				{
					getbigger[0][c] = a;
					getbigger[1][c] = net - c;
					flag = 1;
					break;
				}
				else
				{
					c = 0;	flag = 0;	d++;
				}

			case 3:
				if (move[c]==printer[a+c][net])
				{
					getbigger[0][c] = a+c;
					getbigger[1][c] = net;
					flag = 1;
					break;	
				}
				else
				{
					c = 0;	flag = 0;	d++;
				}

			case 4:
				if (move[c]==printer[a-c][net])
				{
					getbigger[0][c] = a-c;
					getbigger[1][c] = net;
					flag = 1;
					break;
				}
				else
				{
					c = 0;	flag = 0;	d++;
				}

			case 5:
				if (move[c]==printer[a+c][net+c])
				{
					getbigger[0][c] = a+c;
					getbigger[1][c] = net+c;
					flag = 1;
					break;
				}
				else
				{
					c = 0;	flag = 0;	d++;
				}

			case 6:
				if (move[c]==printer[a-c][net-c])
				{
					getbigger[0][c] = a-c;
					getbigger[1][c] = net-c;
					flag = 1;
					break;
				}
				else
				{
					c = 0;	flag = 0;	d++;
				}

			case 7:
				if (move[c]==printer[a+c][net-c])
				{
					getbigger[0][c] = a+c;
					getbigger[1][c] = net-c;
					flag = 1;
					break;
				}
				else
				{
					c = 0;	flag = 0;	d++;
				}

			case 8:
				if (move[c]==printer[a-c][net+c])
				{
					getbigger[0][c] = a-c;
					getbigger[1][c] = net+c;
					flag = 1;
					break;
				}
				else
				{
					c = 0;	flag = 0;	d++;
				}

			default:
				c= 13;	flag = 0;
		}
	c++;
	}
	return flag;
}

