#include<stdio.h>
#include<pthread.h>

FILE *fp;
int readflag=0;
int completed=0;
void *thread1(void *arg)
{
    fp = fopen("New.txt","r");
    char ch;
    
    while(1)
    {
    	if(completed==1)
    		break;
    	if(readflag==0)
    	{
			ch = getc(fp);
			if(ch==EOF)
			{
				completed=1;
				break;
			}
			printf("%c",ch);
			readflag=1;
		}
	}
}

void *thread2(void *arg)
{
    sleep(1);
    char ch;
    
    while(1)
    {
    	if(completed==1)
    		break;
    	if(readflag==1)
    	{
			ch = getc(fp);
			if(ch==EOF)
			{
				fclose(fp);
				completed=1;
				break;
			}
			printf("%c",ch);
			readflag=0;
		}
	}
}


int main()
{
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread1,NULL);
    pthread_create(&t2,NULL,thread2,NULL);
    
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    
    printf("\n");
    return 0;

}
