#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#define N 300
#define M 300

int max_subarray( int *array )
{
    int max_ending_here=0,  max_so_far=0;
	int i, num;

    for(i=0; i<num; i++ )
    {
        if ( max_ending_here + array[i] > 0 )
            max_ending_here += array[i];
        else
            max_ending_here = 0;

        if ( max_so_far < max_ending_here )
            max_so_far = max_ending_here;
    }
    return max_so_far;
}

// Implementation of Kadane's algorithm for 1D array.
// The function returns the maximum sum and stores starting and ending indexes of the maximum sum subarray
// at addresses pointed by start and finish pointers respectively.
int kadane(int* arr, int* start, int* finish, int n)
{
    // initialize sum, maxSum and
    int sum = 0, maxSum = INT_MIN, i;
    // Just some initial value to check for all negative values case
    *finish = -1;
    // local variable
    int local_start = 0;
 
    for (i = 0; i < n; ++i)
    {
        sum += arr[i];
        if (sum < 0)
        {
            sum = 0;
            local_start = i+1;
        }
        else if (sum > maxSum)
        {
            maxSum = sum;
            *start = local_start;
            *finish = i;
        }
    }
 
     // There is at-least one non-negative number
    if (*finish != -1)
        return maxSum;
 
    // Special Case: When all numbers in arr[] are negative
    maxSum = arr[0];
    *start = *finish = 0;
 
    // Find the maximum element in array
    for (i = 1; i < n; i++)
    {
        if (arr[i] > maxSum)
        {
            maxSum = arr[i];
            *start = *finish = i;
        }
    }
    return maxSum;
}

void findMaxSum(int Matrix[][N])
{
	//Variables to store the final output
	int maxSum = INT_MIN, finalLeft, finalRight, finalTop, finalBottom; 
	int left, right, i;
	int temp[M], sum, start, finish;               
	// Set the left column
	 for (left = 0; left < N; ++left)
	 {
		 memset(temp, 0, sizeof(temp));
		 //Set the right column for the left column set by outer loop
		 for (right = left; right < N; ++right)
		 {
			 // Calculate sum between current left and right for every row 'i'
			 for (i = 0; i < M; ++i)
				 temp[i] += Matrix[i][right];
			 // Find the maximum sum subarray in temp[]. The kadane() function
			 // also sets values of start and finish.  So 'sum' is sum of
			 // rectangle between (start, left) and (finish, right) which is the
			 // maximum sum with boundary columns strictly as left and right.
			   sum = kadane(temp, &start, &finish, M);
			   // Compare sum with maximum sum so far. If sum is more, then update
			   // // maxSum and other output values
			   if(sum > maxSum)
			   {
					maxSum = sum;
					finalLeft = left;
					finalRight = right;
					finalTop = start;
					finalBottom = finish;
			   }
		 }
	 }
	// Print final values
    printf("(Top, Left) (%d, %d)\n", finalTop, finalLeft);
    printf("(Bottom, Right) (%d, %d)\n", finalBottom, finalRight);
    printf("Max sum is: %d\n", maxSum);
}
int main(void)
{
	int m,n;
	scanf("%d", &n);
	scanf("%d", &m);
	int array[m][n];
	printf("Row = m : %d and Column = n : %d \n", m,n);

	int i,j;
	for(i=0; i<m;i++)
		for(j=0;j<n;j++)
			scanf("%d", array[i]+j);

	int (*row)[n]=array;
//	for(i=0;i<1;i++)
//		for(j=0;j<n;j++)	
//			printf("%d ",row[i][j]);

	int sumarray[m][n];
	for(i=0;i<m;i++)
	{
		int (*rw)[n] = malloc(sizeof(int)*n);		
	}

	findMaxSum(array);
}
