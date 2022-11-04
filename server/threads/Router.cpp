//
// Created by Admin on 2022-10-31.
//

#include "Router.hpp"
#include <stdio.h>
#include <unistd.h>

#include "../servlets/UploadServlet.hpp"

Router::Router(Socket *sock) : Thread(this)
{
    request.setSocket(sock);
    request.parse();
    this->sock = sock;
}

void Router::run()
{
    // TODO route thread
    UploadServlet endPoint;

    switch (request.getMethod())
    {
    case HttpServletRequest::GET:
        endPoint.doGet(request, response);
        break;
    case HttpServletRequest::POST:
        endPoint.doPost(request, response);
        break;
    default:;
    }
    // sock->sendResponse(response.getResponse());
}

Router::~Router()
{
    // delete sock;
}
