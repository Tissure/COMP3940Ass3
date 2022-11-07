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

class HttpResponseParser
{
public:
    enum Method
    {
        GET,
        POST,
        DELETE
    };

    HttpResponseParser(){};

    /**
     * Parses response.
     */
    HttpResponseParser(char * res) : res(res){};

    HttpResponseParser::Method getMethod() { return this->method; }
    HttpResponseParser::Method stringToMethod(string method);

    /**
     * Access map and returns copy
     * @return
     */
    char *getAttribute();
    char *getSocket() { return res; };
    void setSocket(char *res) { this->res = res; }
    vector<char> getBody() { return this->body;}
    void parse() { this->parseResponse(); }

private:
    char *res;

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
    void parseResponse();
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
    friend ostream &operator<<(ostream &os, const HttpResponseParser &response);
};

#endif // C_WRAPPERS_HTTPSERVLETRESQUEST_HPP
