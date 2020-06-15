#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#define DEST_MAC0 0x00
#define DEST_MAC1 0x00
#define DEST_MAC2 0x00
#define DEST_MAC3 0x00
#define DEST_MAC4 0x00
#define DEST_MAC5 0x00

#define MY_DEST_MAC0 0x00
#define MY_DEST_MAC1 0x00
#define MY_DEST_MAC2 0x00
#define MY_DEST_MAC3 0x00
#define MY_DEST_MAC4 0x00
#define MY_DEST_MAC5 0x00

#define ETHER_TYPE 0x0800

#define DEFAULT_IF "eth0"


#define BUF_SIZ 1024


int main()
{
int i = 0;
    int saddr_size , data_size, daddr_size, bytes_sent;
  int saddr_size1 , data_size1, daddr_size1, bytes_sent1;
struct sockaddr_ll saddr1, daddr1;   
 struct sockaddr_ll saddr, daddr;

    unsigned char *buffer=malloc(655555);
  unsigned char *buffer1=malloc(655555);
/*htons(ETH_P_ALL)   IPPROTO_RAW
*/    int sock_raw = socket( AF_PACKET , SOCK_RAW , IPPROTO_RAW) ; //For receiving
    int sock = socket( PF_PACKET , SOCK_RAW , IPPROTO_RAW) ;            //For sending

int sock_raw1 = socket( AF_PACKET , SOCK_RAW , IPPROTO_RAW) ; //For receiving
    int sock1 = socket( PF_PACKET , SOCK_RAW , IPPROTO_RAW) ;            //For sending

    memset(&saddr, 0, sizeof(struct sockaddr_ll));
    saddr.sll_family = PF_PACKET;
    saddr.sll_protocol = htons(ETH_P_ALL);
    saddr.sll_ifindex = if_nametoindex("eth0");
    if (bind(sock_raw, (struct sockaddr*) &saddr, sizeof(saddr)) < 0) {
        perror("bind failed\n");
        close(sock_raw);
    }
	
	memset(&daddr, 0, sizeof(struct sockaddr_ll));
    daddr.sll_family = PF_PACKET;
    daddr.sll_protocol = htons(ETH_P_ALL);
    daddr.sll_ifindex = if_nametoindex("eth1");
    if (bind(sock, (struct sockaddr*) &daddr, sizeof(daddr)) < 0) {
      perror("bind failed\n");
      close(sock);
    }

	memset(&saddr1, 1, sizeof(struct sockaddr_ll));
    saddr1.sll_family = PF_PACKET;
    saddr1.sll_protocol = htons(ETH_P_ALL);
    saddr1.sll_ifindex = if_nametoindex("eth1");
    if (bind(sock_raw1, (struct sockaddr*) &saddr1, sizeof(saddr1)) < 0) {
        perror("bind failed \n");
        close(sock_raw1);
    }

	memset(&daddr1, 1, sizeof(struct sockaddr_ll));
    daddr1.sll_family = PF_PACKET;
    daddr1.sll_protocol = htons(ETH_P_ALL);
    daddr1.sll_ifindex = if_nametoindex("eth0");
    if (bind(sock1, (struct sockaddr*) &daddr1, sizeof(daddr1)) < 0) {
      perror("bind failed \n");
      close(sock1);
    } 

	struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "eth1");
    if (setsockopt(sock, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        perror("bind to eth0");
        } 

	struct ifreq ifr1;
    memset(&ifr1, 0, sizeof(ifr1));
    snprintf(ifr1.ifr_name, sizeof(ifr1.ifr_name), "eth0");
    if (setsockopt(sock1, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr1, sizeof(ifr1)) < 0) {
        perror("bind to eth1");
        } 

	saddr_size = sizeof (struct sockaddr);
        daddr_size = sizeof (struct sockaddr);
	saddr_size1 = sizeof (struct sockaddr);
        daddr_size1 = sizeof (struct sockaddr);

	while(1)
    { 
        //Receive a packet
        data_size = recvfrom(sock_raw , buffer , 655361 , 0 ,(struct sockaddr *) &saddr , (socklen_t*)&saddr_size);

        if(data_size <0 )
        {
            printf("Recvfrom error , failed to get packets\n");
            return 1;
        }
        else{ 

		printf("Received %d bytes eth0\n",data_size);

	if(buffer[11] == buffer1[11] && buffer[12] == buffer1[12] && buffer[13] == buffer1[13] && buffer[10] == buffer1[10] ){}
	else{

	bytes_sent=write(sock,buffer,data_size);
        printf("Sent %d bytes eth0 -> eth1 \n",bytes_sent);

	int g = 0;
	for (g=0; g<data_size; g++) printf("%02x:", buffer[g]);
   
	printf("\n");

}}

	data_size1 = recvfrom(sock_raw1 , buffer1 , 655361 , 0 ,(struct sockaddr *) &saddr1 , (socklen_t*)&saddr_size1);


        if(data_size1<0)
        {
            printf("Recvfrom error , failed to get packets\n");
            
        }1] == buffer1[11] && buffer[12] == buffer1[12] && buffer[13] == buffer1[13] ){}
	else{printf("Received %d  bytes eth1 \n",data_size1); }
    
	if(buffer[10] == buffer1[10] && buffer[1
	else{ 

	bytes_sent1=write(sock1,buffer1,data_size1);
        printf("Sent %d bytes eth1-> eth0\n",bytes_sent1);
        
	int f=0;
	for(f=0;f<data_size1;f++){
	printf("%02x:",buffer1[f]);
}}   } 
	close(sock_raw1);
    close(sock_raw);
    return 0;
}
