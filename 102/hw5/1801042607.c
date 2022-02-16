#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

/*Prototypes of functions are used in program*/
void menu();
void read_news(char buffer[500], char file_path[10], int is_Only_Title);
void append_file(char* file_path, char c );
void read_magic_numbers(char buffer_magic[10], char buffer_news[500]);
double f_func(int x);
double g_func(double f(int x), int a);
int is_readed(char* file_path, char c);
void all_readed_news(char* file_path);

int main()
{
	menu (); /*Calling menu*/

	return 0;
}

/*Functions are used in program*/

void menu()
{
	char s_op, s_yn,c, buffer[500], buffer_news[500]; 
	/*s_op = operation selection helper, s_yn = YES NO selection helper, arrays for storing news*/
	char file_path1[11] = "news/1.txt", file_path2[11] = "news/2.txt", file_path3[11] = "news/3.txt", file_path4[11] = "news/4.txt";
	/*In operation a they used for calling the function for reading the news user wanted*/
	char buffer_magic1[11]="news/1.txt", buffer_magic2[11]="news/2.txt", buffer_magic3[11]="news/3.txt", buffer_magic4[11]="news/4.txt";
	/*In operation c they used first for determining which new will decrypt, and then they used for saving magic numbers*/
	int s_new,is_Only_Title,stopper = 0;
	/*s_new = new selection helper, is_Only_Title = Type of reading selection helper, stopper = continuity determination helper */


	printf("**********Daily Press**************\n");
	printf("\nToday's news are listed for you :\n\n");
	printf("Title of 1. news:YENI TIP KORONAVIRUS SALGININDA SON 24 SAAT\n");
	printf("Title of 2. news:Fatih Terim'in kızı Merve Terim patladı! ""Inanılmaz sinirliyim...""\n");
	printf("Title of 3. news:Kapıköy Gümrük Kapısı'ndaki yolcu giriş ve çıkışları geçici süreyle durduruldu\n");
	printf("Title of 4. news:Son dakika... Bakan Selçuk: 7 milyar liraya yakın asgari ücret desteği vereceğiz\n");
	printf("\nWhat do you want to do?\n");
	printf("a.Read a new\n");
	printf("b.List the readed news\n");
	printf("c.Get decrypted information from the news\n");

	scanf (" %c",&s_op); /*Selection of operation*/

	switch (s_op) /*Calling only the operation selected by user*/
	{
		case 'a': 
			printf("Which news text you want to read?\n");
			scanf ("%d",&s_new); /*Selection of news user wants to read*/
			c = s_new + 48; /*s_new is an integer. Its for using true char version*/
			
			if (is_readed("readed_news_id.txt",c) == 1) /*Controlling is the wanted new readed or not. 1- Its readed, 0- Not yet*/
			{
				printf("This new is readed. Do you want to read again? Yes(1) / No(O)\n");
				scanf (" %c",&s_yn); 

				if (s_yn == '0')
				{
					printf("Do you want to continue? Yes(y)/No(n):\n");
					scanf (" %c",&s_yn);

					if (s_yn == 'y'||s_yn == 'Y')
						menu (); /*For continuity program turns back to the top of menu*/

					else if (s_yn == 'n'||s_yn == 'N')
						printf("Good Bye!\n");

					else 
						printf("Invalid YES NO selection\n");

					stopper = 1;
				}

				else if (s_yn != '1')
				{
					printf("Invalid selection\n");
					stopper = 1;
				}

			}
			
			if (stopper == 0)
			{
				append_file ("readed_news_id.txt",c); /*Its for adding the selected new as readed one */
				switch (s_new) /*Calling only the new user wanted to read*/
				{
					case 1: 
						printf("Is only title? Yes(1)/No(0)\n");
						scanf ("%d",&is_Only_Title);
						
						if (is_Only_Title == 1 || is_Only_Title == 0)
						{
							read_news (buffer,file_path1,is_Only_Title); /*Function call for reading*/
							
							printf("Do you want to continue? Yes(y)/No(n):\n");
							scanf (" %c",&s_yn);

							switch (s_yn)
							{
								case 'y':
								case 'Y':
									return menu();
									break;

								case 'n':
								case 'N':
									printf("Good bye!\n");
									break;

								default : 
									printf("Invalid selection.\n"); 
							}
						}
						
						else
							printf("Invalid YES/NO Selection!!\n");
						
						break;

					case 2: 
						printf("Is only title? Yes(1)/No(0)\n");
						scanf ("%d",&is_Only_Title);
						
						if (is_Only_Title == 1 || is_Only_Title == 0)
						{
							read_news (buffer,file_path2,is_Only_Title);
							
							printf("Do you want to continue? Yes(y)/No(n):\n");
							scanf (" %c",&s_yn);

							switch (s_yn)
							{
								case 'y':
								case 'Y':
									return menu();
									break;

								case 'n':
								case 'N':
									printf("Good bye!\n");
									break;

								default : 
									printf("Invalid selection.\n");
							}
						}

						else
							printf("Invalid YES/NO Selection!!\n");
						
						break;

					case 3: 
						printf("Is only title? Yes(1)/No(0)\n");
						scanf ("%d",&is_Only_Title);
						
						if (is_Only_Title == 1 || is_Only_Title == 0)
						{
							read_news (buffer,file_path3,is_Only_Title);

							printf("Do you want to continue? Yes(y)/No(n):\n");
							scanf (" %c",&s_yn);

							switch (s_yn)
							{
								case 'y':
								case 'Y':
									return menu();
									break;

								case 'n':
								case 'N':
									printf("Good bye!\n");
									break;

								default : 
									printf("Invalid selection.\n");
							}
						}
						
						else
							printf("Invalid YES/NO Selection!!\n");
						
						break;

					case 4: 
						printf("Is only title? Yes(1)/No(0)\n");
						scanf ("%d",&is_Only_Title);
						
						if (is_Only_Title == 1 || is_Only_Title == 0)
						{
							read_news (buffer,file_path4,is_Only_Title);

							printf("Do you want to continue? Yes(y)/No(n):\n");
							scanf (" %c",&s_yn);

							switch (s_yn)
							{
								case 'y':
								case 'Y':
									return menu();
									break;

								case 'n':
								case 'N':
									printf("Good bye!\n");
									break;

								default : 
									printf("Invalid selection.\n");
							}
						}

						else
							printf("Invalid YES/NO Selection!!\n");
						
						break;

					default : printf("Sorry! The page you are looking for was not found.\n");
				}
			}
			break;

		case 'b':
			all_readed_news("readed_news_id.txt"); /*This called function shows all readed news*/

			printf("Do you want to continue? Yes(y)/No(n):\n");
			scanf (" %c",&s_yn);

			switch (s_yn)
			{
				case 'y':
				case 'Y':
				  	return menu();
					break;

				case 'n':
				case 'N':
					printf("Good Bye!");
					break;

				default : 
					printf("Invalid YES NO selection\n");		
			}

			break;

		case 'c':
			printf("Which news would you like to decrypt?:");
			scanf ("%d",&s_new);/*Selection of new */
			c = s_new + 48; /*Integer to char type changing*/

			switch (s_new)
			{
				case 1: 
					read_magic_numbers(buffer_magic1,buffer_news);
					break;

				case 2: 
					read_magic_numbers(buffer_magic2,buffer_news);
					break;

				case 3: 
					read_magic_numbers(buffer_magic3,buffer_news);
					break;

				case 4: 
					read_magic_numbers(buffer_magic4,buffer_news);
					break;

				default: printf("Sorry! The page you are looking for was not found.\n");
			}

			printf("Do you want to continue? Yes(y)/No(n):\n");
			scanf (" %c",&s_yn);

			switch (s_yn)
			{
				case 'y':
					return menu();
					break;

				case 'n':
					printf("Good bye!\n");
					break;

				default : 
					printf("Invalid YES NO selection.\n");
			}

			break;

		default: printf("Invalid operation selection.\n");
	}
	printf("\n");
}

void read_news(char buffer[500], char file_path[10], int is_Only_Title) /*For reading news*/
{
	char ch;
	int n;	

	FILE *fp;
	fp = fopen (file_path,"r"); /*It opens the file selected by user in the menu for reading*/

	for (n=0; n<=500; n++) /*It resets and clear tehe array for new news*/
		buffer[n] = '\0';

	if (is_Only_Title == 1)
	{	
		n=0;	
		while (!feof(fp))           
		{	
			ch = getc(fp);

			if(ch == '\n') /*When the title ends new line came, so for only title we stopped loop at new line */
				break;
	
			buffer[n]= ch;
			n++;
		}
	}

	else 
	{
		n = 0;
		while (!feof(fp)) /*It get in the array full text to print*/
		{
			ch = getc(fp);
			
			buffer[n]= ch;
			n++;
		}
		buffer [n-1] = '\0';
	}

	n = 0;
	while (buffer[n]!='\0') /*It prints the array*/
	{
		printf("%c",buffer[n]);
		n++;
	}

	printf("\n\n"); /*for a good view*/
	
	fclose (fp);   /*Closing file*/
}

void append_file(char* file_path, char c) /*For saving readed texts id */
{	
	int q, f = 0; /*q = for statement counter || f = control flag*/

	FILE *fp;
	fp = fopen (file_path,"a+"); /*File opens for adding new things at the end*/
	
	while (!feof(fp))
	{
		for (q = 0; q <= 4; q++) /*It checks is the id of the new already saved or not*/
		{		
			if (c == getc(fp))
				f = 1;		     /*If id is saved flag changes*/
		}

		if (f == 0)
			fprintf(fp,"%c",c);	 /*ID is not already saved so we need to save, so we write it on file*/
	}
	fclose (fp); /*Closing file for keeping changes*/
}

int is_readed (char *file_path, char c) /*This function checks the news that user wants to read is readed or not*/

{
	int flag = 0; /*Control flag. It controls is the wanted new readed. 1- readed 0- not readed yet*/

	FILE *fp;
	fp = fopen (file_path,"r"); /*Opening file with reading mode*/

	while (!feof(fp))
	{
		if (getc(fp)== c) /*It looks saved IDs */
		{
			flag = 1; /*It is readed, so flag changed*/
			break;
		}
	}

	fclose (fp);
	return flag; /*Returns the result*/
}

void all_readed_news(char *file_path) /*This function shows all readed news IDs */
{
	char ch;
	FILE *fp;
	fp = fopen (file_path,"r"); /*File opened with reading mode*/

	while (!feof(fp))
	{
		ch = getc (fp);
		if (ch <='4' && ch >= '1') 
			printf("%c. new is readed.\n",ch); /*Prints all readed numbers as a list*/
	}
	fclose(fp);
}
void read_magic_numbers(char buffer_magic[10], char buffer_news[500]) /*It shows bigger picture :D*/
{
	char ch,id = buffer_magic[5]; /*ch = transfers the character file to array, id= id of news */
	int n,d,a; /*n = array index, d= array index , a = magic number*/
	double sum=0; /*Sum of g function results*/

	FILE *fp;
	fp = fopen (buffer_magic,"r"); /*Opening with reading mode*/

	for (n=0; n<=500; n++)
		buffer_news[n] = '\0'; /*Clearing arrays*/
	for (d=0; d<=9; d++)
		buffer_magic[d] = '\0';

	n = 0;
	while (!feof(fp))           
	{
		ch = getc(fp);
		
		buffer_news[n]= ch; /*Saving characters in array*/
		n++;
	}
	buffer_news[n-1] = '\0'; /*For stopping at end point*/

	n = 0; /*Reseting index counters*/
	d = 0;
	while (buffer_news[n]!='\0')
	{
		printf("%c",buffer_news[n]); /*Printing full new*/

		if (buffer_news[n] == '#') /*Determining magic numbers*/
		{
			buffer_magic[d] = buffer_news [n+1];
			a = buffer_magic[d]-48; /*Changing char to integer*/

			sum = sum + g_func(f_func,a); /*Summation */
			d++;
		}
		n++; /*next array character*/
	}
	switch (id) /*Printing the message with hidden number of each new*/
	{
		case '1': printf("\n\nExpected number of tests performed = %.2f\n",sum );
			break;
		case '2': printf("\n\nNumber of sick people = %.2f\n",sum );
			break;
		case '3': printf("\n\nNumber of deaths = %.2f\n",sum );
			break;
		case '4': printf("\n\nNumber of sick people = %.2f\n",sum );
			break;
	}
	
	printf("\n\n"); /*New lines for good view*/
	fclose (fp);    /*Closing file*/
}

double f_func(int x)
{
	return pow(x,3) - pow (x,2) + 2; /*Calculating x^3 − x^2 + 2 equation as a step of decryption*/
}

double g_func(double f(int x), int a)
{
	return pow(f(a),2);   /*Calculating x^2 equation as aa step of decryption*/
}