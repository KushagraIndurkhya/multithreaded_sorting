#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include <time.h>

typedef struct data{
	long int* arr;
	int start;
	int seg;
	int len;
}share;

typedef struct merge_data
{
	long int* arr;
	int arr_len;
	
	int seg_size;
	int seg_idx;
	int phase;	
}
merge_thread_data;

int expo(int pow)
{
	int res=1;
	for(int i=0;i<pow;i++)
		res=res*2;
	return res;	
}

void print_arr(long int*arr,int n)
{
	for(int i=0;i<n;i++)
		printf("%ld ",arr[i]);
	printf("\n");
}

void fill_arr(long int*arr,int n)
{
	for(int i=0;i<n;i++)
		arr[i]=random();
}
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

void merge(int a,int b,int c,int d,long int* arr,int len)
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

void sort(long int*arr,int l,int r,int len)
{
	if(l>=r)
		return;
	int m = (l+r-1)/2;
	sort(arr,l,m,len);
    sort(arr,m+1,r,len);
    merge(l,m,m+1,r,arr,len);

}


void* sort_thread(void* seg_start)
{
	share* data=(share*)seg_start;
	long int* arr=data->arr;
	int start=data->start;
	int seg_size=data->seg;
	int len=data->len;
	// Sorting the segment
	sort(arr,start,start+seg_size-1,len);
}
void* merge_thread(void* shared_data)
{
	merge_thread_data* data=(merge_thread_data*) shared_data;
	long int* arr=data->arr;
	int len=data->arr_len;
	int phase=data->phase;
	int seg_size=data->seg_size;
	int seg_idx=data->seg_idx;

	int a=seg_idx*seg_size;
	int b=a+(phase*seg_size)-1;
	int c=b+1;
	int d=c+(phase*seg_size)-1;

	merge(a,b,c,d,arr,len);

	pthread_exit(NULL);
}

int main()
{
	int n,p;
	scanf("%d %d",&n,&p);

	int len=expo(n);
	int no_of_threads=expo(p);
	int seg_size=expo(n-p);
	
	long int arr[len];
	fill_arr(&arr[0],len);
	// print_arr(&arr[0],len);
	

	clock_t start_time=clock();
	pthread_t thread_ids[no_of_threads];

	int thread_dead[no_of_threads];
	for (int i = 0; i < no_of_threads; i++)
		thread_dead[i]=0;
	
	share shared_data[no_of_threads];
	for (int i = 0; i < no_of_threads; i++)
	{
		shared_data[i].arr=&arr[0];
		shared_data[i].start=i*seg_size;
		shared_data[i].seg=seg_size;
		shared_data[i].len=len;

	}

	
	for (int i = 0; i < no_of_threads; ++i)
		pthread_create(&thread_ids[i],NULL,sort_thread,(void*)&shared_data[i]);
	for (int i = 0; i < no_of_threads; i++)
		pthread_join(thread_ids[i], NULL);


	merge_thread_data data[no_of_threads];
	for (int i = 1; 2*i<=no_of_threads; i*=2)
	{
		int j=0;
		for (int thread_idx = 0; thread_idx < no_of_threads ; thread_idx++)
		{
			if (thread_idx%(2*i)==0)
			{
				data[thread_idx].arr=&arr[0];
				data[thread_idx].arr_len=len;
				data[thread_idx].phase=i;
				data[thread_idx].seg_size=seg_size;
				data[thread_idx].seg_idx=thread_idx;
				pthread_create(&thread_ids[j],NULL,merge_thread,(void*)&data[thread_idx]);
				j++;
			}	
		}
		for (int k = 0; k <j; k++)
			pthread_join(thread_ids[k], NULL);	
	}
	clock_t end_time=clock();
	// print_arr(&arr[0],len);
	printf("Time taken:%f Microseconds\n",((((double)end_time-start_time)/CLOCKS_PER_SEC)*1000000));
	check_sorted(arr,len);
	
	return 0;
}

