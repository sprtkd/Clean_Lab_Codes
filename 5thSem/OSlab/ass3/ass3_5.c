#include<stdio.h>
#include<pthread.h>


void *thread1(void *arg)
{
}


int main()
{
    pthread_t t;
    long long int count=0;
    int s;
    printf("\nWorking");
    while(1)
    {
		s= pthread_create(&t,NULL,thread1,NULL);
		if(s)
		{
			printf("\nThread creation failed");
			break;
		}
		else
		{
			
			count++;
			if(count%500==0)
			printf("\nCount =%lld",count);
		}
		
	}
	
	printf("\nCount =%lld",count);
    	
    
    return 0;

}
