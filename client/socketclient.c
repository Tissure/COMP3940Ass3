#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int sock;
    struct sockaddr_in server;
    int msgsock;
    char buf[1024];
    struct hostent *hp;
    char *host = "127.0.0.1";
    int rval;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("opening stream socket");
    }

    bzero(&server, sizeof(server));
    hp = gethostbyname("localhost");
    bcopy((char *)hp->h_addr, (char *)&server.sin_addr, hp->h_length);
    server.sin_family = AF_INET;
    server.sin_port = 8888;

    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("connecting");
    }

    strcpy(buf, "GET /somedir/page.html HTTP/1.1\r\nHOST:www.sameschool.edu\r\nConnection:close\r\nUser-agent:Mozzilla/4.0\r\nAccept Language: fr\r\nContent-Type:multipart/form-data; boundry=ABCD1234\r\n");

    if ((rval = write(sock, buf, 1024)) < 0)
    {
        perror("writing socket");
    }

    printf("%s\n", "Waiting response");
    while ((rval = read(sock, buf, 1024)) > 0)
    {
        printf("Response %s\n", buf);
    }
    close(sock);
    return 0;
}
