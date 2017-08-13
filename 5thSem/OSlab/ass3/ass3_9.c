#include<stdio.h>
#include<pthread.h>


void *thread1(void *arg)
{
    
}


int main()
{
    pthread_t t;
    int s;
    pthread_create(&t,NULL,thread1,NULL);
    pthread_detach(t);
    sleep(1);
    s = pthread_cancel(t);
    if(s!=0)
    	printf("\nCould not kill thread");
    else
    	printf("\nKilled thread");
    
    return 0;

}
