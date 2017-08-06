//program to get elapsed time and actual time taken by process

#include<stdio.h>
#include <sys/time.h>
#include <sys/resource.h>

int main()
{

	long int i;
	struct timeval begin, end, cpu_begin, cpu_end;
	double elapsed, cpu_elapsed;
	
	int who = RUSAGE_SELF;
	struct rusage usage;
	
	gettimeofday(&begin, NULL);
	getrusage(who, &usage);
	cpu_begin = usage.ru_utime;
	for(i=1; i<= 1000; i++ );
	getrusage(who, &usage);
	cpu_begin = usage.ru_utime;
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);
    cpu_elapsed = (cpu_end.tv_sec - cpu_begin.tv_sec) + ((cpu_end.tv_usec - cpu_begin.tv_usec)/1000000.0);
    printf("\nTime elapsed for 1000 runs : %fs",elapsed);
    printf("\nCpu time for 1000 runs : %fs",cpu_elapsed);
    
    
    gettimeofday(&begin, NULL);
	for(i=1; i<= 10000; i++ );
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);
    printf("\nTime elapsed for 10000 runs : %fs",elapsed);
    
    gettimeofday(&begin, NULL);
	for(i=1; i<= 1000000; i++ );
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);
    printf("\nTime elapsed for 1000000 runs : %fs",elapsed);
    
    gettimeofday(&begin, NULL);
	for(i=1; i<= 10000000; i++ );
	gettimeofday(&end, NULL);
	elapsed = (end.tv_sec - begin.tv_sec) + ((end.tv_usec - begin.tv_usec)/1000000.0);
    printf("\nTime elapsed for 10000000 runs : %fs",elapsed);

    
	printf("\n");
	return 0;
}
