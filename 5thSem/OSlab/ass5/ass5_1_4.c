//This is only to delete the shared memory

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define ARRSIZE 15
#define KEY_SHARED 8334
#define SHM_FLAG 0666


int main()
{
	printf("\nTrying to delete...\n");
	int shm_id;//the shared memory ID
	int *arr_shared,*sgmnt_addr;
	
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
	
	
	//deletion code
	
	if(shmdt(sgmnt_addr)==0)
		printf("\nDetached shared memory segment succesfully!");
	else
		printf("\nFailed to detach shared memory segment!");
	
	if(shmctl(shm_id, IPC_RMID, NULL)==0)
		printf("\nDeleted shared memory segment succesfully!");
	else
		printf("\nFailed to delete shared memory segment!");
		
	
	
	
	return 0;
}
