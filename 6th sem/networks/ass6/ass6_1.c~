#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h>
    
#define PORT 15050 
#define BUF_SIZE 1025
#define PEND_LIST_SIZE 20
#define MSG_LIST_SIZE 1000

struct msgNode
{
    int valid;
    char src_ip[BUF_SIZE];
    char dest_ip[BUF_SIZE];
    char msg[BUF_SIZE];
};

struct msgNode *msgList;

void clearBuf(char *b)
{
	int i;
	for(i=0;i<BUF_SIZE;i++)
		b[i]='\0';
}

int process_buf(char *buffer, char *src_ip)
{
	char ip_addr[BUF_SIZE], msg[BUF_SIZE];
	int i,j,k;
	
    printf("\n------------------------\n");
    printf("Src IP: %s\n",src_ip);

    if(buffer[0]==(char)0)
    {
        clearBuf(buffer);
        //client is asking for messages
        printf("Client is asking for messages\n");
        for(i=0; i<MSG_LIST_SIZE; i++)
        {
            if(msgList[i].valid==1 && strcmp(src_ip,msgList[i].dest_ip)==0)
            {
                printf("Got a message for him\n");
                printf("\nS:%s D:%s M:%s\n",msgList[i].src_ip,msgList[i].dest_ip,msgList[i].msg);
                buffer[0]=(char)strlen(msgList[i].src_ip);
                printf("\nBuff: %d\n",buffer[0]);

                for(j=1;j<=(int)buffer[0];j++)
                {
                    buffer[j] = msgList[i].src_ip[j-1];
                    printf("HH%d: %c\n",j,buffer[j]);
                }

                for(k=0;k<=strlen(msgList[i].msg);k++,j++)
                {
                    buffer[j] = msgList[i].msg[k];
                    printf("MM: %c\n",buffer[j]);
                }

                msgList[i].valid=0;
                printf("\n------------------------\n");
                return 1; 
            }
        }
        //if no msgs are there
        buffer[0]=(char)0;
        printf("\n------------------------\n");
        return 1;
    }
    else
    {
        printf("Msg Received\n");
        //fill up ip address
        for(i=1; i<=(int)buffer[0]; i++)
        {
            ip_addr[i-1] = buffer[i];
            printf("H: %d: [%c]\n",i,ip_addr[i-1]);
        }
        ip_addr[i-1] = '\0';
        printf("IP to send: %s\n",ip_addr);

        //fill up msg
        for(j=0; buffer[i-1]!='\0'; i++,j++)
        {
            msg[j] = buffer[i];
            printf("M: %d: [%c]\n",i,msg[j]);
        }

        printf("MSG to store: %s\n",msg);

        for(i=0; i<MSG_LIST_SIZE; i++)
        {
            if(msgList[i].valid==0)
            {
                msgList[i].valid=1;
                strcpy(msgList[i].src_ip, src_ip);
                strcpy(msgList[i].msg,msg);
                strcpy(msgList[i].dest_ip,ip_addr);
                break;
            }
        }
        printf("\n------------------------\n");
        return 0;
    }
    
}



int main()  
{  
    
    int master_socket , addrlen , new_socket , client_socket[PEND_LIST_SIZE], opt=1;  
    int max_sd, max_clients = PEND_LIST_SIZE , activity, i , valread , sd, b_len;  
    struct sockaddr_in address;
    char buffer[BUF_SIZE];  
    fd_set readfds;
    
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );
    addrlen = sizeof(address);
    
    //initialize msglist
    msgList = (struct msgNode*)malloc(MSG_LIST_SIZE*sizeof(struct msgNode));
    for(i=0; i<MSG_LIST_SIZE; i++)
        msgList[i].valid=0;

    //initialise all client_socket[] to 0 so not checked 
    for (i = 0; i < max_clients; i++)
        client_socket[i] = 0;
        
    //create a master socket 
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
    
    //set master socket to allow multiple connections
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }
    
    //bind
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
        
    //listen
    if (listen(master_socket, PEND_LIST_SIZE) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
        
    //accept the incoming connection
    puts("Waiting for connections ...");  
        
    while(1)  
    {  
        //clear the socket set 
        FD_ZERO(&readfds);
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
            
        //add child sockets to set 
        for ( i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
    
        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
      
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
            
        //If something happened on the master socket , then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
            
            //inform user of socket number - used in send and receive commands 
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
          
            
            //add new socket to array of sockets 
            for (i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = new_socket;  
                    printf("Adding to list of sockets as %d\n" , i);  
                        
                    break;  
                }  
            }  
        }
        
        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)  
        {  
            sd = client_socket[i];  
                
            if (FD_ISSET( sd , &readfds))  
            {
            	clearBuf(buffer);
                //Check if it was for closing , and also read the incoming message
                if ((valread = read( sd , buffer, BUF_SIZE-1)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n" ,  inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                        
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    client_socket[i] = 0;  
                }
                else
                {
                	//############Process the message######################
                    getpeername(sd , (struct sockaddr*)&address , (socklen_t*)&addrlen);
                    if(process_buf(buffer,inet_ntoa(address.sin_addr)))
                    {
                    	if(strlen(buffer)==0)
                    		b_len=10;
                    	else
    						b_len=strlen(buffer);
                        send(sd , buffer , b_len+1 , 0 );
                    } 
                }  
            }  
        }  
    }  
        
    return 0;  
} 
