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
#define LINE "\r\n"
#define BOUNDRY "\r\n\r\n"
#define CT "Content-Type"
#define CT_MULTI_PART_FORM_DATA "multipart/form-data"
#define CD "Content-Disposition:"

#include <map>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>

#include "../sockets/Socket.h"

using namespace std;

class HttpRequestParser
{
public:
    enum Method
    {
        GET,
        POST,
        DELETE
    };

    HttpRequestParser(){};

    /**
     * Parses response.
     */
    HttpRequestParser(Socket *socket) : socket(socket){};

    HttpRequestParser::Method getMethod() { return this->method; }
    HttpRequestParser::Method stringToMethod(string method);

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

    // Head
    Method method;
    string version;
    string url;

    // Headers
    map<string, string> headersMap;

    // Body
    std::vector<char> body;

    // If is form type
    map<string, string> bodyMap;

    // multipart/form-data bounrdry
    string boundry;

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
    void parseMultiPart();
    void parseMultiPartMetaData(string str, std::map<string, string> &map);

    /**
     * Returns true is pattern is found at the end of str
     */
    bool isMatch(string str, string pattern);

    /**
     * Returns true is pattern is in string
     */
    bool hasPattern(string str, string patter);

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

    void trim(string &str, char pattern);
    void trim(string &str);

    void parseContentDisposition(string line);

    void streamIntoFile(string fileName);

    /**
     * F**g overloaded operator
     */
    friend ostream &operator<<(ostream &os, const HttpRequestParser &request);
};

#endif // C_WRAPPERS_HTTPSERVLETRESQUEST_HPP
