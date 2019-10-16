#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include<arpa/inet.h>
#include<pthread.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/mman.h>
#define PORTS    8081
#define MAXLINE 8 
#define MSEC 5000
#define SEC  5
#define MSG "ATAMAM"
#define my_addr 20     
#define fname "neibours"
int neold[255];  
int nenew[255];
FILE *f1;
void * table_val()
{
	f1=fopen(fname,"w");
	if(f1==NULL)
	 
	for(int i=0;i<255;i++)
	{
		neold[i]=0;  
		nenew[i]=0;
		fprintf(f1,"%c",0X0);
	}
	fseek(f1,0,SEEK_SET);
	fflush(f1);
	while(1)
	{
		for(int i=0;i<255;i++)
		  {
			neold[i]=nenew[i];
			nenew[i]=0;
			if(neold[i])
			 {
				fprintf(f1,"%c",0x1);
			 }
			else
			 {
				fprintf(f1,"%c",0x1);
			 }
		    }
		  fflush(f1);
		  fseek(f1,0,SEEK_SET);
		  sleep(5);
		  
	}

}

