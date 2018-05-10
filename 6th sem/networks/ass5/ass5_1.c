#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAC_LEN 6
#define WOL_PKT_LEN 102
#define BCAST_ADDR "10.24.255.255"
#define WOL_PORT 8080

void wolPacketFillup(unsigned char *pkt, unsigned char *mac)
{
	int i,j, l;
	
	//fillup 1st 6 bytes with ff
	for(l=0; l<6; l++)
	{
		pkt[l]=0xFF;
	}
	
	//copy 16 times
	for(i=0;i<16;i++)
	{
		for(j=0;j<MAC_LEN;j++)
		{
			pkt[l] = mac[j];
			l++;
		}
	}
	
	printf("\nFilled up magic packet\n");
}

int main()
{
	unsigned char wol_packet[WOL_PKT_LEN];
	unsigned char mac_addr[MAC_LEN]={0x00,0x00,0x00,0x00,0x00,0x00};
	int wol_sockfd;
	struct sockaddr_in wolDestAddr, wolServer;
	int bcast=1;
	
	printf("\nEnter MAC address: ");
	//scanf("%x:%x:%x:%x:%x:%x",&mac_addr[0],&mac_addr[1],&mac_addr[2],&mac_addr[3],&mac_addr[4],&mac_addr[5]);
	mac_addr[0] = 0x8C;
	mac_addr[1] = 0xdC;
	mac_addr[2] = 0xd4;
	mac_addr[3] = 0x33;
	mac_addr[4] = 0x46;
	mac_addr[5] = 0x9b;
	printf("\nThe Entered MAC is : %x:%x:%x:%x:%x:%x\n",mac_addr[0],mac_addr[1],mac_addr[2],mac_addr[3],mac_addr[4],mac_addr[5]);
	
	
	//opening connection-------------------------------------------------------
	//open socket
	wol_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(wol_sockfd<0)
	{
		printf("\nSocket file descriptor not received!!\n");
		return 0;
	}
	else
		printf("\nSocket file descriptor %d received\n",wol_sockfd);
	
	//set socket options
	if(setsockopt(wol_sockfd, SOL_SOCKET, SO_BROADCAST, &bcast, sizeof(bcast))<0)
		printf("\nSet options error");
	
	//fillup server address
	wolServer.sin_family = AF_INET;
  	wolServer.sin_port = 0;
  	wolServer.sin_addr.s_addr = INADDR_ANY;
  	
  	//bind server
  	bind(wol_sockfd, (struct sockaddr*)&wolServer, sizeof(wolServer));
  	
  	//fillup client address
  	wolDestAddr.sin_family = AF_INET;
  	wolDestAddr.sin_port = htons(WOL_PORT);
  	wolDestAddr.sin_addr.s_addr = inet_addr("10.24.255.255");
	//opening connection-------------------------------------------------------
	
	//fillup the packet
	wolPacketFillup(wol_packet, mac_addr);
	
	//send the packet
	if(sendto(wol_sockfd, &wol_packet, sizeof(wol_packet), 0, (struct sockaddr*)&wolDestAddr, sizeof(wolDestAddr))<0)
		printf("\nMagic packet sending failed!\n");
	else
		printf("\nMagic packet sent successfully\n");
	
	
	return 0;
}
