#include<stdio.h>
#include<pthread.h>



void *thread3(void *arg)
{
    sleep(4);
    return NULL;

}


void *thread2(void *arg)
{
    pthread_t t3;
    
    pthread_create(&t3,NULL,thread3,NULL);
    return NULL;

}

void *thread1(void *arg)
{
    pthread_t t2;
    
    pthread_create(&t2,NULL,thread2,NULL);
    return NULL;

}


int main()
{
    pthread_t t1;
    
    pthread_create(&t1,NULL,thread1,NULL);
    
    return 0;

}
