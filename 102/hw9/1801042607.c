#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//Prototypes of Functions are used in program.
void part1();
int numPathsHome(int street, int avenue); //PART 1 
void part2();
struct Hospital //PART 2
	{
		char* name;
		char citiesServed[4];
	};
int canOfferCovidCoverage(char _cities[6], char _locations[4][4], int _numHospitals, struct Hospital results[4]); //PART2
void fillControlArray(int _numHospitals, struct Hospital results[4],char citiesResults[7],int trycounter);//PART2 
void part3();
void random_numbers(int ord[52]); //PART3

int main()
{
	int selection=0;

	printf("***************WELCOME!!***************\n");
	
	while(selection!=4)
	{
		printf("\nPlease Select:\n(1) for PART 1\n(2) for PART 2 (SEG!)\n(3) for PART 3\n(4) for EXIT\n");
		scanf("%d",&selection);

		switch(selection)
		{
			case 1: part1();
				break;
			case 2: part2(); //SEG FAULT! But I believe my algorithm. It needs 1 or 2 small touches but I couldn't make it until deadline
				break;
			case 3: part3();
				break;
			case 4: 
				break;
			default: printf("INVALID SELECTION!\n");
				break;
		}
	}
	printf("GOOD BYE!\n");

	return 0;
}

void part1()
{
	int street,avenue,t_av,a,b,together;
  
  printf("Enter the street number:");
  scanf("%d",&street); /*Where is Cin Ali (street)*/
  printf("street:%d \n",street);
  printf("Enter the avenue: ");
  scanf("%d",&avenue); /*Where is Cin Ali (avenue)*/
  printf("avenue:%d \n",avenue);
  
  t_av = avenue -1; /*Home is at (1,1) so distance between avenue and home is avenue minus one*/
  together = street + avenue - 2; /*Distance between avenues (avenue -1) + distance between streets (street -1)*/
  street --; /*Home is at (1,1) so distance between street and home is street minus one*/
  avenue = 1;
  
  a = numPathsHome(street,avenue); /*All lefts are same. Part of combination process*/

  street = t_av;
  b = numPathsHome(street,avenue); /*All downs are same. Part of combination process*/

  street = together;               /*For calculating upper part of combination*/
  together = numPathsHome(street,avenue);
  printf("Number of optimal paths to take back home: %d\n",together/(a*b)); /*Answer*/
}

int numPathsHome(int street, int avenue)
{
	if(street>1)
  {
    avenue = avenue * street;
    numPathsHome(street-1,avenue); /*Calculating factorial recursively*/
  }
  
  else
  {
    return avenue; //Factorial result
  }
}

void part2()
{
	char _locations[4][4] = {{'A','B','C'},{'A','C','D'},{'B','F'},{'C','E','F'}}; 
	char _cities[7] = {'A','B','C','D','E','F','\0'};
	struct Hospital results[4];
	int _numHospitals, resultnum;

	results[0].name = "Hospital_1";
	results[1].name = "Hospital_2";
	results[2].name = "Hospital_3";
	results[3].name = "Hospital_4";

	printf("Enter the maximum number of hospitals that can be constructed: ");
	scanf("%d",&_numHospitals); //It is not sended to function. It is only for comparison.

	resultnum = canOfferCovidCoverage(_cities,_locations,0,results); //I planned it as a optimum number finder. But there is some mistake.

	if(_numHospitals < resultnum)
		printf("No, some cities are not covered.\n");

	else if(_numHospitals == resultnum)
	{
		printf("YESS\n"); //If I could solve my little problem I would change it to output example.
	}

	else
		printf("https://www.youtube.com/watch?v=4bETxR6sRLE\n"); //Small joke not a bad thing. It is about money.
}

int canOfferCovidCoverage(char _cities[6], char _locations[4][4], int _numHospitals, struct Hospital results[4])
{
	char citiesResults[6];//I planned to use it by compare with original cities array after filling it at line 125...->

	strcpy(results[_numHospitals].citiesServed , _locations[_numHospitals]); //Filling structure array

	fillControlArray(_numHospitals,results,citiesResults,0); // Error included part (I think). 

	if(strcmp(_cities,citiesResults)!=0) //...->Recursion would continue until they become equal.
		canOfferCovidCoverage(_cities,_locations,_numHospitals+1,results);
	
	else
		return _numHospitals;
}

void fillControlArray(int _numHospitals, struct Hospital results[4],char citiesResults[7],int trycounter)
{
	int i=0,j,flag=0;
	char temp;

	while(citiesResults[i]!='\0')
	{
		if(citiesResults[i] == results[_numHospitals].citiesServed[trycounter]) //It controls is new one same with inside the array
		{
			flag = 1; // Yes, the same. I don't need it.
			break;
		}
		else
			flag = 0;// Different.

		i++;		
	}
	if(flag == 0) //New one is different so I save this new one 
		citiesResults[i+1] = results[_numHospitals].citiesServed[trycounter];

	if(trycounter<2) //All location arrays includes 3 elements, so loop continues until 3rd element.
		fillControlArray(_numHospitals,results,citiesResults,trycounter+1);

	else //Its for making items order alphabetic. 
	{
		for (i=0; i<5;i++)
		{
			for (j=i; j<6; j++)
			{
				if(citiesResults[i]-citiesResults[j]==1)
				{
					temp = citiesResults[i];
					citiesResults[i]=citiesResults[j];
					citiesResults[j] = temp;
				}
			}
		}
	}
}

void part3()
{
	char faces[13][6] = {"Ace","Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
	char suits[4][9] = {"Hearts", "Diamonds", "Clubs", "Spades"};
	int i,j=0,k=0,ord[52];
	
	struct card /*Card informations struct*/
	{
		const char *face;
		const char *suit;
	};
	
	struct card gamecards[52]; /*Array for saving 52 different cards*/

	for(i=0; i<52; i++) /*Storing its suit and face for each card*/
	{
		if(j==4)
			j=0;
		if(k==13)
			k=0;

		gamecards[i].suit = suits[j];
		gamecards[i].face = faces[k];

		j++;
		k++;
	}

	random_numbers(ord);

	j=0;
	for(i=0; i<52; i++) //Printing card as two column list
	{
		printf("  %5s of %s",gamecards[ord[i]].face, gamecards[ord[i]].suit);
		j++;

		if(j%2==0)
			printf("\n");
		else
		{
			for(k=0; k+strlen(gamecards[ord[i]].suit)<15;k++)
			printf(" ");
		}

	}
}

void random_numbers(int ord[52])
{
	int temp, i, a; /*i and a are loop counters, temp is carrier*/

	srand(time(NULL));
	temp = rand()%52;
	ord[0] = temp; /*Determination of first rotation number. (Naturally first ball is free :D)*/

	for (a = 1; a <= 51 ; a++) /*First member of array is given, so loop starts from 1*/
	{
		temp = rand()%52; /*Creating candidates for rotation numbers.*/
		for (i=0; i<a; i++) /*Equality control loop. Controlling only certain numbers are enough, so loop is bounded above by 'a'*/
		{
			if (temp == ord[i]) /*Candidate equals one of certain members*/
			{
				a--;   /*Loop counter decrease for retry uncertain order*/
				break; /*To retry determination need to go back older loop, so exits from this loop*/
			}
			else
				ord[a]=temp; /*Candidate is fit, we can keep it*/
		}				
	}
}