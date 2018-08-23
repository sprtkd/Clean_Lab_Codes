#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT_NO 15050
#define BACKLOG_VAL 20
#define SEND_RECV_FLAG 0
#define NET_BUF_SIZE 1024

void clearBuf(char *buf)
{
    int i;
    for(i=0; i<NET_BUF_SIZE; i++)
    {
        buf[i] = '\0';
    }
}

void printDebug(char *str, int val, int flag)
{
    if(val<0)
    {
        printf("%s failed!\n",str);
        exit(0);
    }
    else
    {
        if(flag)
            printf("%s %d success!\n", str,val);
        else
            printf("%s success!\n", str);
    }
}

int process_buf(char *buf)
{
    printf("String received: %s\n",buf);
}

int main()
{
    int sockfd,temp, acc_sockfd, addrlen;
    struct sockaddr_in addr_con;
    char net_buf[NET_BUF_SIZE];


    addr_con.sin_family = AF_INET;
    addr_con.sin_port = htons(PORT_NO);
    addr_con.sin_addr.s_addr = INADDR_ANY;
    addrlen = sizeof(addr_con);

    //socket
    sockfd = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
    printDebug("Socket open", sockfd, 1);

    //bind
    temp = bind(sockfd, (struct sockaddr*)&addr_con, sizeof(addr_con));
    printDebug("Bind", temp,0);

    //listen
    temp = listen(sockfd, BACKLOG_VAL);
    printDebug("Listen", temp,0);

    while(1)
    {
        printf("Waiting for connection..\n");

        //accept
        acc_sockfd = accept(sockfd,(struct sockaddr*)&addr_con, &addrlen);
        printDebug("Accepted socket open", acc_sockfd, 1);

        if(fork()==0)
        {
            close(sockfd);
            while(1)
            {
                clearBuf(net_buf);

                //recv
                temp = recv(acc_sockfd, net_buf, NET_BUF_SIZE, SEND_RECV_FLAG);
                printDebug("Received", temp, 1);
                if(temp==0)
                    break;

                //process
                process_buf(net_buf);

                //send
                temp = send(acc_sockfd, net_buf, strlen(net_buf), SEND_RECV_FLAG);
                printDebug("Sent", temp, 1);
            }
            exit(0);
            
        }
        else
            close(acc_sockfd);
    }
    

    return 0;
}