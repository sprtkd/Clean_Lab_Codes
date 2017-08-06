#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	pid_t pid_val;
	long long int childcount=0;
	while(1)
	{
		pid_val = fork();
		childcount++;
		if(pid_val == 0)
		{
			printf("\nNew child created.Pid is %d.Childcount now %lld",getpid(),childcount);
			break;
		}
		if(pid_val == -1)
		{
			exit(0);
		}
		
	}
	

	return 0;
}
