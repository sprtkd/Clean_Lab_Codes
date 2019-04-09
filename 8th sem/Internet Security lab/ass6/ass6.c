#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_STRING 100

int isPrime(long long int n)
{
    long long int i;
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n%2 == 0 || n%3 == 0)
        return 0;
    for (i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return 0;
    return 1;
}

long long int randNum(long long int minNum, long long int maxNum)
{
    return (minNum + (rand()%(maxNum-minNum)));
}

long long int ExtendedGCD(long long int a, long long int b,long long int *x,long long int *y)
{
    if (b == 0)
    {
        *x = 1;
        *y = 0;
        return a;
    }
    long long int currGCD, prev_x,prev_y;
    currGCD = ExtendedGCD(b, a % b, &prev_x, &prev_y);
    *x = prev_y;
    *y = prev_x - (a/b)*prev_y;
    return currGCD;
}


int FastExpo(long long int x, unsigned long long int y, long long int p)
{
    long long int res = 1;
    x = x % p;
    while (y > 0)
    {
        res = (res*x) % p;
        y--;
    }
    return res;
}

int main()
{
    srand(time(NULL));
    long long int P_a, Alpha_a, D_a, Beta_a,x,y;
    char msg[MAX_STRING];
    int T_msg[MAX_STRING];
    long long int k,R,t,R_Da;

    //inputs
    printf("\nEnter large prime P_a: ");
    scanf("%lld",&P_a);
    if(isPrime(P_a))
        printf("P_a is prime.\n");
    else
    {
        printf("P_a is not prime. Exiting..");
        return 0;
    }

    getchar();
    printf("Enter msg: \n");
    scanf("%[^\n]",msg);


    //generate D_a
    D_a = randNum(2,P_a-2);

    //generate Alpha_a
    printf("Generating Alpha_a, Beta_a..\n");
    do
    {
        Alpha_a = randNum(1,P_a-1);
    }while(ExtendedGCD(Alpha_a,P_a,&x,&y)!=1);

    Beta_a = FastExpo(Alpha_a, D_a, P_a);
    printf("Generated Alpha_a = %lld, D_a = %lld, Beta_a = %lld\n",Alpha_a, D_a,Beta_a);
    printf("\nPublic key = (%lld,%lld,%lld)\nPrivate key = %lld\n",P_a,Alpha_a,Beta_a,D_a);

    k = randNum(1,P_a-1);
    R = FastExpo(Alpha_a, k, P_a);

    t = FastExpo(Beta_a, k, P_a);

    printf("Ready for encryption with k = %lld, R = %lld, t = %lld, P_a = %lld\n",k,R,t,P_a);

    for(x=0; msg[x]!='\0'; x++)
        T_msg[x] = (msg[x]*t) % P_a;

    T_msg[x] = '\0';

    printf("Message:\n");
    printf("%s",msg);

    printf("\n\nEncrypted Message:\n");
    for(x=0; msg[x]!='\0'; x++)
      printf("%d",T_msg[x]);

    R_Da = FastExpo(R,P_a-D_a-1,P_a);
    printf("\nDecrypting with R_Da = %lld...\n",R_Da);

    for(x=0; T_msg[x]!='\0'; x++)
        printf("%c",(char)((R_Da*T_msg[x]) % P_a));
    printf("\n");
	return 0;
}
