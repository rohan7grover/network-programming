#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
	
#define PORT 1234
	
int main() {
	int sockfd;
	char *hello = "Hello from Jashan";
	struct sockaddr_in broadaddr;
	
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&broadaddr, 0, sizeof(broadaddr));
		
    int opt=1;

    setsockopt(sockfd,SOL_SOCKET,SO_BROADCAST,(const void *)&opt,(socklen_t)sizeof(opt));

	broadaddr.sin_family = AF_INET;
	broadaddr.sin_port = htons(PORT);
	broadaddr.sin_addr.s_addr = inet_addr("172.16.119.255");

	sendto(sockfd, (const char *)hello, strlen(hello),0, (const struct sockaddr *) &broadaddr,sizeof(broadaddr));

	printf("Hello message sent.\n");

	close(sockfd);

	return 0;
}
