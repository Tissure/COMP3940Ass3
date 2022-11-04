//
// Created by Admin on 2022-10-31.
//

#include "Router.hpp"
#include <stdio.h>
#include <unistd.h>

#include "../servlets/Http/HttpServletRequest.hpp"
#include "../servlets/Http/HttpServletResponse.hpp"
#include "../servlets/UploadServlet.hpp"

#include <iostream>

using namespace std;

Router::Router(Socket *sock): Thread(this) {
    this->sock = sock;
}

void Router::run(){
    // TODO route thread
        HttpServletRequest httpRequest{sock->getRequest()};
        HttpServletResponse httpResponse;

        UploadServlet endPoint;

        switch(httpRequest.getMethod()){
            case HttpServletRequest::GET:
                endPoint.doGet(httpRequest, httpResponse);
                break;
            case HttpServletRequest::POST:
                endPoint.doPost(httpRequest, httpResponse);
                break;
            default:
                endPoint.doGet(httpRequest, httpResponse);
        }
        sock->sendResponse(httpResponse.getResponse());
        //
}

Router::~Router() {
    delete sock;
}
