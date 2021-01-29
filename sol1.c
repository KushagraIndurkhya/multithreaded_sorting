#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


typedef struct data{
	int* arr;
	int start;
	int seg;
	int len;
}share;

int expo(int pow)
{
	int res=1;
	for(int i=0;i<pow;i++)
		res=res*2;
	return res;
	
}
void print_arr(int*arr,int n)
{
	for(int i=0;i<n;i++)
		printf("%d ",arr[i]);
	printf("\n");
}
void fill_arr(int*arr,int n)
{
	for(int i=0;i<n;i++)
		arr[i]=rand()%100;
}

void merge(int a,int b,int c,int d,int* arr,int len)
{
	int temp[len];
	int i=a,j=c,k=a;
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
	
	for (int i = a; i <=d; i++)
		arr[i]=temp[i];
}
void sort(int*arr,int l,int r,int len)
{
	if(l>=r)
		return;
	int m = (l+r-1)/2;
	sort(arr,l,m,len);
    sort(arr,m+1,r,len);
    merge(l,m,m+1,r,arr,len);

}


void* sort_seg(void* seg_start)
{
	share* data=(share*)seg_start;
	int start=data->start;
	int* arr=data->arr;
	int seg_size=data->seg;
	int len=data->len;

	sort(arr,start,start+seg_size-1,len);
	pthread_exit(NULL);	

}

int main()
{
	int n,p;
	scanf("%d %d",&n,&p);
	int len=expo(n);
	int arr[len];

	fill_arr(&arr[0],len);
	// print_arr(&arr[0],len);

	clock_t start_time=clock();
	int no_of_threads=expo(p);
	int seg_size=expo(n-p);
	pthread_t thread_ids[no_of_threads];


	share shared_data[no_of_threads];
	for (int i = 0; i < no_of_threads; i++)
	{
		shared_data[i].arr=&arr[0];
		shared_data[i].start=i*seg_size;
		shared_data[i].seg=seg_size;
		shared_data[i].len=len;

	}
	
	for (int i = 0; i < no_of_threads; ++i)
		pthread_create(&thread_ids[i],NULL,sort_seg,(void*)&shared_data[i]);	

	for (int i = 0; i < no_of_threads; i++)
		pthread_join(thread_ids[i], NULL);

	for (int i = 1; i < no_of_threads; i++)
		merge(0,(i*seg_size)-1,i*seg_size,(i*seg_size)-1+seg_size,&arr[0],len);
	clock_t end_time=clock();
	// print_arr(&arr[0],len);
	printf("Time taken:%f Microseconds\n",((((double)end_time-start_time)/CLOCKS_PER_SEC)*1000000));
		int flag=1;
	for (int i = 0; i < len-1; i++)
		if(arr[i]>arr[i+1])
		flag=0;
	if(flag==0)
		printf("NOT SORTED\n");
	else
		printf("SORTED\n");
	return 0;
}

