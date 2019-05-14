#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <immintrin.h>


void* sequential_readwrite();
void* random_filewrite();
void* sequential_fileread();
void* random_fileread();
 int block_size=0;
long int mem_size = 1024*1024*1024;
int no_threads;


int main()
{

	int operation,thread_choice,i=0;
	pthread_t thread[8];
	clock_t start_time,end_time;
	double cpu_totaltime;


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
			break;
	case 2 : no_threads = 2;
			break;
	case 3 : no_threads = 4;
			break;
	case 4 : no_threads = 8;
			break;
	default : printf("Invalid Choice \n");

}

printf("--------SEQUENTIAL - READ + WRITE with %d and for size %lu----------",no_threads,block_size);

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
        printf("Throughput is: %lf MBPS\n",((no_threads * mem_size)/cpu_totaltime)/(1024*1024));
        printf("Latency is: %0.16lf ms\n",(cpu_totaltime*1000)/(mem_size*no_threads*block_size));
printf("\n\n\n");

printf("--------SEQUENTIAL - READ with %d and for size %lu----------",no_threads,block_size);

start_time = clock();
		for(i=0;i<no_threads;i++)
		{
			pthread_create(&thread[i],NULL,sequential_fileread,NULL);
		}
		for(i=0;i<no_threads;i++)
		{
			pthread_join(thread[i],NULL);
		}
		end_time = clock();
		cpu_totaltime = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
		printf("Time taken: %lf\n",cpu_totaltime);
        printf("Throughput is: %lf MBPS\n",((no_threads * mem_size)/cpu_totaltime)/(1024*1024));
        printf("Latency is: %0.16lf ms\n",(cpu_totaltime*1000)/(mem_size*no_threads*block_size));
printf("\n\n\n");


printf("--------RANDOM - READ with %d and for size %lu----------",no_threads,block_size);

start_time = clock();
		for(i=0;i<no_threads;i++)
		{
			pthread_create(&thread[i],NULL,random_fileread,NULL);
		}
		for(i=0;i<no_threads;i++)
		{
			pthread_join(thread[i],NULL);
		}
		end_time = clock();
		cpu_totaltime = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
		printf("Time taken: %lf\n",cpu_totaltime);
        printf("Throughput is: %lf MBPS\n",((no_threads * mem_size)/cpu_totaltime)/(1024*1024));
        printf("Latency is: %0.16lf ms\n",(cpu_totaltime*1000)/(mem_size*no_threads*block_size));
printf("\n\n\n");

return 0;
}
void *sequential_readwrite() {

	FILE *fptr,*fptr1;
long int loop_count = mem_size / block_size;
long int limit = loop_count / no_threads ;
int i,j;


char *c = (char*) malloc(block_size);
fptr = fopen("tempwrite1.txt","r+");
for(i=0;i<limit;i++)
{
 fread(c,block_size,1,fptr);
} 
 // printf("%s",d);


	fclose(fptr);
	//char c[block_size];
	
	

	fptr1 = fopen("sequential.txt", "a");
	for(i=0;i<limit;i++)
	{
		fwrite(c, 1, block_size, fptr1);
	
	}
//printf("\nLOOP COUNT%d",j);
	fclose(fptr1);
}
void *sequential_fileread() {

	FILE *fptr;
long int loop_count = mem_size / block_size;
long int limit = loop_count / no_threads ;
int i;
char *d = (char*) malloc(block_size);
//char d[block_size];
fptr = fopen("sequential.txt","r+");
for(i=0;i<limit;i++)
{
 fread(d,block_size,1,fptr);
} 
 // printf("%s",d);


	fclose(fptr);
}

void *random_fileread() {

	FILE *fptr;
long int loop_count = mem_size / block_size;
long int limit = loop_count / no_threads ;
int i,temp;
char *d = (char*) malloc(block_size);
//char d[block_size];
fptr = fopen("sequential.txt","r+");
for(i=0;i<limit;i++)
{
temp = rand() % block_size;
fseek(fptr, temp, SEEK_SET);
 fread(d,block_size,1,fptr);

} 
 // printf("%s",d);


	fclose(fptr);
}

















