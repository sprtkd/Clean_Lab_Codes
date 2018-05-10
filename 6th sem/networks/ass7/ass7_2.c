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

#define IP_PROTOCOL 0
#define PORT_NO 15050
#define NET_BUF_SIZE 1025
#define NET_SEND_FLAG 0
#define IP_ADDRESS "127.0.0.1"

char ip_addr[NET_BUF_SIZE];
int loopFlag=1;

void clearBuf(char *b)
{
	int i;
	for(i=0;i<NET_BUF_SIZE;i++)
		b[i]='\0';
}

int isInvalidIpAddress(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    if(result != 0)
		return 0;
	else
	{
		printf("Wrong IP!\n");
		return 1;
	}
}

int EnterIp()
{
	printf("Enter friend IP address (Crtl+c to exit) :");
	scanf("%s",ip_addr);
	getchar();
	//printf("IP: %s\n",ip_addr);

	return isInvalidIpAddress(ip_addr);
}
int takeStrInput(char *buf)
{
	char msg[NET_BUF_SIZE - strlen(ip_addr)-4];
	int i,j;
	
	clearBuf(buf);
	clearBuf(msg);
	//take input string
	printf("\nYou: ");
	scanf("%[^\n]",msg);
	getchar();
	if(strcmp(msg,"bye")==0)
	{
		loopFlag=0;
		return 0;
	}
	
	if(strlen(msg)==0)
		return 0;
	printf("\t\t\t\t\tYou: ");
	printf("%s\n",msg);

	//keep size of ip in 0th position
	buf[0] = (char)strlen(ip_addr);
	//printf("Size of buf 0 : %d\n",(int)buf[0]);

	//fill up ip in buffer

	//printf("IP: %s\n",ip_addr);

	for(i=1; i<=(int)buf[0]; i++)
	{
		buf[i] = ip_addr[i-1];
		//printf("H: %d: [%c]\n",i,buf[i]);
	}
	
	//fill up msg in buffer
	for(j=0; j<=strlen(msg); j++,i++)
	{
		buf[i] = msg[j];
		//printf("M: %d: [%c]\n",i,buf[i]);
	}

	return 1;
	//printf("\nWaiting for server...\n");
}

int net_process(char *buf)
{
	//printf("\nReceived answer for server!\n");
	
	int i;
	
	printf("\nFriend (IP: ");
	
	for(i=1;i<=(int)buf[0];i++)
	{
		printf("%c",buf[i]);
	}
	
	printf("): ");
	
	for(;buf[i]!='\0';i++)
	{
		printf("%c",buf[i]);
	}
	
	printf("\n");
}

int main()
{
	int sockfd, n_bytes, flag;
	struct sockaddr_in addr_con;
	int addrlen = sizeof(addr_con);
	addr_con.sin_family = AF_INET;
  	addr_con.sin_port = htons (PORT_NO);
  	char net_buf[NET_BUF_SIZE];
  	pid_t net_pid;
  	
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
		printf("\nConnection Success..  \n");
	}	
	
	while(1)
	{
		if(EnterIp())
			continue;
			
		loopFlag=1;
		printf("\n=======Blank messages will not be sent======\n");
		printf("\n=======Write bye to talk to another IP======\n");
		while(loopFlag)
		{
			//check continuously for mssages until none is there.

			do
			{
				flag=1;
				clearBuf(net_buf);
				net_buf[0]=(char)0;//mark that i am asking for messages
				//send
				send(sockfd, net_buf, 10, NET_SEND_FLAG);
				//printf("Request Sent\n");
				clearBuf(net_buf);
				
				//read
				n_bytes = read(sockfd, net_buf, NET_BUF_SIZE);
				if(net_buf[0]==(char)0)
				{
					flag=0;
					//printf("\nNothing Received\n");
				}
				else
					net_process(net_buf);
			}while(flag);
			//if no messages are there break

			//take msg
			if(takeStrInput(net_buf))
				send(sockfd, net_buf, strlen(net_buf)+1, NET_SEND_FLAG);
			
		}
	}
	
	
	return 0;
}
