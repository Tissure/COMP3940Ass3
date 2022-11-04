//
// Created by Admin on 2022-10-31.
//

#pragma once

using namespace std;

class HttpServletRequest {
public:
    enum Method{
        GET,
        POST,
        DELETE
    };

    HttpServletRequest();
    HttpServletRequest(char *);
    Method getMethod(){return GET;}
private:

    char * rawRequest;
};

