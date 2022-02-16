#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

/*Prototypes of functions are used in program*/
void decrypt_and_print (char* file_path);
char decrypt_numbers (int number);
void deep_decrypt_and_print (char* file_path);
void track_machine ();
void refresh_position (int *X, int *Y, double *D, double *R);
void encrypt_messages (char* file_path);
int encrypt_numbers (char character);
void menu ();

int main()
{
	menu();
	
	return 0;
}

/*Functions are used in program*/
void menu ()
{
	int choice;

	printf("\n"); /*For good view on Terminal screen. :D */
	printf("1-) Decrypt and print encrypted_p1.img\n");/*Menu*/
	printf("2-) Decrypt and print encrypted_p2.img\n");
	printf("3-) Switch on the tracking machine\n");
	printf("4-) Encrypt the message\n");
	printf("5-) Switch off\n");
	printf("\nPlease make your choice:\n");

	scanf("%d",&choice); /*Selection from menu*/

	if (choice <= 4 && choice > 0) /*Menu - App matching and Function calls*/
	{
		switch (choice)
		{
		case 1: decrypt_and_print ("encrypted_p1.img");
			break;

		case 2: deep_decrypt_and_print ("encrypted_p2.img");
			break;

		case 3: track_machine ();
			break;

		case 4: encrypt_messages ("decrypted_p4.img");
			break;		
		}
	}

	else if (choice == 5) /*Shutdowning program*/
	{
		printf("FAREWELL CAPTAIN!!😢\n");
	}

	else /*Elimination of the invalid commands*/
	{
		printf("Menu does not include your selection. Please try again\n");
		return menu (); /*Command is invalid. We need valid selection.*/
	}
}

void decrypt_and_print (char* file_path)
{
	char ch;
	
	FILE *fp;
	fp = fopen (file_path,"r"); /*Opening file with reading mode*/
	
	while (!feof(fp))           /*It checks is program reached end of file or not*/
	{
		ch = getc(fp);
		printf("%c",decrypt_numbers ((int)ch-48)); /*Zero has value 48 when it is a character. 
													 To get integer type we need this subtition*/
	}
	fclose (fp);                /*Closing file. Like olds said: Leave it how you find it.*/

	return menu();
}

char decrypt_numbers (int number) /*Helper function of decrypt_and_print and deep_decrypt_and_print functions*/
{
	char character;
	switch (number) /*Swapping numbers with characters for decryption.*/
	{
		case 0: character = ' '; 
			break;

		case 1: character = '-';
			break;

		case 2: character = '_';
			break;

		case 3: character = '|';
			break;

		case 4: character = '/';
			break;

		case 5: character = '\\';
			break;

		case 6: character = 'O';
			break;

		default : printf("\n");
	}
	return character;
}

void deep_decrypt_and_print (char* file_path)
{
	int n1=0,n2=0,n3=0,counter=0; /*n1,n2 and n3 are for applying formula (summation elements)*/
	char ch;
	
	FILE *fp;
	fp = fopen (file_path,"r");   /*Opening file with reading mode*/
	
	while (!feof(fp))             /*It checks is program reach end of file or not*/
	{
		ch = getc(fp);
		n1 = n2;
		n2 = n3;
		n3 = (int)(ch)-48;        /*To keep three fresh value which used in formula in their step*/
		counter++;                /*Counter controls the line. Where we start reading
		 							new line and where will start writing*/

		if (ch =='\n')            /*New lines new beginings*/
		{
			n1 = 0;
			n2 = 0;
			n3 = (int)(ch)-48;    /*Each new line program refreshes variables and restart read-write operation*/
			counter = 0;
			printf("%c",decrypt_numbers ((n1+n2+n3)%7));
		}

		if (counter >= 3)         /*To decrypt we need first three character. So we wait it.*/
		{
			printf("%c",decrypt_numbers ((n1+n2+n3)%7));
		}		
	}
	fclose (fp);                  /*If you do not use it, close it.*/
	return menu();
}

void track_machine ()
{	
	int X=0,Y=0;         /*Initial coordinates of enemy*/
	double R=0.0,D=8.49; /*Initial values of displacement end distance to our camp*/
	char command;

	do  /*Do-While loop*/
	{
		int a;  /*Vertical axis of map*/
		for (a=1; a<=11; a++)
		{
			int b;  /*Horizontal axis of map*/
			for (b=1; b<=11; b++)
			{
				if (a==6 && b==6)  /*Center of map...*/
				{
					if (X==6 && Y==6)
					{
						printf("LOVE  "); /*GREATEST LOVES START WİTH HATE*/
					}
					else
					{
						printf("O     "); /*...and our camp.*/
					}
				}
				else if (a==X && b==Y)    /*Marking coordinates of enemy on the map*/
				{
					printf("E     ");     /*Enemies 'E'*/
				}
				else 
				{
					printf(".     ");     /*Empty areas (maybe not empty but we do not know so it is empty)*/
				}
			}
			printf("\n");
		}
		printf("Enemies X position: %d, Y position: %d, Displacement: %.2f, Distance to our camp:%.2f\n",X,Y,R,D);
		/* When enemy at 0,0 (initial position) we can not see him on map, because map starts 
		   from 1,1. However we can determine where are they even we can not show on the map. */
		printf("Command waiting...:");

		scanf(" %c",&command); /*Give the Command Captain!*/

		if (command == 'R') 
		{
			refresh_position(&X,&Y,&D,&R);
		}
		else if (command != 'E') 
		{
			printf("\nInvalid Command! Command Waiting...:\n");
		}			
	} 
	while (command != 'E');/*For running program until user enter 'E'*/
	
	return menu();

}

void refresh_position (int *X, int *Y, double *D, double *R) /*Helper function of track_machine function*/
{
	int oldX=*X,oldY=*Y;  /*We keep old values for calculating displacement and distance*/

	srand(time(NULL));    /*Program gives random values for coordiantes*/

	*X = rand()%11+1;     /*Map starts from (1,1) and length and width of map is 11.*/
	*Y = rand()%11+1;

	*R = sqrt(pow(*X-oldX,2)+pow(*Y-oldY,2)); /*Calculating displacement*/
	*D = sqrt(pow(*X-6,2)+pow(*Y-6,2));       /*Calculating distance from our camp*/
}

void encrypt_messages (char* file_path)
{
	int n1=0,n2=0,n3=0; /*n1,n2 and n3 are for applying formula (summation elements)*/
	char ch;
	FILE *fp1,*fp2;                       /*Program runs for two different file*/
	fp1 = fopen (file_path,"r"); /*First one opens for reading, program will encrypt it*/
	fp2 = fopen ("encrypted_p4.img","w"); /*Second one opens for writing, the encrypted message will inside it*/

	while (!feof(fp1))  /*It checks are file pointer reached the end of the file or not*/
	{
		ch = getc(fp1); /*Gets characters from reading file*/

		if (ch == '\n') /*New line control*/
		{
			n1 = 0;
			n2 = 0; 
			n3 = 0;
			fprintf(fp2,"\n");
		}

		else 
		{
			n1 = n2;
			n2 = n3;
			n3 = encrypt_numbers(ch);       /*Applying the encryption formula*/
			fprintf(fp2,"%d",(n1+n2+n3)%7); /*Printing the encrypted message in the file*/
		}
	}
	fclose (fp1); 
	fclose (fp2);

	printf("Message has been encrypted sir! It is in the file: encrypted_p4.img\n");
	
	return menu();
}

int encrypt_numbers (char character) /*Helper function of encrypt_messages function*/
{
	int number; /*This time characters changes to integers.*/
	switch (character)
	{
		case ' ': number =0;
			break;
		
		case '-': number =1;
			break;	
	
		case '_': number =2;
			break;

		case '|': number =3;
			break;

		case '/': number =4;
			break;

		case '\\': number =5;
			break;

		case 'O': number =6;
			break;		

		default : printf("\n");
	}
	return number;
}
