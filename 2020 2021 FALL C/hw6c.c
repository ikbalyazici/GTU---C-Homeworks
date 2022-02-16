#include <stdio.h>
#include <string.h>

/*Unfortunately it runs only if every parent object has only 1 child object*/

typedef struct 
{
	double val; //price of object
	char name[50]; //name of object
} object ;

int func(object obj , object parent_obj); //The recursive function calculates prize of main object

int main()
{
	object obj,parent_obj; //Variables in object type

	printf("Name the object:\n");
	scanf("%s",parent_obj.name); //Taking name of the object
	parent_obj.val = 1.0; //Initial value of main object is 1. Because we need prize of only one object
	obj.val = 1.0; //Initial value of child object. 
	strcpy(obj.name," "); //At the beginning there is no child object
	
	parent_obj.val = func(obj,parent_obj); //Function call for determining the prize of main object
	printf("Total cost of %s is %lf\n",parent_obj.name,parent_obj.val);

	return 0;
}

int func(object obj , object parent_obj)
{
	char c; //Its for a control mechanism 
	
	if(strcmp(obj.name," ")==0 && obj.val==1.0) //At first it have only one object. Anything is not in anything.
	{
		printf("Define %s?\n",parent_obj.name);
		scanf("%lf %s",&obj.val,obj.name);	//Taking child objects name and value (how many same object in parent object)
	}

	printf("Define %s in %s?\n",obj.name,parent_obj.name);
	
	strcpy(parent_obj.name,obj.name); //Child object will be parent object 
	parent_obj.val = parent_obj.val * obj.val;
	
	while(c!='\n') //Its for checking is user clicks enter 
	{
		fscanf(stdin,"%lf",&obj.val); //takes value of child object
		c = getc(stdin); //control character takes one next character
		if(c=='\n') //Child object may be final object so it may have not no child name 
			strcpy(obj.name," "); //No name string for checking later
		else //This is not final object
		{
			fscanf(stdin,"%s",obj.name); //takes name of the child object
			c = getc(stdin); //controls new line
		}
	}
	if(strcmp(obj.name," ")==0) //It is final object
		return parent_obj.val*obj.val; //Returns total prize of all childs

	func(obj,parent_obj);	//Its is not final. Function recall for next parent child pair
}