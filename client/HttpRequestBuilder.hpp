//
// Created by Admin on 2022-10-31.
//
#pragma once
#ifndef C_WRAPPERS_HTTPREQUESTBUILDER_HPP
#define C_WRAPPERS_HTTPREQUESTBUILDER_HPP

#include <string>

using namespace std;

class HttpRequestBuilder {
public:
    inline static const string VERSION = "HTTP/1.1";
    inline static const string HOST = "localhost:8888";
    inline static const string BOUNDARY = "12345abcde";
    static string buildMultipartRequest(string filePath, string caption, string date);
private:
    static string buildBody(string filePath, string caption, string date);
//    static void buildFile(string bodyBuilder, string filePath);
//    static void buildContentType(string bodyBuilder, string filePath);
};


#endif //C_WRAPPERS_HTTPREQUESTBUILDER_HPP
