#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char str[100];
    char str2[100];
    int listen_fd, comm_fd;
    struct sockaddr_in servaddr;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(22000);
    bind(listen_fd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listen_fd, 10);

    comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
    while (1)
    {
        bzero(str, 100);
        bzero(str, 100);

        recv(comm_fd, str, 100, 0);
        printf("Client - %s", str);

        fgets(str2, 100, stdin);
        printf("Server - %s", str2);

        send(comm_fd, str2, strlen(str2), 0);
        // close(comm_fd);
    }
}