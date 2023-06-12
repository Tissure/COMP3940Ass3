//
// Created by Admin on 2022-10-31.
//
#pragma once

#include "Thread.h"
#include "../sockets/Socket.h"
#include "../servlets/HttpServletRequest.hpp"
#include "../servlets/HttpServletResponse.hpp"

class Router : public Thread
{
private:
    HttpServletRequest request;
    HttpServletResponse response;
    Socket *sock;

public:
    Router(Socket *sock);
    void run() override;
    ~Router();
};
