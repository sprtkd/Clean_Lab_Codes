#include<stdio.h>
#include<pthread.h>
#include<time.h>

void *fact(void *arg)
{
    int i=1,f=1,num=9;
    while(i<=num)
    {
      f=f*i;
      i++;
    }
    printf("\nThe fact of %d is %d",num, f);
}


void *printTime(void *arg)
{
    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    puts(buffer);

    
}

void *printPrime(void *arg)
{
    int numbr,k,remark;

    printf(" The prime numbers between 1 and 1000 : \n");

    for(numbr=2;numbr<=1000;++numbr)
    {
		remark=0;
		for(k=2;k<=numbr/2;k++){
			if((numbr % k) == 0){
				remark++;
				break;

   				}
   			}
   		if(remark==0)
		printf("%d, ",numbr);
    }

}


void *printFibonacci(void *arg)
{
    int i, n, t1 = 0, t2 = 1, nextTerm;
    printf("\nFibonacci series upto 1000:");
    while((t1 + t2)<=1000)
    {
        
        nextTerm = t1 + t2;
        printf("%d, ", nextTerm);
        t1 = t2;
        t2 = nextTerm;
    }
}


int main()
{
    pthread_t t;
    int opt;
    
    do
    {
    	printf("\nEnter option: ");
    	scanf("%d",&opt);
    	
    	switch(opt)
    	{
    		case 1: pthread_create(&t,NULL,fact,NULL);
    				pthread_join(t,NULL);
    				break;
    		case 2: pthread_create(&t,NULL,printTime,NULL);
    				pthread_join(t,NULL);
    				break;
    		case 3: pthread_create(&t,NULL,printPrime,NULL);
    				pthread_join(t,NULL);
    				break;
    		case 4: pthread_create(&t,NULL,printFibonacci,NULL);
    				pthread_join(t,NULL);
    				break;
    		case 0: break;
    	}
	}while(opt);
    return 0;

}
