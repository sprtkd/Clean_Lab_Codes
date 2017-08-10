#include<stdio.h>
#include<pthread.h>


void *thread1(void *arg)
{
    while (1)
    {
        printf("Speaking from the detached thread...\n");
        sleep(1);
    }
}


int main()
{
    pthread_t t1;
    int s;
    pthread_create(&t1,NULL,thread1,NULL);
    pthread_detach(t1);
    sleep(1);
    s = pthread_join(t1,NULL);
    if(s!=0)
    	printf("\nJoin failed");
    	
    while(1);
    return 0;

}
