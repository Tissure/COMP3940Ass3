//
// Created by Admin on 2022-10-31.
//
#pragma once


#include <ostream>
#include <string>
#include <map>
#include <cstring>

using namespace std;

class HttpServletResponse {
private:
    static string VERSION;
    string status;
    string statusPhrase;

    map<string, string> headers;

    string responseStr;
    string *bodyStr;

    void buildResponse();

public:
    HttpServletResponse();
    ~HttpServletResponse();

    void addHeader(const string& key, const string& val) {
        headers.insert(make_pair(key, val));
    }
    void setContentLength(int contentLength) {
        headers.insert(make_pair("Content-Length", to_string(contentLength)));
    }
    void setContentType(string type) {
        headers.insert(make_pair("Content-Type", type));
    }
    void setStatus(int newStatus) {
        status = to_string(newStatus);
    }
    void setStatusPhrase(string newStatusPhrase) {
        statusPhrase = newStatusPhrase;
    }
    string* getWriter() {
        return bodyStr;
    }

    string getResponse();

};
