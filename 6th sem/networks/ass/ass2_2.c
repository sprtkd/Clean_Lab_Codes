//client for ass1
//by Suprotik Dey
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>

#define IP_PROTOCOL 0
#define PORT_NO 15000
#define NET_BUF_SIZE 512
#define NET_SEND_FLAG 0
#define IP_ADDRESS "10.24.109.30"//localhost

void clearBuf(char *b)
{
	int i;
	for(i=0;i<NET_BUF_SIZE;i++)
		b[i]='\0';
}


void takeStrInput(char *buf)
{
	getchar();
	clearBuf(buf);
	printf("\nPlease enter a String: \n");
	scanf("%[^\n]",buf);
	if(strcmp(buf,"bye")==0)
		exit(0);
	printf("Input String is: ");
	printf("%s",buf);
	printf("\nWaiting for server...\n");
}

int net_process(char *buf)
{
	printf("\nReceived answer for server!\n Palindrome? : ");
	printf("%s",buf);
	printf("\n");
}

int main()
{
	int sockfd, n_bytes;
	struct sockaddr_in addr_con;
	int addrlen = sizeof(addr_con);
	addr_con.sin_family = AF_INET;
  	addr_con.sin_port = htons (PORT_NO);
  	char net_buf[NET_BUF_SIZE];
  	pid_t net_pid;
  	
  	struct timespec start, stop;
	long long int time_taken;
	clock_gettime(CLOCK_MONOTONIC, &start);
	
	
  	
	//socket()
	sockfd = socket(AF_INET, SOCK_STREAM, IP_PROTOCOL);
	if(sockfd==0)
		printf("Socket file descriptor not received!!\n");
	else
		printf("Socket file descriptor %d received\n",sockfd);
	
	if(inet_pton(AF_INET, IP_ADDRESS, &addr_con.sin_addr)<=0)
	{
		printf("\nInvalid address");
		return -1;
	}
	
	//connect
	if (connect(sockfd, (struct sockaddr *)&addr_con, sizeof(addr_con)) < 0)
	{
		printf("\nConnection Failed\n");
		return -1;
	}
	else
	{
		printf("\nConnection Success..\n");
	}	
	clock_gettime(CLOCK_MONOTONIC , &stop);
	time_taken = (( stop.tv_sec - start.tv_sec )*1000000000) + ( stop.tv_nsec - start.tv_nsec );
	printf("\nTime taken for establishing connection: %lld ns\n Press Enter..\n",time_taken);
	while(1)
	{
		takeStrInput(net_buf);
		//write
		send(sockfd, net_buf, strlen(net_buf), NET_SEND_FLAG);
		clearBuf(net_buf);
		//read
		n_bytes = read(sockfd, net_buf, NET_BUF_SIZE);
		net_process(net_buf);
	}
	
	
	
	return 0;
}

