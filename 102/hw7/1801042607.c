#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Function Prototypes*/
void menu(); 
void store_all (char all[2001][210]);
/*Stores everything in txt file to all array*/
void store(char all[2001][210],char names[2001][110],float gameinfo[2001][7],char genres[12][21], char pform[10][21],int cg[12],int cp[10]);
/*Makes all necessary seperate store operations*/
void genres_and_pform (char genres[12][21], char pform[10][21],char t_genres[2001][21],char t_pform[2001][21],int cg[12],int cp[10], float gameinfo[2001][7]);
/*Helper function of store function. Makes all necessary operations for genre and platform datas*/
int control_years(char user_entry[110],int selection);
/*Before listing games through the years this controls selection and entry*/
void print_years(char user_entry[110], int selection, char names[2001][110], float gameinfo[2001][7]);
/*After control this function prints on monitor all the games inside the wanted area*/
float average(float gameinfo[2001][7]);
/*Calculates the average of user scores*/
int compare(char user_entry[110],char names[2001][110],float gameinfo[2001][7]);
/*Compares North America and Europe sales*/
int info(char user_entry[110],char names[2001][110],float gameinfo[2001][7],char genres[12][21],char pform[10][21]);
/*Gives all information about single selected game*/


int main()
{
	menu();
	return 0;
}

/*Functions*/
void menu()
{
	int order,letter,operation=0,selection,flag=0,cg[12],cp[10]; 
	char all[2001][210],names[2001][110],genres[12][21],pform[10][21],user_entry[110];
	float gameinfo[2001][7];
	/*Arrays, loop counters and selection things for this function*/

	store_all(all);
	store(all,names,gameinfo,genres,pform,cg,cp);	

	while(operation!=8) /*Program does not terminate itself until user selects 8th operation */
	{
		printf("0: List of the Genres\n");
		printf("1: List of the Platforms\n");
		printf("2: List of the Games Through the Years \n");
		printf("3: All Informations of a Single Game \n");
		printf("4: Average of the User Scores\n");
		printf("5: Georographical Information of a Single Game\n");
		printf("6: Frequence of the Genres\n");
		printf("7: Frequence of the Platforms\n");
		printf("8: Exit\n");
		printf("\nPlease select an operation:");
		scanf("%d",&operation);
		printf("\n\n\n\n");

		switch(operation)
		{
			case 0:
				for(order=0; order<=11; order++)
					printf("%s\n",genres[order]); /*Prints the list of genres of games*/
				break;
			case 1:
				for(order=0; order<=9; order++)
					printf("%s\n",pform[order]); /*Prints the list of platforms of games*/
				break;
			case 2:
				flag = 0;
				while(flag!=1)
				{
					printf("\n\nEnter a year: "); /*Takes year value from user*/
					scanf("%s",user_entry);
					printf("Until (0) or Since (1) %s : ",user_entry); /*Takes operation selection of user*/
					scanf("%d",&selection);
					if(control_years(user_entry,selection) == 1) /*Truth control*/
					{
						print_years(user_entry, selection, names, gameinfo);
						flag=1;
					}
					else
						printf("TRY AGAIN\n");
				}
				break;
			case 3:
				flag = 0;
				while (flag!=1)
				{
					printf("Please enter the name of the game: \n"); /*Takes game name from user*/
					scanf("%s",user_entry);
					flag = info(user_entry,names,gameinfo,genres,pform);
				}
				break;
			case 4:
				printf("Average = %f\n",average(gameinfo));
				break;
			case 5:
				flag = 0;
				while (flag!=1)
				{
					printf("Please enter the name of the game: \n"); /*Takes game name from user*/
					scanf("%s",user_entry);
					flag = compare(user_entry,names,gameinfo);
				}
				break;
			case 6:
				for(order=0; order<=11; order++)
				{
					printf("%s",genres[order]);
					for(letter=0; 15-letter>=strlen(genres[order]); letter++) /*Prints genres of games with frequences*/
						printf(" ");
					printf("%d\n",cg[order]);
				}
				break;
			case 7:
				for(order=0; order<=9; order++)
				{
					printf("%s",pform[order]);
					for(letter=0; 8-letter>=strlen(pform[order]); letter++) /*Prints platforms of games with frequences*/
						printf(" ");
					printf("%d\n",cp[order]);
				}
				break;
			case 8:	
				printf("SEE YOU AGAIN\n"); /*Farevell message*/
				break;
			default: printf("TRY AGAIN\n\n\n");
		}
		printf("\n\n\n");
	}
}

void store_all(char all[2001][210])
{
	int order;
	FILE *fp;
	fp = fopen ("Video_Games.txt","r"); /*Opening file with reading mode*/

	for (order=0; order<=2000; order++)
		fgets(all[order],210,fp);	/*Takes everything string by string*/
}

void store(char all[2001][210],char names[2001][110],float gameinfo[2001][7],char genres[12][21], char pform[10][21],int cg[12],int cp[10])
{
	char t_genres[2001][21],t_pform[2001][21],r_year[2001][15],NA[2001][15],EU[2001][15],global[2001][15],score[2001][15];
	int order,letter=0,counter;
	/*Arrays, loop counters and selection things for this function*/

	for(order=0; order<=2000; order++)
	{
		letter = 0;
		counter = 0;
		for(letter=0;letter<=109;letter++) /*Cleaning arrays */
			names[order][letter] = '\0';

		for(letter=0;letter<=20;letter++)
			t_genres[order][letter] = '\0';

		for(letter=0;letter<=20;letter++)
			t_pform[order][letter] = '\0';

		for(letter=0;letter<=14;letter++)
			r_year[order][letter] = '\0';

		for(letter=0;letter<=14;letter++)
			NA[order][letter] = '\0';

		for(letter=0;letter<=14;letter++)
			EU[order][letter] = '\0';

		for(letter=0;letter<=14;letter++)
			global[order][letter] = '\0';

		for(letter=0;letter<=14;letter++)
			score[order][letter] = '\0';
			

		letter = 0;
		counter = 0;
		while(all[order][letter]!=',') /*Takes only names and keeps them in the its array*/
		{	
			names[order][counter] = all[order][letter];
			letter++;
			counter++;
		}
		
		counter = 0;
		letter++;
		while(all[order][letter]!=',') /*Takes only genres and keeps them in the its array*/
		{	
			t_genres[order][counter] = all[order][letter];
			letter++;
			counter++;
		}

		counter = 0;
		letter++;
		while(all[order][letter]!=',') /*Takes only platforms and keeps in the its array*/
		{	
			t_pform[order][counter] = all[order][letter];
			letter++;
			counter++;
		}
		
		counter = 0;
		letter++;
		while(all[order][letter]!=',') /*Takes only years and keeps in the its array*/
		{	
			r_year[order][counter] = all[order][letter];
			letter++;
			counter++;
		}
		gameinfo[order][2]=strtof(r_year[order],NULL); /*Year datas saves as float in a special array*/

		counter = 0;
		letter++;
		while(all[order][letter]!=',') /*Takes only North America sales and keeps in the its array*/
		{	
			NA[order][counter] = all[order][letter];
			letter++;
			counter++;
		}
		gameinfo[order][3]=strtof(NA[order],NULL); /*North America sale datas saves as float in a special array*/

		counter = 0;
		letter++;
		while(all[order][letter]!=',') /*Takes only Europe sales and keeps in the its array*/
		{	
			EU[order][counter] = all[order][letter];
			letter++;
			counter++;
		}
		gameinfo[order][4]=strtof(EU[order],NULL); /*Europe sale datas saves as float in a special array*/

		counter = 0;
		letter++;
		while(all[order][letter]!=',') /*Takes only total sales and keeps in the its array*/
		{	
			global[order][counter] = all[order][letter];
			letter++;
			counter++;
		}

		if(strcmp(global[order],"not_available")==0) /*For non number data special operation*/
			gameinfo[order][5] = 100; 
		else
			gameinfo[order][5] = strtof(global[order],NULL); /*Global sale datas saves as a float in a special array*/

		counter = 0;
		letter++;
		
		if(order == 2000)
		{
			while(all[order][letter]!='\0' ) /*Takes only scores on last string and keeps in the its array*/
			{	
				score[order][counter] = all[order][letter];
				letter++;
				counter++;										
			}
			gameinfo[order][6] = strtof(score[order],NULL); /*Score data saves as a float in a special array*/
		}
		else
		{
			while(all[order][letter]!='\n') /*Takes only scores except last string and keeps in the its array*/
			{	
				score[order][counter] = all[order][letter];
				letter++;
				counter++;
			}
			gameinfo[order][6] = strtof(score[order],NULL);	 /*Score datas saves as a float in a special array*/
		}
	}
	genres_and_pform(genres,pform,t_genres,t_pform,cg,cp,gameinfo); 
}

void genres_and_pform (char genres[12][21], char pform[10][21],char t_genres[2001][21],char t_pform[2001][21],int cg[12],int cp[10], float gameinfo[2001][7])
{
	int norder,sorder,flag,i,saver;

	for(sorder=0; sorder<=11; sorder++) /*Array cleaning*/
	{
		for (i = 0; i <= 20; i++)
			genres[sorder][i]='\0';
		cg[sorder] = 1;
	}
	
	saver = 0;

	for(i=0;i<=20;i++) /*Saves first genre. First are special*/
		genres[saver][i]=t_genres[1][i];
	
	saver++;

	for(norder=2;norder<=2000;norder++) /*Saves other genres*/
	{
		flag = 0;
		
		for(sorder=0; sorder<=saver; sorder++)
		{
			if(strcmp(genres[sorder],t_genres[norder])==0) /*Controls similarity*/
			{
				cg[sorder]++; /*One more same genre detected*/
				flag = 1;
				break;
			}
		}
		if(flag==0) /*New genre*/
		{
			for(i=0;i<=20;i++)
				genres[saver][i]=t_genres[norder][i];

			saver++;
		}
	}

	for(sorder=0; sorder<=9; sorder++) /*Array cleaning*/
	{
		for (i = 0; i <= 20; i++)
			pform[sorder][i]='\0';
		cp[sorder] = 1;
	}
	
	saver = 0;
	for(i=0;i<=20;i++) /*Saves first platform. First are special*/
		pform[saver][i]=t_pform[1][i];

	saver++;																			
	for(norder=2;norder<=2000;norder++) /*Saves other platforms*/
	{
		flag = 0;
		
		for(sorder=0; sorder<=saver; sorder++)
		{
			if(strcmp(pform[sorder],t_pform[norder])==0) /*Controls similarity*/
			{
				cp[sorder]++; /*One more same platform detected*/
				flag = 1;
				break;
			}
		}
		if(flag==0) /*New genre*/
		{
			for(i=0;i<=20;i++)
				pform[saver][i]=t_pform[norder][i];

			gameinfo[norder][1]=saver;
			saver++;
		}
	}
	for (norder=0; norder<=2000; norder++)
	{
		for(sorder=0;sorder<=11;sorder++) /*Indexes of genres are saves in special array*/
		{
			if(strcmp(genres[sorder],t_genres[norder])==0)
			{
				gameinfo[norder-1][0] = sorder;
				break;
			}
		}
		for(sorder=0;sorder<=9;sorder++) /*Indexes of platforms are saves in special array*/
		{
			if(strcmp(pform[sorder],t_pform[norder])==0)
			{
				gameinfo[norder-1][1] = sorder;
				break;
			}
		}
	}
}

int control_years(char user_entry[110],int selection)
{
	int flag = 0,entry;
	entry = strtof(user_entry,NULL);


	if (1985>=entry) /*Older from oldest game in the list*/
	{
		if (selection == 1)
			flag = 1;
		else 
			flag = 0;
	}

	else if (2005<=entry) /*Newe from newest game in the list*/
	{
		if (selection == 0)
			flag = 1;
		else 
			flag = 0;
	}
	else /*Same with the games in the list*/
	{	
		if(selection == 1 || selection == 0)
			flag = 1;
		else
			flag = 0;
	}

	return flag;
}

void print_years(char user_entry[110], int selection, char names[2001][110], float gameinfo[2001][7])
{
	printf("\n\n");
	int order, entry;
	entry = strtof(user_entry,NULL);
	if (selection==0) /*Until*/
	{	
		order=1;
		while(entry > gameinfo[order][2])
		{
			printf("%s\n",names[order]);
			order++;
		}
	}
	else if (selection == 1) /*Since (I dont add '=' because I dont sure about that.)*/
	{
		printf("\n\n");
		order=2000;
		while(gameinfo[order][2] > entry)
		{
			if(order==0)
				break;
			printf("%s\n",names[order]);
			order--;
		}
	}
}

float average(float gameinfo[2001][7])
{
	float sum=0.0, average=0.0;
	int order;		

	for (order=1; order<=2000; order++)
		sum = sum + gameinfo[order][6]; /*Adding*/
	
	average = sum / 2000.0; /*Dividing*/

	return average;
}

int compare(char user_entry[110],char names[2001][110],float gameinfo[2001][7])
{
	int order,flag=0;

	for (order=1; order<=2000; order++)
	{
		if(strcmp(user_entry,names[order])==0)
		{	
			flag = 1;
			if(gameinfo[order][3] > gameinfo[order][4])
				printf("This game was more popular in North America.\n");

			else if (gameinfo[order][3] < gameinfo[order][4])
				printf("This game was more popular in Europe.\n");

			else 
				printf("This game was equal popular in Europe and North America.\n");

			break;
		}
		else
			flag = 0;
	}
	if (flag == 0)
		printf("Game not found. TRY AGAIN\n");

	return flag;
}

int info(char user_entry[110],char names[2001][110],float gameinfo[2001][7],char genres[12][21],char pform[10][21])
{
	int order, flag=0;

	for(order=1;order<=2000;order++)
	{
		if(strcmp(user_entry,names[order])==0)
		{	
			flag = 1;
			printf("Name:         %s\n",names[order]);
			printf("Genre:        %s\n",genres[(int)gameinfo[order-1][0]]);
			printf("Platform:     %s\n",pform[(int)gameinfo[order-1][1]]);
			printf("Year:         %d\n",(int)gameinfo[order][2]);
			printf("Sales In NA:  %f\n",gameinfo[order][3]);
			printf("Sales In EU   %f\n",gameinfo[order][4]);
			if (gameinfo[order][5]!=100)
				printf("Total Sales   %f\n",gameinfo[order][5]);
			else
				printf("Total Sales:  Not Available\n");
			printf("User Score:   %f\n",gameinfo[order][6]);

			break;
		}
		else
			flag = 0;
	}
	if (flag == 0)
		printf("Game not found. TRY AGAIN\n");


	return flag;
}















