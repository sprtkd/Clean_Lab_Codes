//This is the consumer

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <unistd.h>

#define ARRSIZE 15
#define KEY_SHARED 8334
#define SHM_FLAG 0666

#define MIN_CON_SLEEP 1
#define MAX_CON_SLEEP 3

void random_sleep_con()
{
	int m, sleep_time;
	m = MAX_CON_SLEEP - MIN_CON_SLEEP + 1;
	sleep_time = rand() % m + MIN_CON_SLEEP;
	sleep(sleep_time);	
}


int main()
{
	printf("\nI am the consumer...");
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
		printf("\nSuccess. Received shared memory address!");
	
	arr_shared = sgmnt_addr;
	count = sgmnt_addr + ARRSIZE;
	turn = count+1;
	flag=turn+1;
	
	printf("\nReady for consumption. Press enter...");
	getchar();
	printf("\n\nStarting consumption...\n");
	while(1)
	{
		random_sleep_con();
		while((*count)==0);
		while(arr_shared[i]!=1)
			i = (i+1)%ARRSIZE;
		
		//entry section
		flag[1] = 1;
		(*turn) = 0;
		while ( flag[0] && (*turn) == 0);
			
			//critical section
			arr_shared[i] = 0;
			(*count)--;
			
		//exit section
		flag[1] = 0;
	}
		
	return 0;
}
