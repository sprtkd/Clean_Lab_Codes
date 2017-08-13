#include<stdio.h>
#include<pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define randCreate_max 20000 //usec
#define randSleep_max 10000 //usec


FILE *fp;
int completed=0;


void *thread_worker(void *arg)
{
    char ch;
    int del_sleep;
    del_sleep = rand() % randSleep_max;
    usleep(del_sleep);
    ch = getc(fp);
    if(ch==EOF)
    {
	completed=1;
    }
    else
	printf("%c",ch);
}



void *thread_master(void *arg)
{
    int del_create;
    fp = fopen("New.txt","r");
    pthread_t t;
    
    while(completed==0)
    {
    	del_create = rand()%randCreate_max;
    	usleep(del_create);
    	
    	pthread_create(&t,NULL,thread_worker,NULL);
        pthread_join(t,NULL);
    
    }
}


int main()
{
    srand(time(NULL));   // should only be called once
    pthread_t t;
    pthread_create(&t,NULL,thread_master,NULL);
    pthread_join(t,NULL);
    printf("\n");
    return 0;

}
