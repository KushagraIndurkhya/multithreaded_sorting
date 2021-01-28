#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>
#include <time.h>

typedef struct data
{
	pthread_t * thread_arr;
	int* arr;
	int* thread_dead;

	int arr_len;
	int no_of_threads;
	
	int start;
	int seg;
	
}
share;

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

void merge_segments(int a,int b,int c,int d,int* arr,int len)
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
	while(i<=b)
		temp[k++]=arr[i++];
	while(j<=d)
		temp[k++]=arr[j++];
	for (int i = a,j = 0; i <=d; i++)
		arr[i]=temp[j++];
}

void sort(int*arr,int start,int seg_size)
{
	int min,temp;
	for(int i=start;i<start+seg_size;i++)
	{
		min=i;
		for (int j = i; j<start+seg_size;j++)
			if (arr[j]<=arr[min])
				min=j;
		if (min!=i)
		{
			temp=arr[i];
			arr[i]=arr[min];
			arr[min]=temp;
		}
	}

}


void* sort_and_merge_seg(void* seg_start)
{
	// Retrieving shared data from seq_struct
	share* data=(share*)seg_start;

	int* arr=data->arr;
	pthread_t * thread_arr=data->thread_arr;
	int* thread_alive=data->thread_dead;

	int start=data->start;
	int seg_size=data->seg;

	int len=data->arr_len;
	int no_of_threads=data->no_of_threads;
	
	// getting index of current thread in the array of thread indexes
	int thread_idx;
	for (int i = 0; i < no_of_threads; i++)
		if((int)thread_arr[i] == (int)pthread_self())
			thread_idx=i;
	// Sorting the segment
	sort(arr,start,seg_size);
	thread_alive[thread_idx]=1;
	int phase=1,a,b,c,d;
	while (thread_idx%(2*phase)==0 && start+(2*phase*seg_size)-1<len && thread_idx+phase<no_of_threads )
	{
		a=start;
		b=a+(phase*seg_size)-1;
		c=b+1;
		d=c+(phase*seg_size)-1;
		while (!thread_alive[thread_idx+phase])	
			sleep(0);
		pthread_join(thread_arr[thread_idx+phase],NULL);
		// printf("Thread(%d)....Merging...%d...%d...%d...%d\n",thread_idx,a,b,c,d);
		merge_segments(a,b,c,d,arr,len);
		phase*=2;
	}
	// printf("Thread(%d) EXITING \n",thread_idx);
	pthread_exit(NULL);	

}

int main()
{
	int n,p;
	scanf("%d %d",&n,&p);

	int len=expo(n);
	int no_of_threads=expo(p);
	int seg_size=expo(n-p);
	
	int arr[len];
	fill_arr(&arr[0],len);
	// print_arr(&arr[0],len);
	

	pthread_t thread_ids[no_of_threads];

	int thread_dead[no_of_threads];
	for (int i = 0; i < no_of_threads; i++)
		thread_dead[i]=0;
	
	share shared_data[no_of_threads];
	for (int i = 0; i < no_of_threads; i++)
	{
		shared_data[i].arr=&arr[0];
		shared_data[i].thread_arr=&thread_ids[0];
		shared_data[i].thread_dead=&thread_dead[0];

		shared_data[i].start=i*seg_size;
		shared_data[i].seg=seg_size;

		shared_data[i].arr_len=len;
		shared_data[i].no_of_threads=no_of_threads;
	}

	clock_t start_time=clock();
	for (int i = 0; i < no_of_threads; ++i)
		pthread_create(&thread_ids[i],NULL,sort_and_merge_seg,(void*)&shared_data[i]);
	pthread_join(thread_ids[0], NULL);
	clock_t end_time=clock();
	// print_arr(&arr[0],len);
	printf("Time taken:%f Microseconds\n",((((double)end_time-start_time)/CLOCKS_PER_SEC)*1000000));
	return 0;
}

