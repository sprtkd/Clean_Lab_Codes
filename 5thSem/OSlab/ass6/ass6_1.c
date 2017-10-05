#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define randSleep_minG 100 //usec
#define randSleep_maxG 1000 //usec

#define randSleep_minR 100 //usec
#define randSleep_maxR 1000 //usec

#define randSleep_minW 100 //usec
#define randSleep_maxW 1000 //usec

#define clear() printf("\033[H\033[J")
#define USLEEP_DISP 10//usec

#define read_writ_creat_ratio 3 //N:1

//globals
sem_t mutex,rd_mutex,wrt_mutex;
int readcount=0, rwaitcount=0, writecount=0, wwaitcount=0;

void randSleep(int Sleep_min,int Sleep_max)
{
	int del_sleep;
    del_sleep = (rand() + Sleep_min ) % Sleep_max;
    usleep(del_sleep);
}




void *reader(void *arg)
{
	pthread_detach(pthread_self());
	
	//entry
    sem_wait(&mutex);
    readcount++;
    if(readcount==1)
    	sem_wait(&wrt_mutex);
    sem_post(&mutex);
    
    //reading
    randSleep(randSleep_minR,randSleep_maxR);
    
    //exit
    sem_wait(&mutex);
    readcount--;
    if(readcount==0)
    {
    	sem_post(&wrt_mutex);
    }
    sem_post(&mutex);
    
}

void *writer(void *arg)
{
	pthread_detach(pthread_self());
    
    //entry
    sem_wait(&wrt_mutex);
    
    
    //writing
    randSleep(randSleep_minW,randSleep_maxW);
    
    //exit
    sem_post(&wrt_mutex);
    
}

void *generator(void *arg)
{
	pthread_detach(pthread_self());
	int type;
	pthread_t t;
	
    while(1)
    {
    	//random sleep
    	randSleep(randSleep_minG,randSleep_maxG);
    	
    	type= rand() % read_writ_creat_ratio;
    	
    	if(type==0)
    	{
    		//create a writer
    		pthread_create(&t,NULL,writer,NULL);
    	}
    	else
    	{
    		//create a reader
    		pthread_create(&t,NULL,reader,NULL);
    	}
    	
    }
    
}

void display()
{
	int value;
	while(1)
	{
		clear();
		printf("\n===================================\n");
		sem_getvalue(&mutex, &value);
		printf("\nMutex lock: %d",value);
		printf("\nNumber of readers: %d",readcount);
		printf("\nNumber of writers: %d",writecount);
		printf("\nNumber of waiting readers: %d",rwaitcount);
		printf("\nNumber of waiting writers: %d",wwaitcount);
		printf("\n===================================\n");
		usleep(USLEEP_DISP);
	}
	
}

int main()
{
	
	
	//init
	srand(time(NULL));
	sem_init(&mutex, 0, 1);
	sem_init(&wrt_mutex, 0, 0);
	sem_init(&rd_mutex, 0, 0);
	pthread_t t;
	pthread_create(&t,NULL,generator,NULL);
    
	display();
	
	return 0;
}
