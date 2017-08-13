#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/time.h>


void *thread1(void *arg)
{
    int a=100;
    a=a+199;
}


int main()
{
    pthread_t t;
    pid_t pid_val;
    struct timeval begin, end;
	double elapsed, tot_elap,avg;
	int count=1000,i;
	
	tot_elap=0;
	for(i=1;i<=count;i++)
	{
		gettimeofday(&begin, NULL);
		pthread_create(&t,NULL,thread1,NULL);
		pthread_join(t,NULL);
		gettimeofday(&end, NULL);
		elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);
		tot_elap = tot_elap + elapsed;
	}
	avg= tot_elap /count;
	printf("Time elapsed for creating threads in average over %d is: %fs\n",count,avg);
	
	tot_elap=0;
	for(i=1;i<=count;i++)
	{
		gettimeofday(&begin, NULL);
		pid_val = fork();
		if(pid_val != 0)
		{
			gettimeofday(&end, NULL);
			elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);
			tot_elap = tot_elap + elapsed;
		}
		else
		{
			break;
		}
		
	}
	if(pid_val!=0)
	{
		avg= tot_elap /count;
		printf("Time elapsed for creating children in average over %d is: %fs\n",count,avg);
    	return 0;
    }

}
