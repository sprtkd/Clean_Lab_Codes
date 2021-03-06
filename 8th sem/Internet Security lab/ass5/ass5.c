#include <stdio.h>
#define KEY_LEN 8
#define BLOCK_LEN 8
#define NUM_KEYS 16
#define NEW_BLOCK_LEN 14
#define NEW_KEY_LEN (KEY_LEN*(BLOCK_LEN-1))/NEW_BLOCK_LEN

int verbose = 0;

void fillupMat(int (*mat)[KEY_LEN], char *key)
{
	int i,j;
	
	for(i=0; i<KEY_LEN; i++)
		for (j = 0; j < BLOCK_LEN; j++)
    		mat[i][BLOCK_LEN-1-j] = ((key[i] >> j) & 1);
    if(verbose)
    {		
		printf("\nKey Matrix:\n");
		for(i=0; i<KEY_LEN; i++)
		{
			for (j = 0; j < BLOCK_LEN; j++)
				printf("%d",mat[i][j]);
			printf("\n");
		}
	}
	
}

void keyGenerator(int (*mat)[KEY_LEN], int rot_val)
{
	int i,j, pass,k;
	
	if(verbose)
    {
		printf("\nD box Key Matrix:\n");
		for(i=0; i<KEY_LEN; i++)
		{
			for (j = 0; j < BLOCK_LEN-1; j++)
				printf("%d",mat[i][j]);
			printf("\n");
		}
	}
	
	for(k=1; k<=rot_val; k++)
	{
		//shift box
		for(i=0; i<NEW_KEY_LEN; i++)
		{
			for(j=0; j<NEW_BLOCK_LEN; j++)
			{
				//0
				if(j==0)
					pass=mat[i*2][0];
				else if(j==NEW_BLOCK_LEN-1) //13
				{
					mat[(i*2) + 1][j - BLOCK_LEN] = mat[(i*2) + 1][j - BLOCK_LEN + 1];
					mat[(i*2) + 1][BLOCK_LEN-2] = pass;
				}
				else if(j==BLOCK_LEN-1)
				{
					//7
					mat[i*2][BLOCK_LEN-2] = mat[(i*2) + 1][0];
				}
				else if(j>BLOCK_LEN-1)
				{
					//from 8 to 12
					mat[(i*2) + 1][j - BLOCK_LEN] = mat[(i*2) + 1][j - BLOCK_LEN + 1];
				}
				else
				{
					//1 upto 6
					mat[i*2][j-1] = mat[i*2][j];
				}
			}
		}
	}
	
	if(verbose)
    {
		printf("\nAfter rotate %d times, Key Matrix:\n", rot_val);
		for(i=0; i<KEY_LEN; i++)
		{
			for (j = 0; j < BLOCK_LEN-1; j++)
				printf("%d",mat[i][j]);
			if(i%2==1)
				printf("\n");
		}
	}
	
	if(verbose)
		printf("\n2nd D box Key Matrix (Final Key):\n");
		
	for(i=0; i<KEY_LEN; i++)
	{
		for (j = 0; j < BLOCK_LEN-2; j++)
    		printf("%d",mat[i][j]);
	}
}



int main()
{
	int rot_val_arr[NUM_KEYS] = { 1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	char key[KEY_LEN+1];
	int key_mat[KEY_LEN][BLOCK_LEN], i;
	printf("Enter key (8 bits): ");
	scanf("%s",key);
	printf("Key is: %s\n",key);
	
	fillupMat(key_mat,key);
	
	for(i=0; i<NUM_KEYS; i++)
	{
		printf("\nGenerating key: %d ..\n",i+1);
		keyGenerator(key_mat, rot_val_arr[i]);
	}
	printf("\n");
	return 0; 
}
