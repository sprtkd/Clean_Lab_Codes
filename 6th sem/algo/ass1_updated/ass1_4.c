#include <stdio.h>
#define numofrec 100
#define range 10000000

int main()
{
	long long int h,k,i,sum=0,recs=0;
	double time;
	for(i=0;i<numofrec;i++)
	{
		
		scanf("%lld %lld",&h,&k);
		sum=sum+k;
		recs++;
		if(h%range==0)
		{
			time=sum/recs;
			printf("%lld %lf\n",h,time);
			sum=0;
			recs=0;
		}
		
		
	}
	
	return 0;
}
