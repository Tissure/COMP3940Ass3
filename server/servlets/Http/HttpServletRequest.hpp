//
// Created by Admin on 2022-10-31.
//

#pragma once
#ifndef C_WRAPPERS_HTTPSERVLETRESQUEST_HPP
#define C_WRAPPERS_HTTPSERVLETRESQUEST_HPP

#define MAX_REQUEST_SIZE 1024;
#include <map>
#include <string>
#include <iostream>

using namespace std;

class HttpServletRequest {
public:
    enum Method{GET,POST,DELETE};

    HttpServletRequest();

    /**
     * Parses response.
     */
    HttpServletRequest(char * request): raw(request) { parseRequest(); };

    Method getMethod(){return this->method;}

    /**
     * Access map and returns copy
     * @return
     */
    char * getAttribute();
    char * getRawRequest() { return raw; };
    void setRawRequest(char * request) {this->raw = request; }
    void parse() { this->parseRequest(); }

private:
    char * raw;
    int head;
    int headers;
    int body = MAX_REQUEST_SIZE;

    // Head
    Method method;
    string version;
    string url;

    // Headers
    map<string, string> headersMap;

    // Body
    map<string, string> bodyMap;

    /**
    * Parses request
    * @author Ravinder Shokar
    * @param request
    * @return char *
    */
    void parseRequest();
    void parseHead();
    void parseHeaders();
    void parseBody();
};


#endif //C_WRAPPERS_HTTPSERVLETRESQUEST_HPP

