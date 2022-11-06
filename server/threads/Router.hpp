//
// Created by Admin on 2022-10-31.
//
#pragma once

#include "Thread.h"
#include "../sockets/Socket.h"

class Router : public Thread{
private:
    Socket * sock;
public:
    Router(Socket *sock);
    void run() override;
    ~Router();
};
