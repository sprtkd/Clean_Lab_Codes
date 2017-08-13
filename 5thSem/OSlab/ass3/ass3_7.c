#include<stdio.h>
#include<pthread.h>


void *thread1(void *arg)
{
    int a;
    sleep(1);
    while(1)
    {
    	a = 26+65;
    	printf("\t%d",a);
    }

}

void *thread2(void *arg)
{
    int a;
    printf("\nEnter a number: ");
    scanf("%d",&a);
}




int main()
{
    pthread_t t1,t2;
    
    pthread_create(&t1,NULL,thread1,NULL);
    pthread_create(&t2,NULL,thread2,NULL);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    
    return 0;

}
