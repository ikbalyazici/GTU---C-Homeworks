#include <stdio.h>

#define GRIDSIZE 512

typedef struct grid 	//Group of values for each point on map (each integer except first one)
{
	int length;			//Each integer except first one represents length of its point
	int island_name;	//Its for count islands. Names are numeric 	
	int coordinate[2];	//Coordianates of island starting points
}grid;

int makemap (struct grid map[GRIDSIZE][GRIDSIZE]); //Takes values from input.txt to map array
int island_counter (struct grid map[GRIDSIZE][GRIDSIZE], struct grid islands [100]); //Counts how many island in map
int define_island(struct grid map[GRIDSIZE][GRIDSIZE] , int x , int y , int counter); //Determines all points of each island

int main()
{
	int i,n; //i is loop counter , n is number of islands
	grid map[GRIDSIZE][GRIDSIZE]; //an array for storing input.txt
	grid islands[100];			  //an array for storing island starting points as island representer	

	makemap(map);				  
	n = island_counter(map,islands);

	FILE *outp;
	outp = fopen("output.txt","w"); //creation of output.txt
	
	fprintf(outp,"%d\n",n); //printing output in output.txt
	for(i=0;i<n;i++)
		fprintf(outp,"%d %d\n",islands[i].coordinate[0],islands[i].coordinate[1]);
}

int makemap (struct grid map[GRIDSIZE][GRIDSIZE])
{
	FILE *inp;
	inp = fopen("input.txt","r"); //opening input.txt for reading 

	int sealvl,x,y;	//sealvl is first integer of input.txt it represents zero point of map

	fscanf(inp,"%d ",&sealvl); //taking sealvl value

	for(y=0 ; y<GRIDSIZE ;y++) //ordinate axis
	{
		for(x=0 ; x<GRIDSIZE; x++) //apsis axis
		{
			fscanf(inp,"%d ",&map[y][x].length); //points in input.txt stores in array
			if(map[y][x].length > sealvl)
				map[y][x].island_name = 0;	//this points are upper from sea as parts of islands
		
			else 
				map[y][x].island_name = 999; //this points are under the sea not part of islands. 999 is random number
		}
	}
}

int island_counter (struct grid map[GRIDSIZE][GRIDSIZE] , struct grid islands[100])
{
	int x=0, y=0, counter=0;
	for(y=0 ; y<GRIDSIZE; y++) //ordinate
	{
		for(x=0 ; x<GRIDSIZE; x++) //apsis
		{	
			if(map[y][x].island_name==0) //a point on islands
			{
				counter++; //its a new island
				map[y][x].island_name = counter; //island named with counter
				define_island(map , x , y ,counter); //all parts of this island will find
				islands[counter-1].coordinate[0]=x; //starting apsis coordiante of this island is stored
				islands[counter-1].coordinate[1]=y; //starting ordinate of this island is stored
			}
		}
	}
	return counter; //number of all islands returns to main function
}

int define_island(struct grid map[GRIDSIZE][GRIDSIZE] , int x , int y , int counter)
{
	if(y+1<GRIDSIZE && map[y+1][x].island_name==0) //looking ordiante axis positive way
	{
		map[y+1][x].island_name = counter;
		if((y+2)<GRIDSIZE)
			define_island(map , x , (y+1) , counter); //looking next step in this direction
	}
	if(y-1>0 && map[y-1][x].island_name==0)			//looking ordinate axis negative way
	{
		map[y-1][x].island_name = counter;
		if((y-2)>=0)
			define_island(map , x , (y-1) , counter); //looking next step in this direction
	}
	if(x+1<GRIDSIZE && map[y][x+1].island_name==0)	//looking apsis axis positive way
	{
		map[y][x+1].island_name = counter;
		if((x+2)<GRIDSIZE)
			define_island(map , (x+1) , y , counter); //looking next step in this direction
	}
	if(x-1>0 && map[y][x-1].island_name==0)			//looking apsis axis negative way
	{
		map[y][x-1].island_name = counter;
		if((x-2)>=0)
			define_island(map , (x-1) , y , counter); //looking next step in this direction
	}
}