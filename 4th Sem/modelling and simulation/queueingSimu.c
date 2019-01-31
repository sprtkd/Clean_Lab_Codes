/*A queueing model is represented with the following notation
A/B/c/N/K
M/M/1/~/~
using markov distribution
using SIRO

using 1 service node

quantum of time is 1 sec

*/
#include<stdio.h>
#include<time.h>
#include<math.h>

int main()
{
	srand(time(NULL));
	int totPopu, totPopuActual, totServiceable = 0, currServicing = 0, idleFlag = 0;
	long long int tCurr = -1, currTLast = 0, temp2, currServTimeReqd = 0;
	int serviceDone = 0;
	double temp, InterArrivalbase, Servicebase;
	printf("\nEnter:\n inter-arrival base,\n service Time base\n Total population\n:");
	scanf("%lf %lf %d", &InterArrivalbase, &Servicebase, &totPopu);
	totPopuActual = totPopu;
	
	
	printf("\n========================================================================");
	printf("\nTime   |    Status");
	printf("\n========================================================================\n");
	
	while((totPopu > 0)||(totServiceable > 0)||(currServicing > 0))
	{
         tCurr++;
         
         if(totPopuActual - totPopu == 0)
             temp = 0.0;//to start the job at zreoth instant
         else
             temp= pow( InterArrivalbase, totPopuActual - totPopu);
         temp2 = (long long int)temp;
         //entry
         if((  tCurr >=temp2 )&&(totPopu > 0))
               {//printf("\n%lld %f",temp2, temp);
                     totServiceable++;
               totPopu--;
               printf("\n%lld s\tPerson %d entered queue.", tCurr, (totPopuActual - totPopu));}
             
                 
            
         
                        
         //service & exit 
         
         
         if((idleFlag == 0)&&(totServiceable == 0)&&(currServicing == 0)){
             printf("\n%lld s\tService Idle.", tCurr);
             idleFlag = 1;
             }
         if((currServicing != 0)&&((tCurr - currTLast) >= currServTimeReqd))
         {
               currServicing = 0;
               currServTimeReqd = 0;
               idleFlag = 0;
                currTLast = 0;   
                serviceDone++;
               printf("\n%lld s\tPerson %d has received the service and leaving.", tCurr, serviceDone);          
         }
         
         //selection
          if(( totServiceable > 0)&&(currServicing == 0))
          {
               if(totServiceable == 1)
                 currServicing = 1;
               else
                   currServicing = (rand() % totServiceable) + 1;
                   
               totServiceable--;
               currServTimeReqd = (long long int) pow(Servicebase, (serviceDone+1));
               currTLast = tCurr;
               
               printf("\n%lld s\t%d Service: Person %d chosen among %d people. Reqd time: %lld s.", tCurr, serviceDone+1, currServicing, totServiceable+1, currServTimeReqd); 
               
           }
           
            
    }
    printf("\n========================================================================");
    printf("\nCounter is closed.Have a nice day..");
    printf("\n========================================================================");
     getch();       
	return 0;
}
