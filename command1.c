#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_CMN_LEN 100
#define max_limit 20
#define _GNU_SOURCE
char cmd[MAX_CMN_LEN] = "", **p;

char string[1000]={"sudo iwconfig wlp6s0 channel 1 essid yogi mode ad-hoc"}, sub[1000];
int p1, l, c = 0;

void  parse(char *line, char **argv)
{
     while (*line != '\0') {       
          while (*line == ' ' || *line == '\t' || *line == '\n')
               *line++ = '\0';     
          *argv++ = line;          
          while (*line != '\0' && *line != ' ' && 
                 *line != '\t' && *line != '\n') 
               line++;             
     }
     *argv = '\0';                 
}

void  execute(char **argv)
{
     pid_t  pid;
     int    status;

     if ((pid = fork()) < 0) {     
          printf("*** ERROR: forking child process failed\n");
          exit(1);
     }
     else if (pid == 0) {          
          if (execvp(*argv, argv) < 0) {     
               printf("*** ERROR: exec failed\n");
               exit(1);
          }
     }
     else {                                  
          while (wait(&status) != pid)       
               ;
     }
}


//int main(int argc, char *argv[])
int main(void)
{
	int i=0;
	int ch;
	char line1[]={"rfkill unblock wifi"}; 
	char line2[]={"sudo ifconfig wlp6s0 down"};
	char line3[]={"sudo iwconfig wlp6s0 mode ad-hoc"};
	char line4[]={"sudo iwconfig wlp6s0 channel 1 essid yogi mode ad-hoc"};
	char line5[]={"sudo ifconfig wlp6s0 up"};
	char line6[]={"sudo ifconfig wlp6s0 192.168.1.127 netmask 255.255.255.0"};
	char line8[]={"ping 192.168.1.229"};
	char line9[]={"sudo arp-scan --interface=wlp6s0 --localnet"};
	char line11[]={"exit"}	;

        char  *argvp[64];
	for(i=1;i<12;i++)
	   {
	      ch=i;
		switch (ch)
		 {
		    case 1:
			
			    
			   parse(line1, argvp);
			         
                 	   if (strcmp(argvp[0], "exit") == 0)  
                 	   exit(0);                         
                 	   execute(argvp); 
	                
		    break;
		    case 2:
			   
			   parse(line2, argvp);
			            
                 	   if (strcmp(argvp[0], "exit") == 0) 
                 	   exit(0);            
                 	   execute(argvp);  
		    break;
		    case 3:
			 
			  
			   parse(line3, argvp);   
			          
                 	   if (strcmp(argvp[0], "exit") == 0)  
                 	   exit(0);            
                 	   execute(argvp); 	
					
				   
		    break;
		    case 4:
			   
		
			   parse(line4, argvp);  
			          
                 	   if (strcmp(argvp[0], "exit") == 0)  
                 	   exit(0);            
                 	   execute(argvp); 
			   
		    break;
		    case 5:
			  
			/*
			   parse(line5, argvp);
			           
                 	   if (strcmp(argvp[0], "exit") == 0)  
                 	   exit(0);            
                 	   execute(argvp);
			*/
			   //system("rfkill unblock wifi"); 
			   //system("sudo ifconfig wlp6s0 up");
		    break;
		    case 6:
			  
			   
			   parse(line6, argvp);  
			         
                 	   if (strcmp(argvp[0], "exit") == 0)  
                 	   exit(0);            
                 	   execute(argvp);
			 
			
		    break;
		    case 7:
			      
			/*
    			if (argc < 2) //no command specified
    			{
        		fprintf(stderr, "Usage: ./program_name terminal_command ...");
        		exit(EXIT_FAILURE);
   			 }
    			else
    			{
        			strcat(cmd, argv[1]);
        			for (p = &argv[2]; *p; p++)
        			{
          		        strcat(cmd, " ");
                                strcat(cmd, *p);
                                }
			} system(cmd);
			*/
			
			 parse(line8, argvp);       
                 	   if (strcmp(argvp[0], "exit") == 0)  
                 	   exit(0);            
                 	   execute(argvp); 
			
			  
		    break;
		    
		    case 8:
			   		
			     
		    break;
		    case 9:
			     
		  	 
			   parse(line9, argvp);       
                 	   if (strcmp(argvp[0], "exit") == 0)  
                 	   exit(0);            
                 	   execute(argvp); 
			
			  
		    break;
		    case 10:
			   
			 /*  
			   p1=37;
			   l=5;
   			   while (c < l) {
          				sub[c] = string[p1+c-1];
          				c++;
       					}
       					sub[c] = '\0';
     					printf("Network Name is ::\"%s\"\n", sub);
				
			*/
		    
		    case 11:		
				   
				
				    parse(line11, argvp);       
                 	            if (strcmp(argvp[0], "exit") == 0)  
                 	            exit(0);            
                 	  	    execute(argvp); 
				
				  
		    break;
		    			
		    	
		 }
	     }
		
}


