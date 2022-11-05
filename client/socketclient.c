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

    strcpy(buf, "POST / HTTP/1.1\r\n"
                "Host: localhost:8000\r\n"
                "User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux i686; rv:29.0) Gecko/20100101 Firefox/29.0\r\n"
                "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
                "Accept-Language: en-US,en;q=0.5\r\n"
                "Accept-Encoding: gzip, deflate\r\n"
                "Cookie: __atuvc=34%7C7; permanent=0; _gitlab_session=226ad8a0be43681acf38c2fab9497240; __profilin=p%3Dt; request_method=GET\r\n"
                "Connection: keep-alive\r\n"
                "Content-Type: multipart/form-data; boundary=---------------------------9051914041544843365972754266\r\n"
                "Content-Length: 554\r\n\r\n"
                "-----------------------------9051914041544843365972754266"
                "Content-Disposition: form-data; name=\"text\""
                "text default"
                "-----------------------------9051914041544843365972754266"
                "Content-Disposition: form-data; name=\"file1\"; filename=\"a.txt\""
                "Content-Type: text/plain"
                "Content of a.txt."
                "-----------------------------9051914041544843365972754266"
                "Content-Disposition: form-data; name=\"file2\"; filename=\"a.html\""
                "Content-Type: text/html");

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
