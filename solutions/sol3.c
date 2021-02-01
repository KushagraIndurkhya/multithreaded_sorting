#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Function:  expo
 * --------------------
 * 	n: power
 *  returns: 2^n
 *                     
 */
int expo(int pow)
{
	int res=1;
	for(int i=0;i<pow;i++)
		res=res*2;
	return res;	
}
/*
 * Function:  print_arr
 * --------------------
 * 	Prints the given array of long integers
 * 
 * 	*arr:pointer to array
 * 	n: length of array
 *  returns: Void
 *                     
 */
void print_arr(long int*arr,int n)
{
	for(int i=0;i<n;i++)
		printf("%ld ",arr[i]);
	printf("\n");
}

/*
 * Function: Fill_arr
 * ----------------------------
 *   fills array with random long ints
 *
 *   *arr:pointer of array to be filled 
 *   n2: length of the array
 *
 *   returns:Void
 */

void fill_arr(long int*arr,int n)
{
	for(int i=0;i<n;i++)
		arr[i]=random();
}
/*
 * Function: check_sorted
 * ----------------------------
 *   checks if the array is sorted
 *
 *   *arr:pointer of array to be filled 
 *   n2: length of the array
 *
 *   returns:Void
 */
void check_sorted(long int*arr,int len)
{
	int flag=1;
	for (int i = 0; i < len-1; i++)
		if(arr[i]>arr[i+1])
		flag=0;
	if(flag==0)
		printf("NOT SORTED\n");
	else
		printf("SORTED\n");
}
/*
 * Function: merge
 * ----------------------------
 *   merges two sorted subarrays of an array 
 *
 *   *arr: pointer to the array
 * 	 len: length
 *   a: start index of subarray-1
 *   b: end index of subarray-1
 * 	 c:	start index of subarray-2
 *   d:	start index of subarray-2 

 *  
 *
 *   returns: Void
 */

void merge(int a,int b,int c,int d,long int* arr)
{
	int temp[d-a+1];
	int i=a,j=c,k=0;
	while(i<=b && j<=d)
	{
		if (arr[i]<arr[j])
			temp[k++]=arr[i++];
		else
			temp[k++]=arr[j++];
	}
	while (i<=b)
		temp[k++]=arr[i++];
	while (j<=d)
		temp[k++]=arr[j++];
	
	for (int i = a,j=0; i <=d; i++,j++)
		arr[i]=temp[j];
}
/*
 * Function: sort
 * ----------------------------
 *   sorts a subarray of the provided array
 *
 *   *arr: pointer to the array
 *   l:start index of subarray
 * 	 r:end index of subarray 
 *
 *   returns: void
 */
void sort(long int*arr,int l,int r)
{
	if(l>=r)
		return;
	int m = (l+r-1)/2;
	sort(arr,l,m);
    sort(arr,m+1,r);
    merge(l,m,m+1,r,arr);

}
/*
 * Function: sort_thread
 * ----------------------------
 *   function defining the behaviour of Slave thread to sort a segment
 *
 *   shared_data:Struct containing the shared data
 *
 *   returns: void*
 */


int main()
{
	int n,p;
	scanf("%d %d",&n,&p);
	int len=expo(n);
	long int arr[len];
	fill_arr(&arr[0],len);
	// print_arr(&arr[0],len);
	clock_t start_time=clock();
	sort(arr,0,len-1);
	clock_t end_time=clock();
	// print_arr(&arr[0],len);
	printf("Time taken:%f Microseconds\n",((((double)end_time-start_time)/CLOCKS_PER_SEC)*1000000));
	check_sorted(arr,len);
	return 0;
}

