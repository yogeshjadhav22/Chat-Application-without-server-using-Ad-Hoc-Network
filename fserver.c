#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#define BUFFERT 5000		
#ifndef __linux__
#endif
int create_server_socket (int port);

struct sockaddr_in sock_serv,clt;

int main (int argc, char**argv){
    
	int fd, sfd;
    
	char buf[BUFFERT];
	setvbuf(stdout, buf, _IOFBF, sizeof buf);
	off_t  n; 
    int count=0;
	char filename[200];
    unsigned int l=sizeof(struct sockaddr_in);
	
    
    
	if (argc != 2)
    {
		fprintf(stdout,"Error usage : %s <port_serv>\n",argv[0]);
		return EXIT_FAILURE;
	}
    
    sfd = create_server_socket(atoi(argv[1]));
    
	
	bzero(filename,256);

	sprintf(filename,"Vedio.%s","mp4");
	printf("Creating the output file : %s\n",filename);
    if((fd=open(filename,O_CREAT|O_WRONLY|O_APPEND,0644))==-1)
    {
        fprintf(stdout,"open fail");
            return EXIT_FAILURE;
    }

    
	
	bzero(&buf,BUFFERT);
    n=recvfrom(sfd,&buf,BUFFERT,0,(struct sockaddr *)&clt,&l);
	while(n)
      {
		
		if(n==-1)
        {
			fprintf(stdout,"read fails");
			return EXIT_FAILURE;
		}
		count+=n;
		write(fd,buf,n);
        fprintf(stdout,"No of Bits Sending=\t%d\n",count);
       
		bzero(buf,BUFFERT);
        n=recvfrom(sfd,&buf,BUFFERT,0,(struct sockaddr *)&clt,&l);
        if(n==0)
        {
            exit(0);
        }
	}
    
    close(sfd);
    close(fd);
	return EXIT_SUCCESS;
}
int create_server_socket (int port)
    {
    int l;
	int sfd;
    
	sfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sfd == -1)
    {
        fprintf(stdout,"socket fail");
        return EXIT_FAILURE;
	}
    
    l=sizeof(struct sockaddr_in);
	bzero(&sock_serv,l);
	
	sock_serv.sin_family=AF_INET;
	sock_serv.sin_port=htons(port);
	sock_serv.sin_addr.s_addr=htonl(INADDR_ANY);
    
	if(bind(sfd,(struct sockaddr*)&sock_serv,l)==-1)
    {
		fprintf(stdout,"bind fail");
		return EXIT_FAILURE;
	}
    
    return sfd;
}


			
