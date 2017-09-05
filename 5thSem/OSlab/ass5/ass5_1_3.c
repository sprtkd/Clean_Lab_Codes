//This is the display program

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define ARRSIZE 15
#define KEY_SHARED 8334
#define SHM_FLAG 0666
#define clear() printf("\033[H\033[J")
#define USLEEP_DISP 10

int display_buffer(int *arr)
{
	int i,c=0;
	for(i=0; i<ARRSIZE;i++)
	{
		if(arr[i]==1)
			c++;
		printf("%d ",arr[i]);
	}
	return c;
}

int main()
{
	printf("\nI will display the shared memory...");
	int shm_id;//the shared memory ID
	int *arr_shared,*sgmnt_addr, *count, c,cc;
	int *turn,*flag;
	
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
	
	printf("\nPress enter to start display..");
	getchar();
	while(1)
	{
		clear();
		printf("\n");
		c = display_buffer(arr_shared);
		cc = (*count);
		printf("\tCount: %d  Turn: %d  Flags: %d,%d",cc,(*turn),flag[0],flag[1]);
		/*if(c!=cc)
		{
			printf("\n\nSeems like you got a problem with count\n");
			printf("Calculated\tActual\n");
			printf("----------\t------\n");
			printf("%d         \t%d\n",c,cc);
			printf("------------------\n");
			printf("Press enter to resume display");
			getchar();
		}*/
		printf("\n");
		usleep(USLEEP_DISP);	
	}
		
	return 0;
}
