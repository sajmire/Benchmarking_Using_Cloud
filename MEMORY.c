#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <immintrin.h>

void* sequential_readwrite();
void* random_readwrite();
long int block_size=0;
long int mem_size = 1024*1024*1024;
int no_threads;


int main()
{

	int operation,thread_choice,i=0;
	pthread_t thread[8];
	clock_t start_time,end_time;
	double cpu_totaltime;
	long int temp,iterations;


	printf("Please choose the thread count  :\n 1.Single \n 2.Double \n 3.Multiple-4 \n 4.Multiple-8 \n Enter your Choice :\n");
	scanf("%d",&thread_choice);
	printf("Please choose the Block Size  :\n 1- 8B \n 2- 8KB \n 3- 8MB \n 4- 80MB Enter your Choice :\n");
	scanf("%d",&operation);

switch(operation)
{
	case 1 : block_size = 8;

			break;
	case 2 : block_size = 1024*8;
			break;
	case 3 : block_size = 1024*1024*8;
			break;
	case 4 : block_size = 1024*1024*80;
			break;
	default : printf("Invalid Choice \n");

}
switch(thread_choice)
{
	case 1 : no_threads = 1;
			temp = mem_size / block_size;
			 iterations = temp/ 1;
			break;
	case 2 : no_threads = 2;

			temp = mem_size / block_size;
			 iterations = temp/ 2;
			break;
	case 3 : no_threads = 4;

			temp = mem_size / block_size;
			 iterations = temp/ 4;
			break;
	case 4 : no_threads = 8;

			temp = mem_size / block_size;
			 iterations = temp/ 8;
			break;
	default : printf("Invalid Choice \n");

}


printf("--------SEQUENTIAL - READ/WRITE----------");
		start_time = clock();
		for(i=0;i<no_threads;i++)
		{
			pthread_create(&thread[i],NULL,sequential_readwrite,NULL);
		}
		for(i=0;i<no_threads;i++)
		{
			pthread_join(thread[i],NULL);
		}
		end_time = clock();
		cpu_totaltime = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
		printf("Time taken: %lf\n",cpu_totaltime);
        printf("Throughput: %lf MBPS\n",((no_threads * mem_size)/cpu_totaltime) /(1024*1024));
        printf("Latency: %0.12lf ms\n",(cpu_totaltime*1000)/(mem_size*no_threads));
printf("\n\n\n");

printf("--------RANDOM - READ/WRITE----------");
		start_time = clock();
		for(i=0;i<no_threads;i++)
		{
			pthread_create(&thread[i],NULL,random_readwrite,NULL);
		}
		for(i=0;i<no_threads;i++)
		{
			pthread_join(thread[i],NULL);
		}
		end_time = clock();
		cpu_totaltime = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
		printf("Time taken: %lf\n",cpu_totaltime);
        printf("Throughput : %lf MBPS\n",(no_threads * mem_size)/(cpu_totaltime*1024*1024));
        printf("Latency : %0.12lf ms\n",(cpu_totaltime*1000)/(mem_size*no_threads));

return 0;
}


void *sequential_readwrite()
{
	char *source_ptr = (char*) malloc(mem_size);
	char *destination_ptr = (char*) malloc(mem_size);
long int loop_count = mem_size / block_size;
long int limit = loop_count / no_threads ;
int i,e;

	for(i=0;i<limit;i++)
	{
memcpy(destination_ptr+(i*block_size),source_ptr+(i*block_size),block_size*sizeof(char));
			//e=i;
	}
//printf("float iterations :%d",e);
	return NULL;

}

void *random_readwrite()
{
	char *source_ptr = (char*) malloc(mem_size);
	char *destination_ptr = (char*) malloc(mem_size);
long int loop_count = mem_size / block_size;
long int limit = loop_count / no_threads ;
//printf("limit:%lu",limit);
int temp,i,d;

	for(i=0;i<limit;i++)
	{
memcpy(destination_ptr+(i*block_size),source_ptr+((rand()%loop_count)*block_size),block_size*sizeof(char));
//d=i;
	}
	//printf("float iterations :%d",d);
	return NULL;

}
