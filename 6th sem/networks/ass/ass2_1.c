//server for ass1
//by Suprotik Dey
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define IP_PROTOCOL 0
#define PORT_NO 15050
#define B_LOG 30
#define NET_BUF_SIZE 512
#define NET_SEND_FLAG 0


void clearBuf(char *b)
{
	int i;
	for(i=0;i<NET_BUF_SIZE;i++)
		b[i]='\0';
}



int checkPalin(char *str)
{
    int l = 0;
    int h = strlen(str) - 1;

    while (h > l)
    {
        if (str[l++] != str[h--])
        	return 0;
    }
    
    return 1;
}

int net_process(char *buf)
{
	printf("\nChecking palindrome...\nReceived string: ");
	printf("%s",buf);
	printf("\n");
	
	if(checkPalin(buf))
	{
		clearBuf(buf);
		buf[0]='Y';
		buf[1]='e';
		buf[2]='s';
		buf[3]='\0';
		printf("\nString is Palindrome\n");
	}
	else
	{
		clearBuf(buf);
		buf[0]='N';
		buf[1]='o';
		buf[2]='\0';
		printf("\nString is not Palindrome\n");
	}
}

int main()
{
	int sockfd, acc_sockfd, n_bytes;
	struct sockaddr_in addr_con;
	int addrlen = sizeof(addr_con);
	addr_con.sin_family = AF_INET;
  	addr_con.sin_port = htons (PORT_NO);
  	addr_con.sin_addr.s_addr = INADDR_ANY;
  	char net_buf[NET_BUF_SIZE];
  	pid_t net_pid;
  	int num_of_clients=0;
  	
  	FILE *fp;
  	
  	
	//socket()
	sockfd = socket(AF_INET, SOCK_STREAM, IP_PROTOCOL);
	if(sockfd<0)
		printf("\nSocket file descriptor not received!!\n");
	else
		printf("\nSocket file descriptor %d received\n",sockfd);
	
	//bind()
	if(bind(sockfd, (struct sockaddr *)&addr_con, sizeof(addr_con))==0)
		printf("\nSuccessfully binded!\n");
	else
		printf("\nBinding Failed!\n");
	
	//listen()
	if(listen(sockfd,B_LOG)>=0)
		printf("\nListening success!\n");
	else
		printf("\nListening failed!\n");
		
	while(num_of_clients<B_LOG)//server accept loop
	{
		//accept()
		acc_sockfd = accept(sockfd,(struct sockaddr *)&addr_con, (socklen_t*)&addrlen);
		if(acc_sockfd <0)
			printf("Accept failed!\n");
		else
			printf("Connection Accepted!\n");
		num_of_clients++;
		printf("\nNumber of Clients accepted: %d",num_of_clients);
		printf("\nClient Address = %s\n",inet_ntop(AF_INET,&(addr_con.sin_addr), net_buf,sizeof(net_buf)));
		fp=fopen("connectionLog.txt","a");
	  	if(fp==NULL)
	  		printf("\nCould not open file");
	  	else
	  		printf("\nLog file successfully opened!");
		fputs(net_buf,fp);
		fputc('\n',fp);
		fclose(fp);
		net_pid = fork();//creating a child to handle each new client
		
		if(net_pid==0)
		{
			close(sockfd);
			while(1)
			{
				printf("\nWaiting for string....\n");

				clearBuf(net_buf);
				//read
				n_bytes = read(acc_sockfd, net_buf, NET_BUF_SIZE);
		
				//process
				net_process(net_buf);
		
				//write
				send(acc_sockfd, net_buf, strlen(net_buf), NET_SEND_FLAG);

			}
			exit(0);
		}
		else
		{
			close(acc_sockfd);
		}
	}
	printf("\nServer Crashed.. too many clients");
	return 0;
}
