//
// Created by Admin on 2022-10-31.
//

#include <string>
#include "HttpRequestBuilder.hpp"

using namespace std;

string HttpRequestBuilder::buildMultipartRequest(string filePath, string caption, string date) {
    // build the body before hand so we can get the content length
    string bodyBuilder = buildBody(filePath, caption, date);

    string bodyLength = to_string(bodyBuilder.length());

    string reqBuilder =
            "POST / " +  HttpRequestBuilder::VERSION + "\r\n"
            + "User-Agent: " + "CLI" + "\r\n"
            + "Accept: "+"*/*"+"\r\n"
            + "Host: " +  HttpRequestBuilder::HOST + "\r\n"
            + "Accept-Encoding: gzip, deflate, br" + "\r\n"
            + "Connection: " + "keep-alive" + "\r\n"
            + "Content-Type: " + "multipart/form-data; boundary=" +  HttpRequestBuilder::BOUNDARY + "\r\n"
            + "Content-Length: " + bodyLength + "\r\n"
            + "\r\n"
            + bodyBuilder;
            // request line

    return reqBuilder;
}

string HttpRequestBuilder::buildBody(string filePath, string caption, string date) {
    return "test bitch";
}