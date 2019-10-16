#include "head.h"
int msgs[255][500];
int main(int argc, char *argv[])
{
    int status;
    int sock,i,j,sock1,k;                         
    struct sockaddr_in broadcastAddr,sendadd; 
    unsigned short broadcastPort;     
    char recvString[MAXRECVSTRING+1]; 
    int recvStringLen;
	int broadcastPer=1;                
	memset(&sendadd,0,sizeof(sendadd));

	for(i=0;i<255;i++)
		for(j=0;j<500;j++)
		msgs[i][j]=0;
    
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock<0)
     {
	perror("socket open error");
	exit(1);
     } 
        
    status=(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPer,sizeof(broadcastPer)));
	if(status<0)
	 {
        	printf("setsockopt() failed");
		 
	 }
    
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   
    broadcastAddr.sin_family = AF_INET;                 
    broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);  
    broadcastAddr.sin_port = htons(8081);      
    
    if (bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) < 0)
	{        
		perror("bind error");
		exit(1);
	}
	while(1){
    
    if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, NULL, 0)) < 0)
	{
		perror("recvfrom error");
		exit(1);
	}
	sscanf((const char*)&recvString[0],"%d",&i);
	sscanf((const char*)&recvString[5],"%d",&j);
	sscanf((const char*)&recvString[10],"%d",&k);
	if((!msgs[i][j])&&(k!=myip))
	{
	msgs[i][j]=1;
	if(i==myip)
	{
		printf("\nmessage from %d:-%s",k,(char*)&recvString[15]);
	}
	else
	{
    broadcastAddr.sin_addr.s_addr = inet_addr("192.168.1.255");  

    printf("msg broadcasted");
		sendto(sock, (const char *)recvString, sizeof(recvString),MSG_CONFIRM, (const struct sockaddr *) &broadcastAddr,sizeof(broadcastAddr)); 

    broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);  
	}
   }
	else
		printf("\n message allready handled..");
}
    close(sock);
    exit(0);
}
