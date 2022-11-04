//
// Created by Admin on 2022-10-31.
//

#include "HttpServletResponse.hpp"

#include <iostream>

string HttpServletResponse::VERSION = "HTTP/1.1";

HttpServletResponse::HttpServletResponse() : status("200"), statusPhrase("OK") {
    bodyStr = new string;
}

HttpServletResponse::~HttpServletResponse() {
    delete bodyStr;
}

void HttpServletResponse::buildResponse() {
    // build the response line
    responseStr.append(VERSION).append(" ").append(status).append(" ").append(statusPhrase)
        .append("\r\n");

    // build the response headers
    for (pair<string, string> header : headers) {
        responseStr.append(header.first).append(": ").append(header.second).append("\r\n");
    }

    // separate body from headers
    responseStr.append("\r\n");

    // append the body
    responseStr.append(*bodyStr);
}