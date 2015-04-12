#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>

int main(void)
{
 int listenfd = 0,connfd = 0,i,j;
 
 struct sockaddr_in server_addr;
 char temp,buffer[1024];  
 

 listenfd = socket(AF_INET, SOCK_STREAM, 0);  //AF_INET foe IPv4 protocol family and SOCK_STREAM for stream sockets
 //printf("socket retrieve success\n");
 
 memset(&server_addr, '0', sizeof(server_addr));  //copies the character '0' to server_addr
 memset(buffer, '0', sizeof(buffer));
    
//server settings 
 server_addr.sin_family = AF_INET;    
 server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //kernel chooses IP
 server_addr.sin_port = htons(2000);       //will be bound to port 2000

 bind(listenfd, (struct sockaddr*)&server_addr,sizeof(server_addr));  //assigns local protocol address to the socket
 						//listen() makes unconnected socket, passive i.e.kernel should queue for this socket
 if(listen(listenfd, 10) == -1){      // maximum 10 connections can be queued for this socket
     printf("Listen Failed\n");
     return -1;
 }
 printf("IP: %s\n",inet_ntoa(server_addr.sin_addr));
 //printf("Port: %d\n",ntohs(server_addr.sin_port));
    
 
 while(1)
   {
     printf("Waiting for connection...\n");
     connfd = accept(listenfd, (struct sockaddr*)NULL ,NULL); // accept awaiting request  // we don't care about the client's identity
     if(connfd < 0)
     {
	perror("Accept Failed\n");
	exit(1);
     }
     printf("Connected to a client\n");
     if(read(connfd,buffer,sizeof(buffer))<0)   //reading message from client
		{
			perror("Read Failed\n");
			exit(1);
		}
      printf("Message Received: %s\n",buffer); //Server prints the message received from client 
	j = strlen(buffer)-1; //j starts from end of buffer
      for(i=0;i<j;i++)   //reversing the message
		{
			temp=buffer[i];
			buffer[i]=buffer[j];
			buffer[j]=temp;
			j--;     //moving backwards from the end
		}
      int len=strlen(buffer);
	   	
      if (write(connfd,buffer,sizeof(buffer)) < 0)    //send back the message in reverse
	    	{
	       	 	perror("Write failed\n");
			exit(1);
	   	}
     printf("Message sent in reverse: %s\n",buffer);
     close(connfd);    //closes connection with this client
   }


 return 0;
}
