#include "head.h"
void *sender() { 
    	int sockfd,i,msgno=0;
	int status; 
    	char buffer[MAXLINE],address[13];
	int myaddr=127;
   	sprintf(address,"192.168.1.");
  	struct sockaddr_in servaddr; 
	struct sockaddr_in
	{
		short sin_family;
		u_short sin_port;
	};
	sockfd=socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd<0)
	{
		perror("ERROR opening socket");
		exit(1);
	}
	memset(&servaddr, 0, sizeof(servaddr)); 
       	servaddr.sin_family = AF_INET; 
    	servaddr.sin_port = htons(PORTS);
    	servaddr.sin_addr.s_addr = inet_addr("192.168.1.255"); 
	
       	int broadcastPer = 1;
	char msgg[255];
	int to;
        status=setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPer,sizeof(broadcastPer));
        if(status<0)
	{
		fprintf(stderr, "setsockopt(broadcast) failed:");
	} 
	
	f1=fopen(fname,"r+");
	
	for(i=0;i<255;i++)
	{
		neiboursold[i]=0;
		fprintf(f1,"%c",0);
	}
	fseek(f1,0,SEEK_SET);
	while(1)
	{
	memset((char*)msgg,0x0,255);
	
	printf("\nEnter address of receiver");	
    	scanf("%d",&to);
	sprintf((char*)&msgg[0],"%d",to);
	sprintf((char*)&msgg[5],"%d",msgno++);
	sprintf((char*)&msgg[10],"%d",myaddr);
	
	printf("\n Enter msg:");
	fgets((char*)&msgg[15],240,stdin);	
	fgets((char*)&msgg[15],240,stdin);	
	printmsg(msgg);	
	sendto(sockfd, (const char *)msgg, sizeof(msgg),MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr)); 
   	
    		for(i=2;i<255;i++)
			{
			neiboursold[i]=neiboursnew[i];
			neiboursnew[i]=0;
			if(neiboursold[i])
				fprintf(f1,"1");
			else
				fprintf(f1,"0");
			}
		fflush(f1);
		fseek(f1,0,SEEK_SET);
	}
	close(sockfd); 
}


void * recever() 
{
	int status; 
    	int sockfd,i,l_addr; 
    	char buffer[MAXLINE],address[13],addr[INET_ADDRSTRLEN];
   	sprintf(address,"192.168.1.");
   	struct sockaddr_in servaddr; 
	struct sockaddr_in
          {
	       short sin_family;
	       u_short sin_port;
	   };
  

    	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd<0) 
	{ 
        	perror("Error opening socket"); 
        	exit(1); 
    	} 
    	memset(&servaddr, 0, sizeof(servaddr)); 
        servaddr.sin_family = AF_INET;
    	servaddr.sin_addr.s_addr = INADDR_ANY; 
    	servaddr.sin_port = htons(PORTC);
	
    	status=(bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)));
	if(status<0)
    	{
        	perror("bind is failed");
        	exit(1);
    	}

	while(1)
	{		
    		int n,len;
		
    		recvfrom(sockfd,(char *)buffer, MAXLINE,MSG_WAITALL, (struct sockaddr *) &servaddr,&len); 
 		inet_ntop(AF_INET,&(servaddr.sin_addr), addr, INET_ADDRSTRLEN);	 
		if(strncmp(buffer,MSG,6)==0)
		{
			strcpy(buffer,"      ");
			if((strncmp(address,addr,10)==0))
			{
				l_addr=atoi(addr+10);
				if(l_addr>0&&l_addr<255)
					neiboursnew[l_addr]=1; 
			}

		}
	}
	
	close(sockfd); 
	
}


void updatetable()
{
	pthread_t send,receive;
	int i;
	pthread_create(&send,NULL,sender,NULL);

	pthread_join(send,NULL);

}
void main()
{
	updatetable();
}
