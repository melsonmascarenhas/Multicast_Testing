#include<stdio.h>	
#include<string.h> 
#include<sys/socket.h>	
#include<stdlib.h> 
#include<errno.h>
#include<netinet/udp.h>	
#include<netinet/ip.h>	
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 3000
int main (void)
{
	struct sockaddr_in sin;
	int s = socket (AF_INET, SOCK_DGRAM, 0);
	
	if(s < 0)
	{
		//socket creation failed, may be because of non-root privileges
		perror("Failed to create raw socket");
		exit(1);
	}
	
char buffer[4096] , source_ip[32] , *data , *pseudogram;
	

	memset (buffer, 0, 4096);
	struct sockaddr_in src_ip,des_ip;
	
	src_ip.sin_family = 2;
	src_ip.sin_port = htons(PORT);
	src_ip.sin_addr.s_addr = htonl(INADDR_ANY);
	


	if( bind(s , (struct sockaddr*)&src_ip, sizeof(src_ip) )<0)
	{
		  perror("Bind failed");
        close(s);
        exit(EXIT_FAILURE);
	}

//Multicast group
struct ip_mreq mreq;

mreq.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
mreq.imr_interface.s_addr = htonl(INADDR_ANY);

 if(setsockopt(s,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&mreq,sizeof(mreq))<0){
    perror("setsockopt error");
    return 1;
}
    while(1)

    {
        socklen_t addr_len=sizeof(des_ip);
        int n = recvfrom(s, buffer, 4096, 0, (struct sockaddr*)&des_ip,&addr_len);
        if(n<0){
            perror("recvfrom error");
            close(s);
            exit(EXIT_FAILURE);
        }
        // char *payload = (char *)(buffer + sizeof(struct iphdr) + sizeof(struct udphdr));
        // int payload_size = n - (sizeof(struct iphdr) + sizeof(struct udphdr));
        if(n>0){
            buffer[n]='\0';
            printf("Received from %s:%s\n", inet_ntoa(des_ip.sin_addr), buffer);
            
        }
        else
        {
            printf("No message found in the payload\n");
        }
    }
    close(s);
    return 0;


}