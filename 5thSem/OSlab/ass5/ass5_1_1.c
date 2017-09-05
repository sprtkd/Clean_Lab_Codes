//This is the producer

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

#define ARRSIZE 15
#define KEY_SHARED 8334
#define SHM_FLAG IPC_CREAT | IPC_EXCL | 0666

#define MIN_PROD_SLEEP 1
#define MAX_PROD_SLEEP 2

void random_sleep_prod()
{
	int m, sleep_time;
	m = MAX_PROD_SLEEP - MIN_PROD_SLEEP + 1;
	sleep_time = rand() % m + MIN_PROD_SLEEP;
	sleep(sleep_time);	
}

void reset_buffer(int *arr)
{
	int i;
	for(i=0;i<ARRSIZE;i++)
	{
		arr[i] = 0;
	}
}

int main()
{
	printf("\nI am the producer...");
	srand(time(NULL));
	int shm_id;//the shared memory ID
	int *arr_shared,*sgmnt_addr, *count,*turn,*flag,i=0;
	
	shm_id = shmget(KEY_SHARED,ARRSIZE+1+(2+1),SHM_FLAG);//last places for count, turn and flag
	if(shm_id<0)
	{
		printf("\nCould not get shared memory ID!");
		exit(1);
	}
	else
		printf("\nReceived shared memory ID!");
		
	sgmnt_addr = shmat(shm_id,NULL,0);
	if(sgmnt_addr==(int*)-1)
	{
		printf("\nCould not get shared memory address!");
		exit(1);
	}
	else
		printf("\nSuccess. Created shared memory! Received address..");
		
		
	arr_shared = sgmnt_addr;
	count = sgmnt_addr + ARRSIZE;
	turn = count+1;
	flag=turn+1;
	
	
	(*count) = 0;
	(*turn)=0;
	flag[0] = 0;
	flag[1] = 0;
	reset_buffer(arr_shared);
	
	printf("\nReady for production. Turn on display.. Press enter...");
	getchar();
	printf("\n\nStarting production...\n");
	while(1)
	{
		random_sleep_prod();
		while((*count)==ARRSIZE);
		
		while(arr_shared[i]!=0)
			i = (i+1)%ARRSIZE;
		
		//entry section
		flag[0] = 1;
		(*turn) = 1;
		while ( flag[1] && (*turn) == 1);
		
			//critical section
			arr_shared[i] = 1;
			(*count)++;
		
		//exit section
		flag[0] = 0;
	}
	
	
	return 0;
}
