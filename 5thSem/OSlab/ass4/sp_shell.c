//program to design a shell in c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXCOM 1000
#define MAXLIST 20

int ShellStartedFlag =0 ;

void init_shell()
{
	system("clear");
	printf("\n\n\n\n******************************************");
	printf("\n\n\n\t****SPRTKD SHELL****");
	printf("\n\n\t-USE AT YOUR OWN RISK-");
	printf("\n\n\n\n******************************************");
	printf("\n");
	sleep(1);
	system("clear");
}

void printNewScr()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
       	printf("\nDir: %s", cwd);
       	if(ShellStartedFlag)
       		getchar();
       	else
       		ShellStartedFlag = 1;
       	printf("\n>>> ");
}

int ownCmdHandler(char **parsed)
{
	int NoOfOwnCmds = 1,i, switchOwnArg=0;
	char *ListOfOwnCmds[NoOfOwnCmds];
	
	ListOfOwnCmds[0] = "exit";
	
	for(i=0;i<NoOfOwnCmds;i++)
	{
		if(strcmp(parsed[0],ListOfOwnCmds[i])==0)
		{
			switchOwnArg=i+1;
			break;
		}
	}
	
	switch(switchOwnArg)
	{
		case 1: printf("\nGoodbye\n");
			exit(0);
			return 1;
		default: break;
	}
	
	return 0;
}

int processString(char *str, char **parsed)
{
	int i;
	for(i = 0; i < MAXLIST; i++)
	{
        	parsed[i] = strsep(&str, " ");
        	if(parsed[i] == NULL)
        		break;
    	}
    	if(ownCmdHandler(parsed))
		return 0;
	else
		return 1;
	   
}

void execArgs(char **parsed)
{
	pid_t pid = fork();
		
	if (pid == -1)
        {
        	printf("\nFailed forking child..");
        	return;
        }
        else if(pid == 0)
        {
        	if(execvp(parsed[0], parsed)<0)
        	{
        		printf("\nCould not execute command..");
        	}
        	exit(0);
        }
        else
        {
        	wait(NULL);
        	return;
        }
    
}

int main()
{
	char inputString[MAXCOM], *parsedArgs[MAXLIST];
	int execFlag = 0;
	init_shell();
	
	while(1)
	{
		
		//print shell line
		printNewScr();
		//take input
		inputString[0] = '\0';
		scanf("%[^\n]",inputString);
		//process
		execFlag = processString(inputString, parsedArgs);
		//execute
		if(execFlag)
			execArgs(parsedArgs);
	}
	return 0;
}
