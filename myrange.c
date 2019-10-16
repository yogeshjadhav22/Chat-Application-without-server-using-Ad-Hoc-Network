#include "head.h"
char address[13];
int neold[255];  
int nenew[255];
void * recever()
{
	int sockfd,l_addr;
	int status;
	pthread_t update;
	pthread_create(&update,NULL,table_val,NULL);
    	char buffer[MAXLINE],address[13],addr[INET_ADDRSTRLEN];
   	sprintf(address,"192.168.1.");
	struct sockaddr_in servaddr;
	  struct sockaddr_in
          {
	       short sin_family;
	       u_short sin_port;
	   };
	  sockfd=socket(AF_INET,SOCK_DGRAM,0);
	 if(sockfd<0)
	   {
		perror("ERROR opening socket");
		exit(1);
	   }
	  memset(&servaddr, 0, sizeof(servaddr)); 
	  servaddr.sin_family = AF_INET; 
    	  servaddr.sin_port = htons(PORTS);
    	  servaddr.sin_addr.s_addr =  INADDR_ANY; 
	  status=(bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)));
	  if(status<0)
	  {
		perror("bind is failed:");
		exit(1);
	  }
	 while(1)
	 {
		int len,n;
		recvfrom(sockfd,(char *)buffer, MAXLINE,MSG_WAITALL, (struct sockaddr *) &servaddr,&len);
		inet_ntop(AF_INET,&(servaddr.sin_addr), addr, INET_ADDRSTRLEN);
		strcpy(buffer,"      ");
			if((strncmp(address,addr,10)==0))
			{
				l_addr=atoi(addr+10);
				fprintf(stdout,"\nonline:: %d",l_addr);
				if(l_addr>0&&l_addr<255&&l_addr!=my_addr)
					nenew[l_addr]=1; 
			}
	 }
	pthread_join(update,NULL);
     	close(sockfd); 
}

void *sender()
{
	int sockfd;
        int status;
	char address[13];
        int brodcastpre=1;
	sprintf(address,"192.168.1.");
	
	struct sockaddr_in servaddr;
	  struct sockaddr_in
          {
	       short sin_family;
	       u_short sin_port;
		
	  };
	 sockfd= socket(AF_INET,SOCK_DGRAM,0);
	 if(sockfd<0)
	   {
		perror("ERROR opening socket");
		exit(1);
	   }
	  memset(&servaddr, 0, sizeof(servaddr)); 
	  
    	servaddr.sin_family = AF_INET; 
    	servaddr.sin_port = htons(PORTS);
    	servaddr.sin_addr.s_addr = inet_addr("192.168.1.255"); 
	status=setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (void *) &brodcastpre,sizeof(brodcastpre));
	if(status<0)
	 {
		 fprintf(stderr, "setsockopt(broadcast) failed:");
	 }
	while(1)
	{
		
    		sendto(sockfd, (const char *)MSG, sizeof(MSG),MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
   		sleep(3);
	}
	close(sockfd);
}

int main()
{
	int p1,p2;
	char c;
	if((p1=fork())==0)
	{
		
		recever();
	}
	else
	{
		if((p2=fork())==0)
		 {
			sender();
		 }
		  printf("\n enter the exit ");
		  scanf("%c",&c);
		  kill(p1,SIGKILL);
		  kill(p2,SIGKILL);
		  printf("\n exited successfully..");
	}	
}

