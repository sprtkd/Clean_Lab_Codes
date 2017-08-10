#include<stdio.h>
#include<pthread.h>


void *fact(void *arg)
{
    pthread_detach(pthread_self());
}


void *printTime(void *arg)
{
    
}


void *printPrime(void *arg)
{
    
}


void *printFibonacci(void *arg)
{
    
}


int main()
{
    pthread_t t;
    pthread_create(&t1,NULL,thread1,NULL);
    
    if(s!=0)
    	printf("\nJoin failed");
    	
    while(1);
    return 0;

}
