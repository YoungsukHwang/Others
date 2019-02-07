#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* Function to swap values at two pointers */
void swap(char *x, char *y)
{
	    char temp;
		temp = *x;
		*x = *y;
		*y = temp;
}

/* Function to print permutations of string
 *    This function takes three parameters:
 *       1. String
 *       2. Starting index of the string
 *       3. Ending index of the string. */
void permute(char *a, int l, int r)
{
	   int i;
	   if (l == r)
	   printf("%s\n", a);
	   else
	   {
		   for (i = l; i <= r; i++)
		   {      
			   swap((a+l), (a+i));
		       permute(a, l+1, r);											  
			   swap((a+l), (a+i)); //backtrack
	       }
	   }
}

int main(void){
	char p[20];	
	printf("Input your string :");
	scanf("%s",p);
	printf("Input accepted : %s\n", p);
	int n = strlen(p);
	permute(p,0,n-1);
	return 0;
}
