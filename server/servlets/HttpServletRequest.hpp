//
// Created by Admin on 2022-10-31.
//

#pragma once
#ifndef C_WRAPPERS_HTTPSERVLETRESQUEST_HPP
#define C_WRAPPERS_HTTPSERVLETRESQUEST_HPP

#define MAX_REQUEST_SIZE 1024
#define ASCII_TABLE_LENGTH 127
#define METHOD_ORDER 0
#define URL_ORDER 1
#define CARIGE '\r'
#define NEW_LINE '\n'
#define HEAD_BOUNDRY "\n\r"
#define HEADER_BOUNDRY "\n\r\n\r"
#define CT "Content-Type"
#define CT_MULTI_PART_FORM_DATA "multipart/form-data"

#include <map>
#include <string>
#include <iostream>
#include <cstring>

#include "../sockets/Socket.h"

using namespace std;

class HttpServletRequest
{
public:
    enum Method
    {
        GET,
        POST,
        DELETE
    };

    HttpServletRequest(){};

    /**
     * Parses response.
     */
    HttpServletRequest(Socket *socket) : socket(socket){};

    HttpServletRequest::Method getMethod() { return this->method; }
    HttpServletRequest::Method stringToMethod(string method);

    /**
     * Access map and returns copy
     * @return
     */
    char *getAttribute();
    Socket *getSocket() { return socket; };
    void setSocket(Socket *socket) { this->socket = socket; }
    void parse() { this->parseRequest(); }

private:
    Socket *socket;
    int body = MAX_REQUEST_SIZE;

    // Head
    Method method;
    string version;
    string url;

    // Headers
    map<string, string> headersMap;

    // Body
    map<string, string> bodyMap;

    // multipart/form-data bounrdry
    string boundry;

    /**
     * Parses request
     * @author Ravinder Shokar
     * @param request
     * @return char *
     */
    void
    parseRequest();
    void parseHead();
    void parseHeaders();
    void parseBody();

    /**
     * Returns true is pattern is found at the end of str
     */
    bool isMatch(string str, string pattern);

    /**
     * This will create a string of character up to the delimiter
     * from the classes socket.
     */
    string getNext(string delim);

    /**
     * This will create a string of character up to the delimiter.
     */
    string getNext(char *str, int size, string pattern, int *cursor);

    /**
     * Returns true if key is an edge case.
     */
    bool headerEdgeCases(string key, string value);

    /**
     * Appends key, value to headerMap
     */
    void appendHeader(string key, string value);

    /**
     * F**g overloaded operator
     */
    friend ostream &operator<<(ostream &os, const HttpServletRequest &request);
};

#endif // C_WRAPPERS_HTTPSERVLETRESQUEST_HPP
