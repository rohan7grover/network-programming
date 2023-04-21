#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT 1234
#define MAXLINE 1024
	
int main() {
	int sockfd;
	char buffer[MAXLINE];
	struct sockaddr_in addr , senderaddr;
		
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&addr, 0, sizeof(addr));
    memset(&addr, 0, sizeof(senderaddr));
		
	addr.sin_family = AF_INET; 
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(PORT);
		
	if ( bind(sockfd, (const struct sockaddr *)&addr,
			sizeof(addr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		
	int len, n;
	
	len = sizeof(senderaddr); 
	
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, ( struct sockaddr *) &senderaddr,(socklen_t *)&len);
	buffer[n] = '\0';
	printf("Message Received : %s\n", buffer);

    close(sockfd);
		
	return 0;
}
