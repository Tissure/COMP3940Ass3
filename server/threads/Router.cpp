//
// Created by Admin on 2022-10-31.
//

#include "Router.hpp"
#include <stdio.h>
#include <unistd.h>

Router::Router(Socket *sock): Thread(this) {
    this->sock = sock;
}

void Router::run(){
    // TODO route thread
    for (int i=0; i < 10; i++) {
        printf("%s\n", "Routing");
        sleep(1);
    }
    delete sock;
}

Router::~Router() {}
