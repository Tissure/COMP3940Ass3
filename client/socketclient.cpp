#include <sys/socket.h>
#include <sys/types.h>
#include <resolv.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "FileUploadMenu.hpp"

void uploadFile(int);

int main() {
    int sock;
    struct sockaddr_in server;
    struct hostent *hp;
    char *host = "127.0.0.1";


    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("opening stream socket");
    }

    bzero(&server, sizeof(server));
    hp = gethostbyname("localhost");
    bcopy((char *) hp->h_addr, (char *) &server.sin_addr, hp->h_length);
    server.sin_family = AF_INET;
    server.sin_port = 8888;

    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("connecting");
    }

    uploadFile(sock);

    close(sock);
    return 0;
}

void uploadFile(int sock){
    int rval;
    char buf[1024];

    bool userInput = 0;
    FileUploadMenu menu;
    do {
        cout << "Upload File:" << endl;
        menu.buildRequest(menu.getDataFromUser());
        //Send HTTP request
        strcpy(buf, menu.getRequestString().c_str());
        if ((rval = write(sock, buf, 1024)) < 0) {
            perror("writing socket");
        }
        // Get response
        printf("%s\n", "Waiting response");
        while ((rval = read(sock, buf, 1024)) > 0) {
            printf("Response %s\n", buf);
//        menu.handleResponse(buf);
        }
        cout << "Would you like to upload another file? Y(1)/N(0)" << endl;
        cin >> userInput;
    }while(userInput == 1);

}


