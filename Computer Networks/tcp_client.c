#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int sockfd,i,size=0;
	struct sockaddr_in server;
	struct sockaddr_in client;
	struct hostent *host;
	char buff[1024];
	char *temp;

	client.sin_family=AF_INET;   //client settings
	client.sin_addr.s_addr=INADDR_ANY; 
	client.sin_port=htons(1999); 

	sockfd = socket(AF_INET, SOCK_STREAM, 0);  //create socket
	if(sockfd < 0)	
	{
		perror("Socket Failed\n");
		exit(1);
	}
	if(bind(sockfd,(struct sockaddr *)&client,sizeof(client))<0) //binding the settings to client socket
	{
		perror("Bind Failed\n");
		close(sockfd);
		exit(1);
	}
	if(argc<4)   //checking validity of input
	{
		perror("Invalid input\n");
		close(sockfd);
		exit(1);
	}
	server.sin_family = AF_INET;  //server settings
	host = gethostbyname (argv[1]);
	if(host == 0)
	{
		perror("gethostbyname failed\n");
		close(sockfd);
		exit(1);
	}
	memcpy(&server.sin_addr, host->h_addr,host->h_length);   //copying IP to sin_addr
	server.sin_port = htons(atoi(argv[2]));
	//printf("Port: %d\n",ntohs(server.sin_port));
	if(connect(sockfd,(struct sockaddr *) &server,sizeof(server))<0)    //establishing connection with server
	{
		perror("Connect Failed\n");
		close(sockfd);
		exit(1);
	}
        temp=malloc(1024);
	for(i=3;i<argc;i++)
	{
		strcat(temp,argv[i]);
		if(argc>(i+1))
			strcat(temp," ");
	}
	strcpy(buff,temp);
	if(write(sockfd, buff , sizeof(buff)) <0)   // sending message to server
	{
		perror("Write Failed\n");
		close(sockfd);
		exit(1);
	}

	printf("Message sent: %s\n", buff);
	memset(buff, '0', sizeof(buff));      //reset the buffer

   	if (read(sockfd,buff,sizeof(buff)) < 0)           //reading message from server
    	{
         	perror("Read Failed");
         	exit(1);
    	}
    	printf("Response from server: %s\n",buff);  //printing the message
	
	printf("Closing connection.....\n\n");
	close(sockfd); //Client closes the connection
	return 0;
}
