#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT_NO 15050 
#define BKLOG 30

int main()
{
    int sockfd, acc_sockfd, addrlen;
    struct sockaddr_in addr_con;
    addr_con.sin_family = AF_INET;
    addr_con.sin_port = htons(PORT_NO);
    addr_con.sin_addr.s_addr = INADDR_ANY;
    addrlen = sizeof(addr_con);
    pid_t pid_acc;
    //socket open
    sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
    if(sockfd<0)
    {
        printf("\nSocket opening failed!\n");
        return 0;
    }
    else
    {
        printf("\nSocket descriptor %d received.\n",sockfd);
    }

    //bind port
    if(bind(sockfd, (struct sockaddr*)&addr_con,sizeof(addr_con))<0)
    {
        printf("\nBinding failed!\n");0;
        return 0;
    }
    else
    {
        printf("\nBinded.\n");
    }

    //listen
    if(listen(sockfd,BKLOG)<0)
    {
        printf("\nListening failed\n");
        return 0;
    }
    else
    {
        printf("\nListening..\n");
    }
    while(1)
    {
        //accept
        acc_sockfd = accept(sockfd,(struct sockaddr*)&addr_con,&addrlen);
        if(acc_sockfd <0)
			printf("Accept failed!\n");
		else
			printf("Connection Accepted!\n");
        
        //fork
        pid_acc = fork();

    }

    return 0;
}