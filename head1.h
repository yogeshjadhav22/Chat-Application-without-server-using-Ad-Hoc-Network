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
#include<sys/mman.h>
#define PORTS    8081
#define PORTC    8080
#define MAXLINE 8 
#define MSEC 5000
#define SEC  5
#define MSG "ATAMAM"
#define fname "neibours"
#define myip 20
#define MAXRECVSTRING 255 

FILE *f1;
int neiboursold[253];  
int neiboursnew[253];
void printmsg(char *m)
{	int i;
	for(i=0;i<255;i++)
	{
		printf("%c",m[i]);
	}
}
 
