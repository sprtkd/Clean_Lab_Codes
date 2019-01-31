/*A queueing model is represented with the following notation
A/B/c/N/K
M/M/1/~/~
using markov distribution
using FIFO

using 1 service node

quantum of time is 1 sec

*/
#include<stdio.h>
#include<math.h>

#define MAX 100000

int main()
{
	int totPopu, totPopuActual, totServiceable = 0, currServicing = 0, idleFlag = 0;
	long long int tCurr = -1, currTLast = 0, temp2, currServTimeReqd = 0, timeIdle = 0;
	int serviceDone = 0, T_AvgPersonsInSystem[MAX] = {0}, T_AvgPersonsInQueue[MAX];
	long long int customerTimeInSys[MAX] = {0}, customerTimeInQStart[MAX] = {0}, ttemp, counter;
	double temp, InterArrivalbase, Servicebase, L, Lq, W, Wq, rho;
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
             temp = 0.0;//to start the job at zeroth instant
         else
             temp= pow( InterArrivalbase, totPopuActual - totPopu);
         temp2 = (long long int)temp;
         //entry
         if((  tCurr >=temp2 )&&(totPopu > 0))
               {//printf("\n%lld %f",temp2, temp);
                     totServiceable++;
               totPopu--;
               printf("\n%lld s\tPerson %d entered queue.", tCurr, (totPopuActual - totPopu));

		customerTimeInQStart[(totPopuActual - totPopu)] = tCurr;//computing performance measure
		}
             
                 
            
         
                        
         //service & exit 
         
         
         if((idleFlag == 0)&&(totServiceable == 0)&&(currServicing == 0)){
             printf("\n%lld s\tService Idle.", tCurr);
             idleFlag = 1;
             }
	if((totServiceable == 0)&&(currServicing == 0)){
             timeIdle++;
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
               
                 currServicing = 1;
                 totServiceable--;
               	 currServTimeReqd = (long long int) pow(Servicebase, (serviceDone+1));
                 currTLast = tCurr;
               
               printf("\n%lld s\t%d Service: Person Chosen. Reqd time: %lld s.", tCurr, serviceDone+1, currServTimeReqd); 
               
           }
          
	//computing performance measures:
	T_AvgPersonsInSystem[totPopuActual - serviceDone]++;

	if(currServicing != 0)
		T_AvgPersonsInQueue[totServiceable+1]++;
	else
		T_AvgPersonsInQueue[totServiceable]++;
	
	for(counter = 0; counter < totPopuActual; counter++)
	{
		if(counter+1 > serviceDone)
			customerTimeInSys[counter]++;
	}

	
	
	 
            
    }
    printf("\n========================================================================");
    printf("\nCounter is closed. Have a nice day..");
    printf("\n========================================================================");

    //computing performance measures:
	ttemp=0;
	for(counter = 0; counter <= tCurr; counter++)
	{
		ttemp = ttemp + (counter*T_AvgPersonsInSystem[counter]);
	}
	L = (double) ttemp/tCurr;

	ttemp=0;
	for(counter = 0; counter <= tCurr; counter++)
	{
		ttemp = ttemp + (counter*T_AvgPersonsInQueue[counter]);
	}	
	Lq = (double) ttemp/tCurr;

	ttemp=0;
	for(counter = 0; counter < totPopuActual; counter++)
	{
		ttemp = ttemp + customerTimeInSys[counter];
	}	
	W= (double) ttemp/totPopuActual;

	ttemp=0;
	for(counter = 0; counter < totPopuActual; counter++)
	{
		ttemp = ttemp + (customerTimeInSys[counter]-customerTimeInQStart[counter]);
	}	
	Wq= (double) ttemp/totPopuActual;
	
    rho = (double) (tCurr -timeIdle) /tCurr;
	rho = rho * 100.0;
	  

    printf("\nMeasuring the performances of an M/M/1/∞/∞ queueing model with FIFO service:\n");
    printf("\nTotal Population: %d\nTotal Time taken: %lld",totPopuActual,tCurr);
	printf("\nTime Average number of persons in system: %lf", L);
	printf("\nTime Average number of persons in Queue: %lf", Lq);
	printf("\nAverage Time spent per person in system: %lf", W);
	printf("\nAverage Time spent per person in Queue: %lf", Wq);
	printf("\nServer utilization: %lf percent\n", rho);
	
   
    return 0;
}
