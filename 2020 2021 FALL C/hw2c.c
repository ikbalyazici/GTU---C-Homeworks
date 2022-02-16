#include <stdio.h>

#define p1 (double)0.5
#define p2 (double)20

int main()
{
	double a,b, /*n is new number - a is average before n added - b is average after n added*/
		   sum=0, /*to calculating average of chunks*/
		   n, n_plus; /* current number and next number*/
	int ave_c=0; /*For counting number of program calculate their average */

	FILE *fp;
	fp = fopen("input.txt","r"); /*Program reads all numbers in the input.txt*/

	FILE *fp2;
	fp2 = fopen("output.txt","w"); /*output.txt opens for saving chunks in it*/

	fscanf(fp,"%lf",&n); /*Current number reading from the input file*/

	while(!feof(fp))
	{
		fscanf(fp,"%lf",&n_plus); /*Next number reading from the input file*/

		fprintf(fp2, "%lf ",n); /*Writes next member of the chunk to output.txt*/
		sum = sum + n; /*Calculates sum of chunk */
		a = sum / (ave_c+1);  /*Calculates average of chunk*/
		ave_c++;	  /*Counters get ready for next number*/
		b = (sum + n_plus) / (ave_c+1); /*Calculates average of chunk when next number added to chunk*/

		if((b > a*(1+p1) || b < a*(1-p1) || a > n_plus*p2 || a < n_plus/p2)) 
		/*Controls is number will add to chunk. If tried number satisfies this condition this number not adding the chunk
		/* and new chunk starts with this tried number.*/
		{
			fprintf(fp2, "average: %.4lf\n",a); /*it writes previous chunks average end of previous chunk so next chunk will start*/
			sum=0; ave_c=0; /*Reseting sum and average calculation counter for new chunk*/
		}
		n = n_plus;
	}
	fprintf(fp2, "average: %.4lf\n",a); /*it writes previous chunks average end of previous chunk so this is the last element*/

	fclose (fp); /*Closing input.txt*/
	fclose(fp2); /*Closing output.txt*/

	return 0;
}
