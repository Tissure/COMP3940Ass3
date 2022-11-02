//
// Created by Admin on 2022-10-31.
//

#pragma once
#ifndef C_WRAPPERS_HTTPSERVLETRESQUEST_HPP
#define C_WRAPPERS_HTTPSERVLETRESQUEST_HPP


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


#endif //C_WRAPPERS_HTTPSERVLETRESQUEST_HPP
