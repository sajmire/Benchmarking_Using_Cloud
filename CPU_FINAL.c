#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <immintrin.h>


void *integer_op();
void *float_op();

int main()
{
	int operation, no_threads,thread_choice,i=0;
	pthread_t thread[8];
	clock_t start_time,end_time;
	double cpu_totaltime;

	printf("Please choose the operation to perform  :\n 1.IOPS \n 2.FLOPS \n Enter your Choice :\n");
	scanf("%d",&operation);
	printf("Please choose the thread count  :\n 1.Single \n 2.Double \n 3.Multiple-4 \n 4.Multiple-8 \n Enter your Choice :\n");
	scanf("%d",&thread_choice);
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

	if(operation==1)
	{
		start_time = clock();
		for(i=0;i<no_threads;i++)
		{
			pthread_create(&thread[i],NULL,integer_op,NULL);
		}
		for(i=0;i<no_threads;i++)
		{
			pthread_join(thread[i],NULL);
		}
		end_time = clock();
			cpu_totaltime = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
	printf("total time taken: %lf",cpu_totaltime);
	printf("Performed Integer Operation @ %lf GIOPS\n",((8*no_threads)/cpu_totaltime));
	}
	else
	{
		start_time = clock();
		for(i=0;i<no_threads;i++)
		{
			pthread_create(&thread[i],NULL,float_op,NULL);
		}
		for(i=0;i<no_threads;i++)
		{
			pthread_join(thread[i],NULL);
		}
		end_time = clock();
			cpu_totaltime = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
	printf("total time taken: %lf",cpu_totaltime);
	printf("Performed Integer Operation @ %lf GFLOPS\n",((8*no_threads)/cpu_totaltime));
	}


}

void *integer_op()
{
	int a=10,b=12,c=13,d=15,e=15,i=0;
	for(i=0;i<1000000000;i++)
	{
		a = b+c;
		c = c+d;
		c = a+d;
		d = a+b;
		a = a+e;
		b = b+e;

		

	}
	return NULL;

}

void *float_op()
{
float a = 12.43f, b = 43.55f, c = 198.88f, d = 200.77f, e = 89.67f;
int i=0;

for(i=0;i<1000000000;i++)
	{
		a = b+c;
		c = c+d;
		c = a+d;
		d = a+b;
		a = a+e;
		b = b+e;
		

	}
	return NULL;
}
